%{
#include <errno.h>
#include <limits.h>
#include "y.tab.h"
#include "global.h"

ERROR_N error_val = ERROR_NONE;
%}
%%
[0-9]+    { 
			//Check if the integer given really is an integer within bounds.
			char* end;
			long val = strtol(yytext, &end, 10);
			if (((long)((int)val) != val) || 
				(errno == ERANGE && (val == LONG_MIN || val == LONG_MAX))) {
				error_val = ERROR_OVERFLOW;
			}
			yylval.num = val;
			//sscanf(yytext, "%d", &yylval.num);
            return NUM; }
[ \t]+    {}
.         { return yytext[0]; }

