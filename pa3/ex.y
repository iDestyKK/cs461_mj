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
char overflow_occurred;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

//Just set the stack to take so much that it won't overflow unless you're
//crazy... I'm tired.
#define YYMAXDEPTH 100000000

%}

%union {
  int num;
  char var;
  char* cmd;
}

%token <num> NUM
%token <var> VAR
%token <cmd> CMD
%token ASMT_PLUS ASMT_SUBT ASMT_MULT ASMT_DIVI ASMT_MODU ASMT_SFTL ASMT_SFTR ASMT_ANDO ASMT_XORO ASMT_OROP

%type <num> EXPR
%type <num> EXPR_ASSIGN
%type <num> EXPR_SUPERASSIGN
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
	CMD ';' {
		if (strcmp($1, "dump") == 0) {
			unsigned int i = 0;
			for (; i < 26; i++) {
				printf(
					"%c: %d%s",
					'a' + i,
					vars[i],
					"\n"//(i != 25) ? "\n\0" : "\0"
				);
			}
		}
		else
		if (strcmp($1, "clear") == 0) {
			memset(&vars[0], 0, sizeof(int) * 26);
		}
		free($1);
	}
	|
	EXPR ';' {
		switch (error_val) {
			case ERROR_NONE:
				printf("%d\n", $1);
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

EXPR: EXPR_ASSIGN
	;
	
EXPR_ASSIGN:
	VAR '=' EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			vars[$1] = $3;
			$$ = $3;
		}
	}
	|
	EXPR_SUPERASSIGN
	;

EXPR_SUPERASSIGN:
	VAR ASMT_PLUS EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			vars[$1] = vars[$1] + $3;
			$$ = vars[$1];
		}
	}
	|
	VAR ASMT_SUBT EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			vars[$1] = vars[$1] - $3;
			$$ = vars[$1];
		}
	}
	|
	VAR ASMT_MULT EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			if (vars[$1] != 0 && (vars[$1] * $3) / vars[$1] != $3) {
				if (error_val == ERROR_NONE)
					error_val = ERROR_OVERFLOW;
			}
			else {
				vars[$1] = vars[$1] * $3;
				$$ = vars[$1];
			}
		}
	}
	|
	VAR ASMT_DIVI EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			if ($3 == 0) {
				if (error_val == ERROR_NONE)
					error_val = ERROR_DIVBYZERO;
			}
			else {
				vars[$1] = vars[$1] / $3;
				$$ = vars[$1];
			}
		}
	}
	|
	VAR ASMT_MODU EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			if ($3 == 0) {
				if (error_val == ERROR_NONE)
					error_val = ERROR_DIVBYZERO;
			}
			else {
				vars[$1] = vars[$1] % $3;
				$$ = vars[$1];
			}
		}
	}
	|
	VAR ASMT_SFTL EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			if ($3 < 0) {
				//Matching the undefined behaviour of the solution executable
				char msb = (vars[$1] >> 31) & 1;
				long long val = vars[$1];
				unsigned int lv = (unsigned int)((val << $3) >> 32) & 0xFFFFFFFF;
				int rv = (int)(val << $3) & 0xFFFFFFFF;
				if (lv > 0)
					rv |= (1 << 31); //Set the MSB if any of last 32 bits are anything but 0.
				if (error_val == ERROR_NONE && msb != ((rv >> 31) & 1)) {
					error_val = ERROR_OVERFLOW;
				}
				else {
					vars[$1] = rv;
					$$ = vars[$1];
				}
			}
			else {
				if ((int)((long long)vars[$1] << $3) >> $3 != vars[$1]) {
					if (error_val == ERROR_NONE)
						error_val = ERROR_OVERFLOW;
				}
				else {
					vars[$1] = vars[$1] << $3;
					$$ = vars[$1];
				}
			}
		}
	}
	|
	VAR ASMT_SFTR EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			//vars[$1] = vars[$1] >> ($3 % 32);
			//$$ = vars[$1];
			if ($3 < 0) {
				unsigned int i = 0;
				int v = vars[$1];
				char msb = (vars[$1] >> 31) & 1;
				for (; i < 64 - ((-$3) % 64); i++) {
					v>>=1;
					v |= (((int)msb) << 31);
				}
				vars[$1] = v;
			}
			else {
				unsigned int i = 0, v = vars[$1];
				char msb = (vars[$1] >> 31) & 1;
				for (; i < MIN($3, 32); i++) {
					v>>=1;
					v |= (((int)msb) << 31);
				}
				vars[$1] = v;
			}
			$$ = vars[$1];
		}
	}
	|
	VAR ASMT_ANDO EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			vars[$1] = vars[$1] & $3;
			$$ = vars[$1];
		}
	}
	|
	VAR ASMT_XORO EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			vars[$1] = vars[$1] ^ $3;
			$$ = vars[$1];
		}
	}
	|
	VAR ASMT_OROP EXPR_ASSIGN {
		if (error_val == ERROR_NONE) {
			vars[$1] = vars[$1] | $3;
			$$ = vars[$1];
		}
	}
	|
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
		//$$ = ($1 >> $4) | (((($1 >> 31) & 1) == 1) * (0xFFFFFFFF << ($4 % 32)));
		//$$ = $1 >> $4;
		//$$ = $1 >> MIN($4, 32) | (((($1 >> 31) & 1) == 1) * (0xFFFFFFFF << MIN($4, 32)));
		if ($4 < 0) {
			unsigned int i = 0, v = $1;
			char msb = ($1 >> 31) & 1;
			for (; i < 64 - ((-$4) % 64); i++) {
				v>>=1;
				v |= (((int)msb) << 31);
			}
			$$ = v;
		}
		else {
			unsigned int i = 0, v = $1;
			char msb = ($1 >> 31) & 1;
			for (; i < MIN($4, 32); i++) {
				v>>=1;
				v |= (((int)msb) << 31);
			}
			$$ = v;
		}
	}
	|
	EXPR_SHIFT '<' '<' EXPR_ADDSUB {
		if ($4 < 0) {
			//Matching the undefined behaviour of the solution executable
			char msb = ($1 >> 31) & 1;
			long long val = $1;
			unsigned int lv = (unsigned int)((val << $4) >> 32) & 0xFFFFFFFF;
			int rv = (int)(val << $4) & 0xFFFFFFFF;
			if (lv > 0)
				rv |= (1 << 31); //Set the MSB if any of last 32 bits are anything but 0.
			if (error_val == ERROR_NONE && msb != ((rv >> 31) & 1)) {
				error_val = ERROR_OVERFLOW;
			}
			else
				$$ = rv;
		}
		else {
			if ((int)((long long)$1 << $4) >> $4 != $1) {
				if (error_val == ERROR_NONE)
					error_val = ERROR_OVERFLOW;
			}
			else
				$$ = $1 << $4;
		}
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
	| VAR {
		$$ = vars[$1];
	}
	| NUM
	;

%%

main() {
	memset(&vars[0], 0, sizeof(int) * 26);
	overflow_occurred = 0;
	int val;
	val = yyparse();

	if (val)
		printf("\nInvalid expression.\n");
	else
		printf("\nCalculator off.\n");
}

yyerror(s)
char *s;
{
   fprintf(stderr, "%s\n", s);
}
