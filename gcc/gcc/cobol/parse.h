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

#ifndef YY_YY_COBOL_PARSE_H_INCLUDED
# define YY_YY_COBOL_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 30 "parse.y"

  #include "config.h"
  #include <fstream>  // Before cobol-system because it uses poisoned functions
  #include "cobol-system.h"
  #include "coretypes.h"
  #include "../../libgcobol/io.h"
  #include "../../libgcobol/ec.h"
  #include "tree.h"

#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

  enum radix_t {
    decimal_e = 10,
    hexadecimal_e = 16,
    boolean_e = 2,
  };

  enum accept_func_t {
    accept_e,
    accept_done_e,
    accept_command_line_e,
    accept_envar_e,
  };

  class literal_t {
    size_t isym;
  public:
    char prefix[3];
    size_t len;
    char *data;

    bool empty() const { return data == NULL; }
    size_t isymbol() const { return isym; }
    const char * symbol_name() const {
      return isym? cbl_field_of(symbol_at(isym))->name : "";
    }

    literal_t&
    set( size_t len, char *data, const char prefix[] ) {
      set_prefix(prefix, strlen(prefix));
      set_data(len, data);
      return *this;
    }

    literal_t&
    set( const cbl_field_t * field ) {
      assert(field->has_attr(constant_e));
      assert(is_literal(field));

      set_prefix( "", 0 );
      set_data( field->data.capacity,
                const_cast<char*>(field->data.initial),
                field_index(field) );
      return *this;
    }
    literal_t&
    set_data( size_t len, char *data, size_t isym = 0 ) {
      this->isym = isym;
      this->len = len;
      this->data = data;
      if( this->prefix[0] == 'Z' ) {
        this->data = new char[++this->len];
        auto p = std::copy(data, data + len, this->data);
        *p = '\0';
      }
      return *this;
    }
    literal_t&
    set_prefix( const char *input, size_t len ) {
      assert(len < sizeof(prefix));
      std::fill(prefix, prefix + sizeof(prefix), '\0');
      std::transform(input, input + len, prefix, toupper);
      return *this;
    }
    bool
    compatible_prefix( const literal_t& that ) const {
      if( prefix[0] != that.prefix[0] ) {
        return prefix[0] != 'N' && that.prefix[0] != 'N';
      }
      return true;
    }
  };

  struct acrc_t { // Abbreviated combined relation condition
    cbl_refer_t *term;
    relop_t op;
    bool invert;
    acrc_t& init( cbl_refer_t *term = NULL,
                  relop_t op = relop_t(-1),
                  bool invert = false )
    {
      this->term = term;
      this->op = op;
      this->invert = invert;
      return *this;
    }
    static acrc_t make( cbl_refer_t *term = NULL,
                        relop_t op = relop_t(-1),
                        bool invert = false )
    {
      acrc_t output;
      return output.init( term, op, invert );
    }
    relop_t relop_from( relop_t ante_op ) const {
      assert(ante_op != -1);
      return op != -1? op : ante_op;
    }
    bool is_relation_condition() const { return term && term->field; }
  };
  typedef std::list<acrc_t> acrcs_t;

  enum data_category_t { data_category_none,
                         data_category_all,
                         data_alphabetic_e,
                         data_alphanumeric_e,
                         data_alphanumeric_edited_e,
                         data_boolean_e,
                         data_data_pointer_e,
                         data_function_pointer_e,
                         data_msg_tag_e,
                         data_dbcs_e,
                         data_egcs_e,
                         data_national_e,
                         data_national_edited_e,
                         data_numeric_e,
                         data_numeric_edited_e,
                         data_object_referenc_e,
                         data_program_pointer_e,
                       };

  const char * data_category_str( data_category_t category );

  typedef std::map<data_category_t, struct cbl_refer_t*> category_map_t;

  struct substitution_t {
    enum subst_fl_t { subst_all_e, subst_first_e = 'F', subst_last_e = 'L' };
    bool anycase;
    subst_fl_t first_last;
    cbl_refer_t *orig, *replacement;

    substitution_t& init( bool anycase, char first_last,
                            cbl_refer_t *orig, cbl_refer_t *replacement ) {
      this->anycase = anycase;
      switch(first_last) {
      case 'F': this->first_last = subst_first_e; break;
      case 'L': this->first_last = subst_last_e;  break;
      default:
        this->first_last = subst_all_e;
        break;
      }
      this->orig = orig;
      this->replacement = replacement;
      return *this;
    }
  };
  typedef std::list<substitution_t> substitutions_t;

  struct init_statement_t {
    bool to_value;
    data_category_t category;
    category_map_t replacement;

    explicit init_statement_t( const category_map_t& replacement )
      : to_value(false)
      , category(data_category_none)
      , replacement(replacement)

    {}

    explicit init_statement_t( bool to_value = false )
      : to_value(to_value)
      , category(data_category_none)
      , replacement(category_map_t())
    {}

  };

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
  static data_category_t
  data_category_of( const cbl_refer_t& refer );

  static REAL_VALUE_TYPE
  numstr2i( const char input[], radix_t radix );

  struct cbl_field_t;
  static inline cbl_field_t *
  new_literal( const char initial[], enum radix_t radix );
#pragma GCC diagnostic pop

  enum select_clause_t {
    access_clause_e        = 0x0001,
    alt_key_clause_e       = 0x0002,
    assign_clause_e        = 0x0004,
    collating_clause_e     = 0x0008,
    file_status_clause_e   = 0x0010,
    lock_mode_clause_e     = 0x0020,
    organization_clause_e  = 0x0040,
    padding_clause_e       = 0x0080,
    record_delim_clause_e  = 0x0100,
    record_key_clause_e    = 0x0200,
    relative_key_clause_e  = 0x0400,
    reserve_clause_e       = 0x0800,
    sharing_clause_e       = 0x1000,
  };

  struct symbol_elem_t;
  struct symbol_elem_t * symbols_begin( size_t first );
  struct symbol_elem_t * symbols_end();

  void field_done();

  template <typename E>
  struct Elem_list_t {
    std::list<E> elems;
    Elem_list_t() {}
    explicit Elem_list_t( E elem ) {
      elems.push_back(elem);
    }
    Elem_list_t * push_back( E elem ) {
      elems.push_back(elem);
      return this;
    }
    void clear() {
      for( auto p = elems.begin(); p != elems.end(); p++ ) {
        assert( !(symbols_begin(0) <= *p && *p < symbols_end()) );
        delete *p;
      }
      elems.clear();
    }
  };

  struct file_list_t;
  struct cbl_label_t;
  typedef struct Elem_list_t<cbl_label_t*> Label_list_t;

  struct cbl_file_key_t;
  typedef struct Elem_list_t<cbl_file_key_t*> key_list_t;

  struct cbl_declarative_t;
  typedef struct Elem_list_t<cbl_declarative_t*> declarative_list_t;
  typedef struct Elem_list_t<ec_type_t> ec_list_t;
  typedef struct Elem_list_t<size_t> isym_list_t;

  struct rel_part_t;

  bool set_debug(bool);

