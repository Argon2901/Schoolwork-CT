/* A Bison parser, made by GNU Bison 3.7.4.  */

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
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         Cminus_parse
#define yylex           Cminus_lex
#define yyerror         Cminus_error
#define yydebug         Cminus_debug
#define yynerrs         Cminus_nerrs
#define yylval          Cminus_lval
#define yychar          Cminus_char

/* First part of user prologue.  */
#line 7 "CminusParser.y"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <util/general.h>
#include <util/symtab.h>
#include <util/symtab_stack.h>
#include <util/dlink.h>
#include <util/string_utils.h>

#define SYMTABLE_SIZE 100
#define SYMTAB_VALUE_FIELD     "value"

/*********************EXTERNAL DECLARATIONS***********************/

EXTERN(void,Cminus_error,(const char*));

EXTERN(int,Cminus_lex,(void));

char *fileName;

SymTable symtab;
//SymTable symtab_globle;

extern int Cminus_lineno;

extern FILE *Cminus_in;

DLinkList list;
DLinkList strCnstList;

char* tempString;
char* registers;
//DLinkNode* tempNode;
int spOffset = 0;
int gpOffset = 0;
int stringCnstCount = 0;
int labelCount = 0;

char storingToGlobal = 1;

enum syscalls{
	PRINT_I = 1,
	PRINT_F = 2,
	PRINT_D = 3,
	PRINT_S = 4,
	READ_I = 5,
	READ_F = 6,
	READ_D = 7,
	READ_S = 8,
	MEM_ALLOC = 9,
	EXIT_CALL = 10,
	PRINT_C = 11,
	READ_C = 12
};

char getAvailableRegister();
void freeRegister(char);
void linkStringConstants(DLinkList*, DLinkList*);
void dumpList(DLinkList*);


#line 142 "CminusParser.c"

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

