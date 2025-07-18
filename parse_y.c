/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 10 "parse_y.y"

/*
 *                            COPYRIGHT
 *
 *  PCB, interactive printed circuit board design
 *  Copyright (C) 1994,1995,1996 Thomas Nau
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Contact addresses for paper mail and Email:
 *  Thomas Nau, Schlehenweg 15, 88471 Baustetten, Germany
 *  Thomas.Nau@rz.uni-ulm.de
 *
 */

/* grammar to parse ASCII input of PCB description
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "global.h"
#include "create.h"
#include "data.h"
#include "error.h"
#include "file.h"
#include "flags.h"
#include "layerflags.h"
#include "mymem.h"
#include "misc.h"
#include "parse_l.h"
#include "polygon.h"
#include "remove.h"
#include "rtree.h"
#include "strflags.h"
#include "thermal.h"
#include "move.h"

#ifdef HAVE_LIBDMALLOC
# include <dmalloc.h> /* see http://dmalloc.com */
#endif

static	LayerType	*Layer;
static	PolygonType	*Polygon;
static	SymbolType	*Symbol;
static	int		pin_num;
static	LibraryMenuType	*Menu;
static	bool			LayerFlag[MAX_ALL_LAYER];

enum FileType {NOFILE=0, PCBFILE, DATAFILE, FONTFILE} file_type;

extern	char		*yytext;		/* defined by LEX */
extern	PCBType		*yyPCB;
extern	DataType	*yyData;
extern	ElementType	*yyElement;
extern	FontType	*yyFont;
extern	int		yylineno;		/* linenumber */
extern	char		*yyfilename;	/* in this file */

static AttributeListType *attr_list; 

int yyerror(const char *s);
int yylex();
static int check_file_version (int);

static void do_measure (PLMeasure *m, Coord i, double d, int u);
#define M(r,f,d) do_measure (&(r), f, d, 1)

/* Macros for interpreting what "measure" means - integer value only,
   old units (mil), or new units (cmil).  */
#define IV(m) integer_value (m)
#define OU(m) old_units (m)
#define NU(m) new_units (m)

static int integer_value (PLMeasure m);
static Coord old_units (PLMeasure m);
static Coord new_units (PLMeasure m);

/*
#define YYDEBUG 1
#define YYERROR_VERBOSE 1
int yydebug=1;
*/

#include "parse_y.h"


#line 171 "parse_y.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FLOATING = 258,
    INTEGER = 259,
    CHAR_CONST = 260,
    STRING = 261,
    T_FILEVERSION = 262,
    T_PCB = 263,
    T_LAYER = 264,
    T_VIA = 265,
    T_RAT = 266,
    T_LINE = 267,
    T_ARC = 268,
    T_RECTANGLE = 269,
    T_TEXT = 270,
    T_ELEMENTLINE = 271,
    T_ELEMENT = 272,
    T_PIN = 273,
    T_PAD = 274,
    T_GRID = 275,
    T_FLAGS = 276,
    T_SYMBOL = 277,
    T_SYMBOLLINE = 278,
    T_CURSOR = 279,
    T_ELEMENTARC = 280,
    T_MARK = 281,
    T_GROUPS = 282,
    T_STYLES = 283,
    T_POLYGON = 284,
    T_POLYGON_HOLE = 285,
    T_NETLIST = 286,
    T_NET = 287,
    T_CONN = 288,
    T_AREA = 289,
    T_THERMAL = 290,
    T_DRC = 291,
    T_ATTRIBUTE = 292,
    T_UMIL = 293,
    T_CMIL = 294,
    T_MIL = 295,
    T_IN = 296,
    T_NM = 297,
    T_UM = 298,
    T_MM = 299,
    T_M = 300,
    T_KM = 301,
    T_PX = 302
  };
#endif
/* Tokens.  */
#define FLOATING 258
#define INTEGER 259
#define CHAR_CONST 260
#define STRING 261
#define T_FILEVERSION 262
#define T_PCB 263
#define T_LAYER 264
#define T_VIA 265
#define T_RAT 266
#define T_LINE 267
#define T_ARC 268
#define T_RECTANGLE 269
#define T_TEXT 270
#define T_ELEMENTLINE 271
#define T_ELEMENT 272
#define T_PIN 273
#define T_PAD 274
#define T_GRID 275
#define T_FLAGS 276
#define T_SYMBOL 277
#define T_SYMBOLLINE 278
#define T_CURSOR 279
#define T_ELEMENTARC 280
#define T_MARK 281
#define T_GROUPS 282
#define T_STYLES 283
#define T_POLYGON 284
#define T_POLYGON_HOLE 285
#define T_NETLIST 286
#define T_NET 287
#define T_CONN 288
#define T_AREA 289
#define T_THERMAL 290
#define T_DRC 291
#define T_ATTRIBUTE 292
#define T_UMIL 293
#define T_CMIL 294
#define T_MIL 295
#define T_IN 296
#define T_NM 297
#define T_UM 298
#define T_MM 299
#define T_M 300
#define T_KM 301
#define T_PX 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 114 "parse_y.y"

	int		integer;
	double		number;
	char		*string;
	FlagType	flagtype;
	PLMeasure	measure;

#line 325 "parse_y.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   771

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  110
/* YYNRULES -- Number of rules.  */
#define YYNRULES  209
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  631

#define YYUNDEFTOK  2
#define YYMAXUTOK   302


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      50,    51,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    48,     2,    49,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   140,   140,   141,   142,   143,   179,   179,   234,   234,
     262,   262,   265,   270,   270,   311,   312,   351,   357,   363,
     401,   402,   403,   406,   414,   427,   466,   471,   476,   493,
     494,   520,   521,   553,   554,   555,   556,   560,   570,   581,
     608,   612,   617,   645,   654,   710,   719,   728,   732,   733,
     737,   738,   742,   743,   743,   744,   745,   746,   746,   784,
     785,   786,   787,   788,   789,   851,   861,   871,   882,   892,
     902,   942,   947,   991,   990,  1020,  1021,  1025,  1026,  1030,
    1031,  1032,  1033,  1034,  1035,  1037,  1042,  1043,  1044,  1045,
    1045,  1046,  1085,  1094,  1103,  1160,  1169,  1178,  1224,  1234,
    1252,  1316,  1315,  1356,  1357,  1362,  1361,  1369,  1370,  1375,
    1379,  1450,  1451,  1452,  1453,  1454,  1462,  1461,  1480,  1479,
    1498,  1497,  1518,  1516,  1540,  1538,  1640,  1641,  1645,  1646,
    1647,  1648,  1649,  1651,  1656,  1661,  1666,  1671,  1676,  1681,
    1681,  1685,  1686,  1690,  1691,  1692,  1693,  1694,  1695,  1697,
    1703,  1710,  1715,  1720,  1720,  1770,  1782,  1794,  1805,  1821,
    1883,  1897,  1923,  1936,  1961,  1972,  1983,  1984,  1988,  1989,
    2022,  2024,  2040,  2059,  2060,  2064,  2065,  2066,  2096,  2103,
    2119,  2120,  2124,  2129,  2130,  2134,  2135,  2158,  2157,  2167,
    2168,  2172,  2173,  2192,  2251,  2259,  2260,  2264,  2265,  2270,
    2271,  2272,  2273,  2274,  2275,  2276,  2277,  2278,  2279,  2280
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FLOATING", "INTEGER", "CHAR_CONST",
  "STRING", "T_FILEVERSION", "T_PCB", "T_LAYER", "T_VIA", "T_RAT",
  "T_LINE", "T_ARC", "T_RECTANGLE", "T_TEXT", "T_ELEMENTLINE", "T_ELEMENT",
  "T_PIN", "T_PAD", "T_GRID", "T_FLAGS", "T_SYMBOL", "T_SYMBOLLINE",
  "T_CURSOR", "T_ELEMENTARC", "T_MARK", "T_GROUPS", "T_STYLES",
  "T_POLYGON", "T_POLYGON_HOLE", "T_NETLIST", "T_NET", "T_CONN", "T_AREA",
  "T_THERMAL", "T_DRC", "T_ATTRIBUTE", "T_UMIL", "T_CMIL", "T_MIL", "T_IN",
  "T_NM", "T_UM", "T_MM", "T_M", "T_KM", "T_PX", "'['", "']'", "'('",
  "')'", "$accept", "parse", "parsepcb", "$@1", "parsedata", "$@2",
  "pcbfont", "$@3", "parsefont", "$@4", "pcbfileversion", "pcbname",
  "pcbgrid", "pcbgridold", "pcbgridnew", "pcbhigrid", "pcbcursor",
  "polyarea", "pcbthermal", "pcbdrc", "pcbdrc1", "pcbdrc2", "pcbdrc3",
  "pcbflags", "pcbgroups", "pcbstyles", "pcbdata", "pcbdefinitions",
  "pcbdefinition", "$@5", "$@6", "via", "via_ehi_format", "via_hi_format",
  "via_2.0_format", "via_1.7_format", "via_newformat", "via_oldformat",
  "rats", "layer", "$@7", "layerdata", "layerdefinitions",
  "layerdefinition", "$@8", "line_hi_format", "line_1.7_format",
  "line_oldformat", "arc_hi_format", "arc_1.7_format", "arc_oldformat",
  "text_oldformat", "text_newformat", "text_hi_format", "polygon_format",
  "$@9", "polygonholes", "polygonhole", "$@10", "polygonpoints",
  "polygonpoint", "element", "element_oldformat", "$@11",
  "element_1.3.4_format", "$@12", "element_newformat", "$@13",
  "element_1.7_format", "$@14", "element_hi_format", "$@15",
  "elementdefinitions", "elementdefinition", "$@16", "relementdefs",
  "relementdef", "$@17", "pin_hi_format", "pin_1.7_format",
  "pin_1.6.3_format", "pin_newformat", "pin_oldformat", "pad_hi_format",
  "pad_hic_format", "pad_1.7_format", "pad_1.7c_format", "pad_newformat",
  "pad", "flags", "symbols", "symbol", "symbolhead", "symbolid",
  "symboldata", "symboldefinition", "hiressymbol", "pcbnetlist",
  "pcbnetdef", "nets", "netdefs", "net", "$@18", "connections", "conndefs",
  "conn", "attribute", "opt_string", "number", "measure", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,    91,    93,
      40,    41
};
# endif

