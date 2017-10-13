#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 6 "ex.y"
#include <stdio.h>
#include <limits.h>
#include "global.h"

ERROR_N error_val;

#line 14 "ex.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int num;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 37 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define NUM 257
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,   12,    1,    1,    2,    2,    3,    3,    4,
    4,    5,    5,    6,    6,    6,    7,    7,    7,    8,
    8,    8,    8,    9,    9,   10,   10,   11,   11,
};
static const short yylen[] = {                            2,
    0,    2,    2,    1,    1,    1,    1,    3,    1,    3,
    1,    3,    1,    4,    4,    1,    3,    3,    1,    3,
    3,    3,    1,    2,    1,    2,    1,    3,    1,
};
static const short yydefred[] = {                         0,
    5,    0,    0,    0,    0,    0,    4,    0,    0,    0,
    0,    0,    0,   23,   25,   27,    0,   29,   24,   26,
    0,    3,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    2,   28,    0,    0,    0,    0,    0,    0,
    0,   20,   21,   22,    0,    0,
};
static const short yydgoto[] = {                          5,
   18,    7,    8,    9,   10,   11,   12,   13,   14,   15,
   16,   17,
};
static const short yysindex[] = {                       -40,
    0,  -40,  -40,  -40,    0,  -55,    0, -101,  -61,    6,
  -34,  -23,  -26,    0,    0,    0,  -40,    0,    0,    0,
    8,    0,  -40,  -40,  -40,  -11,   -4,  -40,  -40,  -40,
  -40,  -40,    0,    0,  -61,    6,  -34,  -40,  -40,  -26,
  -26,    0,    0,    0,  -23,  -23,
};
static const short yyrindex[] = {                        59,
    0,    0,    0,    0,    0,   31,    0,  224,  -35,  -28,
   60,   71,  149,    0,    0,    0,   59,    0,    0,    0,
   97,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   -2,    5,  126,    0,    0,  185,
  193,    0,    0,    0,  139,  165,
};
static const short yygindex[] = {                        46,
    1,    0,    0,   47,   48,   50,   -9,    9,   23,   69,
   58,    0,
};
#define YYTABLESIZE 318
static const short yytable[] = {                          4,
    6,    9,    9,   22,    2,    9,    9,    9,   11,    9,
   32,    9,   11,   11,   11,   30,   11,    6,   11,   28,
   31,   29,   23,    9,    9,   27,    9,   26,   45,   46,
   11,   11,   24,   11,    8,    8,   40,   41,    8,    8,
    8,   10,    8,   25,    8,   10,   10,   10,   34,   10,
   38,   10,   42,   43,   44,   39,    8,    8,    1,    8,
   20,   21,   33,   10,   10,   11,   10,   29,   29,   35,
   19,   36,   29,   29,   37,   29,    0,   29,    0,    0,
    0,    0,    0,    0,    0,    3,    0,    0,    9,    0,
   29,    0,   29,    0,    0,   11,   13,   13,   10,    0,
   13,   13,   13,    0,   13,    0,   13,   16,   16,    0,
    0,   16,   16,    0,    0,    0,    0,   16,   13,    0,
    0,    8,    0,    0,   29,    0,    0,    0,   10,   16,
   16,    0,   16,   27,   27,    0,    0,    0,   27,   27,
    0,   27,    0,   27,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   13,   29,    0,   27,    0,   27,    0,
    0,    0,   12,   12,   16,    0,   12,   12,   12,    0,
   12,    0,   12,    0,    0,   14,   14,    0,    0,   14,
   14,    0,    0,   13,   12,   14,   19,    0,    0,   19,
   27,   19,    0,   19,   16,    0,    0,   14,   14,    0,
   14,   15,   15,    0,    0,   15,   15,   19,   19,    0,
   19,   15,    0,    0,    0,    0,    1,    0,    0,   12,
   27,    0,   17,   15,   15,   17,   15,   17,    0,   17,
   18,    0,   14,   18,    0,   18,    0,   18,    0,    0,
    0,    0,   19,   17,   17,    0,   17,    0,    0,   12,
    0,   18,   18,    0,   18,    0,    0,    0,   15,    0,
    7,    7,   14,    0,    7,    7,    7,    0,    7,    0,
    7,    0,   19,    0,    0,    0,    0,    0,   17,    0,
    0,    0,    7,    7,    0,    7,   18,    0,   15,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   17,    0,
    0,    0,    0,    0,    0,    0,   18,    7,
};
static const short yycheck[] = {                         40,
    0,   37,   38,   59,   45,   41,   42,   43,   37,   45,
   37,   47,   41,   42,   43,   42,   45,   17,   47,   43,
   47,   45,  124,   59,   60,   60,   62,   62,   38,   39,
   59,   60,   94,   62,   37,   38,   28,   29,   41,   42,
   43,   37,   45,   38,   47,   41,   42,   43,   41,   45,
   62,   47,   30,   31,   32,   60,   59,   60,    0,   62,
    3,    4,   17,   59,   60,   94,   62,   37,   38,   23,
    2,   24,   42,   43,   25,   45,   -1,   47,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  126,   -1,   -1,  124,   -1,
   60,   -1,   62,   -1,   -1,  124,   37,   38,   94,   -1,
   41,   42,   43,   -1,   45,   -1,   47,   37,   38,   -1,
   -1,   41,   42,   -1,   -1,   -1,   -1,   47,   59,   -1,
   -1,  124,   -1,   -1,   94,   -1,   -1,   -1,  124,   59,
   60,   -1,   62,   37,   38,   -1,   -1,   -1,   42,   43,
   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   94,  124,   -1,   60,   -1,   62,   -1,
   -1,   -1,   37,   38,   94,   -1,   41,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,   37,   38,   -1,   -1,   41,
   42,   -1,   -1,  124,   59,   47,   38,   -1,   -1,   41,
   94,   43,   -1,   45,  124,   -1,   -1,   59,   60,   -1,
   62,   37,   38,   -1,   -1,   41,   42,   59,   60,   -1,
   62,   47,   -1,   -1,   -1,   -1,  257,   -1,   -1,   94,
  124,   -1,   38,   59,   60,   41,   62,   43,   -1,   45,
   38,   -1,   94,   41,   -1,   43,   -1,   45,   -1,   -1,
   -1,   -1,   94,   59,   60,   -1,   62,   -1,   -1,  124,
   -1,   59,   60,   -1,   62,   -1,   -1,   -1,   94,   -1,
   37,   38,  124,   -1,   41,   42,   43,   -1,   45,   -1,
   47,   -1,  124,   -1,   -1,   -1,   -1,   -1,   94,   -1,
   -1,   -1,   59,   60,   -1,   62,   94,   -1,  124,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  124,   94,
};
#define YYFINAL 5
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 257
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,
0,"';'","'<'",0,"'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'|'",0,
"'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,"NUM",
};
static const char *yyrule[] = {
"$accept : commands",
"commands :",
"commands : command commands",
"command : EXPR ';'",
"EXPR : EXPR_ASSIGN",
"EXPR : NUM",
"EXPR_ASSIGN : NUM",
"EXPR_ASSIGN : EXPR_BITWISE_OR",
"EXPR_BITWISE_OR : EXPR_BITWISE_OR '|' EXPR_BITWISE_XOR",
"EXPR_BITWISE_OR : EXPR_BITWISE_XOR",
"EXPR_BITWISE_XOR : EXPR_BITWISE_XOR '^' EXPR_BITWISE_AND",
"EXPR_BITWISE_XOR : EXPR_BITWISE_AND",
"EXPR_BITWISE_AND : EXPR_BITWISE_AND '&' EXPR_SHIFT",
"EXPR_BITWISE_AND : EXPR_SHIFT",
"EXPR_SHIFT : EXPR_SHIFT '>' '>' EXPR_ADDSUB",
"EXPR_SHIFT : EXPR_SHIFT '<' '<' EXPR_ADDSUB",
"EXPR_SHIFT : EXPR_ADDSUB",
"EXPR_ADDSUB : EXPR_ADDSUB '+' EXPR_MUDIMO",
"EXPR_ADDSUB : EXPR_ADDSUB '-' EXPR_MUDIMO",
"EXPR_ADDSUB : EXPR_MUDIMO",
"EXPR_MUDIMO : EXPR_MUDIMO '*' EXPR_NEGATE",
"EXPR_MUDIMO : EXPR_MUDIMO '/' EXPR_NEGATE",
"EXPR_MUDIMO : EXPR_MUDIMO '%' EXPR_NEGATE",
"EXPR_MUDIMO : EXPR_NEGATE",
"EXPR_NEGATE : '-' EXPR_BITWISE_NOT",
"EXPR_NEGATE : EXPR_BITWISE_NOT",
"EXPR_BITWISE_NOT : '~' EXPR_PARENTHESES",
"EXPR_BITWISE_NOT : EXPR_PARENTHESES",
"EXPR_PARENTHESES : '(' EXPR_PARENTHESES ')'",
"EXPR_PARENTHESES : EXPR",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 180 "ex.y"

main()
{
   if (yyparse())
      printf("\nInvalid expression.\n");
   else
      printf("\nCalculator off.\n");
}

yyerror(s)
char *s;
{
   fprintf(stderr, "%s\n", s);
}
#line 280 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 38 "ex.y"
	{
		switch (error_val) {
			case ERROR_NONE:
				printf("%d", yystack.l_mark[-1].num);
				break;
			case ERROR_OVERFLOW:
				printf("overflow");
				break;
			case ERROR_DIVBYZERO:
				printf("dividebyzero");
				break;
		}
		error_val = ERROR_NONE;
	}
break;
case 6:
#line 59 "ex.y"
	{
		if ((yystack.l_mark[0].num > 0 && yystack.l_mark[0].num > INT_MAX - yystack.l_mark[0].num) || (yystack.l_mark[0].num < 0 && yystack.l_mark[0].num < INT_MIN - yystack.l_mark[0].num)) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_OVERFLOW;
		}
		else
			yyval.num = yystack.l_mark[0].num;
	}