#include "CminusParser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_AND = 3,                        /* AND  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_EXIT = 5,                       /* EXIT  */
  YYSYMBOL_FOR = 6,                        /* FOR  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_INTEGER = 8,                    /* INTEGER  */
  YYSYMBOL_NOT = 9,                        /* NOT  */
  YYSYMBOL_OR = 10,                        /* OR  */
  YYSYMBOL_READ = 11,                      /* READ  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_WRITE = 13,                     /* WRITE  */
  YYSYMBOL_LBRACE = 14,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 15,                    /* RBRACE  */
  YYSYMBOL_LE = 16,                        /* LE  */
  YYSYMBOL_LT = 17,                        /* LT  */
  YYSYMBOL_GE = 18,                        /* GE  */
  YYSYMBOL_GT = 19,                        /* GT  */
  YYSYMBOL_EQ = 20,                        /* EQ  */
  YYSYMBOL_NE = 21,                        /* NE  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 24,                 /* SEMICOLON  */
  YYSYMBOL_LBRACKET = 25,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 26,                  /* RBRACKET  */
  YYSYMBOL_LPAREN = 27,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 28,                    /* RPAREN  */
  YYSYMBOL_PLUS = 29,                      /* PLUS  */
  YYSYMBOL_TIMES = 30,                     /* TIMES  */
  YYSYMBOL_IDENTIFIER = 31,                /* IDENTIFIER  */
  YYSYMBOL_DIVIDE = 32,                    /* DIVIDE  */
  YYSYMBOL_RETURN = 33,                    /* RETURN  */
  YYSYMBOL_STRING = 34,                    /* STRING  */
  YYSYMBOL_INTCON = 35,                    /* INTCON  */
  YYSYMBOL_MINUS = 36,                     /* MINUS  */
  YYSYMBOL_DIVDE = 37,                     /* DIVDE  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_Program = 39,                   /* Program  */
  YYSYMBOL_Procedures = 40,                /* Procedures  */
  YYSYMBOL_ProcedureDecl = 41,             /* ProcedureDecl  */
  YYSYMBOL_ProcedureHead = 42,             /* ProcedureHead  */
  YYSYMBOL_FunctionDecl = 43,              /* FunctionDecl  */
  YYSYMBOL_ProcedureBody = 44,             /* ProcedureBody  */
  YYSYMBOL_DeclList = 45,                  /* DeclList  */
  YYSYMBOL_IdentifierList = 46,            /* IdentifierList  */
  YYSYMBOL_VarDecl = 47,                   /* VarDecl  */
  YYSYMBOL_Type = 48,                      /* Type  */
  YYSYMBOL_Statement = 49,                 /* Statement  */
  YYSYMBOL_Assignment = 50,                /* Assignment  */
  YYSYMBOL_IfStatement = 51,               /* IfStatement  */
  YYSYMBOL_TestAndThen = 52,               /* TestAndThen  */
  YYSYMBOL_Test = 53,                      /* Test  */
  YYSYMBOL_WhileStatement = 54,            /* WhileStatement  */
  YYSYMBOL_WhileExpr = 55,                 /* WhileExpr  */
  YYSYMBOL_WhileToken = 56,                /* WhileToken  */
  YYSYMBOL_IOStatement = 57,               /* IOStatement  */
  YYSYMBOL_ReturnStatement = 58,           /* ReturnStatement  */
  YYSYMBOL_ExitStatement = 59,             /* ExitStatement  */
  YYSYMBOL_CompoundStatement = 60,         /* CompoundStatement  */
  YYSYMBOL_StatementList = 61,             /* StatementList  */
  YYSYMBOL_Expr = 62,                      /* Expr  */
  YYSYMBOL_SimpleExpr = 63,                /* SimpleExpr  */
  YYSYMBOL_AddExpr = 64,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 65,                   /* MulExpr  */
  YYSYMBOL_Factor = 66,                    /* Factor  */
  YYSYMBOL_Variable = 67,                  /* Variable  */
  YYSYMBOL_StringConstant = 68,            /* StringConstant  */
  YYSYMBOL_Constant = 69                   /* Constant  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   146

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   135,   135,   157,   182,   187,   192,   198,   202,   208,
     216,   223,   228,   235,   241,   247,   255,   268,   274,   278,
     282,   286,   290,   294,   298,   304,   324,   329,   337,   348,
     361,   370,   383,   395,   414,   422,   432,   438,   444,   451,
     455,   461,   466,   483,   501,   514,   519,   535,   550,   564,
     578,   593,   609,   614,   628,   644,   649,   664,   680,   696,
     701,   705,   712,   728,   750,   761
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
  "\"end of file\"", "error", "\"invalid token\"", "AND", "ELSE", "EXIT",
  "FOR", "IF", "INTEGER", "NOT", "OR", "READ", "WHILE", "WRITE", "LBRACE",
  "RBRACE", "LE", "LT", "GE", "GT", "EQ", "NE", "ASSIGN", "COMMA",
  "SEMICOLON", "LBRACKET", "RBRACKET", "LPAREN", "RPAREN", "PLUS", "TIMES",
  "IDENTIFIER", "DIVIDE", "RETURN", "STRING", "INTCON", "MINUS", "DIVDE",
  "$accept", "Program", "Procedures", "ProcedureDecl", "ProcedureHead",
  "FunctionDecl", "ProcedureBody", "DeclList", "IdentifierList", "VarDecl",
  "Type", "Statement", "Assignment", "IfStatement", "TestAndThen", "Test",
  "WhileStatement", "WhileExpr", "WhileToken", "IOStatement",
  "ReturnStatement", "ExitStatement", "CompoundStatement", "StatementList",
  "Expr", "SimpleExpr", "AddExpr", "MulExpr", "Factor", "Variable",
  "StringConstant", "Constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
#endif

#define YYPACT_NINF (-65)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      30,   -65,    11,   -65,    30,    49,    30,    30,   -14,   -65,
     -65,    36,   -21,    20,    60,   -65,    64,    49,   100,    37,
     -65,   -65,   -65,   -65,   -65,    72,   -65,   -65,   -65,   -65,
       9,   104,    30,    76,   -65,   -14,    32,    52,   -65,   101,
     -65,    37,   123,   115,    99,    39,    38,    37,    66,    37,
      54,   -65,    85,    95,   -23,    68,   -65,   -65,   -65,    37,
      49,   -65,   -65,    37,    76,   106,    82,    97,   105,    76,
     -65,    16,   115,   -65,   107,   -65,    55,   108,   -65,     5,
      95,    74,   109,    66,    66,   -65,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    75,   -65,    86,   -65,
     112,   120,   -65,   -65,   -65,   116,   117,   118,   -65,   -65,
     -65,    95,    95,   -23,   -23,   -23,   -23,   -23,   -23,    68,
      68,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,    17,     0,     2,     5,     0,     8,     5,     0,     1,
       4,     0,     0,     0,     0,    32,     0,     0,    62,     0,
       6,    39,    18,    19,    20,     0,    21,    22,    23,    24,
       0,     0,     7,     0,     3,     0,    15,     0,    13,     0,
      37,     0,    27,     0,     0,     0,     0,     0,     0,     0,
      62,    65,     0,    41,    45,    52,    55,    58,    59,     0,
       0,    10,    40,     0,     0,    15,     0,     0,     0,     0,
      11,     0,     0,    28,     0,    64,     0,     0,    38,     0,
      44,     0,     0,     0,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,     0,    12,
       0,     0,    14,    29,    26,     0,     0,     0,    63,    61,
      60,    43,    42,    48,    49,    50,    51,    46,    47,    53,
      54,    56,    57,    31,    25,    16,     9,    33,    34,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -65,   -65,    23,   -65,   -65,   -65,   -65,   133,   -31,    77,
       3,   -28,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -38,   126,    45,   -47,    31,   -64,    29,    -5,
     -65,   -65
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,     5,     6,    20,     7,    37,    38,
       8,    21,    22,    23,    42,    43,    24,    60,    25,    26,
      27,    28,    29,    30,    52,    53,    54,    55,    56,    57,
      77,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      31,    80,    62,    40,    66,    73,    92,    11,    83,    33,
      35,     9,    31,    93,    12,    84,    13,    36,    62,    83,
      14,    15,    16,    17,    61,    31,    84,    10,   119,   120,
      34,   108,    97,    66,   104,    64,   111,   112,     1,    74,
      18,    31,    19,    12,   103,    13,    48,    41,    48,    14,
      15,    16,    17,    78,    12,    31,    13,    67,    83,    68,
      14,    15,    16,    17,    49,    84,    49,    39,    50,    18,
      50,    19,    51,    75,    51,    69,    70,    83,    83,    47,
      18,    82,    19,   106,    84,    84,    71,    44,    83,    83,
      76,    45,    79,    49,    81,    84,    84,    50,    94,    59,
      95,    51,   109,   123,    96,    69,    99,    65,    98,    85,
     124,    86,    87,    88,    89,    90,    91,   113,   114,   115,
     116,   117,   118,   121,   122,    47,    63,    72,    68,    17,
      18,    67,   100,   101,   126,   105,   107,   110,   125,    32,
     127,   128,   129,    46,     0,     0,   102
};

static const yytype_int8 yycheck[] =
{
       5,    48,    30,    24,    35,    43,    29,     4,     3,     6,
       7,     0,    17,    36,     5,    10,     7,    31,    46,     3,
      11,    12,    13,    14,    15,    30,    10,     4,    92,    93,
       7,    26,    60,    64,    72,    32,    83,    84,     8,    44,
      31,    46,    33,     5,    28,     7,     9,    27,     9,    11,
      12,    13,    14,    15,     5,    60,     7,    25,     3,    27,
      11,    12,    13,    14,    27,    10,    27,    31,    31,    31,
      31,    33,    35,    34,    35,    23,    24,     3,     3,    25,
      31,    27,    33,    28,    10,    10,    41,    27,     3,     3,
      45,    27,    47,    27,    49,    10,    10,    31,    30,    27,
      32,    35,    28,    28,    59,    23,    24,    31,    63,    24,
      24,    16,    17,    18,    19,    20,    21,    86,    87,    88,
      89,    90,    91,    94,    95,    25,    22,     4,    27,    14,
      31,    25,    35,    28,    14,    28,    28,    28,    26,     6,
      24,    24,    24,    17,    -1,    -1,    69
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    39,    40,    41,    42,    43,    45,    48,     0,
      40,    48,     5,     7,    11,    12,    13,    14,    31,    33,
      44,    49,    50,    51,    54,    56,    57,    58,    59,    60,
      61,    67,    45,    48,    40,    48,    31,    46,    47,    31,
      24,    27,    52,    53,    27,    27,    61,    25,     9,    27,
      31,    35,    62,    63,    64,    65,    66,    67,    69,    27,
      55,    15,    49,    22,    48,    31,    46,    25,    27,    23,
      24,    62,     4,    60,    67,    34,    62,    68,    15,    62,
      63,    62,    27,     3,    10,    24,    16,    17,    18,    19,
      20,    21,    29,    36,    30,    32,    62,    49,    62,    24,
      35,    28,    47,    28,    60,    28,    28,    28,    26,    28,
      28,    63,    63,    64,    64,    64,    64,    64,    64,    65,
      65,    66,    66,    28,    24,    26,    14,    24,    24,    24
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    42,    42,    43,
      44,    45,    45,    46,    46,    47,    47,    48,    49,    49,
      49,    49,    49,    49,    49,    50,    51,    51,    52,    53,
      54,    55,    56,    57,    57,    57,    58,    59,    60,    61,
      61,    62,    62,    62,    62,    63,    63,    63,    63,    63,
      63,    63,    64,    64,    64,    65,    65,    65,    66,    66,
      66,    66,    67,    67,    68,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     2,     2,     1,     5,
       2,     3,     4,     1,     3,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     2,     2,     3,
       3,     3,     1,     5,     5,     5,     3,     2,     3,     1,
       2,     1,     3,     3,     2,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     1,
       3,     3,     1,     4,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
  case 2: /* Program: Procedures  */