#define YYPACT_NINF (-468)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-90)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     152,  -468,    37,  -468,    33,  -468,    55,  -468,    -5,  -468,
      -4,    45,    27,    90,   108,  -468,    55,  -468,    32,    74,
    -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,   132,
      -5,  -468,  -468,   110,   138,    95,   114,    19,    19,    19,
      19,  -468,    60,  -468,   168,  -468,  -468,  -468,  -468,  -468,
    -468,    23,    23,  -468,    -2,    70,   117,   120,   184,   105,
    -468,  -468,  -468,   127,  -468,  -468,   154,    19,    19,    19,
      19,   135,    48,   198,  -468,  -468,    19,    19,   197,  -468,
    -468,  -468,  -468,    19,     4,    19,    19,   209,   111,   148,
    -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,
      19,    19,   171,   183,   158,  -468,  -468,   166,   204,   222,
     186,   189,    19,    19,    19,  -468,    19,    19,    19,    19,
      19,   200,   214,  -468,   213,    19,    67,    19,    19,   226,
     274,   291,    19,   260,   267,    19,    19,   277,   276,    19,
      19,    19,    19,    19,   280,   293,   285,    19,   326,    80,
      19,    19,  -468,   330,   131,    19,  -468,  -468,    19,    19,
    -468,  -468,   333,    -1,    19,    19,   289,    19,   292,   318,
    -468,  -468,  -468,  -468,    19,   290,   338,   211,   339,   348,
      19,    19,    19,   354,    19,    19,   311,   308,  -468,   312,
     313,  -468,   316,    19,   317,   341,   136,   254,  -468,   315,
     365,   370,    48,   373,    19,    19,    19,   327,    19,    19,
    -468,  -468,  -468,  -468,  -468,    19,   261,   329,   352,   220,
     221,   331,   233,   334,   335,   136,  -468,    32,  -468,  -468,
    -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,   381,    48,
    -468,   340,   385,   343,   342,    19,    19,    19,   344,   353,
     350,    19,   355,   356,   397,   237,   382,    19,    19,    19,
      19,    19,    19,    19,    48,  -468,  -468,  -468,   399,   359,
    -468,   358,  -468,  -468,    19,    19,   406,  -468,  -468,  -468,
       8,  -468,  -468,   362,   408,   410,    55,  -468,    19,    19,
      19,    19,    19,    19,    19,   366,    48,  -468,  -468,    19,
      92,   367,   165,  -468,    10,  -468,   371,   368,   390,  -468,
      19,    19,    19,    19,    19,    19,    19,   374,   376,    19,
     379,    19,   377,   238,   383,   384,   241,   242,     0,  -468,
      32,  -468,  -468,  -468,  -468,  -468,  -468,    19,  -468,  -468,
     386,  -468,  -468,    19,    19,    19,    19,    19,    19,   223,
    -468,  -468,    48,   387,   427,  -468,    19,    19,    19,    19,
      19,    19,    19,    19,  -468,  -468,  -468,   389,   388,    19,
      19,    19,    19,   428,   429,   436,   435,   245,   393,  -468,
     392,   165,    19,    19,    19,    19,    19,    19,    19,    19,
    -468,   394,    19,    19,    19,    19,   395,    48,   398,   441,
      19,    19,  -468,   245,   400,   165,   401,    17,    19,    19,
      19,    19,    19,    19,   403,   402,   416,    48,     5,    19,
      19,  -468,   405,  -468,   404,    19,    19,   -10,  -468,  -468,
     106,  -468,  -468,    19,    19,   227,    19,    19,    19,  -468,
    -468,   407,   411,   416,  -468,   409,   412,  -468,    19,    96,
    -468,  -468,   415,   414,   424,  -468,  -468,   187,  -468,   187,
      19,    19,   452,   453,    19,    19,    19,   469,  -468,  -468,
    -468,  -468,    48,   425,   473,  -468,  -468,  -468,   246,   250,
     253,   265,    42,  -468,    32,  -468,  -468,  -468,  -468,  -468,
    -468,   160,   430,   431,   432,   298,   472,    19,    19,   474,
     437,  -468,   438,   245,    19,    19,    19,    19,    19,    19,
      19,    19,  -468,  -468,  -468,  -468,  -468,  -468,  -468,   447,
     477,   310,    19,    19,   448,  -468,  -468,   449,    19,    19,
      19,    19,    19,    19,    19,    19,  -468,   450,   451,   483,
     439,   454,   464,  -468,    19,    19,    19,    19,    19,    19,
      19,    19,  -468,  -468,   465,  -468,  -468,  -468,    19,    19,
      19,    19,    19,    19,    19,    19,  -468,   471,    19,    19,
      19,    19,    19,    19,    19,    19,   467,   468,   471,  -468,
     466,   478,    19,    19,    19,    19,    19,    19,   512,  -468,
    -468,  -468,  -468,   522,   530,   235,   240,    19,    19,   488,
     534,   535,   536,   537,   545,   546,   504,   503,  -468,    48,
     551,    48,   550,   557,   556,  -468,  -468,   514,   513,   516,
      48,   515,   563,  -468,  -468,  -468,   520,  -468,   519,  -468,
    -468
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     0,     2,    15,     3,    49,     4,     0,     1,
       0,     0,     0,     0,     0,     9,    48,    50,     0,     0,
      52,    59,    60,    61,    62,    63,    64,    55,    56,     0,
      14,   168,   175,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,    54,     0,    58,   111,   112,   113,   114,
     115,     0,     0,   169,     0,     0,     0,     0,     0,    28,
      20,    21,    22,     0,   197,   198,   199,     0,     0,     0,
       0,     0,     0,     0,   173,   174,     0,     0,     0,   170,
     176,   177,    16,     0,     0,     0,     0,     0,    29,   196,
     200,   201,   202,   203,   204,   206,   207,   208,   209,   205,
       0,     0,     0,     0,     0,   166,   167,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,     0,     0,
       0,     0,    31,   195,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,   194,     0,     0,     0,   171,   172,     0,     0,
      19,    18,     0,     0,     0,     0,     0,     0,     0,    42,
      34,    35,    36,    73,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    23,     0,
       0,    30,     0,     0,     0,    44,    76,     0,    70,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      25,    24,    27,    26,    32,     0,     0,     0,    47,     0,
       0,     0,     0,     0,     0,    75,    77,     0,    79,    80,
      81,    82,    83,    84,    88,    87,    86,    91,     0,     0,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,     0,     0,     0,
       0,     0,     0,     0,     0,    74,    78,    90,     0,     0,
      68,     0,    71,    72,     0,     0,     0,   116,   179,   178,
       0,    40,    41,     0,     0,     0,    49,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    66,    67,     0,
       0,     0,   139,    37,     0,    43,     0,     0,   181,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     198,     0,     0,     0,     0,     0,     0,     0,   139,   126,
       0,   128,   129,   130,   131,   132,    38,     0,    46,    45,
       0,     7,   180,     0,     0,     0,     0,     0,     0,     0,
     101,    65,     0,     0,     0,   118,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   127,   140,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   107,     0,   120,
       0,   139,     0,     0,     0,     0,     0,     0,     0,     0,
      39,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   103,   107,     0,   139,     0,   139,     0,     0,
       0,     0,     0,     0,     0,     0,   184,     0,     0,     0,
       0,    85,     0,    98,     0,     0,     0,     0,   108,   124,
     139,   122,   119,     0,     0,     0,     0,     0,     0,   137,
     138,     0,     0,   183,   185,     0,     0,    94,     0,     0,
     100,    99,     0,     0,     0,   102,   104,   153,   121,   153,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   186,
      92,    93,     0,   198,     0,   110,   109,   105,     0,     0,
       0,     0,   153,   141,     0,   144,   143,   147,   148,   145,
     146,   153,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    97,     0,   107,     0,     0,     0,     0,     0,     0,
       0,     0,   125,   142,   154,   123,   133,   134,   159,     0,
       0,     0,     0,     0,     0,    95,    96,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   158,     0,     0,     0,
       0,     0,     0,   106,     0,     0,     0,     0,     0,     0,
       0,     0,   157,   165,     0,   135,   136,   187,     0,     0,
       0,     0,     0,     0,     0,     0,   164,   190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   189,   191,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   188,
     192,   149,   150,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   193,     0,
       0,     0,     0,     0,     0,   151,   152,     0,     0,     0,
       0,     0,     0,   155,   156,   161,     0,   163,     0,   160,
     162
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,   284,  -468,
    -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,
    -468,  -468,  -468,  -468,  -468,  -468,   286,  -468,   558,  -468,
    -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,
    -468,  -468,  -468,   351,  -468,  -468,  -468,  -468,  -468,  -468,
    -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -398,
    -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,
    -468,  -468,  -371,  -322,  -468,   116,  -467,  -468,  -468,  -468,
    -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,  -468,   151,
    -468,   543,  -468,   525,  -468,  -468,  -468,  -468,  -468,  -468,
    -468,   137,  -468,  -468,  -468,     1,  -223,  -468,   -37,   -38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,     6,   286,   287,     7,     8,
      11,    35,    59,    60,    61,    62,    88,   122,   145,   169,
     170,   171,   172,   195,   218,   256,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
     196,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   377,   427,   456,   503,   402,
     403,    45,    46,   302,    47,   381,    48,   405,    49,   459,
      50,   457,   328,   329,   330,   482,   483,   484,   485,   486,
     331,   332,   333,   487,   488,   489,   490,   334,   335,   107,
      30,    31,    32,    76,    54,    80,    81,   341,   342,   442,
     443,   444,   567,   577,   578,   579,    43,   124,    66,    67
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    69,    70,   187,   267,   428,   365,    64,    65,   446,
     407,    64,    65,    64,    65,   513,   323,    29,   324,   325,
     454,    78,    64,    65,   513,   326,   327,    74,    75,   100,
     101,   102,   103,   323,   430,   324,   325,     9,   110,   111,
      10,   455,   326,   327,    33,   114,   116,   117,   118,    79,
     188,   364,   105,    34,   106,   115,   447,   303,   478,   336,
     479,   480,   125,   126,    12,    13,    14,   481,   432,    42,
      64,    65,   -57,   148,   135,   136,   137,    36,   138,   139,
     140,   141,   142,    64,    65,   365,   176,   147,   149,   150,
     151,    44,   -53,   512,   155,    64,   320,   158,   159,    64,
     473,   162,   163,   164,   165,   527,   166,   366,   365,   174,
      71,   177,   178,   179,    55,    58,   182,   183,    63,    82,
     184,   185,   323,    83,   324,   325,    84,   189,   190,    87,
     192,   326,   327,    89,    64,    65,   197,   181,    37,   201,
      38,   104,   204,   205,   206,   121,   208,   209,   219,   220,
     221,   222,    -8,     1,   123,   215,    39,   458,    40,    -6,
      -6,    -8,    -8,    -8,   129,   223,   245,   246,   247,    -8,
     249,   250,   130,   -89,   -13,   127,   478,   251,   479,   480,
      51,   323,    52,   324,   325,   481,    56,   128,    57,    -8,
     326,   327,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   108,   478,   109,   479,   480,   274,   275,   276,
     131,   515,   481,   280,    64,    65,    72,   200,    73,   288,
     289,   290,   291,   292,   293,   294,    64,    65,   132,   375,
      64,    65,    85,   462,    86,   133,   299,   300,    64,    65,
     134,   602,   304,    64,    65,   112,   604,   113,   143,   144,
     310,   311,   312,   313,   314,   315,   316,   119,   238,   120,
     239,   514,   319,   321,   146,   252,   337,   253,   257,   259,
     258,   260,   343,   344,   345,   346,   347,   152,   348,   349,
     153,   262,   352,   263,   354,   284,   356,   285,   357,   360,
     362,   361,   363,   400,   504,   401,   505,   154,   506,   367,
     507,   508,   519,   509,   520,   369,   370,   371,   372,   373,
     156,   374,   376,   510,   538,   511,   539,   157,   382,   383,
     384,   385,   386,   387,   388,   389,   160,   161,   167,   168,
     175,   392,   393,   394,   395,   173,   180,   186,   191,   194,
     193,   198,   199,   202,   408,   409,   410,   411,   412,   413,
     414,   415,   203,   243,   417,   418,   419,   420,   207,   211,
     210,   212,   425,   426,   213,   214,   240,   216,   217,   241,
     433,   434,   435,   436,   437,   438,   242,   244,   248,   254,
     255,   261,   448,   449,   264,   268,   265,   452,   453,   271,
     269,   270,   272,   273,   277,   460,   461,   463,   464,   465,
     466,   279,   278,   283,   -10,   296,   281,   282,   297,   298,
     301,   472,   474,   305,   306,   295,   307,   317,   322,   339,
     338,   340,   492,   493,   350,   351,   496,   355,   497,   498,
     353,   380,   396,   358,   359,   397,   368,   379,   390,   391,
     398,   399,   404,   406,   416,   424,   421,   318,   441,   423,
     429,   431,   439,   440,   450,   451,   494,   467,   470,   495,
     522,   523,   468,   471,   475,   476,   528,   529,   530,   531,
     532,   533,   534,   535,   477,   499,   501,   502,   521,   516,
     524,   537,   517,   518,   540,   541,   525,   554,   555,   526,
     544,   545,   546,   547,   548,   549,   550,   551,   536,   542,
     543,   552,   553,   378,   576,   556,   558,   559,   560,   561,
     562,   563,   564,   565,   557,   591,   566,   588,   599,   589,
     568,   569,   570,   571,   572,   573,   574,   575,   600,   592,
     580,   581,   582,   583,   584,   585,   601,   586,   587,   608,
     609,   610,   611,   612,   593,   594,   595,   596,   422,   597,
     598,   613,   614,   615,   616,   618,   620,   603,   605,   606,
     607,   621,   622,   623,   624,   625,   627,   628,   445,   629,
     630,   309,   308,    53,    41,   491,   266,    77,     0,   590,
     469,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   500,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     617,     0,   619,     0,     0,     0,     0,     0,     0,     0,
       0,   626
};

