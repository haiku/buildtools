SHLIB	= libstdc++.r4.so
LIBS	= $(ARLIB) $(ARLINK) $(SHLIB)
DEPLIBS	= ../$(SHLIB)
SHFLAGS	= -Wl,-soname,$(SHLIB)
SHOPT	= -nostart
