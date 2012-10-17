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
targetArch=x86
gccMakeTarget=bootstrap
gccConfigureArgs="--enable-shared"
binutilsConfigureArgs="--enable-shared"

# parse the arguments
jobArgs=
while [ $# -gt 0 ]; do
	case "$1" in
		-h|--help)	usage; exit 0;;
		-j*)		jobArgs="$1"; shift 1;;
		--arch)
			case "$2" in
				x86)	HAIKU_GCC_MACHINE=i586-pc-haiku;;
				x86_64)	HAIKU_GCC_MACHINE=x86_64-unknown-haiku; targetArch=x86_64;;
				ppc)	HAIKU_GCC_MACHINE=powerpc-apple-haiku; targetArch=ppc;
						gccMakeTarget= gccConfigureArgs="--disable-shared --disable-multilib"
						binutilsConfigureArgs="--disable-shared --disable-multilib" ;;
				m68k)	HAIKU_GCC_MACHINE=m68k-unknown-haiku; targetArch=m68k;
						gccMakeTarget= gccConfigureArgs="--disable-shared --disable-multilib"
						binutilsConfigureArgs="--disable-shared --disable-multilib" ;;
				arm)	HAIKU_GCC_MACHINE=arm-unknown-haiku; targetArch=arm;
						gccMakeTarget= gccConfigureArgs="--disable-shared --disable-multilib"
						binutilsConfigureArgs="--disable-shared --disable-multilib" ;;
				mipsel)	HAIKU_GCC_MACHINE=mipsel-unknown-haiku; targetArch=mips;
						gccMakeTarget= gccConfigureArgs="--disable-shared --disable-multilib"
						binutilsConfigureArgs="--disable-shared --disable-multilib" ;;
				*)		echo "Unsupported target architecture: $2"
						exit 1;;
			esac
			shift 2
			targetCrossToolsMachine="--target=${HAIKU_GCC_MACHINE}";;
		--source-dir)	haikuSourceDir="$2"; shift 2;;
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

gccVersionedName=gcc-${gccVersion}-haiku-${gccDate}


# check whether the installation dir does already exit
installDir=/boot/develop/abi/$targetArch/gcc4/tools/$gccVersionedName
if [ -e "$installDir" ]; then
	echo "The installation directory '$installDir' does already exist." >&2
	echo "Remove it first." >&2
	exit 1
fi


# print some info before we start the action
echo "Building binutils and gcc optional packages from the source."
echo "sources:     $buildtoolsDir"
echo "build dir:   $buildDir"
echo "target arch: $targetArch"
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
	--prefix="$installDir" $targetCrossToolsMachine --disable-nls \
	$binutilsConfigureArgs --with-htmldir=html-docs
make $jobArgs
make install install-html

# prepare the include files
copy_headers()
{
	sourceDir=$1
	targetDir=$2

	headers="$(find $sourceDir -name \*\.h | grep -v /.svn)"
	headers="$(echo $headers | sed -e s@$sourceDir/@@g)"
	for f in $headers; do
		headerTargetDir=$targetDir/$(dirname $f)
		mkdir -p $headerTargetDir
		cp $sourceDir/$f $headerTargetDir
	done
}

if [ -n "$haikuSourceDir" ]; then
	tmpIncludeDir=$currentDir/sysincludes
	tmpLibDir=$currentDir/syslibs
	mkdir -p $tmpIncludeDir $tmpLibDir
	copy_headers $haikuSourceDir/headers/config $tmpIncludeDir/config
	copy_headers $haikuSourceDir/headers/os $tmpIncludeDir/os
	copy_headers $haikuSourceDir/headers/posix $tmpIncludeDir/posix
	headersLibsArgs="--with-headers=$tmpIncludeDir --with-libs=$tmpLibDir"
fi

# build and install gcc
cd "$gccBuildDir"
CFLAGS="-O2" CXXFLAGS="-O2" "$gccSources/configure" \
	--prefix="$installDir" $gccConfigureArgs --enable-languages=c,c++ \
	$targetCrossToolsMachine --disable-nls --without-libiconv-prefix \
	--disable-libstdcxx-pch --with-htmldir=html-docs --enable-lto \
	--enable-frame-pointer $headersLibsArgs
make $jobArgs $gccMakeTarget
make install-strip install-html


# remove installed stuff we don't want
rm -rf "$installDir/info" "$installDir/man" "$installDir/share" \
	"$installDir/lib/libstdc++.so"


# strip the executables of debug info (somewhat crude heuristics to identify
# actual executables: files >= 20 kiB with execute permission and not in a "lib"
# directory)
strip --strip-debug \
	`find "$installDir" -type f -a -perm -u=x -a -size +20k | grep -v /lib/`


# add C++ header symlink
ln -s c++/$gccVersion $installDir/include/g++


# zip everything up
gccVersionYear=20$(echo $gccDate | cut -c1-2)
gccVersionMonth=$(echo $gccDate | cut -c3-4)
gccVersionDay=$(echo $gccDate | cut -c5-6)
packageFile="$currentDir/gcc-${gccVersion}-${targetArch}-gcc4-${gccVersionYear}-${gccVersionMonth}-${gccVersionDay}.zip"

cd /boot
zip -ry "$packageFile" `echo $installDir | cut -d/ -f3-`


# add the "current" version symlink
cd "$buildDir"
mkdir -p develop/abi/$targetArch/gcc4/tools/
ln -s $gccVersionedName develop/abi/$targetArch/gcc4/tools/current
zip -y "$packageFile" develop/abi/$targetArch/gcc4/tools/current


# add the optional package description
cd "$buildDir"
echo "Package:		GCC
Version:		${gccVersion}-${targetArch}-haiku-${gccDate}
Copyright:		1988-2012 Free Software Foundation, Inc.
License:		GNU GPL v3
License:		GNU LGPL v3
URL:			http://www.gnu.org/software/gcc/
" > .OptionalPackageDescription

zip "$packageFile" .OptionalPackageDescription


# clean up
cd "$currentDir"
rm -rf "$buildDir"
