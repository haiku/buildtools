/* DWARF2 EH unwinding support for FreeBSD/ARM64 (aarch64).
   Copyright (C) 2017-2018 Free Software Foundation, Inc.
   Contributed by John Marino <gnugcc@marino.st>

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/* Identify a signal frame, and set the frame state data appropriately.
   See unwind-dw2.c for the structs. */

/* Always include AArch64 unwinder header file.  */
#include "config/aarch64/aarch64-unwind.h"

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>

#define REG_NAME(reg)   mc_gpregs.gp_## reg
#define XREG(num)       mc_gpregs.gp_x[num]
#define DARC            __LIBGCC_DWARF_ALT_FRAME_RETURN_COLUMN__

#define MD_FALLBACK_FRAME_STATE_FOR aarch64_haiku_fallback_frame_state

static _Unwind_Reason_Code
aarch64_haiku_fallback_frame_state
(struct _Unwind_Context *context, _Unwind_FrameState *fs)
{
  // For now just signal end of stack. Once the Haiku implementation
  // for AArch64 is more mature we can consider writing something similar
  // to Linux or FreeBSD support.
  return _URC_END_OF_STACK;
}