static const yytype_int16 yycheck[] =
{
      38,    39,    40,     4,   227,   403,   328,     3,     4,     4,
     381,     3,     4,     3,     4,   482,    16,    22,    18,    19,
      30,    23,     3,     4,   491,    25,    26,     4,     5,    67,
      68,    69,    70,    16,   405,    18,    19,     0,    76,    77,
       7,    51,    25,    26,    48,    83,    84,    85,    86,    51,
      51,    51,     4,     8,     6,    51,    51,    49,    16,    49,
      18,    19,   100,   101,     9,    10,    11,    25,    51,    37,
       3,     4,    17,     6,   112,   113,   114,    50,   116,   117,
     118,   119,   120,     3,     4,   407,     6,   125,   126,   127,
     128,    17,    37,    51,   132,     3,     4,   135,   136,     3,
       4,   139,   140,   141,   142,   503,   143,   330,   430,   147,
      50,   149,   150,   151,     4,    20,   154,   155,     4,    49,
     158,   159,    16,     6,    18,    19,     6,   164,   165,    24,
     167,    25,    26,     6,     3,     4,   174,     6,    48,   177,
      50,     6,   180,   181,   182,    34,   184,   185,    12,    13,
      14,    15,     0,     1,     6,   193,    48,    51,    50,     7,
       8,     9,    10,    11,     6,    29,   204,   205,   206,    17,
     208,   209,     6,    37,    22,     4,    16,   215,    18,    19,
      48,    16,    50,    18,    19,    25,    48,     4,    50,    37,
      25,    26,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     4,    16,     6,    18,    19,   245,   246,   247,
       6,    51,    25,   251,     3,     4,    48,     6,    50,   257,
     258,   259,   260,   261,   262,   263,     3,     4,     6,     6,
       3,     4,    48,     6,    50,    49,   274,   275,     3,     4,
      51,     6,   280,     3,     4,    48,     6,    50,    48,    35,
     288,   289,   290,   291,   292,   293,   294,    48,     4,    50,
       6,   484,   299,   300,    51,     4,   304,     6,    48,    48,
      50,    50,   310,   311,   312,   313,   314,    51,   315,   316,
       6,    48,   319,    50,   321,    48,    48,    50,    50,    48,
      48,    50,    50,    48,    48,    50,    50,     6,    48,   337,
      50,    48,     4,    50,     6,   343,   344,   345,   346,   347,
      50,   348,   349,    48,     4,    50,     6,    50,   356,   357,
     358,   359,   360,   361,   362,   363,    49,    51,    48,    36,
       4,   369,   370,   371,   372,    50,     6,     4,    49,    21,
      48,    51,     4,     4,   382,   383,   384,   385,   386,   387,
     388,   389,     4,   202,   392,   393,   394,   395,     4,    51,
      49,    49,   400,   401,    51,    49,    51,    50,    27,     4,
     408,   409,   410,   411,   412,   413,     6,     4,    51,    50,
      28,    50,   419,   420,    50,     4,    51,   425,   426,     4,
     239,    51,    49,    51,    50,   433,   434,   435,   436,   437,
     438,    51,    49,     6,    22,     6,    51,    51,    49,    51,
       4,   448,   449,    51,     6,   264,     6,    51,    51,    51,
      49,    31,   460,   461,    50,    49,   464,    50,   465,   466,
      51,     4,     4,    50,    50,     6,    50,    50,    49,    51,
       4,     6,    49,    51,    50,     4,    51,   296,    32,    51,
      50,    50,    49,    51,    49,    51,     4,    50,    49,     6,
     497,   498,    51,    51,    49,    51,   504,   505,   506,   507,
     508,   509,   510,   511,    50,     6,    51,     4,     6,    49,
       6,     4,    51,    51,   522,   523,    49,     4,    49,    51,
     528,   529,   530,   531,   532,   533,   534,   535,    51,    51,
      51,    51,    51,   352,    33,    51,   544,   545,   546,   547,
     548,   549,   550,   551,    50,    49,    51,    50,     6,    51,
     558,   559,   560,   561,   562,   563,   564,   565,     6,    51,
     568,   569,   570,   571,   572,   573,     6,   574,   575,    51,
       6,     6,     6,     6,   582,   583,   584,   585,   397,   586,
     587,     6,     6,    49,    51,     4,     6,   595,   596,   597,
     598,     4,     6,    49,    51,    49,    51,     4,   417,    49,
      51,   287,   286,    30,    16,   459,   225,    52,    -1,   578,
     443,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   472,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     609,    -1,   611,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   620
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    53,    54,    55,    56,    57,    60,    61,     0,
       7,    62,     9,    10,    11,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    22,
     142,   143,   144,    48,     8,    63,    50,    48,    50,    48,
      50,    80,    37,   158,    17,   113,   114,   116,   118,   120,
     122,    48,    50,   143,   146,     4,    48,    50,    20,    64,
      65,    66,    67,     4,     3,     4,   160,   161,   161,   161,
     161,    50,    48,    50,     4,     5,   145,   145,    23,    51,
     147,   148,    49,     6,     6,    48,    50,    24,    68,     6,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
     161,   161,   161,   161,     6,     4,     6,   141,     4,     6,
     161,   161,    48,    50,   161,    51,   161,   161,   161,    48,
      50,    34,    69,     6,   159,   161,   161,     4,     4,     6,
       6,     6,     6,    49,    51,   161,   161,   161,   161,   161,
     161,   161,   161,    48,    35,    70,    51,   161,     6,   161,
     161,   161,    51,     6,     6,   161,    50,    50,   161,   161,
      49,    51,   161,   161,   161,   161,   160,    48,    36,    71,
      72,    73,    74,    50,   161,     4,     6,   161,   161,   161,
       6,     6,   161,   161,   161,   161,     4,     4,    51,   160,
     160,    49,   160,    48,    21,    75,    92,   161,    51,     4,
       6,   161,     4,     4,   161,   161,   161,     4,   161,   161,
      49,    51,    49,    51,    49,   161,    50,    27,    76,    12,
      13,    14,    15,    29,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,     4,     6,
      51,     4,     6,   141,     4,   161,   161,   161,    51,   161,
     161,   161,     4,     6,    50,    28,    77,    48,    50,    48,
      50,    50,    48,    50,    50,    51,    95,   158,     4,   141,
      51,     4,    49,    51,   161,   161,   161,    50,    49,    51,
     161,    51,    51,     6,    48,    50,    58,    59,   161,   161,
     161,   161,   161,   161,   161,   141,     6,    49,    51,   161,
     161,     4,   115,    49,   161,    51,     6,     6,    78,    60,
     161,   161,   161,   161,   161,   161,   161,    51,   141,   160,
       4,   160,    51,    16,    18,    19,    25,    26,   124,   125,
     126,   132,   133,   134,   139,   140,    49,   161,    49,    51,
      31,   149,   150,   161,   161,   161,   161,   161,   160,   160,
      50,    49,   160,    51,   160,    50,    48,    50,    50,    50,
      48,    50,    48,    50,    51,   125,   158,   161,    50,   161,
     161,   161,   161,   161,   160,     6,   160,   107,   141,    50,
       4,   117,   161,   161,   161,   161,   161,   161,   161,   161,
      49,    51,   161,   161,   161,   161,     4,     6,     4,     6,
      48,    50,   111,   112,    49,   119,    51,   124,   161,   161,
     161,   161,   161,   161,   161,   161,    50,   161,   161,   161,
     161,    51,   141,    51,     4,   161,   161,   108,   111,    50,
     124,    50,    51,   161,   161,   161,   161,   161,   161,    49,
      51,    32,   151,   152,   153,   141,     4,    51,   160,   160,
      49,    51,   161,   161,    30,    51,   109,   123,    51,   121,
     161,   161,     6,   161,   161,   161,   161,    50,    51,   153,
      49,    51,   160,     4,   160,    49,    51,    50,    16,    18,
      19,    25,   127,   128,   129,   130,   131,   135,   136,   137,
     138,   127,   161,   161,     4,     6,   161,   160,   160,     6,
     141,    51,     4,   110,    48,    50,    48,    50,    48,    50,
      48,    50,    51,   128,   158,    51,    49,    51,    51,     4,
       6,     6,   160,   160,     6,    49,    51,   111,   161,   161,
     161,   161,   161,   161,   161,   161,    51,     4,     4,     6,
     161,   161,    51,    51,   161,   161,   161,   161,   161,   161,
     161,   161,    51,    51,     4,    49,    51,    50,   161,   161,
     161,   161,   161,   161,   161,   161,    51,   154,   161,   161,
     161,   161,   161,   161,   161,   161,    33,   155,   156,   157,
     161,   161,   161,   161,   161,   161,   160,   160,    50,    51,
     157,    49,    51,   161,   161,   161,   161,   160,   160,     6,
       6,     6,     6,   161,     6,   161,   161,   161,    51,     6,
       6,     6,     6,     6,     6,    49,    51,   141,     4,   141,
       6,     4,     6,    49,    51,    49,   141,    51,     4,    49,
      51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    53,    53,    53,    55,    54,    57,    56,
      59,    58,    58,    61,    60,    62,    62,    63,    63,    63,
      64,    64,    64,    65,    66,    67,    68,    68,    68,    69,
      69,    70,    70,    71,    71,    71,    71,    72,    73,    74,
      75,    75,    75,    76,    76,    77,    77,    77,    78,    78,
      79,    79,    80,    81,    80,    80,    80,    82,    80,    83,
      83,    83,    83,    83,    83,    84,    85,    86,    87,    88,
      89,    90,    90,    92,    91,    93,    93,    94,    94,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    96,
      95,    95,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   107,   106,   108,   108,   110,   109,   111,   111,   112,
     112,   113,   113,   113,   113,   113,   115,   114,   117,   116,
     119,   118,   121,   120,   123,   122,   124,   124,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   126,
     125,   127,   127,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   129,   128,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   141,   142,   142,
     143,   144,   144,   145,   145,   146,   146,   146,   147,   148,
     149,   149,   150,   151,   151,   152,   152,   154,   153,   155,
     155,   156,   156,   157,   158,   159,   159,   160,   160,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     0,    14,     0,     2,
       0,     2,     0,     0,     2,     0,     4,     4,     6,     6,
       1,     1,     1,     6,     7,     7,     6,     6,     0,     0,
       4,     0,     4,     0,     1,     1,     1,     6,     7,     9,
       4,     4,     0,     4,     0,     4,     4,     0,     1,     0,
       1,     2,     1,     0,     2,     1,     1,     0,     2,     1,
       1,     1,     1,     1,     1,    13,    11,    11,    10,     9,
       8,    10,    10,     0,    10,     1,     0,     1,     2,     1,
       1,     1,     1,     1,     1,     8,     1,     1,     1,     0,
       2,     1,    10,    10,     9,    12,    12,    11,     8,     9,
       9,     0,     9,     0,     2,     0,     5,     0,     2,     4,
       4,     1,     1,     1,     1,     1,     0,    12,     0,    15,
       0,    16,     0,    18,     0,    18,     1,     2,     1,     1,
       1,     1,     1,     8,     8,    10,    10,     5,     5,     0,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     8,
       8,    10,    10,     0,     2,    12,    12,    10,     9,     8,
      13,    12,    13,    12,    11,    10,     1,     1,     1,     2,
       3,     6,     6,     1,     1,     0,     2,     2,     8,     8,
       1,     0,     6,     1,     0,     1,     2,     0,     9,     1,
       0,     1,     2,     4,     5,     1,     0,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 5:
#line 143 "parse_y.y"
                        { YYABORT; }
#line 1949 "parse_y.c"
    break;

  case 6:
#line 179 "parse_y.y"
                        {       /* reset flags for 'used layers';
					 * init font and data pointers
					 */
				int	i;
                file_type = PCBFILE;
				if (!yyPCB)
				{
					Message(_("illegal pcb file format\n"));
					YYABORT;
				}
				for (i = 0; i < MAX_ALL_LAYER; i++)
					LayerFlag[i] = false;
				yyFont = &yyPCB->Font;
				yyData = yyPCB->Data;
				yyData->pcb = yyPCB;
				yyData->LayerN = 0;
				/* Parse the default layer group string, just in case the file doesn't have one */
				if (ParseGroupString (Settings.Groups, &yyPCB->LayerGroups, &yyData->LayerN))
				    {
				      Message(_("illegal default layer-group string\n"));
				      YYABORT;
				    }
			}
#line 1977 "parse_y.c"
    break;

  case 7:
#line 215 "parse_y.y"
                        {
			  PCBType *pcb_save = PCB;

			  CreateNewPCBPost (yyPCB, 0);
			/* initialize the polygon clipping now since
			 * we didn't know the layer grouping before.
			 */
			PCB = yyPCB;
			ALLPOLYGON_LOOP (yyData);
			{
			  InitClip (yyData, layer, polygon);
			}
			ENDALL_LOOP;
			PCB = pcb_save;
			}
#line 1997 "parse_y.c"
    break;

  case 8:
#line 234 "parse_y.y"
                        {
					/* reset flags for 'used layers';
					 * init font and data pointers
					 */
				int	i;
                file_type = DATAFILE;
                /* Loading a footprint file as a layout */
				if (yyPCB)
                {
				    yyFont = &yyPCB->Font;
				    yyData = yyPCB->Data;
    				yyData->pcb = yyPCB;
                }
                /* e.g. loading data to a buffer */ 
                else if (!yyData || !yyFont)
				{
					Message(_("PCB data not initialized! Cannot load data file\n"));
					YYABORT;
				}

				for (i = 0; i < MAX_ALL_LAYER; i++)
					LayerFlag[i] = false;
				yyData->LayerN = 0;
			}
#line 2026 "parse_y.c"
    break;

  case 10:
#line 262 "parse_y.y"
                  { 
            file_type = FONTFILE;
          }
#line 2034 "parse_y.c"
    break;

  case 13:
#line 270 "parse_y.y"
                        {
					/* mark all symbols invalid */
				int	i;

				if (!yyFont)
				{
					Message(_("illegal file format\n"));
					YYABORT;
				}
				yyFont->Valid = false;
				for (i = 0; i <= MAX_FONTPOSITION; i++)
					free (yyFont->Symbol[i].Line);
				bzero(yyFont->Symbol, sizeof(yyFont->Symbol));
			}
#line 2053 "parse_y.c"
    break;

  case 14:
#line 285 "parse_y.y"
                        {
				yyFont->Valid = true;
		  		SetFontInfo(yyFont);
			}
#line 2062 "parse_y.c"
    break;

  case 16:
#line 313 "parse_y.y"
{
  if (check_file_version ((yyvsp[-1].integer)) != 0)
    {
      YYABORT;
    }
}
#line 2073 "parse_y.c"
    break;

  case 17:
#line 352 "parse_y.y"
                        {
				yyPCB->Name = (yyvsp[-1].string);
				yyPCB->MaxWidth = MAX_COORD;
				yyPCB->MaxHeight = MAX_COORD;
			}
#line 2083 "parse_y.c"
    break;

  case 18:
#line 358 "parse_y.y"
                        {
				yyPCB->Name = (yyvsp[-3].string);
				yyPCB->MaxWidth = OU ((yyvsp[-2].measure));
				yyPCB->MaxHeight = OU ((yyvsp[-1].measure));
			}
#line 2093 "parse_y.c"
    break;

  case 19:
#line 364 "parse_y.y"
                        {
				yyPCB->Name = (yyvsp[-3].string);
				yyPCB->MaxWidth = NU ((yyvsp[-2].measure));
				yyPCB->MaxHeight = NU ((yyvsp[-1].measure));
			}
#line 2103 "parse_y.c"
    break;

  case 23:
#line 407 "parse_y.y"
                        {
				yyPCB->Grid = OU ((yyvsp[-3].measure));
				yyPCB->GridOffsetX = OU ((yyvsp[-2].measure));
				yyPCB->GridOffsetY = OU ((yyvsp[-1].measure));
			}
#line 2113 "parse_y.c"
    break;

  case 24:
#line 415 "parse_y.y"
                        {
				yyPCB->Grid = OU ((yyvsp[-4].measure));
				yyPCB->GridOffsetX = OU ((yyvsp[-3].measure));
				yyPCB->GridOffsetY = OU ((yyvsp[-2].measure));
				if ((yyvsp[-1].integer))
					Settings.DrawGrid = true;
				else
					Settings.DrawGrid = false;
			}
#line 2127 "parse_y.c"
    break;

  case 25:
#line 428 "parse_y.y"
                        {
				yyPCB->Grid = NU ((yyvsp[-4].measure));
				yyPCB->GridOffsetX = NU ((yyvsp[-3].measure));
				yyPCB->GridOffsetY = NU ((yyvsp[-2].measure));
				if ((yyvsp[-1].integer))
					Settings.DrawGrid = true;
				else
					Settings.DrawGrid = false;
			}
#line 2141 "parse_y.c"
    break;

  case 26:
#line 467 "parse_y.y"
                        {
				yyPCB->CursorX = OU ((yyvsp[-3].measure));
				yyPCB->CursorY = OU ((yyvsp[-2].measure));
			}
#line 2150 "parse_y.c"
    break;

  case 27:
#line 472 "parse_y.y"
                        {
				yyPCB->CursorX = NU ((yyvsp[-3].measure));
				yyPCB->CursorY = NU ((yyvsp[-2].measure));
			}
#line 2159 "parse_y.c"
    break;

  case 30:
#line 495 "parse_y.y"
                        {
				/* Read in cmil^2 for now; in future this should be a noop. */
				yyPCB->IsleArea = MIL_TO_COORD (MIL_TO_COORD ((yyvsp[-1].number)) / 100.0) / 100.0;
			}
#line 2168 "parse_y.c"
    break;

  case 32:
#line 522 "parse_y.y"
                        {
				yyPCB->ThermScale = (yyvsp[-1].number);
			}
#line 2176 "parse_y.c"
    break;

  case 37:
#line 561 "parse_y.y"
                        {
				yyPCB->Bloat = NU ((yyvsp[-3].measure));
				yyPCB->Shrink = NU ((yyvsp[-2].measure));
				yyPCB->minWid = NU ((yyvsp[-1].measure));
				yyPCB->minRing = NU ((yyvsp[-1].measure));
			}
#line 2187 "parse_y.c"
    break;

  case 38:
#line 571 "parse_y.y"
                        {
				yyPCB->Bloat = NU ((yyvsp[-4].measure));
				yyPCB->Shrink = NU ((yyvsp[-3].measure));
				yyPCB->minWid = NU ((yyvsp[-2].measure));
				yyPCB->minSlk = NU ((yyvsp[-1].measure));
				yyPCB->minRing = NU ((yyvsp[-2].measure));
			}
#line 2199 "parse_y.c"
    break;

  case 39:
#line 582 "parse_y.y"
                        {
				yyPCB->Bloat = NU ((yyvsp[-6].measure));
				yyPCB->Shrink = NU ((yyvsp[-5].measure));
				yyPCB->minWid = NU ((yyvsp[-4].measure));
				yyPCB->minSlk = NU ((yyvsp[-3].measure));
				yyPCB->minDrill = NU ((yyvsp[-2].measure));
				yyPCB->minRing = NU ((yyvsp[-1].measure));
			}
#line 2212 "parse_y.c"
    break;

  case 40:
#line 609 "parse_y.y"
                        {
				yyPCB->Flags = MakeFlags ((yyvsp[-1].integer) & PCB_FLAGS);
			}
#line 2220 "parse_y.c"
    break;

  case 41:
#line 613 "parse_y.y"
                        {
			  yyPCB->Flags = string_to_pcbflags ((yyvsp[-1].string), yyerror);
                          free ((yyvsp[-1].string));
			}
#line 2229 "parse_y.c"
    break;

  case 43:
#line 646 "parse_y.y"
                        {
			  if (ParseGroupString ((yyvsp[-1].string), &yyPCB->LayerGroups, &yyData->LayerN))
			    {
			      Message(_("illegal layer-group string\n"));
			      YYABORT;
			    }
                            free ((yyvsp[-1].string));
			}
#line 2242 "parse_y.c"
    break;

  case 45:
#line 711 "parse_y.y"
                        {
				if (ParseRouteString(((yyvsp[-1].string) == NULL ? "" : (yyvsp[-1].string)), &yyPCB->RouteStyle[0], "mil"))
				{
					Message(_("illegal route-style string\n"));
					YYABORT;
				}
                                free ((yyvsp[-1].string));
			}
#line 2255 "parse_y.c"
    break;

  case 46:
#line 720 "parse_y.y"
                        {
				if (ParseRouteString(((yyvsp[-1].string) == NULL ? "" : (yyvsp[-1].string)), &yyPCB->RouteStyle[0], "cmil"))
				{
					Message(_("illegal route-style string\n"));
					YYABORT;
				}
                                free ((yyvsp[-1].string));
			}
#line 2268 "parse_y.c"
    break;

  case 53:
#line 743 "parse_y.y"
                  { attr_list = & yyPCB->Attributes; }
#line 2274 "parse_y.c"
    break;

  case 57:
#line 746 "parse_y.y"
          {
            if ( file_type == DATAFILE ) {
 
		      if (yyPCB != NULL)
		        {
			  /* This case is when we load a footprint with file->open, or from the command line */
			  yyFont = &yyPCB->Font;
			  yyData = yyPCB->Data;
			  yyData->pcb = yyPCB;
			  yyData->LayerN = 0;
		        }
		    }
          }
#line 2292 "parse_y.c"
    break;

  case 58:
#line 760 "parse_y.y"
                  {
            if (file_type == DATAFILE){
		      PCBType *pcb_save = PCB;
		      ElementType *e;
		      if (yyPCB != NULL)
		        {
			  /* This case is when we load a footprint with file->open, or from the command line */
			  CreateNewPCBPost (yyPCB, 0);
			  ParseGroupString("1,c:2,s", &yyPCB->LayerGroups, &yyData->LayerN);
			  e = yyPCB->Data->Element->data; /* we know there's only one */
			  PCB = yyPCB;
			  MoveElementLowLevel (yyPCB->Data, e, -e->BoundingBox.X1, -e->BoundingBox.Y1);
			  PCB = pcb_save;
			  yyPCB->MaxWidth = e->BoundingBox.X2;
			  yyPCB->MaxHeight = e->BoundingBox.Y2;
			  yyPCB->is_footprint = 1;
		        }
            }
		  }
#line 2316 "parse_y.c"
    break;

  case 65:
#line 852 "parse_y.y"
                        {
				CreateNewViaEx (yyData, NU ((yyvsp[-10].measure)), NU ((yyvsp[-9].measure)), NU ((yyvsp[-8].measure)), NU ((yyvsp[-7].measure)), NU ((yyvsp[-6].measure)),
						     NU ((yyvsp[-5].measure)), (yyvsp[-2].string), (yyvsp[-1].flagtype), (yyvsp[-4].integer), (yyvsp[-3].integer));
				free ((yyvsp[-2].string));
			}
#line 2326 "parse_y.c"
    break;

  case 66:
#line 862 "parse_y.y"
                        {
				CreateNewVia(yyData, NU ((yyvsp[-8].measure)), NU ((yyvsp[-7].measure)), NU ((yyvsp[-6].measure)), NU ((yyvsp[-5].measure)), NU ((yyvsp[-4].measure)),
				                     NU ((yyvsp[-3].measure)), (yyvsp[-2].string), (yyvsp[-1].flagtype));
				free ((yyvsp[-2].string));
			}
#line 2336 "parse_y.c"
    break;

  case 67:
#line 872 "parse_y.y"
                        {
				CreateNewVia(yyData, OU ((yyvsp[-8].measure)), OU ((yyvsp[-7].measure)), OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), OU ((yyvsp[-3].measure)), (yyvsp[-2].string),
					OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-2].string));
			}