break;
case 8:
#line 71 "ex.y"
	{
		yyval.num = yystack.l_mark[-2].num | yystack.l_mark[0].num;
	}
break;
case 10:
#line 78 "ex.y"
	{
		yyval.num = yystack.l_mark[-2].num ^ yystack.l_mark[0].num;
	}
break;
case 12:
#line 85 "ex.y"
	{
		yyval.num = yystack.l_mark[-2].num & yystack.l_mark[0].num;
	}
break;
case 14:
#line 92 "ex.y"
	{
		yyval.num = yystack.l_mark[-3].num >> yystack.l_mark[0].num;
	}
break;
case 15:
#line 96 "ex.y"
	{
		if ((int)((long long)yystack.l_mark[-3].num << yystack.l_mark[0].num) >> yystack.l_mark[0].num != yystack.l_mark[-3].num) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_OVERFLOW;
		}
		else
			yyval.num = yystack.l_mark[-3].num << yystack.l_mark[0].num;
	}
break;
case 17:
#line 108 "ex.y"
	{
		if ((yystack.l_mark[-2].num > 0 && yystack.l_mark[0].num > INT_MAX - yystack.l_mark[-2].num) || (yystack.l_mark[-2].num < 0 && yystack.l_mark[0].num < INT_MIN - yystack.l_mark[-2].num)) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_OVERFLOW;
		}
		else
			yyval.num = yystack.l_mark[-2].num + yystack.l_mark[0].num;
	}
