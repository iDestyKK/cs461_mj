/*
 * This file defines an example yacc grammar for simple C expressions.
 */

%{
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "global.h"

ERROR_N error_val;
int vars[26];

%}

%union {
  int num;
}

%token <num> NUM

%type <num> EXPR
%type <num> EXPR_ASSIGN
%type <num> EXPR_BITWISE_OR
%type <num> EXPR_BITWISE_XOR
%type <num> EXPR_BITWISE_AND
%type <num> EXPR_SHIFT
%type <num> EXPR_ADDSUB
%type <num> EXPR_MUDIMO
%type <num> EXPR_NEGATE
%type <num> EXPR_BITWISE_NOT
%type <num> EXPR_PARENTHESES

%%
commands:
	|	command commands
	;

command:
	'd' 'u' 'm' 'p' ';' {
		unsigned int i = 0;
		for (; i < 26; i++) {
			printf(
				"%c: %d%s",
				'a' + i,
				vars[i],
				(i != 25) ? "\n\0" : "\0"
			);
		}
	}
	|
	'c' 'l' 'e' 'a' 'r' ';' {
		memset(&vars[0], 0, sizeof(int) * 26);
	}
	|
	EXPR ';' {
		switch (error_val) {
			case ERROR_NONE:
				printf("%d", $1);
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
	;

EXPR: EXPR_ASSIGN
	;
	
EXPR_ASSIGN:
	EXPR_BITWISE_OR
	;

EXPR_BITWISE_OR:
	EXPR_BITWISE_XOR
	|
	EXPR_BITWISE_OR '|' EXPR_BITWISE_XOR {
		$$ = $1 | $3;
	}
	;

EXPR_BITWISE_XOR:
	EXPR_BITWISE_AND
	|
	EXPR_BITWISE_XOR '^' EXPR_BITWISE_AND {
		$$ = $1 ^ $3;
	}
	;

EXPR_BITWISE_AND:
	EXPR_SHIFT
	|
	EXPR_BITWISE_AND '&' EXPR_SHIFT {
		$$ = $1 & $3;
	}
	;

EXPR_SHIFT:
	EXPR_ADDSUB
	|
	EXPR_SHIFT '>' '>' EXPR_ADDSUB {
		$$ = $1 >> $4;
	}
	|
	EXPR_SHIFT '<' '<' EXPR_ADDSUB {
		if ((int)((long long)$1 << $4) >> $4 != $1) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_OVERFLOW;
		}
		else
			$$ = $1 << $4;
	}
	;

EXPR_ADDSUB:
	EXPR_MUDIMO
	|
	EXPR_ADDSUB '+' EXPR_MUDIMO {
		if (($1 > 0 && $3 > INT_MAX - $1) || ($1 < 0 && $3 < INT_MIN - $1)) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_OVERFLOW;
		}
		else
			$$ = $1 + $3;
	}
	|
	EXPR_ADDSUB '-' EXPR_MUDIMO {
		if (($1 > 0 && -$3 > INT_MAX - $1) || ($1 < 0 && -$3 < INT_MIN - $1)) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_OVERFLOW;
		}
		else
			$$ = $1 - $3;
	}
	;

EXPR_MUDIMO:
	EXPR_NEGATE
	|
	EXPR_MUDIMO '*' EXPR_NEGATE {
		if ($1 != 0 && ($1 * $3) / $1 != $3) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_OVERFLOW;
		}
		else
			$$ = $1 * $3;
	}
	|
	EXPR_MUDIMO '/' EXPR_NEGATE {
		if ($3 == 0) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_DIVBYZERO;
		}
		else
			$$ = $1 / $3;
	}
	|
	EXPR_MUDIMO '%' EXPR_NEGATE {
		if ($3 == 0) {
			if (error_val == ERROR_NONE)
				error_val = ERROR_DIVBYZERO;
		}
		else
			$$ = $1 % $3;
	}
	;

EXPR_NEGATE:
	EXPR_BITWISE_NOT
	|
	'-' EXPR_BITWISE_NOT {
		$$ = -$2;
	}
	;

EXPR_BITWISE_NOT:
	EXPR_PARENTHESES
	|
	'~' EXPR_PARENTHESES {
		$$ = ~$2;
	}
	;

EXPR_PARENTHESES:
	'(' EXPR ')' {
		$$ = $2;
	}
	| NUM
	;

%%

main() {
	memset(&vars[0], 0, sizeof(int) * 26);
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