#line 2346 "parse_y.c"
    break;

  case 68:
#line 883 "parse_y.y"
                        {
				CreateNewVia(yyData, OU ((yyvsp[-7].measure)), OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)),
					     OU ((yyvsp[-5].measure)) + OU((yyvsp[-4].measure)), OU ((yyvsp[-3].measure)), (yyvsp[-2].string), OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-2].string));
			}
#line 2356 "parse_y.c"
    break;

  case 69:
#line 893 "parse_y.y"
                        {
				CreateNewVia(yyData, OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), 2*GROUNDPLANEFRAME,
					OU((yyvsp[-4].measure)) + 2*MASKFRAME,  OU ((yyvsp[-3].measure)), (yyvsp[-2].string), OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-2].string));
			}
#line 2366 "parse_y.c"
    break;

  case 70:
#line 903 "parse_y.y"
                        {
				Coord	hole = (OU((yyvsp[-3].measure)) * DEFAULT_DRILLINGHOLE);

				CreateNewVia(yyData, OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), OU ((yyvsp[-3].measure)), 2*GROUNDPLANEFRAME,
					OU((yyvsp[-3].measure)) + 2*MASKFRAME, hole, (yyvsp[-2].string), OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-2].string));
			}
#line 2378 "parse_y.c"
    break;

  case 71:
