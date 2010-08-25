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

base=/boot/develop/abi/x86/gcc2/tools/gcc-2.95.3-haiku-$GCCDATE
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
	makeinfo --html $gcc_base/../binutils/libiberty/libiberty.texi
	makeinfo --force --html $gcc_base/../gcc/libio/iostream.texi

	ln -sf cpp/index.html $html_base/cpp.html
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

if [ -d $base/man -o -d $base/info -o -d $base/share ]; then
	echo "Removing legacy documentation (man/info/share)..."
	rm -rf $base/man
	rm -rf $base/info
	rm -rf $base/share
fi


### C++ includes/lib ######################################

echo "Install C++ includes and library"

rm -rf $base/include/g++
ln -snf /boot/develop/headers/cpp $base/include/g++
ln -sf /system/lib/libstdc++.r4.so $base/lib/


### zip archive ###########################################

echo "Building ZIP archive..."

current_dir=$(pwd)
current_gcc=$(setgcc | cut -d/ -f 2)
version_year=20$(echo $GCCDATE | cut -c1-2)
version_month=$(echo $GCCDATE | cut -c3-4)
version_day=$(echo $GCCDATE | cut -c5-6)
zip_name="$current_dir/gcc-2.95.3-x86-$current_gcc-$version_year-$version_month-$version_day.zip"

cd /boot
rm -f $zip_name
zip -yr $zip_name $base

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
