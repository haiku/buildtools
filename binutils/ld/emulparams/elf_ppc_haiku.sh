SCRIPT_NAME=elf
OUTPUT_FORMAT="elf32-powerpc"
TEXT_START_ADDR=0x200000
NONPAGED_TEXT_START_ADDR=0x200000
MAXPAGESIZE=0x1000
ARCH=powerpc
MACHINE=
NOP=0x60000000
TEMPLATE_NAME=elf32
GENERATE_SHLIB_SCRIPT=yes
BSS_PLT=
OTHER_RELRO_SECTIONS="
  .fixup        ${RELOCATING-0} : { *(.fixup) }
  .got1         ${RELOCATING-0} : { *(.got1) }
  .got2         ${RELOCATING-0} : { *(.got2) }
"
OTHER_GOT_RELOC_SECTIONS="
  .rela.got1         ${RELOCATING-0} : { *(.rela.got1) }
  .rela.got2         ${RELOCATING-0} : { *(.rela.got2) }
"