#line 943 "parse_y.y"
                        {
				CreateNewRat(yyData, NU ((yyvsp[-7].measure)), NU ((yyvsp[-6].measure)), NU ((yyvsp[-4].measure)), NU ((yyvsp[-3].measure)), (yyvsp[-5].integer), (yyvsp[-2].integer),
					Settings.RatThickness, (yyvsp[-1].flagtype));
			}
#line 2387 "parse_y.c"
    break;

  case 72:
#line 948 "parse_y.y"
                        {
				CreateNewRat(yyData, OU ((yyvsp[-7].measure)), OU ((yyvsp[-6].measure)), OU ((yyvsp[-4].measure)), OU ((yyvsp[-3].measure)), (yyvsp[-5].integer), (yyvsp[-2].integer),
					Settings.RatThickness, OldFlags((yyvsp[-1].integer)));
			}
#line 2396 "parse_y.c"
    break;

  case 73:
#line 991 "parse_y.y"
                        {
				if ((yyvsp[-4].integer) <= 0 || (yyvsp[-4].integer) > MAX_ALL_LAYER)
				{
					yyerror("Layernumber out of range");
					YYABORT;
				}
				if (LayerFlag[(yyvsp[-4].integer)-1])
				{
					yyerror("Layernumber used twice");
					YYABORT;
				}
				Layer = &yyData->Layer[(yyvsp[-4].integer)-1];

                                /* memory for name is already allocated */
				Layer->Name = (yyvsp[-3].string);
                         	if (Layer->Name == NULL)
                                   Layer->Name = strdup("");
				LayerFlag[(yyvsp[-4].integer)-1] = true;
                                if ((yyvsp[-2].string))
                                  Layer->Type = string_to_layertype ((yyvsp[-2].string), yyerror);
                                else
                                  Layer->Type = guess_layertype ((yyvsp[-3].string), (yyvsp[-4].integer), yyData);
                                if ((yyvsp[-2].string) != NULL)
                                  free ((yyvsp[-2].string));
			}
#line 2426 "parse_y.c"
    break;

  case 85:
#line 1038 "parse_y.y"
                        {
				CreateNewPolygonFromRectangle(Layer,
					OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), OU ((yyvsp[-5].measure)) + OU ((yyvsp[-3].measure)), OU ((yyvsp[-4].measure)) + OU ((yyvsp[-2].measure)), OldFlags((yyvsp[-1].integer)));
			}
