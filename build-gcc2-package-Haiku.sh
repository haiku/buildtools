#!/bin/sh
# Builds a GCC package from the installation specified by $GCCDATE (or via the
# arguments).
# Usage: build-gcc2-package-Haiku.sh [gcc-base-dir] [version]

packages_build=/boot/common/packages/build

if [ -d "$1" ]; then
	gcc_base=$1
	shift
fi
if [ "$(basename $(pwd))" = "buildtools" ]; then
	gcc_base=$(pwd)/legacy/gcc-obj
	echo "No exact GCC build directory given, assuming \"$gcc_base\""
	echo "  (only needed for the HTML documentation)."
fi

if [ "$1" == "" ]; then
	if [ "$GCCDATE" = "" ]; then
		echo "No GCC date version given!"
		echo "Either export GCCDATE, or pass the date as argument to this" \
			"script."
		echo "The date is given in the format 'yymmdd', ie. '100818'."
		exit
	fi
else
	GCCDATE=$1
fi

current_dir=$(pwd)
base=/boot/common/develop/tools/gcc-2.95.3-$GCCDATE
if [ ! -d "$base" ]; then
	echo GCC directory \"$base\" does not exist!
	exit
fi

### HTML documentation ####################################

html_base=$base/html-docs
if [ ! -d "$html_base" ]; then
	if [ "$gcc_base" = "" ]; then
		echo "No GCC build directory given, cannot build HTML documenation."
		exit
	fi

	echo "Building HTML documentation..."
	mkdir $html_base
	cd $html_base

	makeinfo --html $gcc_base/../gcc/gcc/cpp.texi
	makeinfo --html $gcc_base/../gcc/gcc/gcc.texi
	makeinfo --html $gcc_base/../binutils/libiberty/libiberty.texi
	makeinfo --force --html $gcc_base/../gcc/libio/iostream.texi

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

cd ${packages_build}
ver=2.95.3_${GCCDATE}
rev=1
while [ -e gcc-2.95.3_${GCCDATE}-$rev ]; do
	rev=$(expr $rev + 1);
done
version=$ver-$rev
echo "Version: $version"

mkdir -p gcc-$version/develop/tools
cp -r $base gcc-$version/develop/tools/
cd gcc-$version
cat >.PackageInfo <<ENDOFHERE
	name = gcc
	version = $version
	architecture = x86_gcc2
	summary = "c/c++ compiler"
	description = "standard compiler for x86_gcc2 platform, ABI-compatible with BeOS R5"
	packager = "Oliver Tappe <zooey@hirschkaefer.de>"
	vendor = "Haiku Project"
	copyrights = [ "1988-2000 Free Software Foundation, Inc." ]
	licenses = [ "GNU GPL v2", "GNU LGPL v2" ]
	provides = [
		gcc = $ver,
		binutils = 2.17_$GCCDATE
	]
	requires = [
		haiku >= r40675,
		package_management_branch,
		cpp-headers == 2.95.3
	]
ENDOFHERE

mimeset -F .
package create ../gcc-$version.hpkg
cd $current_dir