#line 136 "CminusParser.y"
                {
			sprintf(tempString, "li $v0, %d\nsyscall\n", EXIT_CALL);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			//create data section for string constants 

			sprintf(tempString, ".text\n");
			dlinkInsertBefore(dlinkNodeAlloc(strdup(tempString)), dlinkHead(&list));

			sprintf(tempString, "newl: .asciiz \"\\n\"\n");
			dlinkPush(dlinkNodeAlloc(strdup(tempString)), &list);

			linkStringConstants(&list, &strCnstList);

			sprintf(tempString, ".data\n");
			dlinkInsertBefore(dlinkNodeAlloc(strdup(tempString)), dlinkHead(&list));
			
			dumpList(&list);

			//printf("<Program> -> <Procedures>\n");
		}
#line 1304 "CminusParser.c"
    break;

  case 3: /* Program: DeclList Procedures  */
#line 158 "CminusParser.y"
                {
			
			sprintf(tempString, "li $v0, %d\nsyscall\n", EXIT_CALL);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			//create data section for string constants 

			sprintf(tempString, ".text\n");
			dlinkInsertBefore(dlinkNodeAlloc(strdup(tempString)), dlinkHead(&list));

			sprintf(tempString, "newl: .asciiz \"\\n\"\n");
			dlinkPush(dlinkNodeAlloc(strdup(tempString)), &list);

			linkStringConstants(&list, &strCnstList);

			sprintf(tempString, ".data\n");
			dlinkInsertBefore(dlinkNodeAlloc(strdup(tempString)), dlinkHead(&list));
			
			dumpList(&list);

			//printf("<Program> -> <DeclList> <Procedures>\n");
		}
#line 1331 "CminusParser.c"
    break;

  case 4: /* Procedures: ProcedureDecl Procedures  */
#line 183 "CminusParser.y"
                {
			//printf("<Procedures> -> <ProcedureDecl> <Procedures>\n");
		}
