# this script prepares the /boot/develop/tools/gnupro-folder for distribution
#
GCC_VER=`gcc --version`
FULL_VER=gcc-2.95.3_binutils-2.15
# strip executables
strip --strip-unneeded /boot/develop/tools/gnupro/bin/*
strip --strip-unneeded /boot/develop/tools/gnupro/i586-pc-beos/bin/*
strip --strip-unneeded /boot/develop/tools/gnupro/lib/*
strip --strip-unneeded /boot/develop/tools/gnupro/lib/gcc-lib/i586-pc-beos/$GCC_VER/*
# remove info- and man-docs, install html-docs
rm -rf /boot/develop/tools/gnupro/info
rm -rf /boot/develop/tools/gnupro/man
rm -rf /boot/develop/tools/gnupro/html-docs
cp -a html-docs /boot/develop/tools/gnupro
rm /boot/develop/tools/gnupro/html-docs/asconfig.texi
rm /boot/develop/tools/gnupro/html-docs/create-docs.sh
# remove locale files
rm -rf /boot/develop/tools/gnupro/share
# install separate specs-files for R5 and Dano, use Dano by default
sed "s/-lroot/-lroot -lnet/" /boot/develop/tools/gnupro/lib/gcc-lib/i586-pc-beos/$GCC_VER/specs >/boot/develop/tools/gnupro/lib/gcc-lib/i586-pc-beos/$GCC_VER/specs.R5
mv /boot/develop/tools/gnupro/lib/gcc-lib/i586-pc-beos/$GCC_VER/specs /boot/develop/tools/gnupro/lib/gcc-lib/i586-pc-beos/$GCC_VER/specs.Default
ln -sf /boot/develop/tools/gnupro/lib/gcc-lib/i586-pc-beos/$GCC_VER/specs.Default /boot/develop/tools/gnupro/lib/gcc-lib/i586-pc-beos/$GCC_VER/specs
cp -a ../gcc/COPYING* /boot/develop/tools/gnupro/
# install readline lib, headers and html-docs
#strip --strip-unneeded ~/Sources/ports/readline-5.0/lib*.a
#cp -a ~/Sources/ports/readline-5.0/lib*.a /boot/develop/tools/gnupro/lib/
#cp -a /boot/home/config/include/readline /boot/develop/tools/gnupro/include/
#cp -a ~/Sources/ports/readline-5.0/doc/readline.html /boot/develop/tools/gnupro/html-docs/
# identify all files
mimeset /boot/develop/tools/gnupro/
# add sdk-subfolder and create the required links:
rm -rf /boot/develop/tools/sdk_$FULL_VER
mkdir -p /boot/develop/tools/sdk_$FULL_VER
cat >/boot/develop/tools/sdk_$FULL_VER/Readme <<EOF
This folder exists to integrate gcc into the Dano/Zeta layout of the
development-tools. If you want to activate $GCC_VER, just make a link from 
/etc/develop/zeta-r1-gcc2-x86/tools/sdk to this folder.
EOF
mkdir -p /boot/develop/tools/sdk_$FULL_VER/release/H-i586-pc-beos5/T-i586-pc-beos5/i586-pc-beos5
pushd /boot/develop/tools/sdk_$FULL_VER/release/H-i586-pc-beos5/T-i586-pc-beos5/i586-pc-beos5
ln -sf ../../../../../$FULL_VER/i586-pc-beos/lib lib
cd ..
ln -sf ../../../../$FULL_VER/bin bin
ln -sf ../../../../$FULL_VER/lib lib
popd