break;
case 18:
#line 117 "ex.y"
	{
		if ((yystack.l_mark[-2].num > 0 && -yystack.l_mark[0].num > INT_MAX - yystack.l_mark[-2].num) || (yystack.l_mark[-2].num < 0 && -yystack.l_mark[0].num < INT_MIN - yystack.l_mark[-2].num)) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_OVERFLOW;
		}
		else
			yyval.num = yystack.l_mark[-2].num - yystack.l_mark[0].num;
	}
break;
case 20:
#line 129 "ex.y"
	{
		if (yystack.l_mark[-2].num != 0 && (yystack.l_mark[-2].num * yystack.l_mark[0].num) / yystack.l_mark[-2].num != yystack.l_mark[0].num) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_OVERFLOW;
		}
		else
			yyval.num = yystack.l_mark[-2].num * yystack.l_mark[0].num;
	}
break;
case 21:
#line 138 "ex.y"
	{
		if (yystack.l_mark[0].num == 0) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_DIVBYZERO;
		}
		else
			yyval.num = yystack.l_mark[-2].num / yystack.l_mark[0].num;
	}
break;
case 22:
#line 147 "ex.y"
	{
		if (yystack.l_mark[0].num == 0) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_DIVBYZERO;
		}
		else
			yyval.num = yystack.l_mark[-2].num % yystack.l_mark[0].num;
	}
break;
case 24:
#line 159 "ex.y"
	{
		yyval.num = -yystack.l_mark[0].num;
	}
break;
case 26:
#line 166 "ex.y"
	{
		yyval.num = ~yystack.l_mark[0].num;
	}
break;
case 28:
#line 173 "ex.y"
	{
		yyval.num = yystack.l_mark[-1].num;
	}
break;
#line 622 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