#include "../../libgcobol/ec.h"
#include "../../libgcobol/common-defs.h"
#include "inspect.h"

#line 302 "parse.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFICATION_DIV = 258,      /* "IDENTIFICATION DIVISION"  */
    ENVIRONMENT_DIV = 259,         /* "ENVIRONMENT DIVISION"  */
    PROCEDURE_DIV = 260,           /* "PROCEDURE DIVISION"  */
    DATA_DIV = 261,                /* "DATA DIVISION"  */
    FILE_SECT = 262,               /* "FILE SECTION"  */
    INPUT_OUTPUT_SECT = 263,       /* "INPUT-OUTPUT SECTION"  */
    LINKAGE_SECT = 264,            /* "LINKAGE SECTION"  */
    LOCAL_STORAGE_SECT = 265,      /* "LOCAL-STORAGE SECTION"  */
    WORKING_STORAGE_SECT = 266,    /* "WORKING-STORAGE SECTION"  */
    OBJECT_COMPUTER = 267,         /* "OBJECT COMPUTER"  */
    DISPLAY_OF = 268,              /* "DISPLAY OF"  */
    END_FUNCTION = 269,            /* "END FUNCTION"  */
    END_PROGRAM = 270,             /* "END PROGRAM"  */
    END_SUBPROGRAM = 271,          /* "END PROGRAM <contained program>"  */
    JUSTIFIED = 272,               /* JUSTIFIED  */
    RETURNING = 273,               /* RETURNING  */
    NO_CONDITION = 274,            /* "invalid token"  */
    ALNUM = 275,                   /* ALNUM  */
    ALPHED = 276,                  /* ALPHED  */
    ERROR = 277,                   /* ERROR  */
    EXCEPTION = 278,               /* EXCEPTION  */
    SIZE_ERROR = 279,              /* "SIZE ERROR"  */
    EXCEPTION_NAME = 280,          /* "EXCEPTION NAME"  */
    LEVEL = 281,                   /* LEVEL  */
    LEVEL66 = 282,                 /* "66"  */
    LEVEL78 = 283,                 /* "78"  */
    LEVEL88 = 284,                 /* "88"  */
    CLASS_NAME = 285,              /* "class name"  */
    NAME = 286,                    /* NAME  */
    NAME88 = 287,                  /* "Level 88 NAME"  */
    NUME = 288,                    /* "Name"  */
    NUMED = 289,                   /* "NUMERIC-EDITED picture"  */
    NUMED_CR = 290,                /* "NUMERIC-EDITED CR picture"  */
    NUMED_DB = 291,                /* "NUMERIC-EDITED DB picture"  */
    NINEDOT = 292,                 /* NINEDOT  */
    NINES = 293,                   /* NINES  */
    NINEV = 294,                   /* NINEV  */
    PIC_P = 295,                   /* PIC_P  */
    ONES = 296,                    /* ONES  */
    SPACES = 297,                  /* SPACES  */
    LITERAL = 298,                 /* LITERAL  */
    END = 299,                     /* END  */
    EOP = 300,                     /* EOP  */
    FILENAME = 301,                /* FILENAME  */
    INVALID = 302,                 /* INVALID  */
    NUMBER = 303,                  /* NUMBER  */
    NEGATIVE = 304,                /* NEGATIVE  */
    NUMSTR = 305,                  /* "numeric literal"  */
    OVERFLOW_kw = 306,             /* "OVERFLOW"  */
    BINARY_INTEGER = 307,          /* BINARY_INTEGER  */
    COMPUTATIONAL = 308,           /* COMPUTATIONAL  */
    PERFORM = 309,                 /* PERFORM  */
    BACKWARD = 310,                /* BACKWARD  */
    POSITIVE = 311,                /* POSITIVE  */
    POINTER = 312,                 /* POINTER  */
    SECTION = 313,                 /* SECTION  */
    STANDARD_ALPHABET = 314,       /* "STANDARD ALPHABET"  */
    SWITCH = 315,                  /* SWITCH  */
    UPSI = 316,                    /* UPSI  */
    ZERO = 317,                    /* ZERO  */
    SYSIN = 318,                   /* SYSIN  */
    SYSIPT = 319,                  /* SYSIPT  */
    SYSOUT = 320,                  /* SYSOUT  */
    SYSLIST = 321,                 /* SYSLIST  */
    SYSLST = 322,                  /* SYSLST  */
    SYSPUNCH = 323,                /* SYSPUNCH  */
    SYSPCH = 324,                  /* SYSPCH  */
    CONSOLE = 325,                 /* CONSOLE  */
    C01 = 326,                     /* C01  */
    C02 = 327,                     /* C02  */
    C03 = 328,                     /* C03  */
    C04 = 329,                     /* C04  */
    C05 = 330,                     /* C05  */
    C06 = 331,                     /* C06  */
    C07 = 332,                     /* C07  */
    C08 = 333,                     /* C08  */
    C09 = 334,                     /* C09  */
    C10 = 335,                     /* C10  */
    C11 = 336,                     /* C11  */
    C12 = 337,                     /* C12  */
    CSP = 338,                     /* CSP  */
    S01 = 339,                     /* S01  */
    S02 = 340,                     /* S02  */
    S03 = 341,                     /* S03  */
    S04 = 342,                     /* S04  */
    S05 = 343,                     /* S05  */
    AFP_5A = 344,                  /* "AFP 5A"  */
    STDIN = 345,                   /* STDIN  */
    STDOUT = 346,                  /* STDOUT  */
    STDERR = 347,                  /* STDERR  */
    LIST = 348,                    /* LIST  */
    MAP = 349,                     /* MAP  */
    NOLIST = 350,                  /* NOLIST  */
    NOMAP = 351,                   /* NOMAP  */
    NOSOURCE = 352,                /* NOSOURCE  */
    MIGHT_BE = 353,                /* "IS or IS NOT"  */
    FUNCTION_UDF = 354,            /* "UDF name"  */
    FUNCTION_UDF_0 = 355,          /* "UDF"  */
    DATE_FMT = 356,                /* "date format"  */
    TIME_FMT = 357,                /* "time format"  */
    DATETIME_FMT = 358,            /* "datetime format"  */
    BASIS = 359,                   /* BASIS  */
    CBL = 360,                     /* CBL  */
    CONSTANT = 361,                /* CONSTANT  */
    COPY = 362,                    /* COPY  */
    DEFINED = 363,                 /* DEFINED  */
    ENTER = 364,                   /* ENTER  */
    FEATURE = 365,                 /* FEATURE  */
    INSERTT = 366,                 /* INSERTT  */
    LSUB = 367,                    /* "("  */
    PARAMETER_kw = 368,            /* "PARAMETER"  */
    OVERRIDE = 369,                /* OVERRIDE  */
    READY = 370,                   /* READY  */
    RESET = 371,                   /* RESET  */
    RSUB = 372,                    /* ")"  */
    SERVICE_RELOAD = 373,          /* "SERVICE RELOAD"  */
    STAR_CBL = 374,                /* "*CBL"  */
    SUBSCRIPT = 375,               /* SUBSCRIPT  */
    SUPPRESS = 376,                /* SUPPRESS  */
    TITLE = 377,                   /* TITLE  */
    TRACE = 378,                   /* TRACE  */
    USE = 379,                     /* USE  */
    COBOL_WORDS = 380,             /* ">>COBOL-WORDS"  */
    EQUATE = 381,                  /* EQUATE  */
    UNDEFINE = 382,                /* UNDEFINE  */
    CDF_DEFINE = 383,              /* ">>DEFINE"  */
    CDF_DISPLAY = 384,             /* ">>DISPLAY"  */
    CDF_IF = 385,                  /* ">>IF"  */
    CDF_ELSE = 386,                /* ">>ELSE"  */
    CDF_END_IF = 387,              /* ">>END-IF"  */
    CDF_EVALUATE = 388,            /* ">>EVALUATE"  */
    CDF_WHEN = 389,                /* ">>WHEN"  */
    CDF_END_EVALUATE = 390,        /* ">>END-EVALUATE"  */
    CALL_CONVENTION = 391,         /* ">>CALL-CONVENTION"  */
    CALL_COBOL = 392,              /* "CALL"  */
    CALL_VERBATIM = 393,           /* "CALL (as C)"  */
    CDF_PUSH = 394,                /* ">>PUSH"  */
    CDF_POP = 395,                 /* ">>POP"  */
    SOURCE_FORMAT = 396,           /* ">>SOURCE FORMAT"  */
    IF = 397,                      /* IF  */
    THEN = 398,                    /* THEN  */
    ELSE = 399,                    /* ELSE  */
    SENTENCE = 400,                /* SENTENCE  */
    ACCEPT = 401,                  /* ACCEPT  */
    ADD = 402,                     /* ADD  */
    ALTER = 403,                   /* ALTER  */
    CALL = 404,                    /* CALL  */
    CANCEL = 405,                  /* CANCEL  */
    CLOSE = 406,                   /* CLOSE  */
    COMPUTE = 407,                 /* COMPUTE  */
    CONTINUE = 408,                /* CONTINUE  */
    DELETE = 409,                  /* DELETE  */
    DISPLAY = 410,                 /* DISPLAY  */
    DIVIDE = 411,                  /* DIVIDE  */
    EVALUATE = 412,                /* EVALUATE  */
    EXIT = 413,                    /* EXIT  */
    FILLER_kw = 414,               /* "FILLER"  */
    GOBACK = 415,                  /* GOBACK  */
    GOTO = 416,                    /* GOTO  */
    INITIALIZE = 417,              /* INITIALIZE  */
    INSPECT = 418,                 /* INSPECT  */
    MERGE = 419,                   /* MERGE  */
    MOVE = 420,                    /* MOVE  */
    MULTIPLY = 421,                /* MULTIPLY  */
    OPEN = 422,                    /* OPEN  */
    PARAGRAPH = 423,               /* PARAGRAPH  */
    READ = 424,                    /* READ  */
    RELEASE = 425,                 /* RELEASE  */
    RETURN = 426,                  /* RETURN  */
    REWRITE = 427,                 /* REWRITE  */
    SEARCH = 428,                  /* SEARCH  */
    SET = 429,                     /* SET  */
    SELECT = 430,                  /* SELECT  */
    SORT = 431,                    /* SORT  */
    SORT_MERGE = 432,              /* "SORT-MERGE"  */
    STRING_kw = 433,               /* "STRING"  */
    STOP = 434,                    /* STOP  */
    SUBTRACT = 435,                /* SUBTRACT  */
    START = 436,                   /* START  */
    UNSTRING = 437,                /* UNSTRING  */
    WRITE = 438,                   /* WRITE  */
    WHEN = 439,                    /* WHEN  */
    ARGUMENT_NUMBER = 440,         /* ARGUMENT_NUMBER  */
    ARGUMENT_VALUE = 441,          /* ARGUMENT_VALUE  */
    ENVIRONMENT_NAME = 442,        /* ENVIRONMENT_NAME  */
    ENVIRONMENT_VALUE = 443,       /* ENVIRONMENT_VALUE  */
    ABS = 444,                     /* ABS  */
    ACCESS = 445,                  /* ACCESS  */
    ACOS = 446,                    /* ACOS  */
    ACTUAL = 447,                  /* ACTUAL  */
    ADVANCING = 448,               /* ADVANCING  */
    AFTER = 449,                   /* AFTER  */
    ALL = 450,                     /* ALL  */
    ALLOCATE = 451,                /* ALLOCATE  */
    ALPHABET = 452,                /* ALPHABET  */
    ALPHABETIC = 453,              /* ALPHABETIC  */
    ALPHABETIC_LOWER = 454,        /* "ALPHABETIC-LOWER"  */
    ALPHABETIC_UPPER = 455,        /* "ALPHABETIC-UPPER"  */
    ALPHANUMERIC = 456,            /* ALPHANUMERIC  */
    ALPHANUMERIC_EDITED = 457,     /* "ALPHANUMERIC-EDITED"  */
    ALSO = 458,                    /* ALSO  */
    ALTERNATE = 459,               /* ALTERNATE  */
    ANNUITY = 460,                 /* ANNUITY  */
    ANUM = 461,                    /* ANUM  */
    ANY = 462,                     /* ANY  */
    ANYCASE = 463,                 /* ANYCASE  */
    APPLY = 464,                   /* APPLY  */
    ARE = 465,                     /* ARE  */
    AREA = 466,                    /* AREA  */
    AREAS = 467,                   /* AREAS  */
    AS = 468,                      /* AS  */
    ASCENDING = 469,               /* ASCENDING  */
    ACTIVATING = 470,              /* ACTIVATING  */
    ASIN = 471,                    /* ASIN  */
    ASSIGN = 472,                  /* ASSIGN  */
    AT = 473,                      /* AT  */
    ATAN = 474,                    /* ATAN  */
    BASED = 475,                   /* BASED  */
    BASECONVERT = 476,             /* BASECONVERT  */
    BEFORE = 477,                  /* BEFORE  */
    BINARY = 478,                  /* BINARY  */
    BIT = 479,                     /* BIT  */
    BIT_OF = 480,                  /* "BIT-OF"  */
    BIT_TO_CHAR = 481,             /* "BIT-TO-CHAR"  */
    BLANK = 482,                   /* BLANK  */
    BLOCK_kw = 483,                /* BLOCK_kw  */
    BOOLEAN_OF_INTEGER = 484,      /* "BOOLEAN-OF-INTEGER"  */
    BOTTOM = 485,                  /* BOTTOM  */
    BY = 486,                      /* BY  */
    BYTE = 487,                    /* BYTE  */
    BYTE_LENGTH = 488,             /* "BYTE-LENGTH"  */
    CF = 489,                      /* CF  */
    CH = 490,                      /* CH  */
    CHANGED = 491,                 /* CHANGED  */
    CHAR = 492,                    /* CHAR  */
    CHAR_NATIONAL = 493,           /* "CHAR-NATIONAL"  */
    CHARACTER = 494,               /* CHARACTER  */
    CHARACTERS = 495,              /* CHARACTERS  */
    CHECKING = 496,                /* CHECKING  */
    CLASS = 497,                   /* CLASS  */
    COBOL = 498,                   /* COBOL  */
    CODE = 499,                    /* CODE  */
    CODESET = 500,                 /* CODESET  */
    COLLATING = 501,               /* COLLATING  */
    COLUMN = 502,                  /* COLUMN  */
    COMBINED_DATETIME = 503,       /* "COMBINED-DATETIME"  */
    COMMA = 504,                   /* COMMA  */
    COMMAND_LINE = 505,            /* "COMMAND-LINE"  */
    COMMAND_LINE_COUNT = 506,      /* "COMMAND-LINE-COUNT"  */
    COMMIT = 507,                  /* COMMIT  */
    COMMON = 508,                  /* COMMON  */
    CONCAT = 509,                  /* CONCAT  */
    CONDITION = 510,               /* CONDITION  */
    CONFIGURATION_SECT = 511,      /* "CONFIGURATION SECTION"  */
    CONTAINS = 512,                /* CONTAINS  */
    CONTENT = 513,                 /* CONTENT  */
    CONTROL = 514,                 /* CONTROL  */
    CONTROLS = 515,                /* CONTROLS  */
    CONVERT = 516,                 /* CONVERT  */
    CONVERTING = 517,              /* CONVERTING  */
    CORRESPONDING = 518,           /* CORRESPONDING  */
    COS = 519,                     /* COS  */
    COUNT = 520,                   /* COUNT  */
    CURRENCY = 521,                /* CURRENCY  */
    CURRENT = 522,                 /* CURRENT  */
    CURRENT_DATE = 523,            /* CURRENT_DATE  */
    DATA = 524,                    /* DATA  */
    DATE = 525,                    /* DATE  */
    DATE_COMPILED = 526,           /* DATE_COMPILED  */
    DATE_OF_INTEGER = 527,         /* "DATE-OF-INTEGER"  */
    DATE_TO_YYYYMMDD = 528,        /* "DATE-TO-YYYYMMDD"  */
    DATE_WRITTEN = 529,            /* "DATE-WRITTEN"  */
    DAY = 530,                     /* DAY  */
    DAY_OF_INTEGER = 531,          /* "DAY-OF-INTEGER"  */
    DAY_OF_WEEK = 532,             /* "DAY-OF-WEEK"  */
    DAY_TO_YYYYDDD = 533,          /* "DAY-TO-YYYYDDD"  */
    DBCS = 534,                    /* DBCS  */
    DE = 535,                      /* DE  */
    DEBUGGING = 536,               /* DEBUGGING  */
    DECIMAL_POINT = 537,           /* DECIMAL_POINT  */
    DECLARATIVES = 538,            /* DECLARATIVES  */
    DEFAULT = 539,                 /* DEFAULT  */
    DELIMITED = 540,               /* DELIMITED  */
    DELIMITER = 541,               /* DELIMITER  */
    DEPENDING = 542,               /* DEPENDING  */
    DESCENDING = 543,              /* DESCENDING  */
    DETAIL = 544,                  /* DETAIL  */
    DIRECT = 545,                  /* DIRECT  */
    DIRECT_ACCESS = 546,           /* "DIRECT-ACCESS"  */
    DOWN = 547,                    /* DOWN  */
    DUPLICATES = 548,              /* DUPLICATES  */
    DYNAMIC = 549,                 /* DYNAMIC  */
    E = 550,                       /* E  */
    EBCDIC = 551,                  /* EBCDIC  */
    EC = 552,                      /* EC  */
    EGCS = 553,                    /* EGCS  */
    ENTRY = 554,                   /* ENTRY  */
    ENVIRONMENT = 555,             /* ENVIRONMENT  */
    EQUAL = 556,                   /* EQUAL  */
    EVERY = 557,                   /* EVERY  */
    EXAMINE = 558,                 /* EXAMINE  */
    EXHIBIT = 559,                 /* EXHIBIT  */
    EXP = 560,                     /* EXP  */
    EXP10 = 561,                   /* EXP10  */
    EXTEND = 562,                  /* EXTEND  */
    EXTERNAL = 563,                /* EXTERNAL  */
    EXCEPTION_FILE = 564,          /* "EXCEPTION-FILE"  */
    EXCEPTION_FILE_N = 565,        /* "EXCEPTION-FILE-N"  */
    EXCEPTION_LOCATION = 566,      /* "EXCEPTION-LOCATION"  */
    EXCEPTION_LOCATION_N = 567,    /* "EXCEPTION-LOCATION-N"  */
    EXCEPTION_STATEMENT = 568,     /* "EXCEPTION-STATEMENT"  */
    EXCEPTION_STATUS = 569,        /* "EXCEPTION-STATUS"  */
    FACTORIAL = 570,               /* FACTORIAL  */
    FALSE_kw = 571,                /* "False"  */
    FD = 572,                      /* FD  */
    FILE_CONTROL = 573,            /* "FILE-CONTROL"  */
    FILE_KW = 574,                 /* "File"  */
    FILE_LIMIT = 575,              /* "FILE-LIMIT"  */
    FINAL = 576,                   /* FINAL  */
    FINALLY = 577,                 /* FINALLY  */
    FIND_STRING = 578,             /* "FIND-STRING"  */
    FIRST = 579,                   /* FIRST  */
    FIXED = 580,                   /* FIXED  */
    FOOTING = 581,                 /* FOOTING  */
    FOR = 582,                     /* FOR  */
    FORMATTED_CURRENT_DATE = 583,  /* "FORMATTED-CURRENT-DATE"  */
    FORMATTED_DATE = 584,          /* "FORMATTED-DATE"  */
    FORMATTED_DATETIME = 585,      /* "FORMATTED-DATETIME"  */
    FORMATTED_TIME = 586,          /* "FORMATTED-TIME"  */
    FORM_OVERFLOW = 587,           /* "FORM-OVERFLOW"  */
    FREE = 588,                    /* FREE  */
    FRACTION_PART = 589,           /* "FRACTION-PART"  */
    FROM = 590,                    /* FROM  */
    FUNCTION = 591,                /* FUNCTION  */
    GENERATE = 592,                /* GENERATE  */
    GIVING = 593,                  /* GIVING  */
    GLOBAL = 594,                  /* GLOBAL  */
    GO = 595,                      /* GO  */
    GROUP = 596,                   /* GROUP  */
    HEADING = 597,                 /* HEADING  */
    HEX = 598,                     /* HEX  */
    HEX_OF = 599,                  /* "HEX-OF"  */
    HEX_TO_CHAR = 600,             /* "HEX-TO-CHAR"  */
    HIGH_VALUES = 601,             /* "HIGH-VALUES"  */
    HIGHEST_ALGEBRAIC = 602,       /* "HIGHEST-ALGEBRAIC"  */
    HOLD = 603,                    /* HOLD  */
    IBM_360 = 604,                 /* IBM_360  */
    IN = 605,                      /* IN  */
    INCLUDE = 606,                 /* INCLUDE  */
    INDEX = 607,                   /* INDEX  */
    INDEXED = 608,                 /* INDEXED  */
    INDICATE = 609,                /* INDICATE  */
    INITIAL_kw = 610,              /* "INITIAL"  */
    INITIATE = 611,                /* INITIATE  */
    INPUT = 612,                   /* INPUT  */
    INSTALLATION = 613,            /* INSTALLATION  */
    INTERFACE = 614,               /* INTERFACE  */
    INTEGER = 615,                 /* INTEGER  */
    INTEGER_OF_BOOLEAN = 616,      /* "INTEGER-OF-BOOLEAN"  */
    INTEGER_OF_DATE = 617,         /* "INTEGER-OF-DATE"  */
    INTEGER_OF_DAY = 618,          /* "INTEGER-OF-DAY"  */
    INTEGER_OF_FORMATTED_DATE = 619, /* "INTEGER-OF-FORMATTED-DATE"  */
    INTEGER_PART = 620,            /* "INTEGER-PART"  */
    INTO = 621,                    /* INTO  */
    INTRINSIC = 622,               /* INTRINSIC  */
    INVOKE = 623,                  /* INVOKE  */
    IO = 624,                      /* IO  */
    IO_CONTROL = 625,              /* "IO-CONTROL"  */
    IS = 626,                      /* IS  */
    ISNT = 627,                    /* "IS NOT"  */
    KANJI = 628,                   /* KANJI  */
    KEY = 629,                     /* KEY  */
    LABEL = 630,                   /* LABEL  */
    LAST = 631,                    /* LAST  */
    LEADING = 632,                 /* LEADING  */
    LEFT = 633,                    /* LEFT  */
    LENGTH = 634,                  /* LENGTH  */
    LENGTH_OF = 635,               /* "LENGTH-OF"  */
    LIMIT = 636,                   /* LIMIT  */
    LIMITS = 637,                  /* LIMITS  */
    LINE = 638,                    /* LINE  */
    LINES = 639,                   /* LINES  */
    LINE_COUNTER = 640,            /* "LINE-COUNTER"  */
    LINAGE = 641,                  /* LINAGE  */
    LINKAGE = 642,                 /* LINKAGE  */
    LOCALE = 643,                  /* LOCALE  */
    LOCALE_COMPARE = 644,          /* "LOCALE-COMPARE"  */
    LOCALE_DATE = 645,             /* "LOCALE-DATE"  */
    LOCALE_TIME = 646,             /* "LOCALE-TIME"  */
    LOCALE_TIME_FROM_SECONDS = 647, /* "LOCALE-TIME-FROM-SECONDS"  */
    LOCAL_STORAGE = 648,           /* "LOCAL-STORAGE"  */
    LOCATION = 649,                /* LOCATION  */
    LOCK = 650,                    /* LOCK  */
    LOCK_ON = 651,                 /* LOCK_ON  */
    LOG = 652,                     /* LOG  */
    LOG10 = 653,                   /* LOG10  */
    LOWER_CASE = 654,              /* "LOWER-CASE"  */
    LOW_VALUES = 655,              /* "LOW-VALUES"  */
    LOWEST_ALGEBRAIC = 656,        /* "LOWEST-ALGEBRAIC"  */
    LPAREN = 657,                  /* " )"  */
    MANUAL = 658,                  /* MANUAL  */
    MAXX = 659,                    /* "Max"  */
    MEAN = 660,                    /* MEAN  */
    MEDIAN = 661,                  /* MEDIAN  */
    MIDRANGE = 662,                /* MIDRANGE  */
    MINN = 663,                    /* "Min"  */
    MULTIPLE = 664,                /* MULTIPLE  */
    MOD = 665,                     /* MOD  */
    MODE = 666,                    /* MODE  */
    MODULE_NAME = 667,             /* "MODULE-NAME "  */
    NAMED = 668,                   /* NAMED  */
    NAT = 669,                     /* NAT  */
    NATIONAL = 670,                /* NATIONAL  */
    NATIONAL_EDITED = 671,         /* "NATIONAL-EDITED"  */
    NATIONAL_OF = 672,             /* "NATIONAL-OF"  */
    NATIVE = 673,                  /* NATIVE  */
    NESTED = 674,                  /* NESTED  */
    NEXT = 675,                    /* NEXT  */
    NO = 676,                      /* NO  */
    NOTE = 677,                    /* NOTE  */
    NULLS = 678,                   /* NULLS  */
    NULLPTR = 679,                 /* NULLPTR  */
    NUMERIC = 680,                 /* NUMERIC  */
    NUMERIC_EDITED = 681,          /* NUMERIC_EDITED  */
    NUMVAL = 682,                  /* NUMVAL  */
    NUMVAL_C = 683,                /* "NUMVAL-C"  */
    NUMVAL_F = 684,                /* "NUMVAL-F"  */
    OCCURS = 685,                  /* OCCURS  */
    OF = 686,                      /* OF  */
    OFF = 687,                     /* OFF  */
    OMITTED = 688,                 /* OMITTED  */
    ON = 689,                      /* ON  */
    ONLY = 690,                    /* ONLY  */
    OPTIONAL = 691,                /* OPTIONAL  */
    OPTIONS = 692,                 /* OPTIONS  */
    ORD = 693,                     /* ORD  */
    ORDER = 694,                   /* ORDER  */
    ORD_MAX = 695,                 /* "ORD-MAX"  */
    ORD_MIN = 696,                 /* "ORD-MIN"  */
    ORGANIZATION = 697,            /* ORGANIZATION  */
    OTHER = 698,                   /* OTHER  */
    OTHERWISE = 699,               /* OTHERWISE  */
    OUTPUT = 700,                  /* OUTPUT  */
    PACKED_DECIMAL = 701,          /* PACKED_DECIMAL  */
    PADDING = 702,                 /* PADDING  */
    PAGE = 703,                    /* PAGE  */
    PAGE_COUNTER = 704,            /* "PAGE-COUNTER"  */
    PF = 705,                      /* PF  */
    PH = 706,                      /* PH  */
    PI = 707,                      /* PI  */
    PIC = 708,                     /* PIC  */
    PICTURE = 709,                 /* PICTURE  */
    PLUS = 710,                    /* PLUS  */
    PRESENT_VALUE = 711,           /* PRESENT_VALUE  */
    PRINT_SWITCH = 712,            /* PRINT_SWITCH  */
    PROCEDURE = 713,               /* PROCEDURE  */
    PROCEDURES = 714,              /* PROCEDURES  */
    PROCEED = 715,                 /* PROCEED  */
    PROCESS = 716,                 /* PROCESS  */
    PROGRAM_ID = 717,              /* "PROGRAM-ID"  */
    PROGRAM_kw = 718,              /* "Program"  */
    PROPERTY = 719,                /* PROPERTY  */
    PROTOTYPE = 720,               /* PROTOTYPE  */
    PSEUDOTEXT = 721,              /* PSEUDOTEXT  */
    QUOTES = 722,                  /* "QUOTE"  */
    RANDOM = 723,                  /* RANDOM  */
    RANDOM_SEED = 724,             /* RANDOM_SEED  */
    RANGE = 725,                   /* RANGE  */
    RAISE = 726,                   /* RAISE  */
    RAISING = 727,                 /* RAISING  */
    RD = 728,                      /* RD  */
    RECORD = 729,                  /* RECORD  */
    RECORDING = 730,               /* RECORDING  */
    RECORDS = 731,                 /* RECORDS  */
    RECURSIVE = 732,               /* RECURSIVE  */
    REDEFINES = 733,               /* REDEFINES  */
    REEL = 734,                    /* REEL  */
    REFERENCE = 735,               /* REFERENCE  */
    RELATIVE = 736,                /* RELATIVE  */
    REM = 737,                     /* REM  */
    REMAINDER = 738,               /* REMAINDER  */
    REMARKS = 739,                 /* REMARKS  */
    REMOVAL = 740,                 /* REMOVAL  */
    RENAMES = 741,                 /* RENAMES  */
    REPLACE = 742,                 /* REPLACE  */
    REPLACING = 743,               /* REPLACING  */
    REPORT = 744,                  /* REPORT  */
    REPORTING = 745,               /* REPORTING  */
    REPORTS = 746,                 /* REPORTS  */
    REPOSITORY = 747,              /* REPOSITORY  */
    RERUN = 748,                   /* RERUN  */
    RESERVE = 749,                 /* RESERVE  */
    RESTRICTED = 750,              /* RESTRICTED  */
    RESUME = 751,                  /* RESUME  */
    REVERSE = 752,                 /* REVERSE  */
    REVERSED = 753,                /* REVERSED  */
    REWIND = 754,                  /* REWIND  */
    RF = 755,                      /* RF  */
    RH = 756,                      /* RH  */
    RIGHT = 757,                   /* RIGHT  */
    ROUNDED = 758,                 /* ROUNDED  */
    RUN = 759,                     /* RUN  */
    SAME = 760,                    /* SAME  */
    SCREEN = 761,                  /* SCREEN  */
    SD = 762,                      /* SD  */
    SECONDS_FROM_FORMATTED_TIME = 763, /* "SECONDS-FROM-FORMATTED-TIME"  */
    SECONDS_PAST_MIDNIGHT = 764,   /* "SECONDS-PAST-MIDNIGHT"  */
    SECURITY = 765,                /* SECURITY  */
    SEPARATE = 766,                /* SEPARATE  */
    SEQUENCE = 767,                /* SEQUENCE  */
    SEQUENTIAL = 768,              /* SEQUENTIAL  */
    SHARING = 769,                 /* SHARING  */
    SIMPLE_EXIT = 770,             /* "(simple) EXIT"  */
    SIGN = 771,                    /* SIGN  */
    SIN = 772,                     /* SIN  */
    SIZE = 773,                    /* SIZE  */
    SMALLEST_ALGEBRAIC = 774,      /* "SMALLEST-ALGEBRAIC"  */
    SOURCE = 775,                  /* SOURCE  */
    SOURCE_COMPUTER = 776,         /* "SOURCE-COMPUTER"  */
    SPECIAL_NAMES = 777,           /* SPECIAL_NAMES  */
    SQRT = 778,                    /* SQRT  */
    STACK = 779,                   /* STACK  */
    STANDARD = 780,                /* STANDARD  */
    STANDARD_1 = 781,              /* "STANDARD-1"  */
    STANDARD_DEVIATION = 782,      /* "STANDARD-DEVIATION "  */
    STANDARD_COMPARE = 783,        /* "STANDARD-COMPARE"  */
    STATUS = 784,                  /* STATUS  */
    STRONG = 785,                  /* STRONG  */
    SUBSTITUTE = 786,              /* SUBSTITUTE  */
    SUM = 787,                     /* SUM  */
    SYMBOL = 788,                  /* SYMBOL  */
    SYMBOLIC = 789,                /* SYMBOLIC  */
    SYNCHRONIZED = 790,            /* SYNCHRONIZED  */
    TALLY = 791,                   /* TALLY  */
    TALLYING = 792,                /* TALLYING  */
    TAN = 793,                     /* TAN  */
    TERMINATE = 794,               /* TERMINATE  */
    TEST = 795,                    /* TEST  */
    TEST_DATE_YYYYMMDD = 796,      /* "TEST-DATE-YYYYMMDD"  */
    TEST_DAY_YYYYDDD = 797,        /* "TEST-DAY-YYYYDDD"  */
    TEST_FORMATTED_DATETIME = 798, /* "TEST-FORMATTED-DATETIME"  */
    TEST_NUMVAL = 799,             /* "TEST-NUMVAL"  */
    TEST_NUMVAL_C = 800,           /* "TEST-NUMVAL-C"  */
    TEST_NUMVAL_F = 801,           /* "TEST-NUMVAL-F"  */
    THAN = 802,                    /* THAN  */
    TIME = 803,                    /* TIME  */
    TIMES = 804,                   /* TIMES  */
    TO = 805,                      /* TO  */
    TOP = 806,                     /* TOP  */
    TOP_LEVEL = 807,               /* TOP_LEVEL  */
    TRACKS = 808,                  /* TRACKS  */
    TRACK_AREA = 809,              /* TRACK_AREA  */
    TRAILING = 810,                /* TRAILING  */
    TRANSFORM = 811,               /* TRANSFORM  */
    TRIM = 812,                    /* TRIM  */
    TRUE_kw = 813,                 /* "True"  */
    TRY = 814,                     /* TRY  */
    TURN = 815,                    /* TURN  */
    TYPE = 816,                    /* TYPE  */
    TYPEDEF = 817,                 /* TYPEDEF  */
    ULENGTH = 818,                 /* ULENGTH  */
    UNBOUNDED = 819,               /* UNBOUNDED  */
    UNIT = 820,                    /* UNIT  */
    UNITS = 821,                   /* UNITS  */
    UNIT_RECORD = 822,             /* UNIT_RECORD  */
    UNTIL = 823,                   /* UNTIL  */
    UP = 824,                      /* UP  */
    UPON = 825,                    /* UPON  */
    UPOS = 826,                    /* UPOS  */
    UPPER_CASE = 827,              /* UPPER_CASE  */
    USAGE = 828,                   /* USAGE  */
    USING = 829,                   /* USING  */
    USUBSTR = 830,                 /* USUBSTR  */
    USUPPLEMENTARY = 831,          /* USUPPLEMENTARY  */
    UTILITY = 832,                 /* UTILITY  */
    UUID4 = 833,                   /* UUID4  */
    UVALID = 834,                  /* UVALID  */
    UWIDTH = 835,                  /* UWIDTH  */
    VALUE = 836,                   /* VALUE  */
    VARIANCE = 837,                /* VARIANCE  */
    VARYING = 838,                 /* VARYING  */
    VOLATILE = 839,                /* VOLATILE  */
    WHEN_COMPILED = 840,           /* WHEN_COMPILED  */
    WITH = 841,                    /* WITH  */
    WORKING_STORAGE = 842,         /* WORKING_STORAGE  */
    XML = 843,                     /* XML  */
    XMLGENERATE = 844,             /* XMLGENERATE  */
    XMLPARSE = 845,                /* XMLPARSE  */
    YEAR_TO_YYYY = 846,            /* YEAR_TO_YYYY  */
    YYYYDDD = 847,                 /* YYYYDDD  */
    YYYYMMDD = 848,                /* YYYYMMDD  */
    ARITHMETIC = 849,              /* ARITHMETIC  */
    ATTRIBUTE = 850,               /* ATTRIBUTE  */
    AUTO = 851,                    /* AUTO  */
    AUTOMATIC = 852,               /* AUTOMATIC  */
    AWAY_FROM_ZERO = 853,          /* "AWAY-FROM-ZERO"  */
    BACKGROUND_COLOR = 854,        /* "BACKGROUND-COLOR"  */
    BELL = 855,                    /* BELL  */
    BINARY_ENCODING = 856,         /* "BINARY-ENCODING"  */
    BLINK = 857,                   /* BLINK  */
    CAPACITY = 858,                /* CAPACITY  */
    CENTER = 859,                  /* CENTER  */
    CLASSIFICATION = 860,          /* CLASSIFICATION  */
    CYCLE = 861,                   /* CYCLE  */
    DECIMAL_ENCODING = 862,        /* "DECIMAL-ENCODING"  */
    ENTRY_CONVENTION = 863,        /* ENTRY_CONVENTION  */
    EOL = 864,                     /* EOL  */
    EOS = 865,                     /* EOS  */
    ERASE = 866,                   /* ERASE  */
    EXPANDS = 867,                 /* EXPANDS  */
    FLOAT_BINARY = 868,            /* "FLOAT-BINARY"  */
    FLOAT_DECIMAL = 869,           /* "FLOAT-DECIMAL"  */
    FOREGROUND_COLOR = 870,        /* FOREGROUND_COLOR  */
    FOREVER = 871,                 /* FOREVER  */
    FULL = 872,                    /* FULL  */
    HIGHLIGHT = 873,               /* HIGHLIGHT  */
    HIGH_ORDER_LEFT = 874,         /* "HIGH-ORDER-LEFT"  */
    HIGH_ORDER_RIGHT = 875,        /* "HIGH-ORDER-RIGHT"  */
    IGNORING = 876,                /* IGNORING  */
    IMPLEMENTS = 877,              /* IMPLEMENTS  */
    INITIALIZED = 878,             /* INITIALIZED  */
    INTERMEDIATE = 879,            /* INTERMEDIATE  */
    LC_ALL_kw = 880,               /* "LC-ALL"  */
    LC_COLLATE_kw = 881,           /* "LC-COLLATE"  */
    LC_CTYPE_kw = 882,             /* "LC-CTYPE"  */
    LC_MESSAGES_kw = 883,          /* "LC-MESSAGES"  */
    LC_MONETARY_kw = 884,          /* "LC-MONETARY"  */
    LC_NUMERIC_kw = 885,           /* "LC-NUMERIC"  */
    LC_TIME_kw = 886,              /* "LC-TIME"  */
    LOWLIGHT = 887,                /* LOWLIGHT  */
    NEAREST_AWAY_FROM_ZERO = 888,  /* "NEAREST-AWAY-FROM-ZERO"  */
    NEAREST_EVEN = 889,            /* NEAREST_EVEN  */
    NEAREST_TOWARD_ZERO = 890,     /* "NEAREST-EVEN NEAREST-TOWARD-ZERO"  */
    NONE = 891,                    /* NONE  */
    NORMAL = 892,                  /* NORMAL  */
    NUMBERS = 893,                 /* NUMBERS  */
    PREFIXED = 894,                /* PREFIXED  */
    PREVIOUS = 895,                /* PREVIOUS  */
    PROHIBITED = 896,              /* PROHIBITED  */
    RELATION = 897,                /* RELATION  */
    REQUIRED = 898,                /* REQUIRED  */
    REVERSE_VIDEO = 899,           /* REVERSE_VIDEO  */
    ROUNDING = 900,                /* ROUNDING  */
    SECONDS = 901,                 /* SECONDS  */
    SECURE = 902,                  /* SECURE  */
    SHORT = 903,                   /* SHORT  */
    SIGNED_kw = 904,               /* SIGNED_kw  */
    STANDARD_BINARY = 905,         /* "STANDARD-BINARY"  */
    STANDARD_DECIMAL = 906,        /* "STANDARD-DECIMAL"  */
    STATEMENT = 907,               /* STATEMENT  */
    STEP = 908,                    /* STEP  */
    STRUCTURE = 909,               /* STRUCTURE  */
    TOWARD_GREATER = 910,          /* "TOWARD-GREATER"  */
    TOWARD_LESSER = 911,           /* "TOWARD-LESSER"  */
    TRUNCATION = 912,              /* TRUNCATION  */
    UCS_4 = 913,                   /* "UCS-4"  */
    UNDERLINE = 914,               /* UNDERLINE  */
    UNSIGNED_kw = 915,             /* UNSIGNED_kw  */
    UTF_16 = 916,                  /* "UTF-16"  */
    UTF_8 = 917,                   /* "UTF-8"  */
    ADDRESS = 918,                 /* ADDRESS  */
    END_ACCEPT = 919,              /* "END-ACCEPT"  */
    END_ADD = 920,                 /* "END-ADD"  */
    END_CALL = 921,                /* "END-CALL"  */
    END_COMPUTE = 922,             /* "END-COMPUTE"  */
    END_DELETE = 923,              /* "END-DELETE"  */
    END_DISPLAY = 924,             /* "END-DISPLAY"  */
    END_DIVIDE = 925,              /* "END-DIVIDE"  */
    END_EVALUATE = 926,            /* "END-EVALUATE"  */
    END_MULTIPLY = 927,            /* "END-MULTIPLY"  */
    END_PERFORM = 928,             /* "END-PERFORM"  */
    END_READ = 929,                /* "END-READ"  */
    END_RETURN = 930,              /* "END-RETURN"  */
    END_REWRITE = 931,             /* "END-REWRITE"  */
    END_SEARCH = 932,              /* "END-SEARCH"  */
    END_START = 933,               /* "END-START"  */
    END_STRING = 934,              /* "END-STRING"  */
    END_SUBTRACT = 935,            /* "END-SUBTRACT"  */
    END_UNSTRING = 936,            /* "END-UNSTRING"  */
    END_WRITE = 937,               /* "END-WRITE"  */
    END_IF = 938,                  /* "END-IF"  */
    THRU = 939,                    /* THRU  */
    OR = 940,                      /* OR  */
    AND = 941,                     /* AND  */
    NOT = 942,                     /* NOT  */
    NE = 943,                      /* NE  */
    LE = 944,                      /* LE  */
    GE = 945,                      /* GE  */
    POW = 946,                     /* POW  */
    NEG = 947                      /* NEG  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 846 "parse.y"

    bool boolean;
    int number;
    char *string;
    REAL_VALUE_TYPE float128;
    literal_t literal;
    cbl_field_attr_t field_attr;
    ec_type_t ec_type;
    ec_list_t* ec_list;
    cbl_nameloc_t  *nameloc;
    cbl_namelocs_t *namelocs;
           declarative_list_t* dcl_list_t;
           isym_list_t* isym_list;
    struct { radix_t radix; char *string; } numstr;
    struct { YYLTYPE loc; int token; literal_t name; } prog_end;
    struct { int token; special_name_t id; } special_type;
    struct { cbl_field_type_t type;
             uint32_t capacity; bool signable; } computational;
    struct cbl_special_name_t *special;
    struct cbl_alphabet_t *alphasym;
    struct tgt_list_t *targets;
    struct cbl_file_t *file;
    struct { bool varying; size_t min, max; } min_max;
    struct { cbl_file_t *file; cbl_field_t *buffer; } rewrite_t;
    struct { cbl_file_t *file; file_status_t handled; } file_op;
    struct cbl_label_t *label;
    struct { cbl_label_t *label; int token; } exception;
    struct cbl_field_data_t *field_data;
    struct cbl_field_t *field;
    struct { bool tf; cbl_field_t *field; } bool_field;
    struct { int token; cbl_field_t *cond; } cond_field;
    struct cbl_refer_t *refer;

    struct rel_term_type { bool invert; cbl_refer_t *term; } rel_term_t;
    struct log_expr_t *log_expr_t;
    struct vargs_t* vargs;
    struct perform_t *perf;
    struct cbl_perform_tgt_t *tgt;
           Label_list_t *labels;
           key_list_t *file_keys;
           cbl_file_mode_t io_mode;
    struct cbl_file_key_t *file_key;
    struct file_list_t *files;
    struct field_list_t *fields;
    struct refer_list_t *refers;
    struct sort_key_t *sort_key;
    struct sort_keys_t *sort_keys;
    struct file_sort_io_t *sort_io;
    struct arith_t *arith;
    struct { size_t ntgt; cbl_num_result_t *tgts;
             cbl_refer_t *expr; } compute_body_t;
    struct cbl_inspect_t *insp_one;
           cbl_inspect_opers_t *insp_all;
    struct cbl_inspect_oper_t *insp_oper;
    struct { bool before; cbl_inspect_qual_t *qual; } insp_qual;
           cbl_inspect_t *inspect;
           cbl_inspect_match_t *insp_match;
           cbl_inspect_replace_t *insp_replace;

    struct { cbl_refer_t *delimited; refer_list_t *inputs; } delimited;
    struct { cbl_refer_t *input, *delimiter; } delimited_1;
    struct { cbl_refer_t *from, *len; } refmod_parts;
    struct refer_collection_t *delimiteds;
    struct { cbl_label_t *on_error, *not_error; } error;
    struct { unsigned int nclause; bool tf; } error_clauses;
    struct refer_pair_t { cbl_refer_t *first, *second; } refer2;
    struct { refer_collection_t *inputs; refer_pair_t into; } str_body;

    struct { accept_func_t func; cbl_refer_t *into, *from; special_name_t special;} accept_func;
    struct unstring_into_t *uns_into;
    struct unstring_tgt_list_t *uns_tgts;
    struct unstring_tgt_t *uns_tgt;
    struct { cbl_refer_t *input;
             refer_list_t *delimited; unstring_into_t *into; } uns_body;

    struct cbl_ffi_arg_t *ffi_arg;
    struct ffi_args_t *ffi_args;
    struct { YYLTYPE loc; cbl_refer_t *ffi_name, *ffi_returning;
             ffi_args_t *using_params; } ffi_impl;

    struct { bool common, initial, recursive; } comminit;
    struct { enum select_clause_t clause; cbl_file_t *file; } select_clause;
    struct { size_t clauses; cbl_file_t *file; } select_clauses;
    struct { YYLTYPE loc; char *on, *off; } switches;
    struct cbl_domain_t *false_domain;
    struct { size_t also; unsigned char *low, *high; } colseq;
    struct { cbl_field_attr_t attr; int nbyte; } pic_part;

           data_category_t data_category;
    struct { data_category_t category; cbl_refer_t* replacement; } replacement;
           category_map_t *replacements;
           init_statement_t *init_stmt;
    struct { cbl_special_name_t *special; vargs_t *vargs; } display;
           substitution_t substitution;
           substitutions_t  *substitutions;
    struct { bool is_locale; cbl_refer_t *arg2; } numval_locale_t;

    cbl_options_t::arith_t opt_arith;
    cbl_round_t opt_round;
    cbl_section_type_t opt_init_sect;
    struct { bool local, working; } opt_init_sects;
    module_type_t module_type;

#line 1115 "parse.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_COBOL_PARSE_H_INCLUDED  */
