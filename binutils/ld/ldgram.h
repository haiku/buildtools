/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 370 "ldgram.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LDGRAM_H_INCLUDED  */