#line 1339 "CminusParser.c"
    break;

  case 5: /* Procedures: %empty  */
#line 187 "CminusParser.y"
                {
			//printf("<Procedures> -> epsilon\n");
		}
#line 1347 "CminusParser.c"
    break;

  case 6: /* ProcedureDecl: ProcedureHead ProcedureBody  */
#line 193 "CminusParser.y"
                {
			//printf("<ProcedureDecl> -> <ProcedureHead> <ProcedureBody>\n");
		}
#line 1355 "CminusParser.c"
    break;

  case 7: /* ProcedureHead: FunctionDecl DeclList  */
#line 199 "CminusParser.y"
                {
			//printf("<ProcedureHead> -> <FunctionDecl> <DeclList>\n");
		}
#line 1363 "CminusParser.c"
    break;

  case 8: /* ProcedureHead: FunctionDecl  */
#line 203 "CminusParser.y"
                {
			//printf("<ProcedureHead> -> <FunctionDecl>\n");
		}
#line 1371 "CminusParser.c"
    break;

  case 9: /* FunctionDecl: Type IDENTIFIER LPAREN RPAREN LBRACE  */
#line 209 "CminusParser.y"
                {
			sprintf(tempString, ".globl main\nmain :\n");
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			//printf("<FunctionDecl> ->  <Type> <IDENTIFIER> <LP> <RP> <LBR>\n"); 
		}
#line 1381 "CminusParser.c"
    break;

  case 10: /* ProcedureBody: StatementList RBRACE  */
#line 217 "CminusParser.y"
                {
			//printf("<ProcedureBody> -> <StatementList> <RBR>\n");
		}
#line 1389 "CminusParser.c"
    break;

  case 11: /* DeclList: Type IdentifierList SEMICOLON  */
#line 224 "CminusParser.y"
                {
			storingToGlobal = 0;
			//printf("<DeclList> -> <Type> <IdentifierList> <SC>\n");
		}
#line 1398 "CminusParser.c"
    break;

  case 12: /* DeclList: DeclList Type IdentifierList SEMICOLON  */
#line 229 "CminusParser.y"
                {
			//printf("<DeclList> -> <DeclList> <Type> <IdentifierList> <SC>\n");
	 	}
#line 1406 "CminusParser.c"
    break;

  case 13: /* IdentifierList: VarDecl  */
#line 236 "CminusParser.y"
                {

			//printf("<IdentifierList> -> <VarDecl>\n");
		}
#line 1415 "CminusParser.c"
    break;

  case 14: /* IdentifierList: IdentifierList COMMA VarDecl  */
#line 242 "CminusParser.y"
                {
			//printf("<IdentifierList> -> <IdentifierList> <CM> <VarDecl>\n");
		}
#line 1423 "CminusParser.c"
    break;

  case 15: /* VarDecl: IDENTIFIER  */
#line 248 "CminusParser.y"
                { 
			int index = SymIndex(symtab, (yyvsp[0].string));
			int* offset = malloc(4);
			*offset = gpOffset;
			SymPutFieldByIndex(symtab, index, SYMTAB_VALUE_FIELD, offset);
			gpOffset += 4;
		}
#line 1435 "CminusParser.c"
    break;

  case 16: /* VarDecl: IDENTIFIER LBRACKET INTCON RBRACKET  */
#line 256 "CminusParser.y"
        {
			int index = SymIndex(symtab, (yyvsp[-3].string));
			int* offset = malloc(4);
			
			*offset = gpOffset;
			SymPutFieldByIndex(symtab, index, SYMTAB_VALUE_FIELD, offset);
			gpOffset += (yyvsp[-1].value) * 4;
			
			//printf("<VarDecl> -> <IDENTIFIER> <LBK> <INTCON> <RBK>\n");
		}
#line 1450 "CminusParser.c"
    break;

  case 17: /* Type: INTEGER  */
#line 269 "CminusParser.y"
                { 
			//printf("<Type> -> <INTEGER>\n");
		}
#line 1458 "CminusParser.c"
    break;

  case 18: /* Statement: Assignment  */
#line 275 "CminusParser.y"
                { 
			//printf("<Statement> -> <Assignment>\n");
		}
#line 1466 "CminusParser.c"
    break;

  case 19: /* Statement: IfStatement  */
#line 279 "CminusParser.y"
                { 
			//printf("<Statement> -> <IfStatement>\n");
		}
#line 1474 "CminusParser.c"
    break;

  case 20: /* Statement: WhileStatement  */
#line 283 "CminusParser.y"
                { 
			//printf("<Statement> -> <WhileStatement>\n");
		}
#line 1482 "CminusParser.c"
    break;

  case 21: /* Statement: IOStatement  */
#line 287 "CminusParser.y"
                { 
			//printf("<Statement> -> <IOStatement>\n");
		}
#line 1490 "CminusParser.c"
    break;

  case 22: /* Statement: ReturnStatement  */
#line 291 "CminusParser.y"
                { 
			//printf("<Statement> -> <ReturnStatement>\n");
		}
#line 1498 "CminusParser.c"
    break;

  case 23: /* Statement: ExitStatement  */
#line 295 "CminusParser.y"
                { 
			//printf("<Statement> -> <ExitStatement>\n");
		}
