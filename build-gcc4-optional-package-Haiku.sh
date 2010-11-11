#!/bin/sh
#
# Builds an GCC (optional) package from the sources.

usage()
{
	echo "Usage: $0 [ <options> ] <gcc date>"
}


# get the relevant directories
currentDir=`pwd`
cd `dirname "$0"`
buildtoolsDir=`pwd`
cd "$currentDir"

binutilsSources="$buildtoolsDir/binutils"
gccSources="$buildtoolsDir/gcc"

buildDir="$currentDir/gcc-objects"
binutilsBuildDir="$buildDir/binutils"
gccBuildDir="$buildDir/gcc"


# parse the arguments
jobArgs=
while [ $# -gt 0 ]; do
	case "$1" in
		-h|--help)	usage; exit 0;;
		-j*)		jobArgs="$1"; shift 1;;
		*)			break;;
	esac
done

# get the GCC date
if [ $# -ne 1 ]; then
	usage >&2
	exit 1
fi

gccDate=$1

case "$gccDate" in
	[0-9][0-9][0-9][0-9][0-9][0-9])	true;;
	*)	echo "Invalid GCC date string '$gccDate'." >&2; exit 1;;
esac



# get the GCC version
gccVersion=`cat $gccSources/gcc/BASE-VER`
if [ -z "$gccVersion" ]; then
	echo "Failed to get GCC version." >&2
	exit 1
fi


# get the architecture
gccArch=`uname -m`
case $gccArch in
	BePC)	gccArch=x86;;
	*)		echo "Unsupported architecture: '$gccArch'" >&2; exit 1;;
esac


# check whether the installation dir does already exit
installDir=/boot/develop/abi/$gccArch/gcc4/tools/gcc-${gccVersion}-haiku-${gccDate}
if [ -e "$installDir" ]; then
	echo "The installation directory '$installDir' does already exist." >&2
	echo "Remove it first." >&2
	exit 1
fi


# print some info before we start the action
echo "Building binutils and gcc optional packages from the source."
echo "sources:     $buildtoolsDir"
echo "build dir:   $buildDir"
echo "GCC date:    $gccDate"
echo "GCC version: $gccVersion"
echo "install dir: $installDir"
echo
echo "This is going to take a while ..."
sleep 3


# From now on fail, if anything goes wrong.
set -o errexit


# remove and recreate the build directories
rm -rf "$buildDir"
mkdir -p "$binutilsBuildDir" "$gccBuildDir"


# build and install the binutils
cd "$binutilsBuildDir"
CFLAGS="-O2" CXXFLAGS="-O2" "$binutilsSources/configure" \
	--prefix="$installDir" --disable-nls --enable-shared=yes \
	--with-htmldir=html-docs
make $jobArgs
make install install-html


# build and install gcc
cd "$gccBuildDir"
CFLAGS="-O2" CXXFLAGS="-O2" "$gccSources/configure" \
	--prefix="$installDir" --enable-shared --enable-languages=c,c++ \
	--disable-nls --without-libiconv-prefix --disable-libstdcxx-pch \
	--with-htmldir=html-docs
make $jobArgs bootstrap
make install install-html


# remove installed stuff we don't want
rm -rf "$installDir/info" "$installDir/man" "$installDir/share" \
	"$installDir/lib/libstdc++.so"


# zip everything up
gccVersionYear=20$(echo $GCCDATE | cut -c1-2)
gccVersionMonth=$(echo $GCCDATE | cut -c3-4)
gccVersionDay=$(echo $GCCDATE | cut -c5-6)
packageFile="$currentDir/gcc-${gccVersion}-${gccArch}-gcc4-${gccVersionYear}-${gccVersionMonth}-${gccVersionDay}.zip"

cd /boot
zip -ry "$packageFile" `echo $installDir | cut -d/ -f3-`


# add the optional package description
cd "$buildDir"
echo "Package:		GCC
Version:		${gccVersion}-haiku-${gccDate}
Copyright:		1988-2010 Free Software Foundation, Inc.
License:		GNU GPL v3
License:		GNU LGPL v3
URL:			http://www.gnu.org/software/gcc/
" > .OptionalPackageDescription

zip "$packageFile" .OptionalPackageDescription


# clean up
cd "$currentDir"
rm -rf "$buildDir"