#line 2435 "parse_y.c"
    break;

  case 89:
#line 1045 "parse_y.y"
                  { attr_list = & Layer->Attributes; }
#line 2441 "parse_y.c"
    break;

  case 92:
#line 1086 "parse_y.y"
                        {
				CreateNewLineOnLayer(Layer, NU ((yyvsp[-7].measure)), NU ((yyvsp[-6].measure)), NU ((yyvsp[-5].measure)), NU ((yyvsp[-4].measure)),
				                            NU ((yyvsp[-3].measure)), NU ((yyvsp[-2].measure)), (yyvsp[-1].flagtype));
			}
#line 2450 "parse_y.c"
    break;

  case 93:
#line 1095 "parse_y.y"
                        {
				CreateNewLineOnLayer(Layer, OU ((yyvsp[-7].measure)), OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)),
						     OU ((yyvsp[-3].measure)), OU ((yyvsp[-2].measure)), OldFlags((yyvsp[-1].integer)));
			}
#line 2459 "parse_y.c"
    break;

  case 94:
#line 1104 "parse_y.y"
                        {
				/* eliminate old-style rat-lines */
			if ((IV ((yyvsp[-1].measure)) & RATFLAG) == 0)
				CreateNewLineOnLayer(Layer, OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), OU ((yyvsp[-3].measure)), OU ((yyvsp[-2].measure)),
					200*GROUNDPLANEFRAME, OldFlags(IV ((yyvsp[-1].measure))));
			}
#line 2470 "parse_y.c"
    break;

  case 95:
#line 1161 "parse_y.y"
                        {
			  CreateNewArcOnLayer(Layer, NU ((yyvsp[-9].measure)), NU ((yyvsp[-8].measure)), NU ((yyvsp[-7].measure)), NU ((yyvsp[-6].measure)), (yyvsp[-3].number), (yyvsp[-2].number),
			                             NU ((yyvsp[-5].measure)), NU ((yyvsp[-4].measure)), (yyvsp[-1].flagtype));
			}
#line 2479 "parse_y.c"
    break;

  case 96:
#line 1170 "parse_y.y"
                        {
				CreateNewArcOnLayer(Layer, OU ((yyvsp[-9].measure)), OU ((yyvsp[-8].measure)), OU ((yyvsp[-7].measure)), OU ((yyvsp[-6].measure)), (yyvsp[-3].number), (yyvsp[-2].number),
						    OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), OldFlags((yyvsp[-1].integer)));
			}
#line 2488 "parse_y.c"
    break;

  case 97:
#line 1179 "parse_y.y"
                        {
				CreateNewArcOnLayer(Layer, OU ((yyvsp[-8].measure)), OU ((yyvsp[-7].measure)), OU ((yyvsp[-6].measure)), OU ((yyvsp[-6].measure)), IV ((yyvsp[-3].measure)), (yyvsp[-2].number),
					OU ((yyvsp[-4].measure)), 200*GROUNDPLANEFRAME, OldFlags((yyvsp[-1].integer)));
			}
#line 2497 "parse_y.c"
    break;

  case 98:
#line 1225 "parse_y.y"
                        {
					/* use a default scale of 100% */
				CreateNewText(Layer,yyFont,OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), (yyvsp[-3].number), 100, (yyvsp[-2].string), OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-2].string));
			}
#line 2507 "parse_y.c"
    break;

  case 99:
#line 1235 "parse_y.y"
                        {
				if ((yyvsp[-1].integer) & ONSILKFLAG)
				{
					LayerType *lay = &yyData->Layer[yyData->LayerN +
						(((yyvsp[-1].integer) & ONSOLDERFLAG) ? BOTTOM_SILK_LAYER : TOP_SILK_LAYER)];

					CreateNewText(lay ,yyFont, OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), (yyvsp[-4].number), (yyvsp[-3].number), (yyvsp[-2].string),
						      OldFlags((yyvsp[-1].integer)));
				}
				else
					CreateNewText(Layer, yyFont, OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), (yyvsp[-4].number), (yyvsp[-3].number), (yyvsp[-2].string),
						      OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-2].string));
			}
#line 2526 "parse_y.c"
    break;

  case 100:
#line 1253 "parse_y.y"
                        {
				/* FIXME: shouldn't know about .f */
				/* I don't think this matters because anything with hi_format
				 * will have the silk on its own layer in the file rather
				 * than using the ONSILKFLAG and having it in a copper layer.
				 * Thus there is no need for anything besides the 'else'
				 * part of this code.
				 */
				if ((yyvsp[-1].flagtype).f & ONSILKFLAG)
				{
					LayerType *lay = &yyData->Layer[yyData->LayerN +
						(((yyvsp[-1].flagtype).f & ONSOLDERFLAG) ? BOTTOM_SILK_LAYER : TOP_SILK_LAYER)];

					CreateNewText(lay, yyFont, NU ((yyvsp[-6].measure)), NU ((yyvsp[-5].measure)), (yyvsp[-4].number), (yyvsp[-3].number), (yyvsp[-2].string), (yyvsp[-1].flagtype));
				}
				else
					CreateNewText(Layer, yyFont, NU ((yyvsp[-6].measure)), NU ((yyvsp[-5].measure)), (yyvsp[-4].number), (yyvsp[-3].number), (yyvsp[-2].string), (yyvsp[-1].flagtype));
				free ((yyvsp[-2].string));
			}
#line 2550 "parse_y.c"
    break;

  case 101:
#line 1316 "parse_y.y"
                        {
				Polygon = CreateNewPolygon(Layer, (yyvsp[-2].flagtype));
			}
#line 2558 "parse_y.c"
    break;

  case 102:
#line 1321 "parse_y.y"
                        {
				Cardinal contour, contour_start, contour_end;
				bool bad_contour_found = false;
				/* ignore junk */
				for (contour = 0; contour <= Polygon->HoleIndexN; contour++)
				  {
				    contour_start = (contour == 0) ?
						      0 : Polygon->HoleIndex[contour - 1];
				    contour_end = (contour == Polygon->HoleIndexN) ?
						 Polygon->PointN :
						 Polygon->HoleIndex[contour];
				    if (contour_end - contour_start < 3)
				      bad_contour_found = true;
				  }

				if (bad_contour_found)
				  {
				    Message(_("WARNING parsing file '%s'\n"
					    "    line:        %i\n"
					    "    description: 'ignored polygon "
					    "(< 3 points in a contour)'\n"),
					    yyfilename, yylineno);
				    DestroyObject(yyData, POLYGON_TYPE, Layer, Polygon, Polygon);
				  }
				else
				  {
				    SetPolygonBoundingBox (Polygon);
				    if (!Layer->polygon_tree)
				      Layer->polygon_tree = r_create_tree (NULL, 0, 0);
				    r_insert_entry (Layer->polygon_tree, (BoxType *) Polygon, 0);
				  }
			}
#line 2595 "parse_y.c"
    break;

  case 105:
#line 1362 "parse_y.y"
                        {
				CreateNewHoleInPolygon (Polygon);
			}
#line 2603 "parse_y.c"
    break;

  case 109:
#line 1376 "parse_y.y"
                        {
				CreateNewPointInPolygon(Polygon, OU ((yyvsp[-2].measure)), OU ((yyvsp[-1].measure)));
			}
#line 2611 "parse_y.c"
    break;

  case 110:
#line 1380 "parse_y.y"
                        {
				CreateNewPointInPolygon(Polygon, NU ((yyvsp[-2].measure)), NU ((yyvsp[-1].measure)));
			}
#line 2619 "parse_y.c"
    break;

  case 116:
#line 1462 "parse_y.y"
                        {
				yyElement = CreateNewElement(yyData, yyFont, NoFlags(),
					(yyvsp[-6].string), (yyvsp[-5].string), NULL, OU ((yyvsp[-4].measure)), OU ((yyvsp[-3].measure)), (yyvsp[-2].integer), 100, NoFlags(), false);
				free ((yyvsp[-6].string));
				free ((yyvsp[-5].string));
				pin_num = 1;
			}
#line 2631 "parse_y.c"
    break;

  case 117:
#line 1470 "parse_y.y"
                        {
				SetElementBoundingBox(yyData, yyElement, yyFont);
			}
#line 2639 "parse_y.c"
    break;

  case 118:
#line 1480 "parse_y.y"
                        {
				yyElement = CreateNewElement(yyData, yyFont, OldFlags((yyvsp[-9].integer)),
					(yyvsp[-8].string), (yyvsp[-7].string), NULL, OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), IV ((yyvsp[-4].measure)), IV ((yyvsp[-3].measure)), OldFlags((yyvsp[-2].integer)), false);
				free ((yyvsp[-8].string));
				free ((yyvsp[-7].string));
				pin_num = 1;
			}
#line 2651 "parse_y.c"
    break;

  case 119:
#line 1488 "parse_y.y"
                        {
				SetElementBoundingBox(yyData, yyElement, yyFont);
			}
#line 2659 "parse_y.c"
    break;

  case 120:
#line 1498 "parse_y.y"
                        {
				yyElement = CreateNewElement(yyData, yyFont, OldFlags((yyvsp[-10].integer)),
					(yyvsp[-9].string), (yyvsp[-8].string), (yyvsp[-7].string), OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), IV ((yyvsp[-4].measure)), IV ((yyvsp[-3].measure)), OldFlags((yyvsp[-2].integer)), false);
				free ((yyvsp[-9].string));
				free ((yyvsp[-8].string));
				free ((yyvsp[-7].string));
				pin_num = 1;
			}
#line 2672 "parse_y.c"
    break;

  case 121:
#line 1507 "parse_y.y"
                        {
				SetElementBoundingBox(yyData, yyElement, yyFont);
			}
#line 2680 "parse_y.c"
    break;

  case 122:
#line 1518 "parse_y.y"
                        {
				yyElement = CreateNewElement(yyData, yyFont, OldFlags((yyvsp[-12].integer)),
					(yyvsp[-11].string), (yyvsp[-10].string), (yyvsp[-9].string), OU ((yyvsp[-8].measure)) + OU ((yyvsp[-6].measure)), OU ((yyvsp[-7].measure)) + OU ((yyvsp[-5].measure)),
					(yyvsp[-4].number), (yyvsp[-3].number), OldFlags((yyvsp[-2].integer)), false);
				yyElement->MarkX = OU ((yyvsp[-8].measure));
				yyElement->MarkY = OU ((yyvsp[-7].measure));
				free ((yyvsp[-11].string));
				free ((yyvsp[-10].string));
				free ((yyvsp[-9].string));
			}