#line 1506 "CminusParser.c"
    break;

  case 24: /* Statement: CompoundStatement  */
#line 299 "CminusParser.y"
                { 
			//printf("<Statement> -> <CompoundStatement>\n");
		}
#line 1514 "CminusParser.c"
    break;

  case 25: /* Assignment: Variable ASSIGN Expr SEMICOLON  */
#line 305 "CminusParser.y"
                {
			
			if((yyvsp[-3].reg)  < 0){
				sprintf(tempString,
							"sw $%d, 0($%d)\n"
							, (yyvsp[-1].reg), (yyvsp[-3].reg));
			} else{
				sprintf(tempString,
							"sw $%d, 0($%d)\n"
							, (yyvsp[-1].reg), (yyvsp[-3].reg));
			}
			
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			freeRegister((yyvsp[-1].reg));
			freeRegister((yyvsp[-3].reg));
			//setValue($1, $3);
		}
#line 1536 "CminusParser.c"
    break;

  case 26: /* IfStatement: IF TestAndThen ELSE CompoundStatement  */
#line 325 "CminusParser.y"
                {
			sprintf(tempString, "L%d:\n", (yyvsp[-2].index)); //after if statement
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
		}
#line 1545 "CminusParser.c"
    break;

  case 27: /* IfStatement: IF TestAndThen  */
#line 330 "CminusParser.y"
                {
			sprintf(tempString, "L%d:\n", (yyvsp[0].index)); //after if statement
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
		}
#line 1554 "CminusParser.c"
    break;

  case 28: /* TestAndThen: Test CompoundStatement  */
#line 338 "CminusParser.y"
                {
			(yyval.index) = labelCount; 
			sprintf(tempString, "j L%d\n", labelCount);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			sprintf(tempString, "L%d:\n", (yyvsp[-1].index)); //after if statement
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			labelCount += 1;
		}
#line 1567 "CminusParser.c"
    break;

  case 29: /* Test: LPAREN Expr RPAREN  */
#line 349 "CminusParser.y"
                {
			(yyval.index) = labelCount;

			sprintf(tempString, "beq $%d $0 L%d\n", (yyvsp[-1].reg)	, labelCount);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-1].reg));
			labelCount += 1;
		}
#line 1581 "CminusParser.c"
    break;

  case 30: /* WhileStatement: WhileToken WhileExpr Statement  */
#line 362 "CminusParser.y"
                {
			sprintf(tempString, "j L%d\n", (yyvsp[-2].index)); //after if statement
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			sprintf(tempString, "L%d:\n", (yyvsp[-1].index)); //after if statement
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
		}
#line 1592 "CminusParser.c"
    break;

  case 31: /* WhileExpr: LPAREN Expr RPAREN  */
#line 371 "CminusParser.y"
                {
			(yyval.index) = labelCount;

			sprintf(tempString, "beq $%d $0 L%d\n", (yyvsp[-1].reg), labelCount); 
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			labelCount += 1;

			freeRegister((yyvsp[-1].reg));
		}
#line 1607 "CminusParser.c"
    break;

  case 32: /* WhileToken: WHILE  */
#line 384 "CminusParser.y"
                {
			(yyval.index) = labelCount;
			sprintf(tempString, "L%d:\n", labelCount);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			labelCount += 1; 

			//printf("<WhileToken> -> <WHILE>\n");
		}
#line 1620 "CminusParser.c"
    break;

  case 33: /* IOStatement: READ LPAREN Variable RPAREN SEMICOLON  */
#line 396 "CminusParser.y"
                {
			//char r = getAvailableRegister();
			if((yyvsp[-2].reg) < 0){
				sprintf(tempString,
							"li $v0, %d\n"
							"syscall\n"
							"sw $v0, 0($%d)\n"
							, READ_I, (yyvsp[-2].reg));
			} else{
				sprintf(tempString,
							"li $v0, %d\n"
							"syscall\n"
							"sw $v0, 0($%d)\n"
							, READ_I, (yyvsp[-2].reg));
			}
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			freeRegister((yyvsp[-2].reg));
		}
#line 1643 "CminusParser.c"
    break;

  case 34: /* IOStatement: WRITE LPAREN Expr RPAREN SEMICOLON  */
#line 415 "CminusParser.y"
                {

			sprintf(tempString, "move $a0, $%d\nli $v0 %d\nsyscall\nla $a0, newl\nli $v0, %d\nsyscall\n", (yyvsp[-2].reg), PRINT_I, PRINT_S);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			freeRegister((yyvsp[-2].reg));

		}
#line 1655 "CminusParser.c"
    break;

  case 35: /* IOStatement: WRITE LPAREN StringConstant RPAREN SEMICOLON  */
#line 423 "CminusParser.y"
                {
			sprintf(tempString, "la $a0, S%d\nli $v0, %d\nsyscall\nla $a0, newl\nsyscall\n", (yyvsp[-2].index), PRINT_S);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

		 	//printf("%s\n", (char *)SymGetFieldByIndex(symtab,$3, SYM_NAME_FIELD));
			//printf("<IOStatement> -> <WRITE> <LP> <StringConstant> <RP> <SC>\n");
		}
#line 1667 "CminusParser.c"
    break;

  case 36: /* ReturnStatement: RETURN Expr SEMICOLON  */
