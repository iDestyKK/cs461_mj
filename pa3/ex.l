%{
#include "y.tab.h"
%}
%%
[0-9]+    { sscanf(yytext, "%d", &yylval.num);
            return NUM; }
[ \t]+    {}
.         { return yytext[0]; }

