/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 22 "ldgram.y"

/*

 */

#define DONTDECLARE_MALLOC

#include "sysdep.h"
#include "bfd.h"
#include "bfdlink.h"
#include "ctf-api.h"
#include "ld.h"
#include "ldexp.h"
#include "ldver.h"
#include "ldlang.h"
#include "ldfile.h"
#include "ldemul.h"
#include "ldmisc.h"
#include "ldmain.h"
#include "mri.h"
#include "ldctor.h"
#include "ldlex.h"

#ifndef YYDEBUG
#define YYDEBUG 1
#endif

static enum section_type sectype;
static etree_type *sectype_value;
static lang_memory_region_type *region;

static bool ldgram_had_keep = false;
static char *ldgram_vers_current_lang = NULL;

#define ERROR_NAME_MAX 20
static char *error_names[ERROR_NAME_MAX];
static int error_index;
#define PUSH_ERROR(x) if (error_index < ERROR_NAME_MAX) error_names[error_index] = x; error_index++;
#define POP_ERROR()   error_index--;

#line 112 "ldgram.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_LDGRAM_H_INCLUDED
# define YY_YY_LDGRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    NAME = 259,                    /* NAME  */
    LNAME = 260,                   /* LNAME  */
    PLUSEQ = 261,                  /* PLUSEQ  */
    MINUSEQ = 262,                 /* MINUSEQ  */
    MULTEQ = 263,                  /* MULTEQ  */
    DIVEQ = 264,                   /* DIVEQ  */
    LSHIFTEQ = 265,                /* LSHIFTEQ  */
    RSHIFTEQ = 266,                /* RSHIFTEQ  */
    ANDEQ = 267,                   /* ANDEQ  */
    OREQ = 268,                    /* OREQ  */
    OROR = 269,                    /* OROR  */
    ANDAND = 270,                  /* ANDAND  */
    EQ = 271,                      /* EQ  */
    NE = 272,                      /* NE  */
    LE = 273,                      /* LE  */
    GE = 274,                      /* GE  */
    LSHIFT = 275,                  /* LSHIFT  */
    RSHIFT = 276,                  /* RSHIFT  */
    UNARY = 277,                   /* UNARY  */
    END = 278,                     /* END  */
    ALIGN_K = 279,                 /* ALIGN_K  */
    BLOCK = 280,                   /* BLOCK  */
    BIND = 281,                    /* BIND  */
    QUAD = 282,                    /* QUAD  */
    SQUAD = 283,                   /* SQUAD  */
    LONG = 284,                    /* LONG  */
    SHORT = 285,                   /* SHORT  */
    BYTE = 286,                    /* BYTE  */
    ASCIZ = 287,                   /* ASCIZ  */
    SECTIONS = 288,                /* SECTIONS  */
    PHDRS = 289,                   /* PHDRS  */
    INSERT_K = 290,                /* INSERT_K  */
    AFTER = 291,                   /* AFTER  */
    BEFORE = 292,                  /* BEFORE  */
    LINKER_VERSION = 293,          /* LINKER_VERSION  */
    DATA_SEGMENT_ALIGN = 294,      /* DATA_SEGMENT_ALIGN  */
    DATA_SEGMENT_RELRO_END = 295,  /* DATA_SEGMENT_RELRO_END  */
    DATA_SEGMENT_END = 296,        /* DATA_SEGMENT_END  */
    SORT_BY_NAME = 297,            /* SORT_BY_NAME  */
    SORT_BY_ALIGNMENT = 298,       /* SORT_BY_ALIGNMENT  */
    SORT_NONE = 299,               /* SORT_NONE  */
    SORT_BY_INIT_PRIORITY = 300,   /* SORT_BY_INIT_PRIORITY  */
    SIZEOF_HEADERS = 301,          /* SIZEOF_HEADERS  */
    OUTPUT_FORMAT = 302,           /* OUTPUT_FORMAT  */
    FORCE_COMMON_ALLOCATION = 303, /* FORCE_COMMON_ALLOCATION  */
    OUTPUT_ARCH = 304,             /* OUTPUT_ARCH  */
    INHIBIT_COMMON_ALLOCATION = 305, /* INHIBIT_COMMON_ALLOCATION  */
    FORCE_GROUP_ALLOCATION = 306,  /* FORCE_GROUP_ALLOCATION  */
    SEGMENT_START = 307,           /* SEGMENT_START  */
    INCLUDE = 308,                 /* INCLUDE  */
    MEMORY = 309,                  /* MEMORY  */
    REGION_ALIAS = 310,            /* REGION_ALIAS  */
    LD_FEATURE = 311,              /* LD_FEATURE  */
    NOLOAD = 312,                  /* NOLOAD  */
    DSECT = 313,                   /* DSECT  */
    COPY = 314,                    /* COPY  */
    INFO = 315,                    /* INFO  */
    OVERLAY = 316,                 /* OVERLAY  */
    READONLY = 317,                /* READONLY  */
    TYPE = 318,                    /* TYPE  */
    DEFINED = 319,                 /* DEFINED  */
    TARGET_K = 320,                /* TARGET_K  */
    SEARCH_DIR = 321,              /* SEARCH_DIR  */
    MAP = 322,                     /* MAP  */
    ENTRY = 323,                   /* ENTRY  */
    NEXT = 324,                    /* NEXT  */
    SIZEOF = 325,                  /* SIZEOF  */
    ALIGNOF = 326,                 /* ALIGNOF  */
    ADDR = 327,                    /* ADDR  */
    LOADADDR = 328,                /* LOADADDR  */
    MAX_K = 329,                   /* MAX_K  */
    MIN_K = 330,                   /* MIN_K  */
    STARTUP = 331,                 /* STARTUP  */
    HLL = 332,                     /* HLL  */
    SYSLIB = 333,                  /* SYSLIB  */
    FLOAT = 334,                   /* FLOAT  */
    NOFLOAT = 335,                 /* NOFLOAT  */
    NOCROSSREFS = 336,             /* NOCROSSREFS  */
    NOCROSSREFS_TO = 337,          /* NOCROSSREFS_TO  */
    ORIGIN = 338,                  /* ORIGIN  */
    FILL = 339,                    /* FILL  */
    LENGTH = 340,                  /* LENGTH  */
    CREATE_OBJECT_SYMBOLS = 341,   /* CREATE_OBJECT_SYMBOLS  */
    INPUT = 342,                   /* INPUT  */
    GROUP = 343,                   /* GROUP  */
    OUTPUT = 344,                  /* OUTPUT  */
    CONSTRUCTORS = 345,            /* CONSTRUCTORS  */
    ALIGNMOD = 346,                /* ALIGNMOD  */
    AT = 347,                      /* AT  */
    SUBALIGN = 348,                /* SUBALIGN  */
    HIDDEN = 349,                  /* HIDDEN  */
    PROVIDE = 350,                 /* PROVIDE  */
    PROVIDE_HIDDEN = 351,          /* PROVIDE_HIDDEN  */
    AS_NEEDED = 352,               /* AS_NEEDED  */
    CHIP = 353,                    /* CHIP  */
    LIST = 354,                    /* LIST  */
    SECT = 355,                    /* SECT  */
    ABSOLUTE = 356,                /* ABSOLUTE  */
    LOAD = 357,                    /* LOAD  */
    NEWLINE = 358,                 /* NEWLINE  */
    ENDWORD = 359,                 /* ENDWORD  */
    ORDER = 360,                   /* ORDER  */
    NAMEWORD = 361,                /* NAMEWORD  */
    ASSERT_K = 362,                /* ASSERT_K  */
    LOG2CEIL = 363,                /* LOG2CEIL  */
    FORMAT = 364,                  /* FORMAT  */
    PUBLIC = 365,                  /* PUBLIC  */
    DEFSYMEND = 366,               /* DEFSYMEND  */
    BASE = 367,                    /* BASE  */
    ALIAS = 368,                   /* ALIAS  */
    TRUNCATE = 369,                /* TRUNCATE  */
    REL = 370,                     /* REL  */
    INPUT_SCRIPT = 371,            /* INPUT_SCRIPT  */
    INPUT_MRI_SCRIPT = 372,        /* INPUT_MRI_SCRIPT  */
    INPUT_DEFSYM = 373,            /* INPUT_DEFSYM  */
    CASE = 374,                    /* CASE  */
    EXTERN = 375,                  /* EXTERN  */
    START = 376,                   /* START  */
    VERS_TAG = 377,                /* VERS_TAG  */
    VERS_IDENTIFIER = 378,         /* VERS_IDENTIFIER  */
    GLOBAL = 379,                  /* GLOBAL  */
    LOCAL = 380,                   /* LOCAL  */
    VERSIONK = 381,                /* VERSIONK  */
    INPUT_VERSION_SCRIPT = 382,    /* INPUT_VERSION_SCRIPT  */
    KEEP = 383,                    /* KEEP  */
    ONLY_IF_RO = 384,              /* ONLY_IF_RO  */
    ONLY_IF_RW = 385,              /* ONLY_IF_RW  */
    SPECIAL = 386,                 /* SPECIAL  */
    INPUT_SECTION_FLAGS = 387,     /* INPUT_SECTION_FLAGS  */
    ALIGN_WITH_INPUT = 388,        /* ALIGN_WITH_INPUT  */
    EXCLUDE_FILE = 389,            /* EXCLUDE_FILE  */
    CONSTANT = 390,                /* CONSTANT  */
    INPUT_DYNAMIC_LIST = 391       /* INPUT_DYNAMIC_LIST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INT 258
#define NAME 259
#define LNAME 260
#define PLUSEQ 261
#define MINUSEQ 262
#define MULTEQ 263
#define DIVEQ 264
#define LSHIFTEQ 265
#define RSHIFTEQ 266
#define ANDEQ 267
#define OREQ 268
#define OROR 269
#define ANDAND 270
#define EQ 271
#define NE 272
#define LE 273
#define GE 274
#define LSHIFT 275
#define RSHIFT 276
#define UNARY 277
#define END 278
#define ALIGN_K 279
#define BLOCK 280
#define BIND 281
#define QUAD 282
#define SQUAD 283
#define LONG 284
#define SHORT 285
#define BYTE 286
#define ASCIZ 287
#define SECTIONS 288
#define PHDRS 289
#define INSERT_K 290
#define AFTER 291
#define BEFORE 292
#define LINKER_VERSION 293
#define DATA_SEGMENT_ALIGN 294
#define DATA_SEGMENT_RELRO_END 295
#define DATA_SEGMENT_END 296
#define SORT_BY_NAME 297
#define SORT_BY_ALIGNMENT 298
#define SORT_NONE 299
#define SORT_BY_INIT_PRIORITY 300
#define SIZEOF_HEADERS 301
#define OUTPUT_FORMAT 302
#define FORCE_COMMON_ALLOCATION 303
#define OUTPUT_ARCH 304
#define INHIBIT_COMMON_ALLOCATION 305
#define FORCE_GROUP_ALLOCATION 306
#define SEGMENT_START 307
#define INCLUDE 308
#define MEMORY 309
#define REGION_ALIAS 310
#define LD_FEATURE 311
#define NOLOAD 312
#define DSECT 313
#define COPY 314
#define INFO 315
#define OVERLAY 316
#define READONLY 317
#define TYPE 318
#define DEFINED 319
#define TARGET_K 320
#define SEARCH_DIR 321
#define MAP 322
#define ENTRY 323
#define NEXT 324
#define SIZEOF 325
#define ALIGNOF 326
#define ADDR 327
#define LOADADDR 328
#define MAX_K 329
#define MIN_K 330
#define STARTUP 331
#define HLL 332
#define SYSLIB 333
#define FLOAT 334
#define NOFLOAT 335
#define NOCROSSREFS 336
#define NOCROSSREFS_TO 337
#define ORIGIN 338
#define FILL 339
#define LENGTH 340
#define CREATE_OBJECT_SYMBOLS 341
#define INPUT 342
#define GROUP 343
#define OUTPUT 344
#define CONSTRUCTORS 345
#define ALIGNMOD 346
#define AT 347
#define SUBALIGN 348
#define HIDDEN 349
#define PROVIDE 350
#define PROVIDE_HIDDEN 351
#define AS_NEEDED 352
#define CHIP 353
#define LIST 354
#define SECT 355
#define ABSOLUTE 356
#define LOAD 357
#define NEWLINE 358
#define ENDWORD 359
#define ORDER 360
#define NAMEWORD 361
#define ASSERT_K 362
#define LOG2CEIL 363
#define FORMAT 364
#define PUBLIC 365
#define DEFSYMEND 366
#define BASE 367
#define ALIAS 368
#define TRUNCATE 369
#define REL 370
#define INPUT_SCRIPT 371
#define INPUT_MRI_SCRIPT 372
#define INPUT_DEFSYM 373
#define CASE 374
#define EXTERN 375
#define START 376
#define VERS_TAG 377
#define VERS_IDENTIFIER 378
#define GLOBAL 379
#define LOCAL 380
#define VERSIONK 381
#define INPUT_VERSION_SCRIPT 382
#define KEEP 383
#define ONLY_IF_RO 384
#define ONLY_IF_RW 385
#define SPECIAL 386
#define INPUT_SECTION_FLAGS 387
#define ALIGN_WITH_INPUT 388
#define EXCLUDE_FILE 389
#define CONSTANT 390
#define INPUT_DYNAMIC_LIST 391

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 62 "ldgram.y"

  bfd_vma integer;
  struct big_int
    {
      bfd_vma integer;
      char *str;
    } bigint;
  fill_type *fill;
  char *name;
  const char *cname;
  struct wildcard_spec wildcard;
  struct wildcard_list *wildcard_list;
  struct name_list *name_list;
  struct flag_info_list *flag_info_list;
  struct flag_info *flag_info;
  int token;
  union etree_union *etree;
  struct phdr_info
    {
      bool filehdr;
      bool phdrs;
      union etree_union *at;
      union etree_union *flags;
    } phdr;
  struct lang_nocrossref *nocrossref;
  struct lang_output_section_phdr_list *section_phdr;
  struct bfd_elf_version_deps *deflist;
  struct bfd_elf_version_expr *versyms;
  struct bfd_elf_version_tree *versnode;

#line 468 "ldgram.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LDGRAM_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_NAME = 4,                       /* NAME  */
  YYSYMBOL_LNAME = 5,                      /* LNAME  */
  YYSYMBOL_PLUSEQ = 6,                     /* PLUSEQ  */
  YYSYMBOL_MINUSEQ = 7,                    /* MINUSEQ  */
  YYSYMBOL_MULTEQ = 8,                     /* MULTEQ  */
  YYSYMBOL_DIVEQ = 9,                      /* DIVEQ  */
  YYSYMBOL_10_ = 10,                       /* '='  */
  YYSYMBOL_LSHIFTEQ = 11,                  /* LSHIFTEQ  */
  YYSYMBOL_RSHIFTEQ = 12,                  /* RSHIFTEQ  */
  YYSYMBOL_ANDEQ = 13,                     /* ANDEQ  */
  YYSYMBOL_OREQ = 14,                      /* OREQ  */
  YYSYMBOL_15_ = 15,                       /* '?'  */
  YYSYMBOL_16_ = 16,                       /* ':'  */
  YYSYMBOL_OROR = 17,                      /* OROR  */
  YYSYMBOL_ANDAND = 18,                    /* ANDAND  */
  YYSYMBOL_19_ = 19,                       /* '|'  */
  YYSYMBOL_20_ = 20,                       /* '^'  */
  YYSYMBOL_21_ = 21,                       /* '&'  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_NE = 23,                        /* NE  */
  YYSYMBOL_24_ = 24,                       /* '<'  */
  YYSYMBOL_25_ = 25,                       /* '>'  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_GE = 27,                        /* GE  */
  YYSYMBOL_LSHIFT = 28,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 29,                    /* RSHIFT  */
  YYSYMBOL_30_ = 30,                       /* '+'  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '*'  */
  YYSYMBOL_33_ = 33,                       /* '/'  */
  YYSYMBOL_34_ = 34,                       /* '%'  */
  YYSYMBOL_UNARY = 35,                     /* UNARY  */
  YYSYMBOL_END = 36,                       /* END  */
  YYSYMBOL_37_ = 37,                       /* '('  */
  YYSYMBOL_ALIGN_K = 38,                   /* ALIGN_K  */
  YYSYMBOL_BLOCK = 39,                     /* BLOCK  */
  YYSYMBOL_BIND = 40,                      /* BIND  */
  YYSYMBOL_QUAD = 41,                      /* QUAD  */
  YYSYMBOL_SQUAD = 42,                     /* SQUAD  */
  YYSYMBOL_LONG = 43,                      /* LONG  */
  YYSYMBOL_SHORT = 44,                     /* SHORT  */
  YYSYMBOL_BYTE = 45,                      /* BYTE  */
  YYSYMBOL_ASCIZ = 46,                     /* ASCIZ  */
  YYSYMBOL_SECTIONS = 47,                  /* SECTIONS  */
  YYSYMBOL_PHDRS = 48,                     /* PHDRS  */
  YYSYMBOL_INSERT_K = 49,                  /* INSERT_K  */
  YYSYMBOL_AFTER = 50,                     /* AFTER  */
  YYSYMBOL_BEFORE = 51,                    /* BEFORE  */
  YYSYMBOL_LINKER_VERSION = 52,            /* LINKER_VERSION  */
  YYSYMBOL_DATA_SEGMENT_ALIGN = 53,        /* DATA_SEGMENT_ALIGN  */
  YYSYMBOL_DATA_SEGMENT_RELRO_END = 54,    /* DATA_SEGMENT_RELRO_END  */
  YYSYMBOL_DATA_SEGMENT_END = 55,          /* DATA_SEGMENT_END  */
  YYSYMBOL_SORT_BY_NAME = 56,              /* SORT_BY_NAME  */
  YYSYMBOL_SORT_BY_ALIGNMENT = 57,         /* SORT_BY_ALIGNMENT  */
  YYSYMBOL_SORT_NONE = 58,                 /* SORT_NONE  */
  YYSYMBOL_SORT_BY_INIT_PRIORITY = 59,     /* SORT_BY_INIT_PRIORITY  */
  YYSYMBOL_60_ = 60,                       /* '{'  */
  YYSYMBOL_61_ = 61,                       /* '}'  */
  YYSYMBOL_SIZEOF_HEADERS = 62,            /* SIZEOF_HEADERS  */
  YYSYMBOL_OUTPUT_FORMAT = 63,             /* OUTPUT_FORMAT  */
  YYSYMBOL_FORCE_COMMON_ALLOCATION = 64,   /* FORCE_COMMON_ALLOCATION  */
  YYSYMBOL_OUTPUT_ARCH = 65,               /* OUTPUT_ARCH  */
  YYSYMBOL_INHIBIT_COMMON_ALLOCATION = 66, /* INHIBIT_COMMON_ALLOCATION  */
  YYSYMBOL_FORCE_GROUP_ALLOCATION = 67,    /* FORCE_GROUP_ALLOCATION  */
  YYSYMBOL_SEGMENT_START = 68,             /* SEGMENT_START  */
  YYSYMBOL_INCLUDE = 69,                   /* INCLUDE  */
  YYSYMBOL_MEMORY = 70,                    /* MEMORY  */
  YYSYMBOL_REGION_ALIAS = 71,              /* REGION_ALIAS  */
  YYSYMBOL_LD_FEATURE = 72,                /* LD_FEATURE  */
  YYSYMBOL_NOLOAD = 73,                    /* NOLOAD  */
  YYSYMBOL_DSECT = 74,                     /* DSECT  */
  YYSYMBOL_COPY = 75,                      /* COPY  */
  YYSYMBOL_INFO = 76,                      /* INFO  */
  YYSYMBOL_OVERLAY = 77,                   /* OVERLAY  */
  YYSYMBOL_READONLY = 78,                  /* READONLY  */
  YYSYMBOL_TYPE = 79,                      /* TYPE  */
  YYSYMBOL_DEFINED = 80,                   /* DEFINED  */
  YYSYMBOL_TARGET_K = 81,                  /* TARGET_K  */
  YYSYMBOL_SEARCH_DIR = 82,                /* SEARCH_DIR  */
  YYSYMBOL_MAP = 83,                       /* MAP  */
  YYSYMBOL_ENTRY = 84,                     /* ENTRY  */
  YYSYMBOL_NEXT = 85,                      /* NEXT  */
  YYSYMBOL_SIZEOF = 86,                    /* SIZEOF  */
  YYSYMBOL_ALIGNOF = 87,                   /* ALIGNOF  */
  YYSYMBOL_ADDR = 88,                      /* ADDR  */
  YYSYMBOL_LOADADDR = 89,                  /* LOADADDR  */
  YYSYMBOL_MAX_K = 90,                     /* MAX_K  */
  YYSYMBOL_MIN_K = 91,                     /* MIN_K  */
  YYSYMBOL_STARTUP = 92,                   /* STARTUP  */
  YYSYMBOL_HLL = 93,                       /* HLL  */
  YYSYMBOL_SYSLIB = 94,                    /* SYSLIB  */
  YYSYMBOL_FLOAT = 95,                     /* FLOAT  */
  YYSYMBOL_NOFLOAT = 96,                   /* NOFLOAT  */
  YYSYMBOL_NOCROSSREFS = 97,               /* NOCROSSREFS  */
  YYSYMBOL_NOCROSSREFS_TO = 98,            /* NOCROSSREFS_TO  */
  YYSYMBOL_ORIGIN = 99,                    /* ORIGIN  */
  YYSYMBOL_FILL = 100,                     /* FILL  */
  YYSYMBOL_LENGTH = 101,                   /* LENGTH  */
  YYSYMBOL_CREATE_OBJECT_SYMBOLS = 102,    /* CREATE_OBJECT_SYMBOLS  */
  YYSYMBOL_INPUT = 103,                    /* INPUT  */
  YYSYMBOL_GROUP = 104,                    /* GROUP  */
  YYSYMBOL_OUTPUT = 105,                   /* OUTPUT  */
  YYSYMBOL_CONSTRUCTORS = 106,             /* CONSTRUCTORS  */
  YYSYMBOL_ALIGNMOD = 107,                 /* ALIGNMOD  */
  YYSYMBOL_AT = 108,                       /* AT  */
  YYSYMBOL_SUBALIGN = 109,                 /* SUBALIGN  */
  YYSYMBOL_HIDDEN = 110,                   /* HIDDEN  */
  YYSYMBOL_PROVIDE = 111,                  /* PROVIDE  */
  YYSYMBOL_PROVIDE_HIDDEN = 112,           /* PROVIDE_HIDDEN  */
  YYSYMBOL_AS_NEEDED = 113,                /* AS_NEEDED  */
  YYSYMBOL_CHIP = 114,                     /* CHIP  */
  YYSYMBOL_LIST = 115,                     /* LIST  */
  YYSYMBOL_SECT = 116,                     /* SECT  */
  YYSYMBOL_ABSOLUTE = 117,                 /* ABSOLUTE  */
  YYSYMBOL_LOAD = 118,                     /* LOAD  */
  YYSYMBOL_NEWLINE = 119,                  /* NEWLINE  */
  YYSYMBOL_ENDWORD = 120,                  /* ENDWORD  */
  YYSYMBOL_ORDER = 121,                    /* ORDER  */
  YYSYMBOL_NAMEWORD = 122,                 /* NAMEWORD  */
  YYSYMBOL_ASSERT_K = 123,                 /* ASSERT_K  */
  YYSYMBOL_LOG2CEIL = 124,                 /* LOG2CEIL  */
  YYSYMBOL_FORMAT = 125,                   /* FORMAT  */
  YYSYMBOL_PUBLIC = 126,                   /* PUBLIC  */
  YYSYMBOL_DEFSYMEND = 127,                /* DEFSYMEND  */
  YYSYMBOL_BASE = 128,                     /* BASE  */
  YYSYMBOL_ALIAS = 129,                    /* ALIAS  */
  YYSYMBOL_TRUNCATE = 130,                 /* TRUNCATE  */
  YYSYMBOL_REL = 131,                      /* REL  */
  YYSYMBOL_INPUT_SCRIPT = 132,             /* INPUT_SCRIPT  */
  YYSYMBOL_INPUT_MRI_SCRIPT = 133,         /* INPUT_MRI_SCRIPT  */
  YYSYMBOL_INPUT_DEFSYM = 134,             /* INPUT_DEFSYM  */
  YYSYMBOL_CASE = 135,                     /* CASE  */
  YYSYMBOL_EXTERN = 136,                   /* EXTERN  */
  YYSYMBOL_START = 137,                    /* START  */
  YYSYMBOL_VERS_TAG = 138,                 /* VERS_TAG  */
  YYSYMBOL_VERS_IDENTIFIER = 139,          /* VERS_IDENTIFIER  */
  YYSYMBOL_GLOBAL = 140,                   /* GLOBAL  */
  YYSYMBOL_LOCAL = 141,                    /* LOCAL  */
  YYSYMBOL_VERSIONK = 142,                 /* VERSIONK  */
  YYSYMBOL_INPUT_VERSION_SCRIPT = 143,     /* INPUT_VERSION_SCRIPT  */
  YYSYMBOL_KEEP = 144,                     /* KEEP  */
  YYSYMBOL_ONLY_IF_RO = 145,               /* ONLY_IF_RO  */
  YYSYMBOL_ONLY_IF_RW = 146,               /* ONLY_IF_RW  */
  YYSYMBOL_SPECIAL = 147,                  /* SPECIAL  */
  YYSYMBOL_INPUT_SECTION_FLAGS = 148,      /* INPUT_SECTION_FLAGS  */
  YYSYMBOL_ALIGN_WITH_INPUT = 149,         /* ALIGN_WITH_INPUT  */
  YYSYMBOL_EXCLUDE_FILE = 150,             /* EXCLUDE_FILE  */
  YYSYMBOL_CONSTANT = 151,                 /* CONSTANT  */
  YYSYMBOL_INPUT_DYNAMIC_LIST = 152,       /* INPUT_DYNAMIC_LIST  */
  YYSYMBOL_153_ = 153,                     /* ','  */
  YYSYMBOL_154_ = 154,                     /* ';'  */
  YYSYMBOL_155_ = 155,                     /* ')'  */
  YYSYMBOL_156_ = 156,                     /* '['  */
  YYSYMBOL_157_ = 157,                     /* ']'  */
  YYSYMBOL_158_ = 158,                     /* '!'  */
  YYSYMBOL_159_ = 159,                     /* '~'  */
  YYSYMBOL_YYACCEPT = 160,                 /* $accept  */
  YYSYMBOL_file = 161,                     /* file  */
  YYSYMBOL_filename = 162,                 /* filename  */
  YYSYMBOL_defsym_expr = 163,              /* defsym_expr  */
  YYSYMBOL_164_1 = 164,                    /* $@1  */
  YYSYMBOL_mri_script_file = 165,          /* mri_script_file  */
  YYSYMBOL_166_2 = 166,                    /* $@2  */
  YYSYMBOL_mri_script_lines = 167,         /* mri_script_lines  */
  YYSYMBOL_mri_script_command = 168,       /* mri_script_command  */
  YYSYMBOL_169_3 = 169,                    /* $@3  */
  YYSYMBOL_ordernamelist = 170,            /* ordernamelist  */
  YYSYMBOL_mri_load_name_list = 171,       /* mri_load_name_list  */
  YYSYMBOL_mri_abs_name_list = 172,        /* mri_abs_name_list  */
  YYSYMBOL_casesymlist = 173,              /* casesymlist  */
  YYSYMBOL_extern_name_list = 174,         /* extern_name_list  */
  YYSYMBOL_script_file = 175,              /* script_file  */
  YYSYMBOL_176_4 = 176,                    /* $@4  */
  YYSYMBOL_ifile_list = 177,               /* ifile_list  */
  YYSYMBOL_ifile_p1 = 178,                 /* ifile_p1  */
  YYSYMBOL_179_5 = 179,                    /* $@5  */
  YYSYMBOL_180_6 = 180,                    /* $@6  */
  YYSYMBOL_181_7 = 181,                    /* $@7  */
  YYSYMBOL_input_list = 182,               /* input_list  */
  YYSYMBOL_183_8 = 183,                    /* $@8  */
  YYSYMBOL_input_list1 = 184,              /* input_list1  */
  YYSYMBOL_185_9 = 185,                    /* @9  */
  YYSYMBOL_186_10 = 186,                   /* @10  */
  YYSYMBOL_187_11 = 187,                   /* @11  */
  YYSYMBOL_sections = 188,                 /* sections  */
  YYSYMBOL_sec_or_group_p1 = 189,          /* sec_or_group_p1  */
  YYSYMBOL_statement_anywhere = 190,       /* statement_anywhere  */
  YYSYMBOL_191_12 = 191,                   /* $@12  */
  YYSYMBOL_wildcard_name = 192,            /* wildcard_name  */
  YYSYMBOL_wildcard_maybe_exclude = 193,   /* wildcard_maybe_exclude  */
  YYSYMBOL_filename_spec = 194,            /* filename_spec  */
  YYSYMBOL_section_name_spec = 195,        /* section_name_spec  */
  YYSYMBOL_sect_flag_list = 196,           /* sect_flag_list  */
  YYSYMBOL_sect_flags = 197,               /* sect_flags  */
  YYSYMBOL_exclude_name_list = 198,        /* exclude_name_list  */
  YYSYMBOL_section_name_list = 199,        /* section_name_list  */
  YYSYMBOL_input_section_spec_no_keep = 200, /* input_section_spec_no_keep  */
  YYSYMBOL_input_section_spec = 201,       /* input_section_spec  */
  YYSYMBOL_202_13 = 202,                   /* $@13  */
  YYSYMBOL_statement = 203,                /* statement  */
  YYSYMBOL_204_14 = 204,                   /* $@14  */
  YYSYMBOL_205_15 = 205,                   /* $@15  */
  YYSYMBOL_statement_list = 206,           /* statement_list  */
  YYSYMBOL_statement_list_opt = 207,       /* statement_list_opt  */
  YYSYMBOL_length = 208,                   /* length  */
  YYSYMBOL_fill_exp = 209,                 /* fill_exp  */
  YYSYMBOL_fill_opt = 210,                 /* fill_opt  */
  YYSYMBOL_assign_op = 211,                /* assign_op  */
  YYSYMBOL_separator = 212,                /* separator  */
  YYSYMBOL_assignment = 213,               /* assignment  */
  YYSYMBOL_opt_comma = 214,                /* opt_comma  */
  YYSYMBOL_memory = 215,                   /* memory  */
  YYSYMBOL_memory_spec_list_opt = 216,     /* memory_spec_list_opt  */
  YYSYMBOL_memory_spec_list = 217,         /* memory_spec_list  */
  YYSYMBOL_memory_spec = 218,              /* memory_spec  */
  YYSYMBOL_219_16 = 219,                   /* $@16  */
  YYSYMBOL_220_17 = 220,                   /* $@17  */
  YYSYMBOL_origin_spec = 221,              /* origin_spec  */
  YYSYMBOL_length_spec = 222,              /* length_spec  */
  YYSYMBOL_attributes_opt = 223,           /* attributes_opt  */
  YYSYMBOL_attributes_list = 224,          /* attributes_list  */
  YYSYMBOL_attributes_string = 225,        /* attributes_string  */
  YYSYMBOL_startup = 226,                  /* startup  */
  YYSYMBOL_high_level_library = 227,       /* high_level_library  */
  YYSYMBOL_high_level_library_NAME_list = 228, /* high_level_library_NAME_list  */
  YYSYMBOL_low_level_library = 229,        /* low_level_library  */
  YYSYMBOL_low_level_library_NAME_list = 230, /* low_level_library_NAME_list  */
  YYSYMBOL_floating_point_support = 231,   /* floating_point_support  */
  YYSYMBOL_nocrossref_list = 232,          /* nocrossref_list  */
  YYSYMBOL_paren_script_name = 233,        /* paren_script_name  */
  YYSYMBOL_234_18 = 234,                   /* $@18  */
  YYSYMBOL_mustbe_exp = 235,               /* mustbe_exp  */
  YYSYMBOL_236_19 = 236,                   /* $@19  */
  YYSYMBOL_exp = 237,                      /* exp  */
  YYSYMBOL_238_20 = 238,                   /* $@20  */
  YYSYMBOL_239_21 = 239,                   /* $@21  */
  YYSYMBOL_memspec_at_opt = 240,           /* memspec_at_opt  */
  YYSYMBOL_opt_at = 241,                   /* opt_at  */
  YYSYMBOL_opt_align = 242,                /* opt_align  */
  YYSYMBOL_opt_align_with_input = 243,     /* opt_align_with_input  */
  YYSYMBOL_opt_subalign = 244,             /* opt_subalign  */
  YYSYMBOL_sect_constraint = 245,          /* sect_constraint  */
  YYSYMBOL_section = 246,                  /* section  */
  YYSYMBOL_247_22 = 247,                   /* $@22  */
  YYSYMBOL_248_23 = 248,                   /* $@23  */
  YYSYMBOL_249_24 = 249,                   /* $@24  */
  YYSYMBOL_250_25 = 250,                   /* $@25  */
  YYSYMBOL_251_26 = 251,                   /* $@26  */
  YYSYMBOL_252_27 = 252,                   /* $@27  */
  YYSYMBOL_253_28 = 253,                   /* $@28  */
  YYSYMBOL_254_29 = 254,                   /* $@29  */
  YYSYMBOL_255_30 = 255,                   /* $@30  */
  YYSYMBOL_256_31 = 256,                   /* $@31  */
  YYSYMBOL_257_32 = 257,                   /* $@32  */
  YYSYMBOL_type = 258,                     /* type  */
  YYSYMBOL_atype = 259,                    /* atype  */
  YYSYMBOL_opt_exp_with_type = 260,        /* opt_exp_with_type  */
  YYSYMBOL_opt_exp_without_type = 261,     /* opt_exp_without_type  */
  YYSYMBOL_opt_nocrossrefs = 262,          /* opt_nocrossrefs  */
  YYSYMBOL_memspec_opt = 263,              /* memspec_opt  */
  YYSYMBOL_phdr_opt = 264,                 /* phdr_opt  */
  YYSYMBOL_overlay_section = 265,          /* overlay_section  */
  YYSYMBOL_266_33 = 266,                   /* $@33  */
  YYSYMBOL_267_34 = 267,                   /* $@34  */
  YYSYMBOL_268_35 = 268,                   /* $@35  */
  YYSYMBOL_phdrs = 269,                    /* phdrs  */
  YYSYMBOL_phdr_list = 270,                /* phdr_list  */
  YYSYMBOL_phdr = 271,                     /* phdr  */
  YYSYMBOL_272_36 = 272,                   /* $@36  */
  YYSYMBOL_273_37 = 273,                   /* $@37  */
  YYSYMBOL_phdr_type = 274,                /* phdr_type  */
  YYSYMBOL_phdr_qualifiers = 275,          /* phdr_qualifiers  */
  YYSYMBOL_phdr_val = 276,                 /* phdr_val  */
  YYSYMBOL_dynamic_list_file = 277,        /* dynamic_list_file  */
  YYSYMBOL_278_38 = 278,                   /* $@38  */
  YYSYMBOL_dynamic_list_nodes = 279,       /* dynamic_list_nodes  */
  YYSYMBOL_dynamic_list_node = 280,        /* dynamic_list_node  */
  YYSYMBOL_dynamic_list_tag = 281,         /* dynamic_list_tag  */
  YYSYMBOL_version_script_file = 282,      /* version_script_file  */
  YYSYMBOL_283_39 = 283,                   /* $@39  */
  YYSYMBOL_version = 284,                  /* version  */
  YYSYMBOL_285_40 = 285,                   /* $@40  */
  YYSYMBOL_vers_nodes = 286,               /* vers_nodes  */
  YYSYMBOL_vers_node = 287,                /* vers_node  */
  YYSYMBOL_verdep = 288,                   /* verdep  */
  YYSYMBOL_vers_tag = 289,                 /* vers_tag  */
  YYSYMBOL_vers_defns = 290,               /* vers_defns  */
  YYSYMBOL_291_41 = 291,                   /* @41  */
  YYSYMBOL_292_42 = 292,                   /* @42  */
  YYSYMBOL_opt_semicolon = 293             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2053

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  160
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  134
/* YYNRULES -- Number of rules.  */
#define YYNRULES  380
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  813

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   391


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   158,     2,     2,     2,    34,    21,     2,
      37,   155,    32,    30,   153,    31,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    16,   154,
      24,    10,    25,    15,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   156,     2,   157,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,    19,    61,   159,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    11,    12,    13,    14,    17,
      18,    22,    23,    26,    27,    28,    29,    35,    36,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   169,   169,   170,   171,   172,   173,   177,   181,   181,
     188,   188,   201,   202,   206,   207,   208,   211,   214,   215,
     216,   218,   220,   222,   224,   226,   228,   230,   232,   234,
     236,   238,   239,   240,   242,   244,   246,   248,   250,   251,
     253,   252,   255,   257,   261,   262,   263,   267,   269,   273,
     275,   280,   281,   282,   286,   288,   290,   295,   295,   301,
     302,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   319,   321,   323,   326,   328,   330,   332,   334,
     336,   338,   337,   341,   344,   343,   346,   350,   354,   354,
     356,   358,   360,   362,   367,   367,   372,   375,   378,   381,
     384,   387,   391,   390,   396,   395,   401,   400,   408,   412,
     413,   414,   418,   420,   421,   421,   427,   434,   441,   451,
     452,   457,   465,   466,   471,   476,   481,   486,   491,   496,
     501,   508,   526,   547,   560,   569,   580,   589,   600,   609,
     618,   622,   631,   635,   643,   645,   644,   651,   652,   653,
     657,   661,   666,   667,   671,   675,   679,   684,   683,   691,
     690,   698,   699,   702,   704,   708,   710,   712,   714,   716,
     721,   728,   730,   734,   736,   738,   740,   742,   744,   746,
     748,   753,   753,   758,   762,   770,   774,   778,   786,   786,
     790,   793,   793,   796,   797,   802,   801,   807,   806,   812,
     819,   832,   833,   837,   838,   842,   844,   849,   854,   855,
     860,   862,   867,   871,   873,   877,   879,   885,   888,   897,
     908,   908,   912,   912,   918,   920,   922,   924,   926,   928,
     931,   933,   935,   937,   939,   941,   943,   945,   947,   949,
     951,   953,   955,   957,   959,   961,   963,   965,   967,   969,
     971,   973,   976,   978,   980,   982,   984,   986,   988,   990,
     992,   994,   996,   998,   999,   998,  1008,  1010,  1012,  1014,
    1016,  1018,  1020,  1022,  1028,  1029,  1033,  1034,  1038,  1039,
    1043,  1044,  1048,  1049,  1053,  1054,  1055,  1056,  1060,  1067,
    1076,  1078,  1059,  1096,  1098,  1100,  1106,  1095,  1121,  1123,
    1120,  1129,  1128,  1136,  1137,  1138,  1139,  1140,  1141,  1142,
    1143,  1147,  1148,  1149,  1153,  1154,  1159,  1160,  1165,  1166,
    1171,  1172,  1177,  1179,  1184,  1187,  1200,  1204,  1211,  1213,
    1202,  1225,  1228,  1230,  1234,  1235,  1234,  1244,  1293,  1296,
    1309,  1318,  1321,  1328,  1328,  1340,  1341,  1345,  1349,  1358,
    1358,  1372,  1372,  1382,  1383,  1387,  1391,  1395,  1402,  1406,
    1414,  1417,  1421,  1425,  1429,  1436,  1440,  1444,  1448,  1453,
    1452,  1466,  1465,  1475,  1479,  1483,  1487,  1491,  1495,  1501,
    1503
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "NAME", "LNAME",
  "PLUSEQ", "MINUSEQ", "MULTEQ", "DIVEQ", "'='", "LSHIFTEQ", "RSHIFTEQ",
  "ANDEQ", "OREQ", "'?'", "':'", "OROR", "ANDAND", "'|'", "'^'", "'&'",
  "EQ", "NE", "'<'", "'>'", "LE", "GE", "LSHIFT", "RSHIFT", "'+'", "'-'",
  "'*'", "'/'", "'%'", "UNARY", "END", "'('", "ALIGN_K", "BLOCK", "BIND",
  "QUAD", "SQUAD", "LONG", "SHORT", "BYTE", "ASCIZ", "SECTIONS", "PHDRS",
  "INSERT_K", "AFTER", "BEFORE", "LINKER_VERSION", "DATA_SEGMENT_ALIGN",
  "DATA_SEGMENT_RELRO_END", "DATA_SEGMENT_END", "SORT_BY_NAME",
  "SORT_BY_ALIGNMENT", "SORT_NONE", "SORT_BY_INIT_PRIORITY", "'{'", "'}'",
  "SIZEOF_HEADERS", "OUTPUT_FORMAT", "FORCE_COMMON_ALLOCATION",
  "OUTPUT_ARCH", "INHIBIT_COMMON_ALLOCATION", "FORCE_GROUP_ALLOCATION",
  "SEGMENT_START", "INCLUDE", "MEMORY", "REGION_ALIAS", "LD_FEATURE",
  "NOLOAD", "DSECT", "COPY", "INFO", "OVERLAY", "READONLY", "TYPE",
  "DEFINED", "TARGET_K", "SEARCH_DIR", "MAP", "ENTRY", "NEXT", "SIZEOF",
  "ALIGNOF", "ADDR", "LOADADDR", "MAX_K", "MIN_K", "STARTUP", "HLL",
  "SYSLIB", "FLOAT", "NOFLOAT", "NOCROSSREFS", "NOCROSSREFS_TO", "ORIGIN",
  "FILL", "LENGTH", "CREATE_OBJECT_SYMBOLS", "INPUT", "GROUP", "OUTPUT",
  "CONSTRUCTORS", "ALIGNMOD", "AT", "SUBALIGN", "HIDDEN", "PROVIDE",
  "PROVIDE_HIDDEN", "AS_NEEDED", "CHIP", "LIST", "SECT", "ABSOLUTE",
  "LOAD", "NEWLINE", "ENDWORD", "ORDER", "NAMEWORD", "ASSERT_K",
  "LOG2CEIL", "FORMAT", "PUBLIC", "DEFSYMEND", "BASE", "ALIAS", "TRUNCATE",
  "REL", "INPUT_SCRIPT", "INPUT_MRI_SCRIPT", "INPUT_DEFSYM", "CASE",
  "EXTERN", "START", "VERS_TAG", "VERS_IDENTIFIER", "GLOBAL", "LOCAL",
  "VERSIONK", "INPUT_VERSION_SCRIPT", "KEEP", "ONLY_IF_RO", "ONLY_IF_RW",
  "SPECIAL", "INPUT_SECTION_FLAGS", "ALIGN_WITH_INPUT", "EXCLUDE_FILE",
  "CONSTANT", "INPUT_DYNAMIC_LIST", "','", "';'", "')'", "'['", "']'",
  "'!'", "'~'", "$accept", "file", "filename", "defsym_expr", "$@1",
  "mri_script_file", "$@2", "mri_script_lines", "mri_script_command",
  "$@3", "ordernamelist", "mri_load_name_list", "mri_abs_name_list",
  "casesymlist", "extern_name_list", "script_file", "$@4", "ifile_list",
  "ifile_p1", "$@5", "$@6", "$@7", "input_list", "$@8", "input_list1",
  "@9", "@10", "@11", "sections", "sec_or_group_p1", "statement_anywhere",
  "$@12", "wildcard_name", "wildcard_maybe_exclude", "filename_spec",
  "section_name_spec", "sect_flag_list", "sect_flags", "exclude_name_list",
  "section_name_list", "input_section_spec_no_keep", "input_section_spec",
  "$@13", "statement", "$@14", "$@15", "statement_list",
  "statement_list_opt", "length", "fill_exp", "fill_opt", "assign_op",
  "separator", "assignment", "opt_comma", "memory", "memory_spec_list_opt",
  "memory_spec_list", "memory_spec", "$@16", "$@17", "origin_spec",
  "length_spec", "attributes_opt", "attributes_list", "attributes_string",
  "startup", "high_level_library", "high_level_library_NAME_list",
  "low_level_library", "low_level_library_NAME_list",
  "floating_point_support", "nocrossref_list", "paren_script_name", "$@18",
  "mustbe_exp", "$@19", "exp", "$@20", "$@21", "memspec_at_opt", "opt_at",
  "opt_align", "opt_align_with_input", "opt_subalign", "sect_constraint",
  "section", "$@22", "$@23", "$@24", "$@25", "$@26", "$@27", "$@28",
  "$@29", "$@30", "$@31", "$@32", "type", "atype", "opt_exp_with_type",
  "opt_exp_without_type", "opt_nocrossrefs", "memspec_opt", "phdr_opt",
  "overlay_section", "$@33", "$@34", "$@35", "phdrs", "phdr_list", "phdr",
  "$@36", "$@37", "phdr_type", "phdr_qualifiers", "phdr_val",
  "dynamic_list_file", "$@38", "dynamic_list_nodes", "dynamic_list_node",
  "dynamic_list_tag", "version_script_file", "$@39", "version", "$@40",
  "vers_nodes", "vers_node", "verdep", "vers_tag", "vers_defns", "@41",
  "@42", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-704)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-352)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -77,  -704,  -704,  -704,  -704,  -704,    77,  -704,  -704,  -704,
    -704,  -704,   230,  -704,   -20,  -704,    45,  -704,   941,  1795,
     718,    65,    93,    98,  -704,   104,    64,   -20,  -704,   112,
      45,  -704,    71,    88,    47,   105,  -704,   119,  -704,  -704,
     184,   186,   210,   212,   213,   218,   223,   231,   242,   247,
     251,  -704,  -704,   252,   256,   265,  -704,   267,  -704,   276,
    -704,  -704,  -704,  -704,   -42,  -704,  -704,  -704,  -704,  -704,
    -704,  -704,   172,  -704,   263,   184,   311,   759,  -704,   312,
     320,   321,  -704,  -704,   322,   324,   325,   759,   328,   331,
     332,   334,   335,   216,  -704,  -704,  -704,  -704,  -704,  -704,
    -704,  -704,  -704,  -704,   339,   340,   341,  -704,   343,  -704,
     336,   337,   287,   196,   104,  -704,  -704,  -704,   290,   204,
    -704,  -704,  -704,   359,   380,   392,   393,  -704,  -704,    25,
     395,   396,   397,   184,   184,   405,   184,    15,  -704,   407,
     407,  -704,   375,   184,   376,  -704,  -704,  -704,  -704,   354,
      75,  -704,    85,  -704,  -704,   759,   759,   759,   381,   382,
     383,   384,   388,  -704,  -704,   389,   399,  -704,  -704,  -704,
    -704,   404,   409,  -704,  -704,   411,   412,   413,   414,   759,
     759,   347,   385,  -704,   289,  -704,   299,    14,  -704,  -704,
     516,  2014,   301,  -704,  -704,   306,  -704,    41,  -704,  -704,
    -704,   759,  -704,   450,   451,   452,   403,   112,   112,   310,
     118,   406,   314,   118,   333,    39,  -704,  -704,   -36,   323,
    -704,  -704,   184,   408,    -2,  -704,   313,   326,   327,   330,
     344,   349,   350,  -704,  -704,   -32,     0,    42,   351,   352,
     362,    19,  -704,   366,   759,   334,   -20,   759,   759,  -704,
     759,   759,  -704,  -704,  1160,   759,   759,   759,   759,   759,
     440,   475,   759,  -704,   443,  -704,  -704,  -704,   759,   759,
    -704,  -704,   759,   759,   759,   483,  -704,  -704,   759,   759,
     759,   759,   759,   759,   759,   759,   759,   759,   759,   759,
     759,   759,   759,   759,   759,   759,   759,   759,   759,   759,
    2014,   484,   486,  -704,   488,   759,   759,  2014,   238,   490,
    -704,   492,  2014,  -704,  -704,  -704,  -704,   369,   370,  -704,
    -704,   521,  -704,  -704,  -704,   -80,  -704,   718,  -704,   184,
    -704,  -704,  -704,  -704,  -704,  -704,  -704,   523,  -704,  -704,
    1022,   491,  -704,  -704,  -704,    25,   525,  -704,  -704,  -704,
    -704,  -704,  -704,  -704,   184,  -704,   184,   407,  -704,  -704,
    -704,  -704,  -704,  -704,   494,    37,   377,  -704,  1598,    46,
     -25,  2014,  2014,  1820,  2014,  2014,  -704,   904,  1180,  1637,
    1657,  1200,   530,   387,  1220,   535,  1677,  1697,  1240,  1735,
    1260,   390,  1964,   953,  1140,  1296,  1454,  1612,   662,   662,
     482,   482,   482,   482,   374,   374,    94,    94,  -704,  -704,
    -704,  2014,  2014,  2014,  -704,  -704,  -704,  2014,  2014,  -704,
    -704,  -704,  -704,   401,   417,   418,   112,   125,   118,   480,
    -704,  -704,   -70,   617,  -704,   719,   617,   759,   398,  -704,
       8,   532,    25,  -704,   420,  -704,  -704,  -704,  -704,  -704,
    -704,   513,    21,  -704,   548,  -704,  -704,  -704,   759,  -704,
    -704,   759,   759,  -704,  -704,  -704,  -704,   422,   759,   759,
    -704,   554,  -704,  -704,   759,  -704,  -704,  -704,   425,   543,
    -704,  -704,  -704,   232,   524,  1848,   544,   454,  -704,  -704,
    1994,   469,  -704,  2014,    29,   563,  -704,   564,     3,  -704,
     481,   545,  -704,    19,  -704,  -704,  -704,   546,   430,  1280,
    1319,  1339,   433,  -704,  1359,  1379,   432,  2014,   118,   528,
     112,   112,  -704,  -704,  -704,  -704,  -704,   553,   582,  -704,
     438,   759,   199,   578,  -704,   558,   559,   453,  -704,  -704,
     454,   538,   562,   571,  -704,   445,  -704,  -704,  -704,   599,
     457,  -704,    23,    19,  -704,  -704,  -704,  -704,  -704,   759,
    -704,  -704,  -704,  -704,   458,   425,   534,   759,  -704,  1399,
    -704,   759,   574,   467,  -704,   509,  -704,   759,    29,   759,
     465,  -704,  -704,   522,  -704,    34,    19,  1419,   118,   561,
     614,  2014,   123,  1439,   759,  -704,   509,   588,  -704,  1731,
    1478,  -704,  1498,  -704,  -704,   616,  -704,  -704,    78,  -704,
    -704,   759,   590,   612,  -704,  1518,   152,   759,   569,  -704,
    -704,    29,  -704,  -704,  1538,   759,  -704,  -704,  -704,  -704,
    -704,  -704,  1558,  -704,  -704,  -704,  -704,  1578,   572,  -704,
    -704,   594,   847,    40,   618,   421,  -704,  -704,  -704,  -704,
    -704,   631,  -704,   600,   604,   184,   605,  -704,  -704,  -704,
     606,   607,   608,  -704,    82,  -704,  -704,   609,    13,  -704,
    -704,  -704,   847,   575,   613,   -42,  -704,   624,  -704,  -704,
      27,    50,  -704,  -704,   615,  -704,   647,   649,  -704,   621,
     622,   625,   626,  -704,  -704,  -104,    82,   627,   628,    82,
     629,  -704,  -704,  -704,  -704,   601,   664,   565,   526,   527,
     529,   847,   555,  -704,   759,     9,  -704,    -1,  -704,    18,
      87,    89,    50,    50,  -704,    82,   127,    50,   -61,    82,
     624,   556,   847,  -704,   651,  -704,  -704,  -704,  -704,   641,
    -704,  1755,   557,   560,   674,  -704,   649,  -704,   643,   646,
     566,   661,   663,   581,   583,   584,  -704,  -704,  -704,   148,
     565,  -704,   640,   705,    62,  -704,   709,  -704,  -704,  -704,
      50,    50,  -704,    50,    50,  -704,  -704,  -704,  -704,  -704,
    -704,  -704,  -704,   710,  -704,   587,   589,   591,   592,   593,
      62,  -704,  -704,  -704,   457,   -42,   596,   597,   598,   610,
    -704,    62,  -704,  -704,  -704,  -704,  -704,  -704,   457,  -704,
    -704,   457,  -704
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,    57,    10,     8,   349,   343,     0,     2,    60,     3,
      13,     6,     0,     4,     0,     5,     0,     1,    58,    11,
       0,     0,     0,     0,     9,   360,     0,   350,   353,     0,
     344,   345,     0,     0,     0,     0,    77,     0,    79,    78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,   216,     0,     0,     0,    81,     0,   114,     0,
      70,    59,    62,    68,     0,    61,    64,    65,    66,    67,
      63,    69,     0,    16,     0,     0,     0,     0,    17,     0,
       0,     0,    19,    46,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,   173,   174,   175,   176,   222,   177,
     178,   179,   180,   222,     0,     0,     0,   366,   377,   365,
     373,   375,     0,     0,   360,   354,   373,   375,     0,     0,
     346,   111,   332,     0,     0,     0,     0,     7,    84,   192,
       0,     0,     0,     0,     0,     0,     0,     0,   214,   217,
     217,    94,     0,     0,     0,    88,   182,   181,   113,     0,
       0,    40,     0,   250,   267,     0,     0,     0,     0,     0,
       0,     0,     0,   251,   263,     0,     0,   220,   220,   220,
     220,     0,     0,   220,   220,     0,     0,     0,     0,     0,
       0,    14,     0,    49,    31,    47,    32,    18,    33,    23,
       0,    36,     0,    37,    52,    38,    54,    39,    42,    12,
     183,     0,   184,     0,     0,     0,     0,     0,     0,     0,
     361,     0,     0,   348,     0,     0,    90,    91,     0,     0,
      60,   195,     0,     0,   189,   194,     0,     0,     0,     0,
       0,     0,     0,   209,   211,   189,   189,   217,     0,     0,
       0,     0,    94,     0,     0,     0,     0,     0,     0,    13,
       0,     0,   228,   224,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   253,     0,   252,   254,   255,     0,     0,
     271,   272,     0,     0,     0,     0,   227,   229,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      25,     0,     0,    45,     0,     0,     0,    22,     0,     0,
      55,     0,   223,   222,   222,   222,   371,     0,     0,   355,
     368,   378,   367,   374,   376,     0,   347,   288,   108,     0,
     293,   298,   110,   109,   334,   331,   333,     0,    74,    76,
     351,   201,   197,   190,   188,     0,     0,    93,    71,    72,
      83,   112,   207,   208,     0,   212,     0,   217,   218,    86,
      87,    80,    96,    99,     0,    95,     0,    73,     0,     0,
       0,    27,    28,    43,    29,    30,   225,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   248,   247,   245,   244,   243,   237,   238,
     241,   242,   239,   240,   235,   236,   233,   234,   230,   231,
     232,    15,    26,    24,    50,    48,    44,    20,    21,    35,
      34,    53,    56,     0,     0,     0,     0,   362,   363,     0,
     358,   356,     0,   312,   301,     0,   312,     0,     0,    85,
       0,     0,   192,   193,     0,   210,   213,   219,   102,    98,
     101,     0,     0,    82,     0,    89,   352,    41,     0,   258,
     266,     0,     0,   262,   264,   249,   226,     0,     0,     0,
     257,     0,   273,   256,     0,   185,   186,   187,   379,   376,
     369,   359,   357,     0,     0,   312,     0,   277,   111,   319,
       0,   320,   299,   337,   338,     0,   205,     0,     0,   203,
       0,     0,    92,     0,   106,    97,   100,     0,     0,     0,
       0,     0,     0,   221,     0,     0,     0,   246,   380,     0,
       0,     0,   303,   304,   305,   306,   307,   309,     0,   313,
       0,     0,     0,     0,   315,     0,   279,     0,   318,   321,
     277,     0,   341,     0,   335,     0,   206,   202,   204,     0,
     189,   198,     0,     0,   104,   115,   259,   260,   261,     0,
     268,   269,   270,   372,     0,   379,     0,     0,   311,     0,
     314,     0,     0,   281,   302,   283,   111,     0,   338,     0,
       0,    75,   222,     0,   103,     0,     0,     0,   364,     0,
       0,   310,   312,     0,     0,   280,   283,     0,   294,     0,
       0,   339,     0,   336,   199,     0,   196,   107,     0,   265,
     370,     0,     0,     0,   276,     0,   287,     0,     0,   300,
     342,   338,   222,   105,     0,     0,   316,   278,   284,   285,
     286,   289,     0,   295,   340,   200,   308,     0,     0,   282,
     326,   312,   163,     0,     0,   138,   165,   166,   167,   168,
     169,     0,   156,     0,     0,     0,     0,   149,   150,   157,
       0,     0,     0,   147,     0,   117,   119,     0,     0,   144,
     152,   162,   164,     0,     0,     0,   327,   323,   317,   154,
       0,     0,   159,   222,     0,   145,     0,     0,   116,     0,
       0,     0,     0,   122,   137,   189,     0,   139,     0,     0,
       0,   161,   290,   222,   148,     0,     0,   275,     0,     0,
       0,   163,     0,   170,     0,     0,   131,     0,   135,     0,
       0,     0,     0,     0,   140,     0,   189,     0,   189,     0,
     323,     0,   163,   322,     0,   324,   151,   120,   121,     0,
     155,     0,   116,     0,     0,   133,     0,   134,     0,     0,
       0,     0,     0,     0,     0,     0,   136,   142,   141,   189,
     275,   153,     0,     0,   172,   160,     0,   146,   132,   118,
       0,     0,   123,     0,     0,   124,   125,   130,   143,   324,
     328,   274,   222,     0,   296,     0,     0,     0,     0,     0,
     172,   324,   171,   325,   189,     0,     0,     0,     0,     0,
     291,   172,   297,   158,   127,   126,   128,   129,   189,   329,
     292,   189,   330
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -704,  -704,   -73,  -704,  -704,  -704,  -704,   468,  -704,  -704,
    -704,  -704,  -704,  -704,   474,  -704,  -704,   517,  -704,  -704,
    -704,  -704,   501,  -704,  -466,  -704,  -704,  -704,  -704,  -467,
     -13,  -704,  -657,  1279,    86,    20,  -704,  -704,  -704,  -648,
      44,  -704,  -704,    61,  -704,  -704,  -704,  -659,  -704,   -27,
    -691,  -704,  -643,   -12,  -220,  -704,   318,  -704,   416,  -704,
    -704,  -704,  -704,  -704,  -704,   266,  -704,  -704,  -704,  -704,
    -704,  -704,  -130,   122,  -704,   -89,  -704,   -76,  -704,  -704,
       6,   227,  -704,  -704,   173,  -704,  -704,  -704,  -704,  -704,
    -704,  -704,  -704,  -704,  -704,  -704,  -704,  -704,  -704,  -477,
     342,  -704,  -704,    49,  -703,  -704,  -704,  -704,  -704,  -704,
    -704,  -704,  -704,  -704,  -704,  -531,  -704,  -704,  -704,  -704,
     740,  -704,  -704,  -704,  -704,  -704,   531,   -24,  -704,   657,
     -23,  -704,  -704,   215
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     6,   128,    11,    12,     9,    10,    19,    93,   249,
     187,   186,   184,   195,   197,     7,     8,    18,    61,   142,
     220,   245,   240,   241,   365,   503,   586,   553,    62,   214,
     332,   144,   665,   666,   667,   694,   717,   668,   719,   695,
     669,   670,   715,   671,   684,   711,   672,   673,   674,   712,
     784,   103,   148,    64,   725,    65,   223,   224,   225,   341,
     442,   550,   606,   441,   498,   499,    66,    67,   235,    68,
     236,    69,   238,   263,   264,   713,   201,   254,   260,   512,
     735,   536,   573,   596,   598,   631,   333,   433,   638,   730,
     808,   435,   618,   640,   794,   436,   541,   488,   530,   486,
     487,   491,   540,   707,   764,   643,   705,   791,   811,    70,
     215,   336,   437,   580,   494,   544,   578,    15,    16,    30,
      31,   118,    13,    14,    71,    72,    27,    28,   432,   112,
     113,   521,   426,   519
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      24,   181,   151,   115,   345,    63,   119,   496,   533,   200,
     239,   191,   496,   742,   202,   354,   356,   697,   303,   127,
     744,   537,   688,   362,   363,   505,   506,   449,   450,   221,
     718,   688,   704,   542,  -191,    25,   456,   552,   449,   450,
      25,   449,   450,   334,   676,   310,   237,   601,   726,   344,
     310,   728,   739,   724,   688,     1,     2,     3,   430,  -191,
     229,   230,   747,   232,   234,   698,     4,   654,   481,   698,
     243,   654,   782,   762,   431,     5,   790,    17,   783,   252,
     253,   759,   449,   450,   482,   247,   688,   585,   801,   769,
     634,   688,   344,   688,   222,   250,   758,   123,   124,   800,
     335,   677,   104,   276,   277,    29,   300,   358,   107,   599,
     809,   146,   147,    26,   307,   613,   107,   337,    26,   338,
     608,   344,   320,   353,   114,   312,   294,   295,   296,   320,
     105,   121,   364,   708,   507,   106,   451,   543,   689,   690,
     691,   692,   125,   748,   749,   751,   752,   451,   122,   342,
     451,   344,   803,   344,   745,   355,   126,   661,   547,   662,
     532,   497,   612,   662,   644,   664,   497,   304,   368,   699,
     233,   371,   372,   746,   374,   375,   452,   662,   584,   377,
     378,   379,   380,   381,   317,   318,   384,   452,   127,   607,
     452,   451,   386,   387,   311,   357,   388,   389,   390,   311,
     662,   455,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   423,   424,   425,   447,   248,   417,
     418,   452,   662,   623,    20,   153,   154,   662,   251,   662,
     108,   419,   420,   109,   110,   111,   129,   130,   108,   131,
     132,   109,   116,   117,   321,   133,   434,   322,   323,   324,
     134,   321,   155,   156,   322,   323,   479,   150,   135,   157,
     158,   159,   522,   523,   524,   525,   526,   527,   528,   136,
     344,   445,   757,   446,   137,   160,   161,   162,   138,   139,
     265,   266,   267,   140,   163,   270,   271,   628,   629,   630,
     164,   344,   141,   778,   143,   522,   523,   524,   525,   526,
     527,   528,   165,   145,   149,   152,   182,   166,   167,   168,
     169,   170,   171,   172,   183,   185,   188,    63,   189,   190,
     583,   173,   192,   174,   193,   199,   194,   327,   196,   198,
      21,    22,    23,   203,   204,   205,   115,   206,   209,   175,
     210,   212,   207,   208,   529,   176,   177,   485,   213,   490,
     485,   493,   278,   216,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   509,   178,   217,   510,   511,   529,   153,   154,
     179,   180,   514,   515,   328,   298,   218,   219,   517,   226,
     227,   228,   329,   478,   292,   293,   294,   295,   296,   231,
     330,   237,   242,   244,   246,   155,   156,    47,   255,   256,
     257,   258,   157,   158,   159,   259,   261,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   262,   331,   160,   161,
     162,   268,   301,    21,    22,    23,   269,   163,   272,   273,
     274,   275,   302,   164,   308,   569,    58,   327,  -116,   309,
     313,   314,   315,   316,   319,   165,   346,   325,   326,   343,
     166,   167,   168,   169,   170,   171,   172,   382,   339,   383,
     385,   347,   348,   587,   173,   349,   174,   391,   414,   574,
     415,   591,   416,   604,   421,   593,   422,   564,   565,   350,
     297,   600,   175,   602,   351,   352,   359,   360,   176,   177,
     290,   291,   292,   293,   294,   295,   296,   361,   615,   153,
     154,   367,   329,   427,   428,   429,   305,   438,   440,   444,
     330,   448,   453,   635,   464,   624,   178,    47,   299,   467,
     480,   632,   465,   179,   180,   473,   155,   156,   500,   637,
     504,   495,   508,   157,   158,   159,   475,   331,   516,   520,
     534,   531,   535,    21,    22,    23,   539,   545,   546,   160,
     161,   162,   476,   477,   802,   502,    58,   513,   163,   518,
     549,   551,   682,   554,   164,   555,   559,   562,   810,   563,
     566,   812,   567,   568,   570,   571,   165,   572,   576,   577,
     581,   166,   167,   168,   169,   170,   171,   172,   579,   582,
     344,   594,   588,   590,   731,   173,   595,   174,   597,   603,
     153,   154,   610,   605,   611,   617,   622,   625,   626,   633,
     675,   532,   642,   175,   678,   679,   702,   680,   741,   176,
     177,   681,   683,   685,   686,   687,   696,   155,   156,   706,
     703,   716,   714,   688,   483,   158,   159,   484,   720,   721,
     675,   732,   722,   723,  -116,   727,   729,   178,   733,   306,
     160,   161,   162,   734,   179,   180,   763,   765,   768,   163,
     770,   736,   737,   771,   738,   164,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   165,   773,   675,
     774,   780,   166,   167,   168,   169,   170,   171,   172,   781,
     740,   761,  -138,   785,   793,   767,   173,   373,   174,   369,
     675,   772,   153,   154,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   701,   175,   489,   775,   340,   776,   777,
     176,   177,   795,   366,   796,   756,   797,   798,   799,   155,
     156,   804,   805,   806,   700,   792,   157,   158,   159,   743,
     501,   443,   153,   154,   548,   807,   779,   575,   178,   616,
     120,   211,   160,   161,   162,   179,   180,   370,   492,   760,
     589,   163,     0,     0,     0,     0,     0,   164,     0,   155,
     156,     0,     0,     0,     0,     0,   157,   158,   159,   165,
       0,     0,     0,     0,   166,   167,   168,   169,   170,   171,
     172,     0,   160,   161,   162,     0,     0,     0,   173,     0,
     174,   163,     0,     0,     0,     0,     0,   164,     0,     0,
       0,     0,     0,     0,     0,     0,   175,     0,     0,   165,
       0,     0,   176,   177,   166,   167,   168,   169,   170,   171,
     172,   645,     0,     0,     0,     0,     0,     0,   173,     0,
     174,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     178,     0,     0,     0,     0,     0,   175,   179,   180,     0,
       0,     0,   176,   177,     0,     0,     0,     0,   646,   647,
     648,   649,   650,   651,     0,     0,     0,     0,     0,   652,
       0,     0,     0,   653,     0,   654,     0,     0,     0,     0,
     178,     0,     0,     0,     0,     0,   655,   179,   180,   278,
       0,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,     0,
       0,     0,     0,     0,     0,    20,     0,   656,     0,   657,
       0,     0,     0,   658,     0,     0,     0,    21,    22,    23,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     659,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,    32,    33,
      34,   660,     0,     0,     0,   661,     0,   662,     0,     0,
       0,   663,     0,   664,    35,    36,    37,    38,    39,     0,
      40,    41,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,    44,    45,    46,    47,    20,     0,     0,     0,
       0,     0,     0,    48,    49,    50,    51,    52,    53,    54,
       0,     0,     0,     0,    55,    56,    57,     0,     0,     0,
       0,    21,    22,    23,     0,     0,     0,   458,   439,   459,
       0,     0,     0,     0,    58,     0,     0,     0,     0,    32,
      33,    34,     0,     0,     0,     0,     0,    59,     0,     0,
       0,     0,     0,  -351,     0,    35,    36,    37,    38,    39,
       0,    40,    41,    42,    43,    60,     0,     0,     0,     0,
       0,     0,     0,    44,    45,    46,    47,     0,     0,     0,
       0,     0,     0,     0,    48,    49,    50,    51,    52,    53,
      54,     0,     0,     0,     0,    55,    56,    57,     0,     0,
       0,     0,    21,    22,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   278,    60,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   278,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   278,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   278,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   278,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   278,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   278,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   376,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,     0,     0,     0,   278,   460,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   278,   463,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   278,   466,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   278,   470,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   278,   472,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   278,   556,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   278,     0,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   557,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,     0,
       0,     0,     0,   278,   558,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   278,   560,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   278,   561,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   278,   592,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   278,   609,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   278,   614,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   278,     0,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   620,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,     0,     0,     0,
       0,     0,   278,   621,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   278,   627,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   278,   636,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   278,   639,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,     0,   641,     0,   327,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     278,   454,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     278,     0,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     461,     0,   619,     0,     0,     0,     0,     0,     0,    73,
     329,     0,     0,     0,     0,     0,     0,     0,   330,     0,
     462,     0,     0,     0,     0,    47,     0,     0,     0,     0,
       0,     0,     0,     0,    73,     0,     0,     0,     0,     0,
     468,     0,     0,    74,     0,   331,     0,     0,     0,     0,
       0,    21,    22,    23,     0,     0,     0,     0,     0,     0,
     469,     0,     0,     0,    58,     0,   457,     0,    74,     0,
       0,     0,     0,   278,    75,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,     0,     0,   532,     0,     0,   471,    75,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    76,     0,     0,     0,     0,     0,   766,    77,
      78,    79,    80,    81,   -43,    82,    83,    84,     0,     0,
      85,    86,     0,    87,    88,    89,     0,    76,     0,     0,
      90,    91,    92,     0,    77,    78,    79,    80,    81,     0,
      82,    83,    84,   693,     0,    85,    86,     0,    87,    88,
      89,     0,     0,     0,     0,    90,    91,    92,     0,   709,
     710,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   693,     0,     0,   693,   278,
     474,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   750,
     753,   754,   755,     0,   693,     0,   709,     0,   693,   278,
     538,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   278,
       0,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   786,
     787,     0,   788,   789
};