#line 433 "CminusParser.y"
                {
			//printf("<ReturnStatement> -> <RETURN> <Expr> <SC>\n");
		}
#line 1675 "CminusParser.c"
    break;

  case 37: /* ExitStatement: EXIT SEMICOLON  */
#line 439 "CminusParser.y"
                {
			//printf("<ExitStatement> -> <EXIT> <SC>\n");
		}
#line 1683 "CminusParser.c"
    break;

  case 38: /* CompoundStatement: LBRACE StatementList RBRACE  */
#line 445 "CminusParser.y"
                {
			
			//printf("<CompoundStatement> -> <LBR> <StatementList> <RBR>\n");
		}
#line 1692 "CminusParser.c"
    break;

  case 39: /* StatementList: Statement  */
#line 452 "CminusParser.y"
                {		
			//printf("<StatementList> -> <Statement>\n");
		}
#line 1700 "CminusParser.c"
    break;

  case 40: /* StatementList: StatementList Statement  */
#line 456 "CminusParser.y"
                {		
			//printf("<StatementList> -> <StatementList> <Statement>\n");
		}
#line 1708 "CminusParser.c"
    break;

  case 41: /* Expr: SimpleExpr  */
#line 462 "CminusParser.y"
                {
			(yyval.reg) = (yyvsp[0].reg);
			//printf("<Expr> -> <SimpleExpr>\n");
		}
#line 1717 "CminusParser.c"
    break;

  case 42: /* Expr: Expr OR SimpleExpr  */
#line 467 "CminusParser.y"
                {

			char r = getAvailableRegister();
			sprintf(tempString, 	"or $%d, $%d, $%d\n"
									"sne $%d, $%d, $0\n", 
									r, (yyvsp[-2].reg), (yyvsp[0].reg), r, r);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;

		        //$$ = $1 | $3;
			//printf("<Expr> -> <Expr> <OR> <SimpleExpr> \n");
		}
#line 1738 "CminusParser.c"
    break;

  case 43: /* Expr: Expr AND SimpleExpr  */
#line 484 "CminusParser.y"
                {
			char r = getAvailableRegister();
			sprintf(tempString, 	"sne $%d, $%d, $0\n"
									"sne $%d, $%d, $0\n"
									"and $%d, $%d, $%d\n", 
									(yyvsp[-2].reg), (yyvsp[-2].reg), (yyvsp[0].reg), (yyvsp[0].reg), r, (yyvsp[-2].reg), (yyvsp[0].reg));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;


			//$$ = $1 & $3;
			//printf("<Expr> -> <Expr> <AND> <SimpleExpr> \n");
		}
#line 1760 "CminusParser.c"
    break;

  case 44: /* Expr: NOT SimpleExpr  */
#line 502 "CminusParser.y"
                {
			sprintf(tempString, 	"seq $%d, $%d, $0\n", 
									(yyvsp[0].reg), (yyvsp[0].reg));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			(yyval.reg) = (yyvsp[0].reg);
		        //$$ = ($1 <= $3);
			//$$ = $2 ^ 1;
			//printf("<Expr> -> <NOT> <SimpleExpr> \n");
		}
#line 1775 "CminusParser.c"
    break;

  case 45: /* SimpleExpr: AddExpr  */
#line 515 "CminusParser.y"
                {
			(yyval.reg) = (yyvsp[0].reg);
			//printf("<SimpleExpr> -> <AddExpr>\n");
		}
#line 1784 "CminusParser.c"
    break;

  case 46: /* SimpleExpr: SimpleExpr EQ AddExpr  */
#line 520 "CminusParser.y"
                {
			char r = getAvailableRegister();

			sprintf(tempString, 	"seq $%d, $%d, $%d\n", 
									r, (yyvsp[-2].reg), (yyvsp[0].reg));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;

			//$$ = ($1 == $3);
			//printf("<SimpleExpr> -> <SimpleExpr> <EQ> <AddExpr> \n");
		}
#line 1804 "CminusParser.c"
    break;

  case 47: /* SimpleExpr: SimpleExpr NE AddExpr  */
#line 536 "CminusParser.y"
                {
			char r = getAvailableRegister();
			sprintf(tempString, 	"sne $%d, $%d, $%d\n", 
									r, (yyvsp[-2].reg), (yyvsp[0].reg));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;

		        //$$ = ($1 != $3);
			//printf("<SimpleExpr> -> <SimpleExpr> <NE> <AddExpr> \n");
		}
#line 1823 "CminusParser.c"
    break;

  case 48: /* SimpleExpr: SimpleExpr LE AddExpr  */
#line 551 "CminusParser.y"
                {
			char r = getAvailableRegister();
			sprintf(tempString, 	"sle $%d, $%d, $%d\n", 
									r, (yyvsp[-2].reg), (yyvsp[0].reg));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;
		        //$$ = ($1 <= $3);
			//printf("<SimpleExpr> -> <SimpleExpr> <LE> <AddExpr> \n");
		}
#line 1841 "CminusParser.c"
    break;

  case 49: /* SimpleExpr: SimpleExpr LT AddExpr  */
#line 565 "CminusParser.y"
                {
			char r = getAvailableRegister();
			sprintf(tempString, 	"slt $%d, $%d, $%d\n", 
									r, (yyvsp[-2].reg), (yyvsp[0].reg));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;
		        //$$ = ($1 < $3);
			//printf("<SimpleExpr> -> <SimpleExpr> <LT> <AddExpr> \n");
		}