#line 2695 "parse_y.c"
    break;

  case 123:
#line 1529 "parse_y.y"
                        {
				SetElementBoundingBox(yyData, yyElement, yyFont);
			}
#line 2703 "parse_y.c"
    break;

  case 124:
#line 1540 "parse_y.y"
                        {
				yyElement = CreateNewElement(yyData, yyFont, (yyvsp[-12].flagtype),
					(yyvsp[-11].string), (yyvsp[-10].string), (yyvsp[-9].string), NU ((yyvsp[-8].measure)) + NU ((yyvsp[-6].measure)), NU ((yyvsp[-7].measure)) + NU ((yyvsp[-5].measure)),
					(yyvsp[-4].number), (yyvsp[-3].number), (yyvsp[-2].flagtype), false);
				yyElement->MarkX = NU ((yyvsp[-8].measure));
				yyElement->MarkY = NU ((yyvsp[-7].measure));
				free ((yyvsp[-11].string));
				free ((yyvsp[-10].string));
				free ((yyvsp[-9].string));
			}
#line 2718 "parse_y.c"
    break;

  case 125:
#line 1551 "parse_y.y"
                        {
				SetElementBoundingBox(yyData, yyElement, yyFont);
			}
#line 2726 "parse_y.c"
    break;

  case 133:
#line 1652 "parse_y.y"
                        {
				CreateNewLineInElement(yyElement, NU ((yyvsp[-5].measure)), NU ((yyvsp[-4].measure)), NU ((yyvsp[-3].measure)), NU ((yyvsp[-2].measure)), NU ((yyvsp[-1].measure)));
			}
#line 2734 "parse_y.c"
    break;

  case 134:
#line 1657 "parse_y.y"
                        {
				CreateNewLineInElement(yyElement, OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), OU ((yyvsp[-3].measure)), OU ((yyvsp[-2].measure)), OU ((yyvsp[-1].measure)));
			}
#line 2742 "parse_y.c"
    break;

  case 135:
#line 1662 "parse_y.y"
                        {
				CreateNewArcInElement(yyElement, NU ((yyvsp[-7].measure)), NU ((yyvsp[-6].measure)), NU ((yyvsp[-5].measure)), NU ((yyvsp[-4].measure)), (yyvsp[-3].number), (yyvsp[-2].number), NU ((yyvsp[-1].measure)));
			}
#line 2750 "parse_y.c"
    break;

  case 136:
#line 1667 "parse_y.y"
                        {
				CreateNewArcInElement(yyElement, OU ((yyvsp[-7].measure)), OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), (yyvsp[-3].number), (yyvsp[-2].number), OU ((yyvsp[-1].measure)));
			}
#line 2758 "parse_y.c"
    break;

  case 137:
#line 1672 "parse_y.y"
                        {
				yyElement->MarkX = NU ((yyvsp[-2].measure));
				yyElement->MarkY = NU ((yyvsp[-1].measure));
			}
#line 2767 "parse_y.c"
    break;

  case 138:
#line 1677 "parse_y.y"
                        {
				yyElement->MarkX = OU ((yyvsp[-2].measure));
				yyElement->MarkY = OU ((yyvsp[-1].measure));
			}
#line 2776 "parse_y.c"
    break;

  case 139:
#line 1681 "parse_y.y"
                  { attr_list = & yyElement->Attributes; }
#line 2782 "parse_y.c"
    break;

  case 149:
#line 1698 "parse_y.y"
                        {
				CreateNewLineInElement(yyElement, NU ((yyvsp[-5].measure)) + yyElement->MarkX,
					NU ((yyvsp[-4].measure)) + yyElement->MarkY, NU ((yyvsp[-3].measure)) + yyElement->MarkX,
					NU ((yyvsp[-2].measure)) + yyElement->MarkY, NU ((yyvsp[-1].measure)));
			}
#line 2792 "parse_y.c"
    break;

  case 150:
#line 1704 "parse_y.y"
                        {
				CreateNewLineInElement(yyElement, OU ((yyvsp[-5].measure)) + yyElement->MarkX,
					OU ((yyvsp[-4].measure)) + yyElement->MarkY, OU ((yyvsp[-3].measure)) + yyElement->MarkX,
					OU ((yyvsp[-2].measure)) + yyElement->MarkY, OU ((yyvsp[-1].measure)));
			}
#line 2802 "parse_y.c"
    break;

  case 151:
#line 1711 "parse_y.y"
                        {
				CreateNewArcInElement(yyElement, NU ((yyvsp[-7].measure)) + yyElement->MarkX,
					NU ((yyvsp[-6].measure)) + yyElement->MarkY, NU ((yyvsp[-5].measure)), NU ((yyvsp[-4].measure)), (yyvsp[-3].number), (yyvsp[-2].number), NU ((yyvsp[-1].measure)));
			}
#line 2811 "parse_y.c"
    break;

  case 152:
#line 1716 "parse_y.y"
                        {
				CreateNewArcInElement(yyElement, OU ((yyvsp[-7].measure)) + yyElement->MarkX,
					OU ((yyvsp[-6].measure)) + yyElement->MarkY, OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), (yyvsp[-3].number), (yyvsp[-2].number), OU ((yyvsp[-1].measure)));
			}
#line 2820 "parse_y.c"
    break;

  case 153:
#line 1720 "parse_y.y"
                  { attr_list = & yyElement->Attributes; }
#line 2826 "parse_y.c"
    break;

  case 155:
#line 1771 "parse_y.y"
                        {
				CreateNewPin(yyElement, NU ((yyvsp[-9].measure)) + yyElement->MarkX,
					NU ((yyvsp[-8].measure)) + yyElement->MarkY, NU ((yyvsp[-7].measure)), NU ((yyvsp[-6].measure)), NU ((yyvsp[-5].measure)), NU ((yyvsp[-4].measure)), (yyvsp[-3].string),
					(yyvsp[-2].string), (yyvsp[-1].flagtype));
				free ((yyvsp[-3].string));
				free ((yyvsp[-2].string));
			}
#line 2838 "parse_y.c"
    break;

  case 156:
#line 1783 "parse_y.y"
                        {
				CreateNewPin(yyElement, OU ((yyvsp[-9].measure)) + yyElement->MarkX,
					OU ((yyvsp[-8].measure)) + yyElement->MarkY, OU ((yyvsp[-7].measure)), OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), (yyvsp[-3].string),
					(yyvsp[-2].string), OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-3].string));
				free ((yyvsp[-2].string));
			}
#line 2850 "parse_y.c"
    break;

  case 157:
#line 1795 "parse_y.y"
                        {
				CreateNewPin(yyElement, OU ((yyvsp[-7].measure)), OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), 2*GROUNDPLANEFRAME,
					OU ((yyvsp[-5].measure)) + 2*MASKFRAME, OU ((yyvsp[-4].measure)), (yyvsp[-3].string), (yyvsp[-2].string), OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-3].string));
				free ((yyvsp[-2].string));
			}
#line 2861 "parse_y.c"
    break;

  case 158:
#line 1806 "parse_y.y"
                        {
				char	p_number[8];

				sprintf(p_number, "%d", pin_num++);
				CreateNewPin(yyElement, OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), 2*GROUNDPLANEFRAME,
					OU ((yyvsp[-4].measure)) + 2*MASKFRAME, OU ((yyvsp[-3].measure)), (yyvsp[-2].string), p_number, OldFlags((yyvsp[-1].integer)));

				free ((yyvsp[-2].string));
			}
#line 2875 "parse_y.c"
    break;

  case 159:
#line 1822 "parse_y.y"
                        {
				Coord	hole = OU ((yyvsp[-3].measure)) * DEFAULT_DRILLINGHOLE;
				char	p_number[8];

				sprintf(p_number, "%d", pin_num++);
				CreateNewPin(yyElement, OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), OU ((yyvsp[-3].measure)), 2*GROUNDPLANEFRAME,
					OU ((yyvsp[-3].measure)) + 2*MASKFRAME, hole, (yyvsp[-2].string), p_number, OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-2].string));
			}
#line 2889 "parse_y.c"
    break;

  case 160:
#line 1884 "parse_y.y"
                        {
				CreateNewPad(yyElement, NU ((yyvsp[-10].measure)) + yyElement->MarkX,
					NU ((yyvsp[-9].measure)) + yyElement->MarkY,
					NU ((yyvsp[-8].measure)) + yyElement->MarkX,
					NU ((yyvsp[-7].measure)) + yyElement->MarkY, NU ((yyvsp[-6].measure)), NU ((yyvsp[-5].measure)), NU ((yyvsp[-4].measure)),
					(yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].flagtype));
				free ((yyvsp[-3].string));
				free ((yyvsp[-2].string));
			}
#line 2903 "parse_y.c"
    break;

  case 161:
#line 1898 "parse_y.y"
                        {
				Coord tx = NU ((yyvsp[-9].measure)),
				      ty = NU ((yyvsp[-8].measure)),
				      tw = NU ((yyvsp[-7].measure)),
				      th = NU ((yyvsp[-6].measure)),
				      thk,
				      dx,
				      dy;

				thk = (tw > th)?th:tw;
				dx = (tw > th)?((tw - th)/2):0;
				dy = (tw > th)?0:((th - tw)/2);

				CreateNewPad(yyElement, tx - dx + yyElement->MarkX,
					ty - dy + yyElement->MarkY,
					tx + dx + yyElement->MarkX,
					ty + dy + yyElement->MarkY, thk, NU ((yyvsp[-5].measure)), NU ((yyvsp[-4].measure)),
					(yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].flagtype));
				free ((yyvsp[-3].string));
				free ((yyvsp[-2].string));
			}
#line 2929 "parse_y.c"
    break;

  case 162:
#line 1924 "parse_y.y"
                        {
				CreateNewPad(yyElement,OU ((yyvsp[-10].measure)) + yyElement->MarkX,
					OU ((yyvsp[-9].measure)) + yyElement->MarkY, OU ((yyvsp[-8].measure)) + yyElement->MarkX,
					OU ((yyvsp[-7].measure)) + yyElement->MarkY, OU ((yyvsp[-6].measure)), OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)),
					(yyvsp[-3].string), (yyvsp[-2].string), OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-3].string));
				free ((yyvsp[-2].string));
			}
