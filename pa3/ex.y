/*
 * This file defines an example yacc grammar for simple C expressions.
 */

%{
#include <stdio.h>
#include <limits.h>

typedef enum error_n {
    ERROR_NONE,
    ERROR_OVERFLOW,
    ERROR_DIVBYZERO
} ERROR_N;

ERROR_N error_val;
%}

%union {
  int num;
}

%token <num> NUM

%type <num> expr
%type <num> expr1
%type <num> expr2
%type <num> expr3
%type <num> expr4
%type <num> expr5
%type <num> expr6
%type <num> expr7
%type <num> expr8
%type <num> expr9
%type <num> expr10

%%
commands:
	|	command commands
	;

command:
	expr ';' {
		switch (error_val) {
			case ERROR_NONE:
				printf("%d", $1);
				break;
			case ERROR_OVERFLOW:
				printf("overflow\n");
				break;
			case ERROR_DIVBYZERO:
				printf("dividebyzero\n");
				break;
		}
		error_val = ERROR_NONE;
	}
	;

expr: expr1
	| NUM
	;
	
expr1:
	NUM {
		if (($1 > 0 && $1 > INT_MAX - $1) || ($1 < 0 && $1 < INT_MIN - $1))
			error_val = ERROR_OVERFLOW;
		else
			$$ = $1;
	}
	| expr2
	;

expr2:
	expr2 '|' expr3 {
		$$ = $1 | $3;
	}
	| expr3
	;

expr3:
	expr3 '^' expr4 {
		$$ = $1 ^ $3;
	}
	| expr4
	;

expr4:
	expr4 '&' expr5 {
		$$ = $1 & $3;
	}
	| expr5
	;

expr5:
	expr5 '>' '>' expr6 {
		$$ = $1 >> $4;
	}
	|
	expr5 '<' '<' expr6 {
		$$ = $1 << $4;
	}
	| expr6
	;

expr6:
	expr6 '+' expr7 {
		$$ = $1 + $3;
	}
	|
	expr6 '-' expr7 {
		$$ = $1 - $3;
	}
	| expr7
	;

expr7:
	expr7 '*' expr8 {
		$$ = $1 * $3;
	}
	|
	expr7 '/' expr8 {
		if ($3 == 0)
			error_val = ERROR_DIVBYZERO;
		else
			$$ = $1 / $3;
	}
	|
	expr7 '%' expr8 {
		if ($3 == 0)
			error_val = ERROR_DIVBYZERO;
		else
			$$ = $1 % $3;
	}
	| expr8
	;

expr8:
	'-' expr9 {
		$$ = -$2;
	}
	| expr9
	;

expr9:
	'~' expr10 {
		$$ = ~$2;
	}
	| expr10
	;

expr10: '(' expr10 ')' {
		$$ = $2;
	}
	| expr
	;

%%

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
