#! /bin/sh

BINUTILS=binutils
GCC=gcc

echo generation html-docs for as...
ln -sf ../../$BINUTILS/gas/doc/all.texi asconfig.texi
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=as ../../$BINUTILS/gas/doc/as.texinfo
ln -sf as/index.html as.html

echo generation html-docs for as...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=as-internals ../../$BINUTILS/gas/doc/internals.texi
ln -sf as-internals/index.html as-internals.html

echo generation html-docs for bfd...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=bfd ../../$BINUTILS/bfd/doc/bfd.texinfo
ln -sf bfd/index.html bfd.html

echo generation html-docs for bfdint...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=bfd-internals ../../$BINUTILS/bfd/doc/bfdint.texi
ln -sf bfd-internals/index.html bfd-internals.html

echo generation html-docs for binutils...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=binutils -I ../../$BINUTILS-obj/binutils/doc ../../$BINUTILS/binutils/doc/binutils.texi
ln -sf binutils/index.html binutils.html

echo generation html-docs for configure...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=configure ../../$BINUTILS/etc/configure.texi
ln -sf configure/index.html configure.html

echo generation html-docs for cpp...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=cpp ../../$GCC/gcc/cpp.texi
ln -sf cpp/index.html cpp.html

echo generation html-docs for gcc...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=gcc ../../$GCC/gcc/gcc.texi
ln -sf gcc/index.html gcc.html

echo generation html-docs for g++int...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=g++-internals ../../$GCC/gcc/cp/gxxint.texi
ln -sf g++-internals/index.html g++-internals.html

echo generation html-docs for gprof...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=gprof ../../$BINUTILS/gprof/gprof.texi
ln -sf gprof/index.html gprof.html

echo generation html-docs for iostream...
texi2html -split=section -nonumber -top_file=index.html -toc_file=toc.html -subdir=iostream ../../$GCC/libio/iostream.texi
ln -sf iostream/index.html iostream.html

echo generation html-docs for ld...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=ld -I ../../$BINUTILS/bfd/doc ../../$BINUTILS/ld/ld.texinfo
ln -sf ld/index.html ld.html

echo generation html-docs for ldint...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=ld-internals ../../$BINUTILS/ld/ldint.texinfo
ln -sf ld-internals/index.html ld-internals.html

echo generation html-docs for libiberty...
texi2html -split=section -top_file=index.html -toc_file=toc.html -subdir=libiberty ../../$BINUTILS/libiberty/libiberty.texi
ln -sf libiberty/index.html libiberty.html
