#!/bin/sh

# Builds a GCC package from the sources.
#
# Usage: build-gcc2-package-Haiku.sh <version date> <release>
#   <version date> must be version date string formatted YYMMDD.
#   <release> must be a number between 1 and 99.

# get version date and release parameters
if [ $# -ne 2 ]; then
	echo "Usage: $0 <version date YYMMDD> <release>" >&2
	exit 1
fi

export GCCDATE=$1
release=$2

# get current dir and buildtools dir
currentDir="$(pwd)/build-gcc-package"
rm -rf "$currentDir"
mkdir "$currentDir"
cd "$(dirname $0)"
buildtoolsDir="$(pwd)/legacy"
cd "$currentDir"

# prepare an install dir with a .PackageInfo
installDir="$currentDir/install"
rm -rf "$installDir"
mkdir "$installDir"

version=2.95.3_${GCCDATE}

packageInfoFile="package-info"

cat > "$packageInfoFile" << ENDOFHERE
	name			gcc
	version			$version-$release
	architecture	x86_gcc2
	summary			"c/c++ compiler"
	description		"standard compiler for x86_gcc2 platform, ABI-compatible with BeOS R5"
	packager		"Oliver Tappe <zooey@hirschkaefer.de>"
	vendor			"Haiku Project"
	copyrights		"1988-2000 Free Software Foundation, Inc."
	licenses {
		"GNU GPL v2"
		"GNU LGPL v2"
	}
	provides {
		gcc = $version compat >= 2.95.3
		binutils = 2.17_$GCCDATE compat >= 2.17
	}
	requires {
		haiku >= r1-alpha3
		haiku-devel >= r1-alpha3
	}
ENDOFHERE

# create a build package
versionedPackageName=gcc-$version-$release
packageFileName="$versionedPackageName-x86_gcc2.hpkg"
packageFile="$currentDir/$packageFileName"

echo "Creating build package..."
package create -b -I "$installDir" -i "$packageInfoFile" $packageFile ||
	exit 1

# activate the package
rm -f /boot/common/packages/$packageFileName
ln -s "$packageFile" /boot/common/packages

finalInstallDir="/packages/$versionedPackageName/.self"

sleep 1

if [ ! -e "$finalInstallDir" ]; then
	echo "Activating the build package failed!"
	exit 1
fi

gccInstallDir="$finalInstallDir/develop/tools/gcc-2.95.3-${GCCDATE}"
mkdir -p "$gccInstallDir"

# build binutils
mkdir binutils-obj
cd binutils-obj
CFLAGS="-O2" CXXFLAGS="-O2" "$buildtoolsDir/binutils/configure" \
	--prefix=$gccInstallDir \
	--disable-nls --enable-shared=yes || exit 1
make || exit 1
make install || exit 1
cd ..

# build gcc
mkdir gcc-obj
cd gcc-obj
CFLAGS="-O2" CXXFLAGS="-O2" "$buildtoolsDir/gcc/configure" \
	--prefix=$gccInstallDir \
	--disable-nls --enable-shared=yes --enable-languages=c,c++ || exit 1
make bootstrap
	# the above will fail when compiling builtinbuf.cc, but we can ignore that
	# since it's trying to build libstdc++.so, which haiku provides anyway
make install || exit 1
cd ..


base=$gccInstallDir

### HTML documentation ####################################

html_base=$base/html-docs
if [ ! -d "$html_base" ]; then
	echo "Building HTML documentation..."
	mkdir $html_base
	cd $html_base

	makeinfo --html "$buildtoolsDir/gcc/gcc/cpp.texi"
	makeinfo --html "$buildtoolsDir/gcc/gcc/gcc.texi"
	makeinfo --html "$buildtoolsDir/binutils/libiberty/libiberty.texi"
	makeinfo --force --html "$buildtoolsDir/gcc/libio/iostream.texi"

	ln -sf cpp/index.html $html_base/cpp.html
	ln -sf gcc/index.html $html_base/gcc.html
	ln -sf libiberty/index.html $html_base/libiberty.html
	ln -sf iostream/index.html $html_base/iostream.html
fi
if [ -d "$base/share/doc" ]; then
	echo "Adding binutils HTML documentation..."

	mv $base/share/doc/as.html $html_base/as
	mv $base/share/doc/binutils.html $html_base/binutils
	mv $base/share/doc/gprof.html $html_base/gprof
	mv $base/share/doc/ld.html $html_base/ld
	#mv $base/share/doc/configure.html $html_base/

	ln -sf as/index.html $html_base/as.html
	ln -sf binutils/index.html $html_base/binutils.html
	ln -sf gprof/index.html $html_base/gprof.html
	ln -sf ld/index.html $html_base/ld.html
fi
if [ ! -e "$html_base/as.html" ]; then
	echo "binutils HTML documentation missing, see" \
		"INSTALL-gcc2-from-source-Haiku."
fi

### Cleanup ###############################################

echo "Cleanup"

cd $base/bin
for binary in ../i586-pc-haiku/bin/*; do
	ln -sfn $binary .
done

if [ -d $base/man -o -d $base/info -o -d $base/share ]; then
	rm -rf $base/man
	rm -rf $base/info
	rm -rf $base/share
fi

rm -f $base/lib/gcc-lib/i586-pc-haiku/2.95.3-haiku-$GCCDATE/include/math.h

### C++ includes ######################################

echo "Install C++ includes & library"

rm -rf $base/include/g++
ln -snf /boot/system/develop/headers/c++/2.95.3 $base/include/g++

ln -snf /boot/system/lib/libstdc++.r4.so $base/lib/
ln -snf /boot/system/lib/libstdc++.so $base/lib/

### package ###########################################

echo "Building package ..."

cd "$currentDir"
mimeset -F "$installDir"
package create -C "$installDir" -i "$packageInfoFile" $packageFile || exit 1

echo "Built package $packageInfoFile successfully."
