#!/bin/sh
# Builds a GCC package from the installation specified by $GCCDATE (or via the
# arguments).
# Usage: build-gcc2-optional-package-Haiku.sh [gcc-base-dir] [version]

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
base=/boot/develop/abi/x86/gcc2/tools/gcc-2.95.3-haiku-$GCCDATE
if [ ! -d "$base" ]; then
	echo GCC directory \"$base\" does not exist, so we start a build ...
	echo "This is going to take a while ..."
	sleep 3

	# From now on fail, if anything goes wrong.
	set -o errexit

	cd $gcc_base/..

	rm -rf binutils-obj
	mkdir binutils-obj
	cd binutils-obj
	CFLAGS="-O2" CXXFLAGS="-O2" ../binutils/configure \
		--prefix=/boot/develop/abi/x86/gcc2/tools/gcc-2.95.3-haiku-${GCCDATE} \
		--disable-nls --enable-shared=yes
	make
	cd ..

	(cd gcc/gcc; touch c-parse.{h,c} cexp.c cp/parse.{c,h} c-gperf.h)

	rm -rf gcc-obj
	mkdir gcc-obj
	cd gcc-obj
	CFLAGS="-O2" CXXFLAGS="-O2" ../gcc/configure \
		--prefix=/boot/develop/abi/x86/gcc2/tools/gcc-2.95.3-haiku-${GCCDATE} \
		--disable-nls --enable-shared=yes --enable-languages=c,c++
	# hack the Makefile to avoid trouble with stuff we don't need anyway
	sedExpr=
	for toRemove in libio libjava libobjc libstdc++; do
		sedExpr="$sedExpr -e 's@^\(TARGET_CONFIGDIRS =.*\)$toRemove\(.*\)@\1\2@'"
	done
	echo sedExpr: $sedExpr
	mv Makefile Makefile.bak || exit 1
	eval "sed $sedExpr Makefile.bak > Makefile" || exit 1
	rm Makefile.bak
	# build gcc
	make bootstrap
	cd ..

	mkdir /boot/develop/abi/x86/gcc2/tools/gcc-2.95.3-haiku-${GCCDATE}
	cd binutils-obj
	make install
	cd ..
	cd gcc-obj
	make install
	cd ..
	ln -sfn gcc-2.95.3-haiku-${GCCDATE} /boot/develop/abi/x86/gcc2/tools/current
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

	ln -sf cpp/index.html $html_base/cpp.html
	ln -sf gcc/index.html $html_base/gcc.html
	ln -sf libiberty/index.html $html_base/libiberty.html
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

if [ -d $base/man -o -d $base/info -o -d $base/share ]; then
	echo "Removing legacy files (man/info/share)..."
	rm -rf $base/man
	rm -rf $base/info
	rm -rf $base/share
fi
rm -f $base/lib/gcc-lib/i586-pc-haiku/2.95.3-haiku-$GCCDATE/include/math.h


### C++ includes ######################################

echo "Install C++ includes"

rm -rf $base/include/g++
ln -snf /boot/develop/headers/cpp $base/include/g++


### zip archive ###########################################

echo "Building ZIP archive..."

current_gcc=$(setgcc | cut -d/ -f 2)
version_year=20$(echo $GCCDATE | cut -c1-2)
version_month=$(echo $GCCDATE | cut -c3-4)
version_day=$(echo $GCCDATE | cut -c5-6)
zip_name="$current_dir/gcc-2.95.3-x86-$current_gcc-$version_year-$version_month-$version_day.zip"

cd /boot
zip_base=$(echo $base | cut -d/ -f3-)
rm -f $zip_name
zip -yr $zip_name $zip_base

current_name=develop/abi/x86/gcc2/tools/current
ln -snf gcc-2.95.3-haiku-$GCCDATE $current_name
zip -yr $zip_name $current_name


### optional package description ##########################

echo "Package:		GCC
Version:		2.95.3-haiku-$GCCDATE
Copyright:		1988-2000 Free Software Foundation, Inc.
License:		GNU GPL v2
License:		GNU LGPL v2
URL:			http://www.gnu.org/software/gcc/" > /tmp/.OptionalPackageDescription

cd /tmp
zip -yr $zip_name .OptionalPackageDescription
rm .OptionalPackageDescription