#line 1859 "CminusParser.c"
    break;

  case 50: /* SimpleExpr: SimpleExpr GE AddExpr  */
#line 579 "CminusParser.y"
                {
			char r = getAvailableRegister();
			sprintf(tempString, 	"sle $%d, $%d, $%d\n", 
									r, (yyvsp[0].reg), (yyvsp[-2].reg));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;
		        //$$ = ($1 <= $3);
		        //$$ = ($1 >= $3);
			//printf("<SimpleExpr> -> <SimpleExpr> <GE> <AddExpr> \n");
		}
#line 1878 "CminusParser.c"
    break;

  case 51: /* SimpleExpr: SimpleExpr GT AddExpr  */
#line 594 "CminusParser.y"
                {
			char r = getAvailableRegister();
			sprintf(tempString, 	"slt $%d, $%d, $%d\n", 
									r, (yyvsp[0].reg), (yyvsp[-2].reg));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;
			//printf("<SimpleExpr> -> <SimpleExpr> <GT> <AddExpr> \n");
		        //$$ = ($1 > $3);
		}
#line 1896 "CminusParser.c"
    break;

  case 52: /* AddExpr: MulExpr  */
#line 610 "CminusParser.y"
                {
			(yyval.reg) = (yyvsp[0].reg);
			//printf("<AddExpr> -> <MulExpr>\n");
		}
#line 1905 "CminusParser.c"
    break;

  case 53: /* AddExpr: AddExpr PLUS MulExpr  */
#line 615 "CminusParser.y"
                {
			char r = getAvailableRegister();
			sprintf(tempString, "add $%d, $%d, $%d\n", r, (yyvsp[-2].reg), (yyvsp[0].reg));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;

			//$$ = $1 + $3;
			//printf("<AddExpr> -> <AddExpr> <PLUS> <MulExpr> \n");
		}
#line 1923 "CminusParser.c"
    break;

  case 54: /* AddExpr: AddExpr MINUS MulExpr  */
#line 629 "CminusParser.y"
                {
			char r = getAvailableRegister();
			sprintf(tempString, "sub $%d, $%d, $%d\n", r, (yyvsp[-2].reg), (yyvsp[0].reg));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;

			//$$ = $1 - $3;
			//printf("<AddExpr> -> <AddExpr> <MINUS> <MulExpr> \n");
		}
#line 1941 "CminusParser.c"
    break;

  case 55: /* MulExpr: Factor  */
#line 645 "CminusParser.y"
                {
			(yyval.reg) = (yyvsp[0].reg);
			//printf("<MulExpr> -> <Factor>\n");
		}
#line 1950 "CminusParser.c"
    break;

  case 56: /* MulExpr: MulExpr TIMES Factor  */
#line 650 "CminusParser.y"
                {
			char r = getAvailableRegister();
			sprintf(tempString, "mult $%d, $%d\nmfhi $%d\nmflo $%d\n", (yyvsp[-2].reg), (yyvsp[0].reg), r, r);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;
			

			//$$ = $1 * $3;
			//printf("<MulExpr> -> <MulExpr> <TIMES> <Factor> \n");
		}
#line 1969 "CminusParser.c"
    break;

  case 57: /* MulExpr: MulExpr DIVIDE Factor  */
#line 665 "CminusParser.y"
                {
			char r = getAvailableRegister();
			sprintf(tempString, "div $%d, $%d\nmfhi $%d\nmflo $%d\n", (yyvsp[-2].reg), (yyvsp[0].reg), r, r);
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			
			freeRegister((yyvsp[-2].reg));
			freeRegister((yyvsp[0].reg));

			(yyval.reg) = r;

			//$$ = $1 / $3;
			//printf("<MulExpr> -> <MulExpr> <DIVIDE> <Factor> \n");
		}
#line 1987 "CminusParser.c"
    break;

  case 58: /* Factor: Variable  */
#line 681 "CminusParser.y"
                { 
			//remake to find all 
			char r = getAvailableRegister();

			if((yyvsp[0].reg) < 0){
				sprintf(tempString, "lw $%d, 0($%d)\n", r, (yyvsp[0].reg));
			} else{
				sprintf(tempString, "lw $%d, 0($%d)\n", r, (yyvsp[0].reg));
			}

			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			(yyval.reg) = r; 
			freeRegister((yyvsp[0].reg));

		}
#line 2007 "CminusParser.c"
    break;

  case 59: /* Factor: Constant  */
#line 697 "CminusParser.y"
                { 
			(yyval.reg) = (yyvsp[0].reg);
			//printf("<Factor> -> <Constant>\n");
		}
#line 2016 "CminusParser.c"
    break;

  case 60: /* Factor: IDENTIFIER LPAREN RPAREN  */
#line 702 "CminusParser.y"
                {	
			//printf("<Factor> -> <IDENTIFIER> <LP> <RP>\n");
		}
#line 2024 "CminusParser.c"
    break;

  case 61: /* Factor: LPAREN Expr RPAREN  */
#line 706 "CminusParser.y"
                {
			(yyval.reg) = (yyvsp[-1].reg);
			//printf("<Factor> -> <LP> <Expr> <RP>\n");
		}
#line 2033 "CminusParser.c"
    break;

  case 62: /* Variable: IDENTIFIER  */
