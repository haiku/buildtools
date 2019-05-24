#define HAIKU_TARGET_OS_CPP_BUILTINS()							\
  do															\
    {															\
	builtin_define ("__HAIKU__");								\
	builtin_define ("__stdcall=__attribute__((__stdcall__))");	\
    builtin_define ("__cdecl=__attribute__((__cdecl__))");		\
    builtin_assert ("system=haiku");							\
	/* Haiku apparently doesn't support merging of symbols across shared \
	 object boundaries. Hence we need to explicitly specify that \
	 type_infos are not merged, so that they get compared by name \
	 instead of by pointer. */ 									\
	builtin_define ("__GXX_MERGED_TYPEINFO_NAMES=0"); 			\
	HAIKU_TARGET_CPU_CPP_BUILTINS();							\
    }															\
  while (0)

/* Define the default Haiku-specific per-CPU hook code.  */
#define HAIKU_TARGET_CPU_CPP_BUILTINS() do {} while (0)

/* Provide a CPP_SPEC appropriate for Haiku.  We just deal with the GCC 
   option `-posix', and PIC issues.  */

#define HAIKU_CPP_SPEC "					\
  %(cpp_cpu)								\
  %(cpp_arch)								\
  %{posix:-D_POSIX_SOURCE}"

#define HAIKU_STARTFILE_SPEC 				\
  "crti.o%s crtbeginS.o%s %{!shared:%{!nostart:start_dyn.o%s}} init_term_dyn.o%s"

#define HAIKU_ENDFILE_SPEC 					\
  "crtendS.o%s crtn.o%s"

#define HAIKU_LIB_SPEC 						\
  "-lroot"

#define HAIKU_DYNAMIC_LINKER				\
  "/system/runtime_loader"