#line 2942 "parse_y.c"
    break;

  case 163:
#line 1937 "parse_y.y"
                        {
				Coord tx = OU ((yyvsp[-9].measure)),
				      ty = OU ((yyvsp[-8].measure)),
				      tw = OU ((yyvsp[-7].measure)),
				      th = OU ((yyvsp[-6].measure)),
				      thk,
				      dx,
				      dy;

				thk = (tw > th)?th:tw;
				dx = (tw > th)?((tw - th)/2):0;
				dy = (tw > th)?0:((th - tw)/2);

				CreateNewPad(yyElement, tx - dx + yyElement->MarkX,
					ty - dy + yyElement->MarkY, tx + dx + yyElement->MarkX,
					ty + dy + yyElement->MarkY, thk, OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)),
					(yyvsp[-3].string), (yyvsp[-2].string), OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-3].string));
				free ((yyvsp[-2].string));
			}
#line 2967 "parse_y.c"
    break;

  case 164:
#line 1962 "parse_y.y"
                        {
				CreateNewPad(yyElement,OU ((yyvsp[-8].measure)),OU ((yyvsp[-7].measure)),OU ((yyvsp[-6].measure)),OU ((yyvsp[-5].measure)),OU ((yyvsp[-4].measure)), 2*GROUNDPLANEFRAME,
					OU ((yyvsp[-4].measure)) + 2*MASKFRAME, (yyvsp[-3].string), (yyvsp[-2].string), OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-3].string));
				free ((yyvsp[-2].string));
			}
#line 2978 "parse_y.c"
    break;

  case 165:
#line 1973 "parse_y.y"
                        {
				char		p_number[8];

				sprintf(p_number, "%d", pin_num++);
				CreateNewPad(yyElement,OU ((yyvsp[-7].measure)),OU ((yyvsp[-6].measure)),OU ((yyvsp[-5].measure)),OU ((yyvsp[-4].measure)),OU ((yyvsp[-3].measure)), 2*GROUNDPLANEFRAME,
					OU ((yyvsp[-3].measure)) + 2*MASKFRAME, (yyvsp[-2].string),p_number, OldFlags((yyvsp[-1].integer)));
				free ((yyvsp[-2].string));
			}
#line 2991 "parse_y.c"
    break;

  case 166:
#line 1983 "parse_y.y"
                                { (yyval.flagtype) = OldFlags((yyvsp[0].integer)); }
#line 2997 "parse_y.c"
    break;

  case 167:
#line 1984 "parse_y.y"
                                { (yyval.flagtype) = string_to_flags ((yyvsp[0].string), yyerror); free((yyvsp[0].string)); }
#line 3003 "parse_y.c"
    break;

  case 171:
#line 2025 "parse_y.y"
                        {
				if ((yyvsp[-3].integer) <= 0 || (yyvsp[-3].integer) > MAX_FONTPOSITION)
				{
					yyerror("fontposition out of range");
					YYABORT;
				}
				Symbol = &yyFont->Symbol[(yyvsp[-3].integer)];
				if (Symbol->Valid)
				{
					yyerror("symbol ID used twice");
					YYABORT;
				}
				Symbol->Valid = true;
				Symbol->Delta = NU ((yyvsp[-2].measure));
			}
#line 3023 "parse_y.c"
    break;

  case 172:
#line 2041 "parse_y.y"
                        {
				if ((yyvsp[-3].integer) <= 0 || (yyvsp[-3].integer) > MAX_FONTPOSITION)
				{
					yyerror("fontposition out of range");
					YYABORT;
				}
				Symbol = &yyFont->Symbol[(yyvsp[-3].integer)];
				if (Symbol->Valid)
				{
					yyerror("symbol ID used twice");
					YYABORT;
				}
				Symbol->Valid = true;
				Symbol->Delta = OU ((yyvsp[-2].measure));
			}
#line 3043 "parse_y.c"
    break;

  case 178:
#line 2097 "parse_y.y"
                        {
				CreateNewLineInSymbol(Symbol, OU ((yyvsp[-5].measure)), OU ((yyvsp[-4].measure)), OU ((yyvsp[-3].measure)), OU ((yyvsp[-2].measure)), OU ((yyvsp[-1].measure)));
			}
#line 3051 "parse_y.c"
    break;

  case 179:
#line 2104 "parse_y.y"
                        {
				CreateNewLineInSymbol(Symbol, NU ((yyvsp[-5].measure)), NU ((yyvsp[-4].measure)), NU ((yyvsp[-3].measure)), NU ((yyvsp[-2].measure)), NU ((yyvsp[-1].measure)));
			}
#line 3059 "parse_y.c"
    break;

  case 187:
#line 2158 "parse_y.y"
                        {
				Menu = CreateNewNet(&yyPCB->NetlistLib, (yyvsp[-3].string), (yyvsp[-2].string));
				free ((yyvsp[-3].string));
				free ((yyvsp[-2].string));
			}
#line 3069 "parse_y.c"
    break;

  case 193:
#line 2193 "parse_y.y"
                        {
				CreateNewConnection(Menu, (yyvsp[-1].string));
				free ((yyvsp[-1].string));
			}
#line 3078 "parse_y.c"
    break;

  case 194:
#line 2252 "parse_y.y"
                        {
			  CreateNewAttribute (attr_list, (yyvsp[-2].string), (yyvsp[-1].string) ? (yyvsp[-1].string) : (char *)"");
				free ((yyvsp[-2].string));
				free ((yyvsp[-1].string));
			}
#line 3088 "parse_y.c"
    break;

  case 195:
#line 2259 "parse_y.y"
                         { (yyval.string) = (yyvsp[0].string); }
#line 3094 "parse_y.c"
    break;

  case 196:
#line 2260 "parse_y.y"
                              { (yyval.string) = 0; }
#line 3100 "parse_y.c"
    break;

  case 197:
#line 2264 "parse_y.y"
                                { (yyval.number) = (yyvsp[0].number); }
#line 3106 "parse_y.c"
    break;

  case 198:
#line 2265 "parse_y.y"
                                { (yyval.number) = (yyvsp[0].integer); }
#line 3112 "parse_y.c"
    break;

  case 199:
#line 2270 "parse_y.y"
                                { do_measure(&(yyval.measure), (yyvsp[0].number), MIL_TO_COORD ((yyvsp[0].number)) / 100.0, 0); }
#line 3118 "parse_y.c"
    break;

  case 200:
#line 2271 "parse_y.y"
                                { M ((yyval.measure), (yyvsp[-1].number), MIL_TO_COORD ((yyvsp[-1].number)) / 1000000.0); }
#line 3124 "parse_y.c"
    break;

  case 201:
#line 2272 "parse_y.y"
                                { M ((yyval.measure), (yyvsp[-1].number), MIL_TO_COORD ((yyvsp[-1].number)) / 100.0); }
#line 3130 "parse_y.c"
    break;

  case 202:
#line 2273 "parse_y.y"
                                { M ((yyval.measure), (yyvsp[-1].number), MIL_TO_COORD ((yyvsp[-1].number))); }
#line 3136 "parse_y.c"
    break;

  case 203:
#line 2274 "parse_y.y"
                                { M ((yyval.measure), (yyvsp[-1].number), INCH_TO_COORD ((yyvsp[-1].number))); }
#line 3142 "parse_y.c"
    break;

  case 204:
#line 2275 "parse_y.y"
                                { M ((yyval.measure), (yyvsp[-1].number), MM_TO_COORD ((yyvsp[-1].number)) / 1000000.0); }
#line 3148 "parse_y.c"
    break;

  case 205:
#line 2276 "parse_y.y"
                                { M ((yyval.measure), (yyvsp[-1].number), MM_TO_COORD ((yyvsp[-1].number)) / 1000000.0); }
#line 3154 "parse_y.c"
    break;

  case 206:
#line 2277 "parse_y.y"
                                { M ((yyval.measure), (yyvsp[-1].number), MM_TO_COORD ((yyvsp[-1].number)) / 1000.0); }
#line 3160 "parse_y.c"
    break;

  case 207:
#line 2278 "parse_y.y"
                                { M ((yyval.measure), (yyvsp[-1].number), MM_TO_COORD ((yyvsp[-1].number))); }
#line 3166 "parse_y.c"
    break;

  case 208:
#line 2279 "parse_y.y"
                                { M ((yyval.measure), (yyvsp[-1].number), MM_TO_COORD ((yyvsp[-1].number)) * 1000.0); }
#line 3172 "parse_y.c"
    break;

  case 209:
#line 2280 "parse_y.y"
                                { M ((yyval.measure), (yyvsp[-1].number), MM_TO_COORD ((yyvsp[-1].number)) * 1000000.0); }
#line 3178 "parse_y.c"
    break;


#line 3182 "parse_y.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2283 "parse_y.y"


/* ---------------------------------------------------------------------------
 * error routine called by parser library
 */
int yyerror(const char * s)
{
	Message(_("ERROR parsing file '%s'\n"
		"    line:        %i\n"
		"    description: '%s'\n"),
		yyfilename, yylineno, s);
	return(0);
}

int yywrap()
{
  return 1;
}

static int
check_file_version (int ver)
{
  if ( ver > PCB_FILE_VERSION ) {
    Message (_("ERROR:  The file you are attempting to load is in a format\n"
	     "which is too new for this version of pcb.  To load this file\n"
	     "you need a version of pcb which is >= %d.  If you are\n"
	     "using a version built from git source, the source date\n"
	     "must be >= %d.  This copy of pcb can only read files\n"
	     "up to file version %d.\n"), ver, ver, PCB_FILE_VERSION);
    return 1;
  }
  
  return 0;
}

static void
do_measure (PLMeasure *m, Coord i, double d, int u)
{
  m->ival = i;
  m->bval = round (d);
  m->dval = d;
  m->has_units = u;
}

static int
integer_value (PLMeasure m)
{
  if (m.has_units)
    yyerror("units ignored here");
  return m.ival;
}

static Coord
old_units (PLMeasure m)
{
  if (m.has_units)
    return m.bval;
  return round (MIL_TO_COORD (m.ival));
}

static Coord
new_units (PLMeasure m)
{
  if (m.has_units)
    return m.bval;
  return round (MIL_TO_COORD (m.ival) / 100.0);
}