#line 713 "CminusParser.y"
                {
			int* a = ((int*)SymGetField(symtab, (yyvsp[0].string), SYMTAB_VALUE_FIELD));
			char r = getAvailableRegister();

			if(*a < 0){
				sprintf(tempString, 	"li $%d %d\n"
										"add $%d $%d $sp\n", r, *a, r, r);
			} else{
				sprintf(tempString, 	"li $%d %d\n"
										"add $%d $%d $gp\n", r, *a, r, r);
			}
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			(yyval.reg) = r;
		}
#line 2053 "CminusParser.c"
    break;

  case 63: /* Variable: IDENTIFIER LBRACKET Expr RBRACKET  */
#line 729 "CminusParser.y"
                {
			char r = getAvailableRegister();
			int* a = ((int*)SymGetField(symtab, (yyvsp[-3].string), SYMTAB_VALUE_FIELD)); //offset of first element in array
			
			sprintf(tempString,	"sll $%d $%d 2\n", (yyvsp[-1].reg), (yyvsp[-1].reg)); //index adjusted for size
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			sprintf(tempString, "add $%d $%d $gp\n", r, (yyvsp[-1].reg));  //increasing gp by index offset
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));

			sprintf(tempString, "li $%d %d\n"
								"add $%d $%d $%d\n", (yyvsp[-1].reg), *a, r, r, (yyvsp[-1].reg));  //increasing gp by index offset
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));


			(yyval.reg) = r;

			freeRegister((yyvsp[-1].reg));
		}
#line 2077 "CminusParser.c"
    break;

  case 64: /* StringConstant: STRING  */
#line 751 "CminusParser.y"
                { 
			(yyval.index) = stringCnstCount;
			stringCnstCount += 1; 

			dlinkAppend(&strCnstList, dlinkNodeAlloc(strdup((yyvsp[0].string))));
			
			//printf("<StringConstant> -> <STRING>\n");
		}
#line 2090 "CminusParser.c"
    break;

  case 65: /* Constant: INTCON  */
#line 762 "CminusParser.y"
                {
			char reg = getAvailableRegister();
			sprintf(tempString, "li $%d, %d\n", reg, (yyvsp[0].value));
			dlinkAppend(&list, dlinkNodeAlloc(strdup(tempString)));
			(yyval.reg) = reg;
			//printf("<Constant> -> <INTCON>\n");
		}
#line 2102 "CminusParser.c"
    break;


#line 2106 "CminusParser.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 771 "CminusParser.y"



/********************C ROUTINES *********************************/

char getAvailableRegister(){
	for(int i = 0; i < 16; i++){
		if(registers[i] == 0){
			registers[i] = 1;
			return i + 8;
		}
	}
}

void freeRegister(char reg){
	reg = reg - 8;
	registers[reg] = 0;
}

void linkStringConstants(DLinkList* list, DLinkList* strings){
	int count = 0;
	DLinkNode* node = dlinkHead(strings);
	if(node == NULL){
		return;
	}

	do{
		sprintf(tempString, "S%d: .asciiz \"%s\"\n", count, (char*)dlinkNodeAtom(node));
		dlinkPush(dlinkNodeAlloc(strdup(tempString)), list);
		count++;
	} while((node = dlinkNext(node)));
}

void dumpList(DLinkList* list){
	DLinkNode* node = dlinkHead(list);
	if(node == NULL){
		return;
	}

	do{
		printf("%s", (char*)dlinkNodeAtom(node));
	} while((node = dlinkNext(node)));
}


void Cminus_error(const char *s)
{
  fprintf(stderr,"%s: line %d: %s\n",fileName,Cminus_lineno,s);
}

int Cminus_wrap() {
	return 1;
}

static void initialize(char* inputFileName) {

	Cminus_in = fopen(inputFileName,"r");
        if (Cminus_in == NULL) {
          fprintf(stderr,"Error: Could not open file %s\n",inputFileName);
          exit(-1);
        }

	char* dotChar = rindex(inputFileName,'.');
	int endIndex = strlen(inputFileName) - strlen(dotChar);
	char *outputFileName = nssave(2,substr(inputFileName,0,endIndex),".s");
	stdout = freopen(outputFileName,"w",stdout);
        if (stdout == NULL) {
          fprintf(stderr,"Error: Could not open file %s\n",outputFileName);
          exit(-1);
        }


	 symtab = SymInit(SYMTABLE_SIZE);
	 SymInitField(symtab,SYMTAB_VALUE_FIELD,(Generic)-1,NULL);

	 tempString = malloc(200);
	 registers = calloc(16, 1);
}

static void finalize() {

    SymKillField(symtab,SYMTAB_VALUE_FIELD);
    SymKill(symtab);
    fclose(Cminus_in);
    fclose(stdout);

}

int main(int argc, char** argv)

{	
	fileName = argv[1];
	initialize(fileName);
	
        Cminus_parse();
  
  	finalize();

  	return 0;
}

/*int getValue(int index)
{
  return (int)SymGetFieldByIndex(symtab, index, SYMTAB_VALUE_FIELD); 
}

int setValue(int index, int value)
{
  SymPutFieldByIndex(symtab, index, SYMTAB_VALUE_FIELD, (Generic)value); 
}*/
/******************END OF C ROUTINES**********************/