static const yytype_int16 yycheck[] =
{
      12,    77,    75,    27,   224,    18,    29,     4,   485,    98,
     140,    87,     4,     4,   103,   235,   236,     4,     4,     4,
      21,   488,     4,     4,     5,     4,     5,     4,     5,     4,
     687,     4,   675,     4,    36,    60,    61,   503,     4,     5,
      60,     4,     5,     4,     4,     4,     4,   578,   696,   153,
       4,   699,   711,   157,     4,   132,   133,   134,   138,    61,
     133,   134,   719,   136,   137,    56,   143,    58,   138,    56,
     143,    58,    10,   732,   154,   152,   779,     0,    16,   155,
     156,   729,     4,     5,   154,    10,     4,   553,   791,   746,
     621,     4,   153,     4,    69,    10,   157,    50,    51,   790,
      61,    61,    37,   179,   180,    60,   182,   237,     4,   576,
     801,   153,   154,   138,   190,   592,     4,   153,   138,   155,
     586,   153,     4,   155,    60,   201,    32,    33,    34,     4,
      37,    60,   113,   106,   113,    37,   113,   108,    56,    57,
      58,    59,    37,    56,    57,    56,    57,   113,    60,   222,
     113,   153,   795,   153,   155,   155,    37,   148,   155,   150,
      37,   158,    39,   150,   641,   156,   158,   153,   244,   156,
     155,   247,   248,   155,   250,   251,   153,   150,   155,   255,
     256,   257,   258,   259,   207,   208,   262,   153,     4,   155,
     153,   113,   268,   269,   153,   153,   272,   273,   274,   153,
     150,   155,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   313,   314,   315,   357,   153,   305,
     306,   153,   150,   155,     4,     3,     4,   150,   153,   150,
     136,     3,     4,   139,   140,   141,    60,    37,   136,    37,
      37,   139,   140,   141,   136,    37,   329,   139,   140,   141,
      37,   136,    30,    31,   139,   140,   141,     4,    37,    37,
      38,    39,    73,    74,    75,    76,    77,    78,    79,    37,
     153,   354,   155,   356,    37,    53,    54,    55,    37,    37,
     168,   169,   170,    37,    62,   173,   174,   145,   146,   147,
      68,   153,    37,   155,    37,    73,    74,    75,    76,    77,
      78,    79,    80,    37,   142,     4,     4,    85,    86,    87,
      88,    89,    90,    91,     4,     4,     4,   340,     4,     4,
     550,    99,     4,   101,     3,   119,     4,     4,     4,     4,
     110,   111,   112,     4,     4,     4,   370,     4,    61,   117,
     154,    61,    16,    16,   155,   123,   124,   433,   154,   435,
     436,   437,    15,     4,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,   458,   151,     4,   461,   462,   155,     3,     4,
     158,   159,   468,   469,    61,    10,     4,     4,   474,     4,
       4,     4,    69,   426,    30,    31,    32,    33,    34,     4,
      77,     4,    37,    37,    60,    30,    31,    84,    37,    37,
      37,    37,    37,    38,    39,    37,    37,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    37,   104,    53,    54,
      55,    37,   153,   110,   111,   112,    37,    62,    37,    37,
      37,    37,   153,    68,   153,   531,   123,     4,    37,   153,
      10,    10,    10,    60,   154,    80,   153,    61,   154,    61,
      85,    86,    87,    88,    89,    90,    91,    37,   155,     4,
      37,   155,   155,   559,    99,   155,   101,     4,     4,    36,
       4,   567,     4,   582,     4,   571,     4,   520,   521,   155,
     153,   577,   117,   579,   155,   155,   155,   155,   123,   124,
      28,    29,    30,    31,    32,    33,    34,   155,   594,     3,
       4,   155,    69,   154,   154,     4,    10,     4,    37,     4,
      77,    37,   155,   622,     4,   611,   151,    84,   153,     4,
      60,   617,   155,   158,   159,   155,    30,    31,    16,   625,
      37,   153,     4,    37,    38,    39,   155,   104,     4,    16,
      16,    37,   108,   110,   111,   112,    97,     4,     4,    53,
      54,    55,   155,   155,   794,   155,   123,   155,    62,   154,
      99,    36,   655,    37,    68,   155,   153,   155,   808,    61,
      37,   811,    10,   155,    16,    37,    80,    38,    60,    37,
     155,    85,    86,    87,    88,    89,    90,    91,    37,    10,
     153,    37,   154,    79,   703,    99,   149,   101,   109,   154,
       3,     4,    61,   101,    10,    37,    10,    37,    16,    60,
     642,    37,    60,   117,    16,     4,    61,    37,   714,   123,
     124,    37,    37,    37,    37,    37,    37,    30,    31,    25,
      37,     4,    37,     4,    37,    38,    39,    40,    37,    37,
     672,    60,    37,    37,    37,    37,    37,   151,     4,   153,
      53,    54,    55,   108,   158,   159,    25,    36,     4,    62,
      37,   155,   155,    37,   155,    68,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    80,    37,   711,
      37,    61,    85,    86,    87,    88,    89,    90,    91,     4,
     155,   155,   155,     4,     4,   155,    99,   249,   101,   245,
     732,   155,     3,     4,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   672,   117,    16,   155,   220,   155,   155,
     123,   124,   155,   242,   155,   725,   155,   155,   155,    30,
      31,   155,   155,   155,   668,   782,    37,    38,    39,   715,
     442,   345,     3,     4,   498,   155,   760,   540,   151,   596,
      30,   114,    53,    54,    55,   158,   159,   246,   436,   730,
     565,    62,    -1,    -1,    -1,    -1,    -1,    68,    -1,    30,
      31,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    80,
      -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,    90,
      91,    -1,    53,    54,    55,    -1,    -1,    -1,    99,    -1,
     101,    62,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,    -1,    -1,    80,
      -1,    -1,   123,   124,    85,    86,    87,    88,    89,    90,
      91,     4,    -1,    -1,    -1,    -1,    -1,    -1,    99,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     151,    -1,    -1,    -1,    -1,    -1,   117,   158,   159,    -1,
      -1,    -1,   123,   124,    -1,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    56,    -1,    58,    -1,    -1,    -1,    -1,
     151,    -1,    -1,    -1,    -1,    -1,    69,   158,   159,    15,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,     4,    -1,   100,    -1,   102,
      -1,    -1,    -1,   106,    -1,    -1,    -1,   110,   111,   112,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     123,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    47,    48,
      49,   144,    -1,    -1,    -1,   148,    -1,   150,    -1,    -1,
      -1,   154,    -1,   156,    63,    64,    65,    66,    67,    -1,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,
      -1,   110,   111,   112,    -1,    -1,    -1,   153,    36,   155,
      -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,   136,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    63,    64,    65,    66,    67,
      -1,    69,    70,    71,    72,   154,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    92,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,
      -1,    -1,   110,   111,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   136,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,   154,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    15,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,   155,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    15,   155,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,   155,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,   155,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,   155,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,   155,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,   155,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    15,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,   155,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    15,   155,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,   155,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,   155,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,   155,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,   155,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,   155,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    15,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,   155,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    15,   155,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    15,   155,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    15,   155,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    15,   155,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,   155,    -1,     4,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,   153,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
     153,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,     4,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
     153,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,
     153,    -1,    -1,    38,    -1,   104,    -1,    -1,    -1,    -1,
      -1,   110,   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,
     153,    -1,    -1,    -1,   123,    -1,    36,    -1,    38,    -1,
      -1,    -1,    -1,    15,    69,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    37,    -1,    -1,   153,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   107,    -1,    -1,    -1,    -1,    -1,   153,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    -1,    -1,
     125,   126,    -1,   128,   129,   130,    -1,   107,    -1,    -1,
     135,   136,   137,    -1,   114,   115,   116,   117,   118,    -1,
     120,   121,   122,   664,    -1,   125,   126,    -1,   128,   129,
     130,    -1,    -1,    -1,    -1,   135,   136,   137,    -1,   680,
     681,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   696,    -1,    -1,   699,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,   720,
     721,   722,   723,    -1,   725,    -1,   727,    -1,   729,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    15,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,   770,
     771,    -1,   773,   774
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   132,   133,   134,   143,   152,   161,   175,   176,   165,
     166,   163,   164,   282,   283,   277,   278,     0,   177,   167,
       4,   110,   111,   112,   213,    60,   138,   286,   287,    60,
     279,   280,    47,    48,    49,    63,    64,    65,    66,    67,
      69,    70,    71,    72,    81,    82,    83,    84,    92,    93,
      94,    95,    96,    97,    98,   103,   104,   105,   123,   136,
     154,   178,   188,   190,   213,   215,   226,   227,   229,   231,
     269,   284,   285,     4,    38,    69,   107,   114,   115,   116,
     117,   118,   120,   121,   122,   125,   126,   128,   129,   130,
     135,   136,   137,   168,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   211,    37,    37,    37,     4,   136,   139,
     140,   141,   289,   290,    60,   287,   140,   141,   281,   290,
     280,    60,    60,    50,    51,    37,    37,     4,   162,    60,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,   179,    37,   191,    37,   153,   154,   212,   142,
       4,   162,     4,     3,     4,    30,    31,    37,    38,    39,
      53,    54,    55,    62,    68,    80,    85,    86,    87,    88,
      89,    90,    91,    99,   101,   117,   123,   124,   151,   158,
     159,   237,     4,     4,   172,     4,   171,   170,     4,     4,
       4,   237,     4,     3,     4,   173,     4,   174,     4,   119,
     235,   236,   235,     4,     4,     4,     4,    16,    16,    61,
     154,   289,    61,   154,   189,   270,     4,     4,     4,     4,
     180,     4,    69,   216,   217,   218,     4,     4,     4,   162,
     162,     4,   162,   155,   162,   228,   230,     4,   232,   232,
     182,   183,    37,   162,    37,   181,    60,    10,   153,   169,
      10,   153,   237,   237,   237,    37,    37,    37,    37,    37,
     238,    37,    37,   233,   234,   233,   233,   233,    37,    37,
     233,   233,    37,    37,    37,    37,   237,   237,    15,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,   153,    10,   153,
     237,   153,   153,     4,   153,    10,   153,   237,   153,   153,
       4,   153,   237,    10,    10,    10,    60,   290,   290,   154,
       4,   136,   139,   140,   141,    61,   154,     4,    61,    69,
      77,   104,   190,   246,     4,    61,   271,   153,   155,   155,
     177,   219,   162,    61,   153,   214,   153,   155,   155,   155,
     155,   155,   155,   155,   214,   155,   214,   153,   232,   155,
     155,   155,     4,     5,   113,   184,   182,   155,   237,   174,
     286,   237,   237,   167,   237,   237,   155,   237,   237,   237,
     237,   237,    37,     4,   237,    37,   237,   237,   237,   237,
     237,     4,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,     4,     4,     4,   237,   237,     3,
       4,     4,     4,   235,   235,   235,   292,   154,   154,     4,
     138,   154,   288,   247,   162,   251,   255,   272,     4,    36,
      37,   223,   220,   218,     4,   162,   162,   232,    37,     4,
       5,   113,   153,   155,   153,   155,    61,    36,   153,   155,
     155,   153,   153,   155,     4,   155,   155,     4,   153,   153,
     155,   153,   155,   155,    16,   155,   155,   155,   290,   141,
      60,   138,   154,    37,    40,   237,   259,   260,   257,    16,
     237,   261,   260,   237,   274,   153,     4,   158,   224,   225,
      16,   216,   155,   185,    37,     4,     5,   113,     4,   237,
     237,   237,   239,   155,   237,   237,     4,   237,   154,   293,
      16,   291,    73,    74,    75,    76,    77,    78,    79,   155,
     258,    37,    37,   259,    16,   108,   241,   189,    16,    97,
     262,   256,     4,   108,   275,     4,     4,   155,   225,    99,
     221,    36,   184,   187,    37,   155,   155,   155,   155,   153,
     155,   155,   155,    61,   290,   290,    37,    10,   155,   237,
      16,    37,    38,   242,    36,   241,    60,    37,   276,    37,
     273,   155,    10,   214,   155,   184,   186,   237,   154,   293,
      79,   237,   155,   237,    37,   149,   243,   109,   244,   189,
     237,   275,   237,   154,   235,   101,   222,   155,   184,   155,
      61,    10,    39,   259,   155,   237,   244,    37,   252,    61,
     155,   155,    10,   155,   237,    37,    16,   155,   145,   146,
     147,   245,   237,    60,   275,   235,   155,   237,   248,   155,
     253,   155,    60,   265,   259,     4,    41,    42,    43,    44,
      45,    46,    52,    56,    58,    69,   100,   102,   106,   123,
     144,   148,   150,   154,   156,   192,   193,   194,   197,   200,
     201,   203,   206,   207,   208,   213,     4,    61,    16,     4,
      37,    37,   162,    37,   204,    37,    37,    37,     4,    56,
      57,    58,    59,   193,   195,   199,    37,     4,    56,   156,
     194,   203,    61,    37,   212,   266,    25,   263,   106,   193,
     193,   205,   209,   235,    37,   202,     4,   196,   192,   198,
      37,    37,    37,    37,   157,   214,   199,    37,   199,    37,
     249,   235,    60,     4,   108,   240,   155,   155,   155,   207,
     155,   237,     4,   200,    21,   155,   155,   192,    56,    57,
     193,    56,    57,   193,   193,   193,   195,   155,   157,   199,
     263,   155,   207,    25,   264,    36,   153,   155,     4,   192,
      37,    37,   155,    37,    37,   155,   155,   155,   155,   240,
      61,     4,    10,    16,   210,     4,   193,   193,   193,   193,
     264,   267,   209,     4,   254,   155,   155,   155,   155,   155,
     210,   264,   214,   212,   155,   155,   155,   155,   250,   210,
     214,   268,   214
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   160,   161,   161,   161,   161,   161,   162,   164,   163,
     166,   165,   167,   167,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     169,   168,   168,   168,   170,   170,   170,   171,   171,   172,
     172,   173,   173,   173,   174,   174,   174,   176,   175,   177,
     177,   178,   178,   178,   178,   178,   178,   178,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   178,   178,   178,
     178,   179,   178,   178,   180,   178,   178,   178,   181,   178,
     178,   178,   178,   178,   183,   182,   184,   184,   184,   184,
     184,   184,   185,   184,   186,   184,   187,   184,   188,   189,
     189,   189,   190,   190,   191,   190,   192,   193,   193,   194,
     194,   194,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   196,   196,   197,   198,   198,   199,   199,   200,   200,
     200,   200,   200,   200,   201,   202,   201,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   204,   203,   205,
     203,   206,   206,   207,   207,   208,   208,   208,   208,   208,
     209,   210,   210,   211,   211,   211,   211,   211,   211,   211,
     211,   212,   212,   213,   213,   213,   213,   213,   214,   214,
     215,   216,   216,   217,   217,   219,   218,   220,   218,   221,
     222,   223,   223,   224,   224,   225,   225,   226,   227,   227,
     228,   228,   229,   230,   230,   231,   231,   232,   232,   232,
     234,   233,   236,   235,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   238,   239,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   240,   240,   241,   241,   242,   242,
     243,   243,   244,   244,   245,   245,   245,   245,   247,   248,
     249,   250,   246,   251,   252,   253,   254,   246,   255,   256,
     246,   257,   246,   258,   258,   258,   258,   258,   258,   258,
     258,   259,   259,   259,   260,   260,   260,   260,   261,   261,
     262,   262,   263,   263,   264,   264,   265,   266,   267,   268,
     265,   269,   270,   270,   272,   273,   271,   274,   275,   275,
     275,   276,   276,   278,   277,   279,   279,   280,   281,   283,
     282,   285,   284,   286,   286,   287,   287,   287,   288,   288,
     289,   289,   289,   289,   289,   290,   290,   290,   290,   291,
     290,   292,   290,   290,   290,   290,   290,   290,   290,   293,
     293
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     1,     0,     2,
       0,     2,     3,     0,     2,     4,     1,     1,     2,     1,
       4,     4,     3,     2,     4,     3,     4,     4,     4,     4,
       4,     2,     2,     2,     4,     4,     2,     2,     2,     2,
       0,     5,     2,     0,     3,     2,     0,     1,     3,     1,
       3,     0,     1,     3,     1,     2,     3,     0,     2,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     4,     4,     4,     8,     4,     1,     1,     1,
       4,     0,     5,     4,     0,     5,     4,     4,     0,     5,
       3,     3,     6,     4,     0,     2,     1,     3,     2,     1,
       3,     2,     0,     5,     0,     7,     0,     6,     4,     2,
       2,     0,     4,     2,     0,     7,     1,     1,     5,     1,
       4,     4,     1,     4,     4,     4,     7,     7,     7,     7,
       4,     1,     3,     4,     2,     1,     3,     1,     1,     2,
       3,     4,     4,     5,     1,     0,     5,     1,     2,     1,
       1,     4,     1,     4,     2,     4,     1,     0,     8,     0,
       5,     2,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     6,     6,     6,     1,     0,
       4,     1,     0,     3,     1,     0,     7,     0,     5,     3,
       3,     0,     3,     1,     2,     1,     2,     4,     4,     3,
       3,     1,     4,     3,     0,     1,     1,     0,     2,     3,
       0,     4,     0,     2,     2,     3,     4,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     3,     3,     4,
       1,     1,     2,     2,     2,     2,     4,     4,     4,     6,
       6,     6,     4,     0,     0,     8,     4,     1,     6,     6,
       6,     2,     2,     4,     3,     0,     4,     0,     4,     0,
       1,     0,     4,     0,     1,     1,     1,     0,     0,     0,
       0,     0,    19,     0,     0,     0,     0,    17,     0,     0,
       7,     0,     5,     1,     1,     1,     1,     1,     6,     1,
       3,     3,     0,     2,     3,     2,     6,    10,     2,     1,
       0,     1,     2,     0,     0,     3,     0,     0,     0,     0,
      11,     4,     0,     2,     0,     0,     6,     1,     0,     3,
       5,     0,     3,     0,     2,     1,     2,     4,     2,     0,
       2,     0,     5,     1,     2,     4,     5,     6,     1,     2,
       0,     2,     4,     4,     8,     1,     1,     3,     3,     0,
       9,     0,     7,     1,     3,     1,     3,     1,     3,     0,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8: /* $@1: %empty  */
#line 181 "ldgram.y"
                { ldlex_expression(); }
#line 2585 "ldgram.c"
    break;

  case 9: /* defsym_expr: $@1 assignment  */
#line 183 "ldgram.y"
                { ldlex_popstate(); }
#line 2591 "ldgram.c"
    break;

  case 10: /* $@2: %empty  */
#line 188 "ldgram.y"
                {
		  ldlex_mri_script ();
		  PUSH_ERROR (_("MRI style script"));
		}
#line 2600 "ldgram.c"
    break;

  case 11: /* mri_script_file: $@2 mri_script_lines  */
#line 193 "ldgram.y"
                {
		  ldlex_popstate ();
		  mri_draw_tree ();
		  POP_ERROR ();
		}
#line 2610 "ldgram.c"
    break;

  case 16: /* mri_script_command: NAME  */
#line 208 "ldgram.y"
                        {
			einfo(_("%F%P: unrecognised keyword in MRI style script '%s'\n"),(yyvsp[0].name));
			}
#line 2618 "ldgram.c"
    break;

  case 17: /* mri_script_command: LIST  */
#line 211 "ldgram.y"
                        {
			config.map_filename = "-";
			}
#line 2626 "ldgram.c"
    break;

  case 20: /* mri_script_command: PUBLIC NAME '=' exp  */
#line 217 "ldgram.y"
                        { mri_public((yyvsp[-2].name), (yyvsp[0].etree)); }
#line 2632 "ldgram.c"
    break;

  case 21: /* mri_script_command: PUBLIC NAME ',' exp  */
#line 219 "ldgram.y"
                        { mri_public((yyvsp[-2].name), (yyvsp[0].etree)); }
#line 2638 "ldgram.c"
    break;

  case 22: /* mri_script_command: PUBLIC NAME exp  */
#line 221 "ldgram.y"
                        { mri_public((yyvsp[-1].name), (yyvsp[0].etree)); }
#line 2644 "ldgram.c"
    break;

  case 23: /* mri_script_command: FORMAT NAME  */
#line 223 "ldgram.y"
                        { mri_format((yyvsp[0].name)); }
#line 2650 "ldgram.c"
    break;

  case 24: /* mri_script_command: SECT NAME ',' exp  */
#line 225 "ldgram.y"
                        { mri_output_section((yyvsp[-2].name), (yyvsp[0].etree));}
#line 2656 "ldgram.c"
    break;

  case 25: /* mri_script_command: SECT NAME exp  */
#line 227 "ldgram.y"
                        { mri_output_section((yyvsp[-1].name), (yyvsp[0].etree));}
#line 2662 "ldgram.c"
    break;

  case 26: /* mri_script_command: SECT NAME '=' exp  */
#line 229 "ldgram.y"
                        { mri_output_section((yyvsp[-2].name), (yyvsp[0].etree));}
#line 2668 "ldgram.c"
    break;

  case 27: /* mri_script_command: ALIGN_K NAME '=' exp  */
#line 231 "ldgram.y"
                        { mri_align((yyvsp[-2].name),(yyvsp[0].etree)); }
#line 2674 "ldgram.c"
    break;

  case 28: /* mri_script_command: ALIGN_K NAME ',' exp  */
#line 233 "ldgram.y"
                        { mri_align((yyvsp[-2].name),(yyvsp[0].etree)); }
#line 2680 "ldgram.c"
    break;

  case 29: /* mri_script_command: ALIGNMOD NAME '=' exp  */
#line 235 "ldgram.y"
                        { mri_alignmod((yyvsp[-2].name),(yyvsp[0].etree)); }
#line 2686 "ldgram.c"
    break;

  case 30: /* mri_script_command: ALIGNMOD NAME ',' exp  */
#line 237 "ldgram.y"
                        { mri_alignmod((yyvsp[-2].name),(yyvsp[0].etree)); }
#line 2692 "ldgram.c"
    break;

  case 33: /* mri_script_command: NAMEWORD NAME  */
#line 241 "ldgram.y"
                        { mri_name((yyvsp[0].name)); }
#line 2698 "ldgram.c"
    break;

  case 34: /* mri_script_command: ALIAS NAME ',' NAME  */
#line 243 "ldgram.y"
                        { mri_alias((yyvsp[-2].name),(yyvsp[0].name),0);}
#line 2704 "ldgram.c"
    break;

  case 35: /* mri_script_command: ALIAS NAME ',' INT  */
#line 245 "ldgram.y"
                        { mri_alias ((yyvsp[-2].name), 0, (int) (yyvsp[0].bigint).integer); }
#line 2710 "ldgram.c"
    break;

  case 36: /* mri_script_command: BASE exp  */
#line 247 "ldgram.y"
                        { mri_base((yyvsp[0].etree)); }
#line 2716 "ldgram.c"
    break;

  case 37: /* mri_script_command: TRUNCATE INT  */
#line 249 "ldgram.y"
                { mri_truncate ((unsigned int) (yyvsp[0].bigint).integer); }
#line 2722 "ldgram.c"
    break;

  case 40: /* $@3: %empty  */
#line 253 "ldgram.y"
                { ldfile_open_command_file ((yyvsp[0].name)); }
#line 2728 "ldgram.c"
    break;

  case 42: /* mri_script_command: START NAME  */
#line 256 "ldgram.y"
                { lang_add_entry ((yyvsp[0].name), false); }
#line 2734 "ldgram.c"
    break;

  case 44: /* ordernamelist: ordernamelist ',' NAME  */
#line 261 "ldgram.y"
                                             { mri_order((yyvsp[0].name)); }
#line 2740 "ldgram.c"
    break;

  case 45: /* ordernamelist: ordernamelist NAME  */
#line 262 "ldgram.y"
                                          { mri_order((yyvsp[0].name)); }
#line 2746 "ldgram.c"
    break;

  case 47: /* mri_load_name_list: NAME  */
#line 268 "ldgram.y"
                        { mri_load((yyvsp[0].name)); }
#line 2752 "ldgram.c"
    break;

  case 48: /* mri_load_name_list: mri_load_name_list ',' NAME  */
#line 269 "ldgram.y"
                                            { mri_load((yyvsp[0].name)); }
#line 2758 "ldgram.c"
    break;

  case 49: /* mri_abs_name_list: NAME  */
#line 274 "ldgram.y"
                        { mri_only_load((yyvsp[0].name)); }
#line 2764 "ldgram.c"
    break;

  case 50: /* mri_abs_name_list: mri_abs_name_list ',' NAME  */
#line 276 "ldgram.y"
                        { mri_only_load((yyvsp[0].name)); }
#line 2770 "ldgram.c"
    break;

  case 51: /* casesymlist: %empty  */
#line 280 "ldgram.y"
                      { (yyval.name) = NULL; }
#line 2776 "ldgram.c"
    break;

  case 54: /* extern_name_list: NAME  */
#line 287 "ldgram.y"
                        { ldlang_add_undef ((yyvsp[0].name), false); }
#line 2782 "ldgram.c"
    break;

  case 55: /* extern_name_list: extern_name_list NAME  */
#line 289 "ldgram.y"
                        { ldlang_add_undef ((yyvsp[0].name), false); }
#line 2788 "ldgram.c"
    break;

  case 56: /* extern_name_list: extern_name_list ',' NAME  */
#line 291 "ldgram.y"
                        { ldlang_add_undef ((yyvsp[0].name), false); }
#line 2794 "ldgram.c"
    break;

  case 57: /* $@4: %empty  */
#line 295 "ldgram.y"
        { ldlex_script (); }
#line 2800 "ldgram.c"
    break;

  case 58: /* script_file: $@4 ifile_list  */
#line 297 "ldgram.y"
        { ldlex_popstate (); }
#line 2806 "ldgram.c"
    break;

  case 71: /* ifile_p1: TARGET_K '(' NAME ')'  */
#line 318 "ldgram.y"
                { lang_add_target((yyvsp[-1].name)); }
#line 2812 "ldgram.c"
    break;

  case 72: /* ifile_p1: SEARCH_DIR '(' filename ')'  */
#line 320 "ldgram.y"
                { ldfile_add_library_path ((yyvsp[-1].name), false); }
#line 2818 "ldgram.c"
    break;

  case 73: /* ifile_p1: OUTPUT '(' filename ')'  */
#line 322 "ldgram.y"
                { lang_add_output((yyvsp[-1].name), 1); }
#line 2824 "ldgram.c"
    break;

  case 74: /* ifile_p1: OUTPUT_FORMAT '(' NAME ')'  */
#line 324 "ldgram.y"
                  { lang_add_output_format ((yyvsp[-1].name), (char *) NULL,
					    (char *) NULL, 1); }
#line 2831 "ldgram.c"
    break;

  case 75: /* ifile_p1: OUTPUT_FORMAT '(' NAME ',' NAME ',' NAME ')'  */
#line 327 "ldgram.y"
                  { lang_add_output_format ((yyvsp[-5].name), (yyvsp[-3].name), (yyvsp[-1].name), 1); }
#line 2837 "ldgram.c"
    break;

  case 76: /* ifile_p1: OUTPUT_ARCH '(' NAME ')'  */
#line 329 "ldgram.y"
                  { ldfile_set_output_arch ((yyvsp[-1].name), bfd_arch_unknown); }
#line 2843 "ldgram.c"
    break;

  case 77: /* ifile_p1: FORCE_COMMON_ALLOCATION  */
#line 331 "ldgram.y"
                { command_line.force_common_definition = true ; }
#line 2849 "ldgram.c"
    break;

  case 78: /* ifile_p1: FORCE_GROUP_ALLOCATION  */
#line 333 "ldgram.y"
                { command_line.force_group_allocation = true ; }
#line 2855 "ldgram.c"
    break;

  case 79: /* ifile_p1: INHIBIT_COMMON_ALLOCATION  */
#line 335 "ldgram.y"
                { link_info.inhibit_common_definition = true ; }
#line 2861 "ldgram.c"
    break;

  case 81: /* $@5: %empty  */
#line 338 "ldgram.y"
                  { lang_enter_group (); }
#line 2867 "ldgram.c"
    break;

  case 82: /* ifile_p1: GROUP $@5 '(' input_list ')'  */
#line 340 "ldgram.y"
                  { lang_leave_group (); }
#line 2873 "ldgram.c"
    break;

  case 83: /* ifile_p1: MAP '(' filename ')'  */
#line 342 "ldgram.y"
                { lang_add_map((yyvsp[-1].name)); }
#line 2879 "ldgram.c"
    break;

  case 84: /* $@6: %empty  */
#line 344 "ldgram.y"
                { ldfile_open_command_file ((yyvsp[0].name)); }
#line 2885 "ldgram.c"
    break;

  case 86: /* ifile_p1: NOCROSSREFS '(' nocrossref_list ')'  */
#line 347 "ldgram.y"
                {
		  lang_add_nocrossref ((yyvsp[-1].nocrossref));
		}
#line 2893 "ldgram.c"
    break;

  case 87: /* ifile_p1: NOCROSSREFS_TO '(' nocrossref_list ')'  */
#line 351 "ldgram.y"
                {
		  lang_add_nocrossref_to ((yyvsp[-1].nocrossref));
		}
#line 2901 "ldgram.c"
    break;

  case 88: /* $@7: %empty  */
#line 354 "ldgram.y"
                           { ldlex_expression (); }
#line 2907 "ldgram.c"
    break;

  case 89: /* ifile_p1: EXTERN '(' $@7 extern_name_list ')'  */
#line 355 "ldgram.y"
                        { ldlex_popstate (); }
#line 2913 "ldgram.c"
    break;

  case 90: /* ifile_p1: INSERT_K AFTER NAME  */
#line 357 "ldgram.y"
                { lang_add_insert ((yyvsp[0].name), 0); }
#line 2919 "ldgram.c"
    break;

  case 91: /* ifile_p1: INSERT_K BEFORE NAME  */
#line 359 "ldgram.y"
                { lang_add_insert ((yyvsp[0].name), 1); }
#line 2925 "ldgram.c"
    break;

  case 92: /* ifile_p1: REGION_ALIAS '(' NAME ',' NAME ')'  */
#line 361 "ldgram.y"
                { lang_memory_region_alias ((yyvsp[-3].name), (yyvsp[-1].name)); }
#line 2931 "ldgram.c"
    break;

  case 93: /* ifile_p1: LD_FEATURE '(' NAME ')'  */
#line 363 "ldgram.y"
                { lang_ld_feature ((yyvsp[-1].name)); }
#line 2937 "ldgram.c"
    break;

  case 94: /* $@8: %empty  */
#line 367 "ldgram.y"
                { ldlex_inputlist(); }
#line 2943 "ldgram.c"
    break;

  case 95: /* input_list: $@8 input_list1  */
#line 369 "ldgram.y"
                { ldlex_popstate(); }
#line 2949 "ldgram.c"
    break;

  case 96: /* input_list1: NAME  */
#line 373 "ldgram.y"
                { lang_add_input_file((yyvsp[0].name),lang_input_file_is_search_file_enum,
				 (char *)NULL); }
#line 2956 "ldgram.c"
    break;

  case 97: /* input_list1: input_list1 ',' NAME  */
#line 376 "ldgram.y"
                { lang_add_input_file((yyvsp[0].name),lang_input_file_is_search_file_enum,
				 (char *)NULL); }
#line 2963 "ldgram.c"
    break;

  case 98: /* input_list1: input_list1 NAME  */
#line 379 "ldgram.y"
                { lang_add_input_file((yyvsp[0].name),lang_input_file_is_search_file_enum,
				 (char *)NULL); }
#line 2970 "ldgram.c"
    break;

  case 99: /* input_list1: LNAME  */
#line 382 "ldgram.y"
                { lang_add_input_file((yyvsp[0].name),lang_input_file_is_l_enum,
				 (char *)NULL); }
#line 2977 "ldgram.c"
    break;

  case 100: /* input_list1: input_list1 ',' LNAME  */
#line 385 "ldgram.y"
                { lang_add_input_file((yyvsp[0].name),lang_input_file_is_l_enum,
				 (char *)NULL); }
#line 2984 "ldgram.c"
    break;

  case 101: /* input_list1: input_list1 LNAME  */
#line 388 "ldgram.y"
                { lang_add_input_file((yyvsp[0].name),lang_input_file_is_l_enum,
				 (char *)NULL); }
#line 2991 "ldgram.c"
    break;

  case 102: /* @9: %empty  */
#line 391 "ldgram.y"
                  { (yyval.integer) = input_flags.add_DT_NEEDED_for_regular;
		    input_flags.add_DT_NEEDED_for_regular = true; }
#line 2998 "ldgram.c"
    break;

  case 103: /* input_list1: AS_NEEDED '(' @9 input_list1 ')'  */
#line 394 "ldgram.y"
                  { input_flags.add_DT_NEEDED_for_regular = (yyvsp[-2].integer); }
#line 3004 "ldgram.c"
    break;

  case 104: /* @10: %empty  */
#line 396 "ldgram.y"
                  { (yyval.integer) = input_flags.add_DT_NEEDED_for_regular;
		    input_flags.add_DT_NEEDED_for_regular = true; }
#line 3011 "ldgram.c"
    break;

  case 105: /* input_list1: input_list1 ',' AS_NEEDED '(' @10 input_list1 ')'  */
#line 399 "ldgram.y"
                  { input_flags.add_DT_NEEDED_for_regular = (yyvsp[-2].integer); }
#line 3017 "ldgram.c"
    break;

  case 106: /* @11: %empty  */
#line 401 "ldgram.y"
                  { (yyval.integer) = input_flags.add_DT_NEEDED_for_regular;
		    input_flags.add_DT_NEEDED_for_regular = true; }
#line 3024 "ldgram.c"
    break;

  case 107: /* input_list1: input_list1 AS_NEEDED '(' @11 input_list1 ')'  */
#line 404 "ldgram.y"
                  { input_flags.add_DT_NEEDED_for_regular = (yyvsp[-2].integer); }
#line 3030 "ldgram.c"
    break;

  case 112: /* statement_anywhere: ENTRY '(' NAME ')'  */
#line 419 "ldgram.y"
                { lang_add_entry ((yyvsp[-1].name), false); }
#line 3036 "ldgram.c"
    break;

  case 114: /* $@12: %empty  */
#line 421 "ldgram.y"
                          {ldlex_expression ();}
#line 3042 "ldgram.c"
    break;

  case 115: /* statement_anywhere: ASSERT_K $@12 '(' exp ',' NAME ')'  */
#line 422 "ldgram.y"
                { ldlex_popstate ();
		  lang_add_assignment (exp_assert ((yyvsp[-3].etree), (yyvsp[-1].name))); }
#line 3049 "ldgram.c"
    break;

  case 116: /* wildcard_name: NAME  */
#line 428 "ldgram.y"
                        {
			  (yyval.cname) = (yyvsp[0].name);
			}
#line 3057 "ldgram.c"
    break;

  case 117: /* wildcard_maybe_exclude: wildcard_name  */
#line 435 "ldgram.y"
                        {
			  (yyval.wildcard).name = (yyvsp[0].cname);
			  (yyval.wildcard).sorted = none;
			  (yyval.wildcard).exclude_name_list = NULL;
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 3068 "ldgram.c"
    break;

  case 118: /* wildcard_maybe_exclude: EXCLUDE_FILE '(' exclude_name_list ')' wildcard_name  */
#line 442 "ldgram.y"
                        {
			  (yyval.wildcard).name = (yyvsp[0].cname);
			  (yyval.wildcard).sorted = none;
			  (yyval.wildcard).exclude_name_list = (yyvsp[-2].name_list);
			  (yyval.wildcard).section_flag_list = NULL;
			}
#line 3079 "ldgram.c"
    break;

  case 120: /* filename_spec: SORT_BY_NAME '(' wildcard_maybe_exclude ')'  */
#line 453 "ldgram.y"
                        {
			  (yyval.wildcard) = (yyvsp[-1].wildcard);
			  (yyval.wildcard).sorted = by_name;
			}
#line 3088 "ldgram.c"
    break;

  case 121: /* filename_spec: SORT_NONE '(' wildcard_maybe_exclude ')'  */
#line 458 "ldgram.y"
                        {
			  (yyval.wildcard) = (yyvsp[-1].wildcard);
			  (yyval.wildcard).sorted = by_none;
			}
#line 3097 "ldgram.c"
    break;

  case 123: /* section_name_spec: SORT_BY_NAME '(' wildcard_maybe_exclude ')'  */
#line 467 "ldgram.y"
                        {
			  (yyval.wildcard) = (yyvsp[-1].wildcard);
			  (yyval.wildcard).sorted = by_name;
			}
#line 3106 "ldgram.c"
    break;

  case 124: /* section_name_spec: SORT_BY_ALIGNMENT '(' wildcard_maybe_exclude ')'  */
#line 472 "ldgram.y"
                        {
			  (yyval.wildcard) = (yyvsp[-1].wildcard);
			  (yyval.wildcard).sorted = by_alignment;
			}
#line 3115 "ldgram.c"
    break;

  case 125: /* section_name_spec: SORT_NONE '(' wildcard_maybe_exclude ')'  */
#line 477 "ldgram.y"
                        {
			  (yyval.wildcard) = (yyvsp[-1].wildcard);
			  (yyval.wildcard).sorted = by_none;
			}
#line 3124 "ldgram.c"
    break;

  case 126: /* section_name_spec: SORT_BY_NAME '(' SORT_BY_ALIGNMENT '(' wildcard_maybe_exclude ')' ')'  */
#line 482 "ldgram.y"
                        {
			  (yyval.wildcard) = (yyvsp[-2].wildcard);
			  (yyval.wildcard).sorted = by_name_alignment;
			}
#line 3133 "ldgram.c"
    break;

  case 127: /* section_name_spec: SORT_BY_NAME '(' SORT_BY_NAME '(' wildcard_maybe_exclude ')' ')'  */
#line 487 "ldgram.y"
                        {
			  (yyval.wildcard) = (yyvsp[-2].wildcard);
			  (yyval.wildcard).sorted = by_name;
			}
#line 3142 "ldgram.c"
    break;

  case 128: /* section_name_spec: SORT_BY_ALIGNMENT '(' SORT_BY_NAME '(' wildcard_maybe_exclude ')' ')'  */
#line 492 "ldgram.y"
                        {
			  (yyval.wildcard) = (yyvsp[-2].wildcard);
			  (yyval.wildcard).sorted = by_alignment_name;
			}
#line 3151 "ldgram.c"
    break;

  case 129: /* section_name_spec: SORT_BY_ALIGNMENT '(' SORT_BY_ALIGNMENT '(' wildcard_maybe_exclude ')' ')'  */
#line 497 "ldgram.y"
                        {
			  (yyval.wildcard) = (yyvsp[-2].wildcard);
			  (yyval.wildcard).sorted = by_alignment;
			}
#line 3160 "ldgram.c"
    break;

  case 130: /* section_name_spec: SORT_BY_INIT_PRIORITY '(' wildcard_maybe_exclude ')'  */
#line 502 "ldgram.y"
                        {
			  (yyval.wildcard) = (yyvsp[-1].wildcard);
			  (yyval.wildcard).sorted = by_init_priority;
			}
#line 3169 "ldgram.c"
    break;

  case 131: /* sect_flag_list: NAME  */
#line 509 "ldgram.y"
                        {
			  struct flag_info_list *n;
			  n = ((struct flag_info_list *) xmalloc (sizeof *n));
			  if ((yyvsp[0].name)[0] == '!')
			    {
			      n->with = without_flags;
			      n->name = &(yyvsp[0].name)[1];
			    }
			  else
			    {
			      n->with = with_flags;
			      n->name = (yyvsp[0].name);
			    }
			  n->valid = false;
			  n->next = NULL;
			  (yyval.flag_info_list) = n;
			}
#line 3191 "ldgram.c"
    break;

  case 132: /* sect_flag_list: sect_flag_list '&' NAME  */
#line 527 "ldgram.y"
                        {
			  struct flag_info_list *n;
			  n = ((struct flag_info_list *) xmalloc (sizeof *n));
			  if ((yyvsp[0].name)[0] == '!')
			    {
			      n->with = without_flags;
			      n->name = &(yyvsp[0].name)[1];
			    }
			  else
			    {
			      n->with = with_flags;
			      n->name = (yyvsp[0].name);
			    }
			  n->valid = false;
			  n->next = (yyvsp[-2].flag_info_list);
			  (yyval.flag_info_list) = n;
			}
#line 3213 "ldgram.c"
    break;

  case 133: /* sect_flags: INPUT_SECTION_FLAGS '(' sect_flag_list ')'  */
#line 548 "ldgram.y"
                        {
			  struct flag_info *n;
			  n = ((struct flag_info *) xmalloc (sizeof *n));
			  n->flag_list = (yyvsp[-1].flag_info_list);
			  n->flags_initialized = false;
			  n->not_with_flags = 0;
			  n->only_with_flags = 0;
			  (yyval.flag_info) = n;
			}
#line 3227 "ldgram.c"
    break;

  case 134: /* exclude_name_list: exclude_name_list wildcard_name  */
#line 561 "ldgram.y"
                        {
			  struct name_list *tmp;
			  tmp = (struct name_list *) xmalloc (sizeof *tmp);
			  tmp->name = (yyvsp[0].cname);
			  tmp->next = (yyvsp[-1].name_list);
			  (yyval.name_list) = tmp;
			}
#line 3239 "ldgram.c"
    break;

  case 135: /* exclude_name_list: wildcard_name  */
#line 570 "ldgram.y"
                        {
			  struct name_list *tmp;
			  tmp = (struct name_list *) xmalloc (sizeof *tmp);
			  tmp->name = (yyvsp[0].cname);
			  tmp->next = NULL;
			  (yyval.name_list) = tmp;
			}
#line 3251 "ldgram.c"
    break;

  case 136: /* section_name_list: section_name_list opt_comma section_name_spec  */
#line 581 "ldgram.y"
                        {
			  struct wildcard_list *tmp;
			  tmp = (struct wildcard_list *) xmalloc (sizeof *tmp);
			  tmp->next = (yyvsp[-2].wildcard_list);
			  tmp->spec = (yyvsp[0].wildcard);
			  (yyval.wildcard_list) = tmp;
			}
#line 3263 "ldgram.c"
    break;

  case 137: /* section_name_list: section_name_spec  */
#line 590 "ldgram.y"
                        {
			  struct wildcard_list *tmp;
			  tmp = (struct wildcard_list *) xmalloc (sizeof *tmp);
			  tmp->next = NULL;
			  tmp->spec = (yyvsp[0].wildcard);
			  (yyval.wildcard_list) = tmp;
			}
#line 3275 "ldgram.c"
    break;

  case 138: /* input_section_spec_no_keep: NAME  */
#line 601 "ldgram.y"
                        {
			  struct wildcard_spec tmp;
			  tmp.name = (yyvsp[0].name);
			  tmp.exclude_name_list = NULL;
			  tmp.sorted = none;
			  tmp.section_flag_list = NULL;
			  lang_add_wild (&tmp, NULL, ldgram_had_keep);
			}
#line 3288 "ldgram.c"
    break;

  case 139: /* input_section_spec_no_keep: sect_flags NAME  */
#line 610 "ldgram.y"
                        {
			  struct wildcard_spec tmp;
			  tmp.name = (yyvsp[0].name);
			  tmp.exclude_name_list = NULL;
			  tmp.sorted = none;
			  tmp.section_flag_list = (yyvsp[-1].flag_info);
			  lang_add_wild (&tmp, NULL, ldgram_had_keep);
			}
#line 3301 "ldgram.c"
    break;

  case 140: /* input_section_spec_no_keep: '[' section_name_list ']'  */
#line 619 "ldgram.y"
                        {
			  lang_add_wild (NULL, (yyvsp[-1].wildcard_list), ldgram_had_keep);
			}
#line 3309 "ldgram.c"
    break;

  case 141: /* input_section_spec_no_keep: sect_flags '[' section_name_list ']'  */
#line 623 "ldgram.y"
                        {
			  struct wildcard_spec tmp;
			  tmp.name = NULL;
			  tmp.exclude_name_list = NULL;
			  tmp.sorted = none;
			  tmp.section_flag_list = (yyvsp[-3].flag_info);
			  lang_add_wild (&tmp, (yyvsp[-1].wildcard_list), ldgram_had_keep);
			}
#line 3322 "ldgram.c"
    break;

  case 142: /* input_section_spec_no_keep: filename_spec '(' section_name_list ')'  */
#line 632 "ldgram.y"
                        {
			  lang_add_wild (&(yyvsp[-3].wildcard), (yyvsp[-1].wildcard_list), ldgram_had_keep);
			}
#line 3330 "ldgram.c"
    break;

  case 143: /* input_section_spec_no_keep: sect_flags filename_spec '(' section_name_list ')'  */
#line 636 "ldgram.y"
                        {
			  (yyvsp[-3].wildcard).section_flag_list = (yyvsp[-4].flag_info);
			  lang_add_wild (&(yyvsp[-3].wildcard), (yyvsp[-1].wildcard_list), ldgram_had_keep);
			}
#line 3339 "ldgram.c"
    break;

  case 145: /* $@13: %empty  */
#line 645 "ldgram.y"
                        { ldgram_had_keep = true; }
#line 3345 "ldgram.c"
    break;

  case 146: /* input_section_spec: KEEP '(' $@13 input_section_spec_no_keep ')'  */
#line 647 "ldgram.y"
                        { ldgram_had_keep = false; }
#line 3351 "ldgram.c"
    break;

  case 149: /* statement: CREATE_OBJECT_SYMBOLS  */
#line 654 "ldgram.y"
                {
		  lang_add_attribute (lang_object_symbols_statement_enum);
		}
#line 3359 "ldgram.c"
    break;

  case 150: /* statement: CONSTRUCTORS  */
#line 658 "ldgram.y"
                {
		  lang_add_attribute (lang_constructors_statement_enum);
		}
#line 3367 "ldgram.c"
    break;

  case 151: /* statement: SORT_BY_NAME '(' CONSTRUCTORS ')'  */
#line 662 "ldgram.y"
                {
		  constructors_sorted = true;
		  lang_add_attribute (lang_constructors_statement_enum);
		}
#line 3376 "ldgram.c"
    break;

  case 153: /* statement: length '(' mustbe_exp ')'  */
#line 668 "ldgram.y"
                {
		  lang_add_data ((int) (yyvsp[-3].integer), (yyvsp[-1].etree));
		}
#line 3384 "ldgram.c"
    break;

  case 154: /* statement: ASCIZ NAME  */
#line 672 "ldgram.y"
                {
		  lang_add_string ((yyvsp[0].name));
		}
#line 3392 "ldgram.c"
    break;

  case 155: /* statement: FILL '(' fill_exp ')'  */
#line 676 "ldgram.y"
                {
		  lang_add_fill ((yyvsp[-1].fill));
		}
#line 3400 "ldgram.c"
    break;

  case 156: /* statement: LINKER_VERSION  */
#line 680 "ldgram.y"
                {
		  lang_add_version_string ();
		}
#line 3408 "ldgram.c"
    break;

  case 157: /* $@14: %empty  */
#line 684 "ldgram.y"
                { ldlex_expression (); }
#line 3414 "ldgram.c"
    break;

  case 158: /* statement: ASSERT_K $@14 '(' exp ',' NAME ')' separator  */
#line 686 "ldgram.y"
                {
		  ldlex_popstate ();
		  lang_add_assignment (exp_assert ((yyvsp[-4].etree), (yyvsp[-2].name)));
		}
#line 3423 "ldgram.c"
    break;

  case 159: /* $@15: %empty  */
#line 691 "ldgram.y"
                {
		  ldfile_open_command_file ((yyvsp[0].name));
		}
#line 3431 "ldgram.c"
    break;

  case 165: /* length: QUAD  */
#line 709 "ldgram.y"
                        { (yyval.integer) = (yyvsp[0].token); }
#line 3437 "ldgram.c"
    break;

  case 166: /* length: SQUAD  */
#line 711 "ldgram.y"
                        { (yyval.integer) = (yyvsp[0].token); }
#line 3443 "ldgram.c"
    break;

  case 167: /* length: LONG  */
#line 713 "ldgram.y"
                        { (yyval.integer) = (yyvsp[0].token); }
#line 3449 "ldgram.c"
    break;

  case 168: /* length: SHORT  */
#line 715 "ldgram.y"
                        { (yyval.integer) = (yyvsp[0].token); }
#line 3455 "ldgram.c"
    break;

  case 169: /* length: BYTE  */
#line 717 "ldgram.y"
                        { (yyval.integer) = (yyvsp[0].token); }
#line 3461 "ldgram.c"
    break;

  case 170: /* fill_exp: mustbe_exp  */
#line 722 "ldgram.y"
                {
		  (yyval.fill) = exp_get_fill ((yyvsp[0].etree), 0, _("fill value"));
		}
#line 3469 "ldgram.c"
    break;

  case 171: /* fill_opt: '=' fill_exp  */
#line 729 "ldgram.y"
                { (yyval.fill) = (yyvsp[0].fill); }
#line 3475 "ldgram.c"
    break;

  case 172: /* fill_opt: %empty  */
#line 730 "ldgram.y"
                { (yyval.fill) = (fill_type *) 0; }
#line 3481 "ldgram.c"
    break;

  case 173: /* assign_op: PLUSEQ  */
#line 735 "ldgram.y"
                        { (yyval.token) = '+'; }
#line 3487 "ldgram.c"
    break;

  case 174: /* assign_op: MINUSEQ  */
#line 737 "ldgram.y"
                        { (yyval.token) = '-'; }
#line 3493 "ldgram.c"
    break;

  case 175: /* assign_op: MULTEQ  */
#line 739 "ldgram.y"
                        { (yyval.token) = '*'; }
#line 3499 "ldgram.c"
    break;

  case 176: /* assign_op: DIVEQ  */
#line 741 "ldgram.y"
                        { (yyval.token) = '/'; }
#line 3505 "ldgram.c"
    break;

  case 177: /* assign_op: LSHIFTEQ  */
#line 743 "ldgram.y"
                        { (yyval.token) = LSHIFT; }
#line 3511 "ldgram.c"
    break;

  case 178: /* assign_op: RSHIFTEQ  */
#line 745 "ldgram.y"
                        { (yyval.token) = RSHIFT; }
#line 3517 "ldgram.c"
    break;

  case 179: /* assign_op: ANDEQ  */
#line 747 "ldgram.y"
                        { (yyval.token) = '&'; }
#line 3523 "ldgram.c"
    break;

  case 180: /* assign_op: OREQ  */
#line 749 "ldgram.y"
                        { (yyval.token) = '|'; }
#line 3529 "ldgram.c"
    break;

  case 183: /* assignment: NAME '=' mustbe_exp  */
#line 759 "ldgram.y"
                {
		  lang_add_assignment (exp_assign ((yyvsp[-2].name), (yyvsp[0].etree), false));
		}
#line 3537 "ldgram.c"
    break;

  case 184: /* assignment: NAME assign_op mustbe_exp  */
#line 763 "ldgram.y"
                {
		  lang_add_assignment (exp_assign ((yyvsp[-2].name),
						   exp_binop ((yyvsp[-1].token),
							      exp_nameop (NAME,
									  (yyvsp[-2].name)),
							      (yyvsp[0].etree)), false));
		}
#line 3549 "ldgram.c"
    break;

  case 185: /* assignment: HIDDEN '(' NAME '=' mustbe_exp ')'  */
#line 771 "ldgram.y"
                {
		  lang_add_assignment (exp_assign ((yyvsp[-3].name), (yyvsp[-1].etree), true));
		}
#line 3557 "ldgram.c"
    break;

  case 186: /* assignment: PROVIDE '(' NAME '=' mustbe_exp ')'  */
#line 775 "ldgram.y"
                {
		  lang_add_assignment (exp_provide ((yyvsp[-3].name), (yyvsp[-1].etree), false));
		}
#line 3565 "ldgram.c"
    break;

  case 187: /* assignment: PROVIDE_HIDDEN '(' NAME '=' mustbe_exp ')'  */
#line 779 "ldgram.y"
                {
		  lang_add_assignment (exp_provide ((yyvsp[-3].name), (yyvsp[-1].etree), true));
		}
#line 3573 "ldgram.c"
    break;

  case 195: /* $@16: %empty  */
#line 802 "ldgram.y"
                { region = lang_memory_region_lookup ((yyvsp[0].name), true); }
#line 3579 "ldgram.c"
    break;

  case 196: /* memory_spec: NAME $@16 attributes_opt ':' origin_spec opt_comma length_spec  */
#line 805 "ldgram.y"
                {}
#line 3585 "ldgram.c"
    break;

  case 197: /* $@17: %empty  */
#line 807 "ldgram.y"
                { ldfile_open_command_file ((yyvsp[0].name)); }
#line 3591 "ldgram.c"
    break;

  case 199: /* origin_spec: ORIGIN '=' mustbe_exp  */
#line 813 "ldgram.y"
                {
		  region->origin_exp = (yyvsp[0].etree);
		}
#line 3599 "ldgram.c"
    break;

  case 200: /* length_spec: LENGTH '=' mustbe_exp  */
#line 820 "ldgram.y"
                {
		  if (yychar == NAME)
		    {
		      yyclearin;
		      ldlex_backup ();
		    }
		  region->length_exp = (yyvsp[0].etree);
		}
#line 3612 "ldgram.c"
    break;

  case 201: /* attributes_opt: %empty  */
#line 832 "ldgram.y"
                  { /* dummy action to avoid bison 1.25 error message */ }
#line 3618 "ldgram.c"
    break;

  case 205: /* attributes_string: NAME  */
#line 843 "ldgram.y"
                  { lang_set_flags (region, (yyvsp[0].name), 0); }
#line 3624 "ldgram.c"
    break;

  case 206: /* attributes_string: '!' NAME  */
#line 845 "ldgram.y"
                  { lang_set_flags (region, (yyvsp[0].name), 1); }
#line 3630 "ldgram.c"
    break;

  case 207: /* startup: STARTUP '(' filename ')'  */
#line 850 "ldgram.y"
                { lang_startup((yyvsp[-1].name)); }
#line 3636 "ldgram.c"
    break;

  case 209: /* high_level_library: HLL '(' ')'  */
#line 856 "ldgram.y"
                        { ldemul_hll((char *)NULL); }
#line 3642 "ldgram.c"
    break;

  case 210: /* high_level_library_NAME_list: high_level_library_NAME_list opt_comma filename  */
#line 861 "ldgram.y"
                        { ldemul_hll((yyvsp[0].name)); }
#line 3648 "ldgram.c"
    break;

  case 211: /* high_level_library_NAME_list: filename  */
#line 863 "ldgram.y"
                        { ldemul_hll((yyvsp[0].name)); }
#line 3654 "ldgram.c"
    break;

  case 213: /* low_level_library_NAME_list: low_level_library_NAME_list opt_comma filename  */
#line 872 "ldgram.y"
                        { ldemul_syslib((yyvsp[0].name)); }
#line 3660 "ldgram.c"
    break;

  case 215: /* floating_point_support: FLOAT  */
#line 878 "ldgram.y"
                        { lang_float(true); }
#line 3666 "ldgram.c"
    break;

  case 216: /* floating_point_support: NOFLOAT  */
#line 880 "ldgram.y"
                        { lang_float(false); }
#line 3672 "ldgram.c"
    break;

  case 217: /* nocrossref_list: %empty  */
#line 885 "ldgram.y"
                {
		  (yyval.nocrossref) = NULL;
		}
#line 3680 "ldgram.c"
    break;

  case 218: /* nocrossref_list: NAME nocrossref_list  */
#line 889 "ldgram.y"
                {
		  struct lang_nocrossref *n;

		  n = (struct lang_nocrossref *) xmalloc (sizeof *n);
		  n->name = (yyvsp[-1].name);
		  n->next = (yyvsp[0].nocrossref);
		  (yyval.nocrossref) = n;
		}
#line 3693 "ldgram.c"
    break;

  case 219: /* nocrossref_list: NAME ',' nocrossref_list  */
#line 898 "ldgram.y"
                {
		  struct lang_nocrossref *n;

		  n = (struct lang_nocrossref *) xmalloc (sizeof *n);
		  n->name = (yyvsp[-2].name);
		  n->next = (yyvsp[0].nocrossref);
		  (yyval.nocrossref) = n;
		}
#line 3706 "ldgram.c"
    break;

  case 220: /* $@18: %empty  */
#line 908 "ldgram.y"
                        { ldlex_script (); }
#line 3712 "ldgram.c"
    break;

  case 221: /* paren_script_name: $@18 '(' NAME ')'  */
#line 910 "ldgram.y"
                        { ldlex_popstate (); (yyval.name) = (yyvsp[-1].name); }
#line 3718 "ldgram.c"
    break;

  case 222: /* $@19: %empty  */
#line 912 "ldgram.y"
                        { ldlex_expression (); }
#line 3724 "ldgram.c"
    break;

  case 223: /* mustbe_exp: $@19 exp  */
#line 914 "ldgram.y"
                        { ldlex_popstate (); (yyval.etree) = (yyvsp[0].etree); }
#line 3730 "ldgram.c"
    break;

  case 224: /* exp: '-' exp  */
#line 919 "ldgram.y"
                        { (yyval.etree) = exp_unop ('-', (yyvsp[0].etree)); }
#line 3736 "ldgram.c"
    break;

  case 225: /* exp: '(' exp ')'  */
#line 921 "ldgram.y"
                        { (yyval.etree) = (yyvsp[-1].etree); }
#line 3742 "ldgram.c"
    break;

  case 226: /* exp: NEXT '(' exp ')'  */
#line 923 "ldgram.y"
                        { (yyval.etree) = exp_unop ((int) (yyvsp[-3].integer),(yyvsp[-1].etree)); }
#line 3748 "ldgram.c"
    break;

  case 227: /* exp: '!' exp  */
#line 925 "ldgram.y"
                        { (yyval.etree) = exp_unop ('!', (yyvsp[0].etree)); }
#line 3754 "ldgram.c"
    break;

  case 228: /* exp: '+' exp  */
#line 927 "ldgram.y"
                        { (yyval.etree) = (yyvsp[0].etree); }
#line 3760 "ldgram.c"
    break;

  case 229: /* exp: '~' exp  */
#line 929 "ldgram.y"
                        { (yyval.etree) = exp_unop ('~', (yyvsp[0].etree));}
#line 3766 "ldgram.c"
    break;

  case 230: /* exp: exp '*' exp  */
#line 932 "ldgram.y"
                        { (yyval.etree) = exp_binop ('*', (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3772 "ldgram.c"
    break;

  case 231: /* exp: exp '/' exp  */
#line 934 "ldgram.y"
                        { (yyval.etree) = exp_binop ('/', (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3778 "ldgram.c"
    break;

  case 232: /* exp: exp '%' exp  */
#line 936 "ldgram.y"
                        { (yyval.etree) = exp_binop ('%', (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3784 "ldgram.c"
    break;

  case 233: /* exp: exp '+' exp  */
#line 938 "ldgram.y"
                        { (yyval.etree) = exp_binop ('+', (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3790 "ldgram.c"
    break;

  case 234: /* exp: exp '-' exp  */
#line 940 "ldgram.y"
                        { (yyval.etree) = exp_binop ('-' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3796 "ldgram.c"
    break;

  case 235: /* exp: exp LSHIFT exp  */
#line 942 "ldgram.y"
                        { (yyval.etree) = exp_binop (LSHIFT , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3802 "ldgram.c"
    break;

  case 236: /* exp: exp RSHIFT exp  */
#line 944 "ldgram.y"
                        { (yyval.etree) = exp_binop (RSHIFT , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3808 "ldgram.c"
    break;

  case 237: /* exp: exp EQ exp  */
#line 946 "ldgram.y"
                        { (yyval.etree) = exp_binop (EQ , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3814 "ldgram.c"
    break;

  case 238: /* exp: exp NE exp  */
#line 948 "ldgram.y"
                        { (yyval.etree) = exp_binop (NE , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3820 "ldgram.c"
    break;

  case 239: /* exp: exp LE exp  */
#line 950 "ldgram.y"
                        { (yyval.etree) = exp_binop (LE , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3826 "ldgram.c"
    break;

  case 240: /* exp: exp GE exp  */
#line 952 "ldgram.y"
                        { (yyval.etree) = exp_binop (GE , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3832 "ldgram.c"
    break;

  case 241: /* exp: exp '<' exp  */
#line 954 "ldgram.y"
                        { (yyval.etree) = exp_binop ('<' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3838 "ldgram.c"
    break;

  case 242: /* exp: exp '>' exp  */
#line 956 "ldgram.y"
                        { (yyval.etree) = exp_binop ('>' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3844 "ldgram.c"
    break;

  case 243: /* exp: exp '&' exp  */
#line 958 "ldgram.y"
                        { (yyval.etree) = exp_binop ('&' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3850 "ldgram.c"
    break;

  case 244: /* exp: exp '^' exp  */
#line 960 "ldgram.y"
                        { (yyval.etree) = exp_binop ('^' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3856 "ldgram.c"
    break;

  case 245: /* exp: exp '|' exp  */
#line 962 "ldgram.y"
                        { (yyval.etree) = exp_binop ('|' , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3862 "ldgram.c"
    break;

  case 246: /* exp: exp '?' exp ':' exp  */
#line 964 "ldgram.y"
                        { (yyval.etree) = exp_trinop ('?' , (yyvsp[-4].etree), (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3868 "ldgram.c"
    break;

  case 247: /* exp: exp ANDAND exp  */
#line 966 "ldgram.y"
                        { (yyval.etree) = exp_binop (ANDAND , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3874 "ldgram.c"
    break;

  case 248: /* exp: exp OROR exp  */
#line 968 "ldgram.y"
                        { (yyval.etree) = exp_binop (OROR , (yyvsp[-2].etree), (yyvsp[0].etree)); }
#line 3880 "ldgram.c"
    break;

  case 249: /* exp: DEFINED '(' NAME ')'  */
#line 970 "ldgram.y"
                        { (yyval.etree) = exp_nameop (DEFINED, (yyvsp[-1].name)); }
#line 3886 "ldgram.c"
    break;

  case 250: /* exp: INT  */
#line 972 "ldgram.y"
                        { (yyval.etree) = exp_bigintop ((yyvsp[0].bigint).integer, (yyvsp[0].bigint).str); }
#line 3892 "ldgram.c"
    break;

  case 251: /* exp: SIZEOF_HEADERS  */
#line 974 "ldgram.y"
                        { (yyval.etree) = exp_nameop (SIZEOF_HEADERS,0); }
#line 3898 "ldgram.c"
    break;

  case 252: /* exp: ALIGNOF paren_script_name  */
#line 977 "ldgram.y"
                        { (yyval.etree) = exp_nameop (ALIGNOF, (yyvsp[0].name)); }
#line 3904 "ldgram.c"
    break;

  case 253: /* exp: SIZEOF paren_script_name  */
#line 979 "ldgram.y"
                        { (yyval.etree) = exp_nameop (SIZEOF, (yyvsp[0].name)); }
#line 3910 "ldgram.c"
    break;

  case 254: /* exp: ADDR paren_script_name  */
#line 981 "ldgram.y"
                        { (yyval.etree) = exp_nameop (ADDR, (yyvsp[0].name)); }
#line 3916 "ldgram.c"
    break;

  case 255: /* exp: LOADADDR paren_script_name  */
#line 983 "ldgram.y"
                        { (yyval.etree) = exp_nameop (LOADADDR, (yyvsp[0].name)); }
#line 3922 "ldgram.c"
    break;

  case 256: /* exp: CONSTANT '(' NAME ')'  */
#line 985 "ldgram.y"
                        { (yyval.etree) = exp_nameop (CONSTANT,(yyvsp[-1].name)); }
#line 3928 "ldgram.c"
    break;

  case 257: /* exp: ABSOLUTE '(' exp ')'  */
#line 987 "ldgram.y"
                        { (yyval.etree) = exp_unop (ABSOLUTE, (yyvsp[-1].etree)); }
#line 3934 "ldgram.c"
    break;

  case 258: /* exp: ALIGN_K '(' exp ')'  */
#line 989 "ldgram.y"
                        { (yyval.etree) = exp_unop (ALIGN_K,(yyvsp[-1].etree)); }
#line 3940 "ldgram.c"
    break;

  case 259: /* exp: ALIGN_K '(' exp ',' exp ')'  */
#line 991 "ldgram.y"
                        { (yyval.etree) = exp_binop (ALIGN_K,(yyvsp[-3].etree),(yyvsp[-1].etree)); }
#line 3946 "ldgram.c"
    break;

  case 260: /* exp: DATA_SEGMENT_ALIGN '(' exp ',' exp ')'  */
#line 993 "ldgram.y"
                        { (yyval.etree) = exp_binop (DATA_SEGMENT_ALIGN, (yyvsp[-3].etree), (yyvsp[-1].etree)); }
#line 3952 "ldgram.c"
    break;

  case 261: /* exp: DATA_SEGMENT_RELRO_END '(' exp ',' exp ')'  */
#line 995 "ldgram.y"
                        { (yyval.etree) = exp_binop (DATA_SEGMENT_RELRO_END, (yyvsp[-1].etree), (yyvsp[-3].etree)); }
#line 3958 "ldgram.c"
    break;

  case 262: /* exp: DATA_SEGMENT_END '(' exp ')'  */
#line 997 "ldgram.y"
                        { (yyval.etree) = exp_unop (DATA_SEGMENT_END, (yyvsp[-1].etree)); }
#line 3964 "ldgram.c"
    break;

  case 263: /* $@20: %empty  */
#line 998 "ldgram.y"
                              { ldlex_script (); }
#line 3970 "ldgram.c"
    break;

  case 264: /* $@21: %empty  */
#line 999 "ldgram.y"
                        { ldlex_popstate (); }
#line 3976 "ldgram.c"
    break;

  case 265: /* exp: SEGMENT_START $@20 '(' NAME $@21 ',' exp ')'  */
#line 1000 "ldgram.y"
                        { /* The operands to the expression node are
			     placed in the opposite order from the way
			     in which they appear in the script as
			     that allows us to reuse more code in
			     fold_binary.  */
			  (yyval.etree) = exp_binop (SEGMENT_START,
					  (yyvsp[-1].etree),
					  exp_nameop (NAME, (yyvsp[-4].name))); }
#line 3989 "ldgram.c"
    break;

  case 266: /* exp: BLOCK '(' exp ')'  */
#line 1009 "ldgram.y"
                        { (yyval.etree) = exp_unop (ALIGN_K,(yyvsp[-1].etree)); }
#line 3995 "ldgram.c"
    break;

  case 267: /* exp: NAME  */
#line 1011 "ldgram.y"
                        { (yyval.etree) = exp_nameop (NAME,(yyvsp[0].name)); }
#line 4001 "ldgram.c"
    break;

  case 268: /* exp: MAX_K '(' exp ',' exp ')'  */
#line 1013 "ldgram.y"
                        { (yyval.etree) = exp_binop (MAX_K, (yyvsp[-3].etree), (yyvsp[-1].etree) ); }
#line 4007 "ldgram.c"
    break;

  case 269: /* exp: MIN_K '(' exp ',' exp ')'  */
#line 1015 "ldgram.y"
                        { (yyval.etree) = exp_binop (MIN_K, (yyvsp[-3].etree), (yyvsp[-1].etree) ); }
#line 4013 "ldgram.c"
    break;

  case 270: /* exp: ASSERT_K '(' exp ',' NAME ')'  */
#line 1017 "ldgram.y"
                        { (yyval.etree) = exp_assert ((yyvsp[-3].etree), (yyvsp[-1].name)); }
#line 4019 "ldgram.c"
    break;

  case 271: /* exp: ORIGIN paren_script_name  */
#line 1019 "ldgram.y"
                        { (yyval.etree) = exp_nameop (ORIGIN, (yyvsp[0].name)); }
#line 4025 "ldgram.c"
    break;

  case 272: /* exp: LENGTH paren_script_name  */
#line 1021 "ldgram.y"
                        { (yyval.etree) = exp_nameop (LENGTH, (yyvsp[0].name)); }
#line 4031 "ldgram.c"
    break;

  case 273: /* exp: LOG2CEIL '(' exp ')'  */
#line 1023 "ldgram.y"
                        { (yyval.etree) = exp_unop (LOG2CEIL, (yyvsp[-1].etree)); }
#line 4037 "ldgram.c"
    break;

  case 274: /* memspec_at_opt: AT '>' NAME  */
#line 1028 "ldgram.y"
                            { (yyval.name) = (yyvsp[0].name); }
#line 4043 "ldgram.c"
    break;

  case 275: /* memspec_at_opt: %empty  */
#line 1029 "ldgram.y"
                { (yyval.name) = 0; }
#line 4049 "ldgram.c"
    break;

  case 276: /* opt_at: AT '(' exp ')'  */
#line 1033 "ldgram.y"
                               { (yyval.etree) = (yyvsp[-1].etree); }
#line 4055 "ldgram.c"
    break;

  case 277: /* opt_at: %empty  */
#line 1034 "ldgram.y"
                { (yyval.etree) = 0; }
#line 4061 "ldgram.c"
    break;

  case 278: /* opt_align: ALIGN_K '(' exp ')'  */
#line 1038 "ldgram.y"
                                    { (yyval.etree) = (yyvsp[-1].etree); }
#line 4067 "ldgram.c"
    break;

  case 279: /* opt_align: %empty  */
#line 1039 "ldgram.y"
                { (yyval.etree) = 0; }
#line 4073 "ldgram.c"
    break;

  case 280: /* opt_align_with_input: ALIGN_WITH_INPUT  */
#line 1043 "ldgram.y"
                                 { (yyval.token) = ALIGN_WITH_INPUT; }
#line 4079 "ldgram.c"
    break;

  case 281: /* opt_align_with_input: %empty  */
#line 1044 "ldgram.y"
                { (yyval.token) = 0; }
#line 4085 "ldgram.c"
    break;

  case 282: /* opt_subalign: SUBALIGN '(' exp ')'  */
#line 1048 "ldgram.y"
                                     { (yyval.etree) = (yyvsp[-1].etree); }
#line 4091 "ldgram.c"
    break;

  case 283: /* opt_subalign: %empty  */
#line 1049 "ldgram.y"
                { (yyval.etree) = 0; }
#line 4097 "ldgram.c"
    break;

  case 284: /* sect_constraint: ONLY_IF_RO  */
#line 1053 "ldgram.y"
                           { (yyval.token) = ONLY_IF_RO; }
#line 4103 "ldgram.c"
    break;

  case 285: /* sect_constraint: ONLY_IF_RW  */
#line 1054 "ldgram.y"
                           { (yyval.token) = ONLY_IF_RW; }
#line 4109 "ldgram.c"
    break;

  case 286: /* sect_constraint: SPECIAL  */
#line 1055 "ldgram.y"
                        { (yyval.token) = SPECIAL; }
#line 4115 "ldgram.c"
    break;

  case 287: /* sect_constraint: %empty  */
#line 1056 "ldgram.y"
                { (yyval.token) = 0; }
#line 4121 "ldgram.c"
    break;

  case 288: /* $@22: %empty  */
#line 1060 "ldgram.y"
                        { ldlex_expression(); }
#line 4127 "ldgram.c"
    break;

  case 289: /* $@23: %empty  */
#line 1067 "ldgram.y"
                        {
			  ldlex_popstate ();
			  ldlex_wild ();
			  lang_enter_output_section_statement ((yyvsp[-7].name), (yyvsp[-5].etree), sectype,
					sectype_value, (yyvsp[-3].etree), (yyvsp[-1].etree), (yyvsp[-4].etree), (yyvsp[0].token), (yyvsp[-2].token));
			}
#line 4138 "ldgram.c"
    break;

  case 290: /* $@24: %empty  */
#line 1076 "ldgram.y"
                        { ldlex_popstate (); }
#line 4144 "ldgram.c"
    break;

  case 291: /* $@25: %empty  */
#line 1078 "ldgram.y"
                        {
			  /* fill_opt may have switched the lexer into
			     expression state, and back again, but in
			     order to find the end of the fill
			     expression the parser must look ahead one
			     token.  If it is a NAME, throw it away as
			     it will have been lexed in the wrong
			     state.  */
			  if (yychar == NAME)
			    {
			      yyclearin;
			      ldlex_backup ();
			    }
			  lang_leave_output_section_statement ((yyvsp[0].fill), (yyvsp[-3].name),
							       (yyvsp[-1].section_phdr), (yyvsp[-2].name));
			}
#line 4165 "ldgram.c"
    break;

  case 293: /* $@26: %empty  */
#line 1096 "ldgram.y"
                        { ldlex_expression (); }
#line 4171 "ldgram.c"
    break;

  case 294: /* $@27: %empty  */
#line 1098 "ldgram.y"
                        { ldlex_popstate (); }
#line 4177 "ldgram.c"
    break;

  case 295: /* $@28: %empty  */
#line 1100 "ldgram.y"
                        {
			  lang_enter_overlay ((yyvsp[-5].etree), (yyvsp[-2].etree));
			}
#line 4185 "ldgram.c"
    break;

  case 296: /* $@29: %empty  */
#line 1106 "ldgram.y"
                        {
			  if (yychar == NAME)
			    {
			      yyclearin;
			      ldlex_backup ();
			    }
			  lang_leave_overlay ((yyvsp[-10].etree), (int) (yyvsp[-11].integer),
					      (yyvsp[0].fill), (yyvsp[-3].name), (yyvsp[-1].section_phdr), (yyvsp[-2].name));
			}
#line 4199 "ldgram.c"
    break;

  case 298: /* $@30: %empty  */
#line 1121 "ldgram.y"
                        { ldlex_expression (); }
#line 4205 "ldgram.c"
    break;

  case 299: /* $@31: %empty  */
#line 1123 "ldgram.y"
                        {
			  ldlex_popstate ();
			  lang_add_assignment (exp_assign (".", (yyvsp[0].etree), false));
			}
#line 4214 "ldgram.c"
    break;

  case 301: /* $@32: %empty  */
#line 1129 "ldgram.y"
                        {
			  ldfile_open_command_file ((yyvsp[0].name));
			}
#line 4222 "ldgram.c"
    break;

  case 303: /* type: NOLOAD  */
#line 1136 "ldgram.y"
                   { sectype = noload_section; }
#line 4228 "ldgram.c"
    break;

  case 304: /* type: DSECT  */
#line 1137 "ldgram.y"
                   { sectype = noalloc_section; }
#line 4234 "ldgram.c"
    break;

  case 305: /* type: COPY  */
#line 1138 "ldgram.y"
                   { sectype = noalloc_section; }
#line 4240 "ldgram.c"
    break;

  case 306: /* type: INFO  */
#line 1139 "ldgram.y"
                   { sectype = noalloc_section; }
#line 4246 "ldgram.c"
    break;

  case 307: /* type: OVERLAY  */
#line 1140 "ldgram.y"
                   { sectype = noalloc_section; }
#line 4252 "ldgram.c"
    break;

  case 308: /* type: READONLY '(' TYPE '=' exp ')'  */
#line 1141 "ldgram.y"
                                         { sectype = typed_readonly_section; sectype_value = (yyvsp[-1].etree); }
#line 4258 "ldgram.c"
    break;

  case 309: /* type: READONLY  */
#line 1142 "ldgram.y"
                    { sectype = readonly_section; }
#line 4264 "ldgram.c"
    break;

  case 310: /* type: TYPE '=' exp  */
#line 1143 "ldgram.y"
                        { sectype = type_section; sectype_value = (yyvsp[0].etree); }
#line 4270 "ldgram.c"
    break;

  case 312: /* atype: %empty  */
#line 1148 "ldgram.y"
                            { sectype = normal_section; }
#line 4276 "ldgram.c"
    break;

  case 313: /* atype: '(' ')'  */
#line 1149 "ldgram.y"
                        { sectype = normal_section; }
#line 4282 "ldgram.c"
    break;

  case 314: /* opt_exp_with_type: exp atype ':'  */
#line 1153 "ldgram.y"
                                        { (yyval.etree) = (yyvsp[-2].etree); }
#line 4288 "ldgram.c"
    break;

  case 315: /* opt_exp_with_type: atype ':'  */
#line 1154 "ldgram.y"
                                        { (yyval.etree) = (etree_type *)NULL;  }
#line 4294 "ldgram.c"
    break;

  case 316: /* opt_exp_with_type: BIND '(' exp ')' atype ':'  */
#line 1159 "ldgram.y"
                                           { (yyval.etree) = (yyvsp[-3].etree); }
#line 4300 "ldgram.c"
    break;

  case 317: /* opt_exp_with_type: BIND '(' exp ')' BLOCK '(' exp ')' atype ':'  */
#line 1161 "ldgram.y"
                { (yyval.etree) = (yyvsp[-7].etree); }
#line 4306 "ldgram.c"
    break;

  case 318: /* opt_exp_without_type: exp ':'  */
#line 1165 "ldgram.y"
                                { (yyval.etree) = (yyvsp[-1].etree); }
#line 4312 "ldgram.c"
    break;

  case 319: /* opt_exp_without_type: ':'  */
#line 1166 "ldgram.y"
                                { (yyval.etree) = (etree_type *) NULL;  }
#line 4318 "ldgram.c"
    break;

  case 320: /* opt_nocrossrefs: %empty  */
#line 1171 "ldgram.y"
                        { (yyval.integer) = 0; }
#line 4324 "ldgram.c"
    break;

  case 321: /* opt_nocrossrefs: NOCROSSREFS  */
#line 1173 "ldgram.y"
                        { (yyval.integer) = 1; }
#line 4330 "ldgram.c"
    break;

  case 322: /* memspec_opt: '>' NAME  */
#line 1178 "ldgram.y"
                { (yyval.name) = (yyvsp[0].name); }
#line 4336 "ldgram.c"
    break;

  case 323: /* memspec_opt: %empty  */
#line 1179 "ldgram.y"
                { (yyval.name) = DEFAULT_MEMORY_REGION; }
#line 4342 "ldgram.c"
    break;

  case 324: /* phdr_opt: %empty  */
#line 1184 "ldgram.y"
                {
		  (yyval.section_phdr) = NULL;
		}
#line 4350 "ldgram.c"
    break;

  case 325: /* phdr_opt: phdr_opt ':' NAME  */
#line 1188 "ldgram.y"
                {
		  struct lang_output_section_phdr_list *n;

		  n = ((struct lang_output_section_phdr_list *)
		       xmalloc (sizeof *n));
		  n->name = (yyvsp[0].name);
		  n->used = false;
		  n->next = (yyvsp[-2].section_phdr);
		  (yyval.section_phdr) = n;
		}
#line 4365 "ldgram.c"
    break;

  case 327: /* $@33: %empty  */
#line 1204 "ldgram.y"
                        {
			  ldlex_wild ();
			  lang_enter_overlay_section ((yyvsp[0].name));
			}
#line 4374 "ldgram.c"
    break;

  case 328: /* $@34: %empty  */
#line 1211 "ldgram.y"
                        { ldlex_popstate (); }
#line 4380 "ldgram.c"
    break;

  case 329: /* $@35: %empty  */
#line 1213 "ldgram.y"
                        {
			  if (yychar == NAME)
			    {
			      yyclearin;
			      ldlex_backup ();
			    }
			  lang_leave_overlay_section ((yyvsp[0].fill), (yyvsp[-1].section_phdr));
			}
#line 4393 "ldgram.c"
    break;

  case 334: /* $@36: %empty  */
#line 1234 "ldgram.y"
                     { ldlex_expression (); }
#line 4399 "ldgram.c"
    break;

  case 335: /* $@37: %empty  */
#line 1235 "ldgram.y"
                                            { ldlex_popstate (); }
#line 4405 "ldgram.c"
    break;

  case 336: /* phdr: NAME $@36 phdr_type phdr_qualifiers $@37 ';'  */
#line 1237 "ldgram.y"
                {
		  lang_new_phdr ((yyvsp[-5].name), (yyvsp[-3].etree), (yyvsp[-2].phdr).filehdr, (yyvsp[-2].phdr).phdrs, (yyvsp[-2].phdr).at,
				 (yyvsp[-2].phdr).flags);
		}
#line 4414 "ldgram.c"
    break;

  case 337: /* phdr_type: exp  */
#line 1245 "ldgram.y"
                {
		  (yyval.etree) = (yyvsp[0].etree);

		  if ((yyvsp[0].etree)->type.node_class == etree_name
		      && (yyvsp[0].etree)->type.node_code == NAME)
		    {
		      const char *s;
		      unsigned int i;
		      static const char * const phdr_types[] =
			{
			  "PT_NULL", "PT_LOAD", "PT_DYNAMIC",
			  "PT_INTERP", "PT_NOTE", "PT_SHLIB",
			  "PT_PHDR", "PT_TLS"
			};

		      s = (yyvsp[0].etree)->name.name;
		      for (i = 0;
			   i < sizeof phdr_types / sizeof phdr_types[0];
			   i++)
			if (strcmp (s, phdr_types[i]) == 0)
			  {
			    (yyval.etree) = exp_intop (i);
			    break;
			  }
		      if (i == sizeof phdr_types / sizeof phdr_types[0])
			{
			  if (strcmp (s, "PT_GNU_EH_FRAME") == 0)
			    (yyval.etree) = exp_intop (0x6474e550);
			  else if (strcmp (s, "PT_GNU_STACK") == 0)
			    (yyval.etree) = exp_intop (0x6474e551);
			  else if (strcmp (s, "PT_GNU_RELRO") == 0)
			    (yyval.etree) = exp_intop (0x6474e552);
			  else if (strcmp (s, "PT_GNU_PROPERTY") == 0)
			    (yyval.etree) = exp_intop (0x6474e553);
			  else
			    {
			      einfo (_("\
%X%P:%pS: unknown phdr type `%s' (try integer literal)\n"),
				     NULL, s);
			      (yyval.etree) = exp_intop (0);
			    }
			}
		    }
		}
#line 4463 "ldgram.c"
    break;

  case 338: /* phdr_qualifiers: %empty  */
#line 1293 "ldgram.y"
                {
		  memset (&(yyval.phdr), 0, sizeof (struct phdr_info));
		}
#line 4471 "ldgram.c"
    break;

  case 339: /* phdr_qualifiers: NAME phdr_val phdr_qualifiers  */
#line 1297 "ldgram.y"
                {
		  (yyval.phdr) = (yyvsp[0].phdr);
		  if (strcmp ((yyvsp[-2].name), "FILEHDR") == 0 && (yyvsp[-1].etree) == NULL)
		    (yyval.phdr).filehdr = true;
		  else if (strcmp ((yyvsp[-2].name), "PHDRS") == 0 && (yyvsp[-1].etree) == NULL)
		    (yyval.phdr).phdrs = true;
		  else if (strcmp ((yyvsp[-2].name), "FLAGS") == 0 && (yyvsp[-1].etree) != NULL)
		    (yyval.phdr).flags = (yyvsp[-1].etree);
		  else
		    einfo (_("%X%P:%pS: PHDRS syntax error at `%s'\n"),
			   NULL, (yyvsp[-2].name));
		}
#line 4488 "ldgram.c"
    break;

  case 340: /* phdr_qualifiers: AT '(' exp ')' phdr_qualifiers  */
#line 1310 "ldgram.y"
                {
		  (yyval.phdr) = (yyvsp[0].phdr);
		  (yyval.phdr).at = (yyvsp[-2].etree);
		}
#line 4497 "ldgram.c"
    break;

  case 341: /* phdr_val: %empty  */
#line 1318 "ldgram.y"
                {
		  (yyval.etree) = NULL;
		}
#line 4505 "ldgram.c"
    break;

  case 342: /* phdr_val: '(' exp ')'  */
#line 1322 "ldgram.y"
                {
		  (yyval.etree) = (yyvsp[-1].etree);
		}
#line 4513 "ldgram.c"
    break;

  case 343: /* $@38: %empty  */
#line 1328 "ldgram.y"
                {
		  ldlex_version_file ();
		  PUSH_ERROR (_("dynamic list"));
		}
#line 4522 "ldgram.c"
    break;

  case 344: /* dynamic_list_file: $@38 dynamic_list_nodes  */
#line 1333 "ldgram.y"
                {
		  ldlex_popstate ();
		  POP_ERROR ();
		}
#line 4531 "ldgram.c"
    break;

  case 348: /* dynamic_list_tag: vers_defns ';'  */
#line 1350 "ldgram.y"
                {
		  lang_append_dynamic_list (current_dynamic_list_p, (yyvsp[-1].versyms));
		}
#line 4539 "ldgram.c"
    break;

  case 349: /* $@39: %empty  */
#line 1358 "ldgram.y"
                {
		  ldlex_version_file ();
		  PUSH_ERROR (_("VERSION script"));
		}
#line 4548 "ldgram.c"
    break;

  case 350: /* version_script_file: $@39 vers_nodes  */
#line 1363 "ldgram.y"
                {
		  ldlex_popstate ();
		  POP_ERROR ();
		}
#line 4557 "ldgram.c"
    break;

  case 351: /* $@40: %empty  */
#line 1372 "ldgram.y"
                {
		  ldlex_version_script ();
		}
#line 4565 "ldgram.c"
    break;

  case 352: /* version: $@40 VERSIONK '{' vers_nodes '}'  */
#line 1376 "ldgram.y"
                {
		  ldlex_popstate ();
		}
#line 4573 "ldgram.c"
    break;

  case 355: /* vers_node: '{' vers_tag '}' ';'  */
#line 1388 "ldgram.y"
                {
		  lang_register_vers_node (NULL, (yyvsp[-2].versnode), NULL);
		}
#line 4581 "ldgram.c"
    break;

  case 356: /* vers_node: VERS_TAG '{' vers_tag '}' ';'  */
#line 1392 "ldgram.y"
                {
		  lang_register_vers_node ((yyvsp[-4].name), (yyvsp[-2].versnode), NULL);
		}
#line 4589 "ldgram.c"
    break;

  case 357: /* vers_node: VERS_TAG '{' vers_tag '}' verdep ';'  */
#line 1396 "ldgram.y"
                {
		  lang_register_vers_node ((yyvsp[-5].name), (yyvsp[-3].versnode), (yyvsp[-1].deflist));
		}
#line 4597 "ldgram.c"
    break;

  case 358: /* verdep: VERS_TAG  */
#line 1403 "ldgram.y"
                {
		  (yyval.deflist) = lang_add_vers_depend (NULL, (yyvsp[0].name));
		}
#line 4605 "ldgram.c"
    break;

  case 359: /* verdep: verdep VERS_TAG  */
#line 1407 "ldgram.y"
                {
		  (yyval.deflist) = lang_add_vers_depend ((yyvsp[-1].deflist), (yyvsp[0].name));
		}
#line 4613 "ldgram.c"
    break;

  case 360: /* vers_tag: %empty  */
#line 1414 "ldgram.y"
                {
		  (yyval.versnode) = lang_new_vers_node (NULL, NULL);
		}
#line 4621 "ldgram.c"
    break;

  case 361: /* vers_tag: vers_defns ';'  */
#line 1418 "ldgram.y"
                {
		  (yyval.versnode) = lang_new_vers_node ((yyvsp[-1].versyms), NULL);
		}
#line 4629 "ldgram.c"
    break;

  case 362: /* vers_tag: GLOBAL ':' vers_defns ';'  */
#line 1422 "ldgram.y"
                {
		  (yyval.versnode) = lang_new_vers_node ((yyvsp[-1].versyms), NULL);
		}
#line 4637 "ldgram.c"
    break;

  case 363: /* vers_tag: LOCAL ':' vers_defns ';'  */
#line 1426 "ldgram.y"
                {
		  (yyval.versnode) = lang_new_vers_node (NULL, (yyvsp[-1].versyms));
		}
#line 4645 "ldgram.c"
    break;

  case 364: /* vers_tag: GLOBAL ':' vers_defns ';' LOCAL ':' vers_defns ';'  */
#line 1430 "ldgram.y"
                {
		  (yyval.versnode) = lang_new_vers_node ((yyvsp[-5].versyms), (yyvsp[-1].versyms));
		}
#line 4653 "ldgram.c"
    break;

  case 365: /* vers_defns: VERS_IDENTIFIER  */
#line 1437 "ldgram.y"
                {
		  (yyval.versyms) = lang_new_vers_pattern (NULL, (yyvsp[0].name), ldgram_vers_current_lang, false);
		}
#line 4661 "ldgram.c"
    break;

  case 366: /* vers_defns: NAME  */
#line 1441 "ldgram.y"
                {
		  (yyval.versyms) = lang_new_vers_pattern (NULL, (yyvsp[0].name), ldgram_vers_current_lang, true);
		}
#line 4669 "ldgram.c"
    break;

  case 367: /* vers_defns: vers_defns ';' VERS_IDENTIFIER  */
#line 1445 "ldgram.y"
                {
		  (yyval.versyms) = lang_new_vers_pattern ((yyvsp[-2].versyms), (yyvsp[0].name), ldgram_vers_current_lang, false);
		}
#line 4677 "ldgram.c"
    break;

  case 368: /* vers_defns: vers_defns ';' NAME  */
#line 1449 "ldgram.y"
                {
		  (yyval.versyms) = lang_new_vers_pattern ((yyvsp[-2].versyms), (yyvsp[0].name), ldgram_vers_current_lang, true);
		}
#line 4685 "ldgram.c"
    break;

  case 369: /* @41: %empty  */
#line 1453 "ldgram.y"
                        {
			  (yyval.name) = ldgram_vers_current_lang;
			  ldgram_vers_current_lang = (yyvsp[-1].name);
			}
#line 4694 "ldgram.c"
    break;

  case 370: /* vers_defns: vers_defns ';' EXTERN NAME '{' @41 vers_defns opt_semicolon '}'  */
#line 1458 "ldgram.y"
                        {
			  struct bfd_elf_version_expr *pat;
			  for (pat = (yyvsp[-2].versyms); pat->next != NULL; pat = pat->next);
			  pat->next = (yyvsp[-8].versyms);
			  (yyval.versyms) = (yyvsp[-2].versyms);
			  ldgram_vers_current_lang = (yyvsp[-3].name);
			}
#line 4706 "ldgram.c"
    break;

  case 371: /* @42: %empty  */
#line 1466 "ldgram.y"
                        {
			  (yyval.name) = ldgram_vers_current_lang;
			  ldgram_vers_current_lang = (yyvsp[-1].name);
			}
#line 4715 "ldgram.c"
    break;

  case 372: /* vers_defns: EXTERN NAME '{' @42 vers_defns opt_semicolon '}'  */
#line 1471 "ldgram.y"
                        {
			  (yyval.versyms) = (yyvsp[-2].versyms);
			  ldgram_vers_current_lang = (yyvsp[-3].name);
			}
#line 4724 "ldgram.c"
    break;

  case 373: /* vers_defns: GLOBAL  */
#line 1476 "ldgram.y"
                {
		  (yyval.versyms) = lang_new_vers_pattern (NULL, "global", ldgram_vers_current_lang, false);
		}
#line 4732 "ldgram.c"
    break;

  case 374: /* vers_defns: vers_defns ';' GLOBAL  */
#line 1480 "ldgram.y"
                {
		  (yyval.versyms) = lang_new_vers_pattern ((yyvsp[-2].versyms), "global", ldgram_vers_current_lang, false);
		}
#line 4740 "ldgram.c"
    break;

  case 375: /* vers_defns: LOCAL  */
#line 1484 "ldgram.y"
                {
		  (yyval.versyms) = lang_new_vers_pattern (NULL, "local", ldgram_vers_current_lang, false);
		}
#line 4748 "ldgram.c"
    break;

  case 376: /* vers_defns: vers_defns ';' LOCAL  */
#line 1488 "ldgram.y"
                {
		  (yyval.versyms) = lang_new_vers_pattern ((yyvsp[-2].versyms), "local", ldgram_vers_current_lang, false);
		}
#line 4756 "ldgram.c"
    break;

  case 377: /* vers_defns: EXTERN  */
#line 1492 "ldgram.y"
                {
		  (yyval.versyms) = lang_new_vers_pattern (NULL, "extern", ldgram_vers_current_lang, false);
		}
#line 4764 "ldgram.c"
    break;

  case 378: /* vers_defns: vers_defns ';' EXTERN  */
#line 1496 "ldgram.y"
                {
		  (yyval.versyms) = lang_new_vers_pattern ((yyvsp[-2].versyms), "extern", ldgram_vers_current_lang, false);
		}
#line 4772 "ldgram.c"
    break;


#line 4776 "ldgram.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1506 "ldgram.y"

void
yyerror(arg)
     const char *arg;
{
  if (ldfile_assumed_script)
    einfo (_("%P:%s: file format not recognized; treating as linker script\n"),
	   ldlex_filename ());
  if (error_index > 0 && error_index < ERROR_NAME_MAX)
    einfo (_("%F%P:%pS: %s in %s\n"), NULL, arg, error_names[error_index - 1]);
  else
    einfo ("%F%P:%pS: %s\n", NULL, arg);
}
