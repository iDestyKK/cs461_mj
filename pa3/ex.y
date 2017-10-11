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

%%
commands:
	|	commands command
	;

command	:	expr ';' {
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

expr:       '(' expr ')' {
                $$ = $2;
            }
        |   expr '(' expr ')' {
                $$ = $1 + $3;
            }
        |   '~' NUM {
            $$ = ~$2;
        }
        |   '-' NUM {
            $$ = $2 * -1;
        }
        |   expr '*' expr {
                $$ = $1 * $3;
            }
        |   expr '/' expr {
                if ($3 == 0)
                    error_val = ERROR_DIVBYZERO;
                else
                    $$ = $1 / $3;
            }
        |   expr '%' expr {
                if ($3 == 0)
                    error_val = ERROR_DIVBYZERO;
                else
                    $$ = $1 % $3;
            }
        |	expr '+' expr {
                if (($1 > 0 && $1 > INT_MAX - $3) || ($3 < 0 && $1 < INT_MIN - $3))
                    error_val = ERROR_OVERFLOW;
                else
                    $$ = $1 + $3;
            }
        |   expr '-' expr {
                $$ = $1 - $3;
            }
	    |   NUM {
                if (($1 > 0 && $1 > INT_MAX - $1) || ($1 < 0 && $1 < INT_MIN - $1))
                    error_val = ERROR_OVERFLOW;
                else
                    $$ = $1;
            }
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
