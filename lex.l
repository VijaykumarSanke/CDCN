
%{
#include <stdio.h>
%}

%%

[0-9]+                  { printf("Number      : %s\n", yytext); }

"int"|"float"|"char"|"if"|"else"|"while"|"for"|"return"
                        { printf("Keyword     : %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("Identifier  : %s\n", yytext); }

"=="|"!="|"<="|">="|"+"|"-"|"*"|"/"|"="|"<"|">"
                        { printf("Operator    : %s\n", yytext); }

[(){};,]                { printf("Symbol      : %s\n", yytext); }

[ \t\n]+                { /* ignore spaces */ }

.                       { printf("Unknown     : %s\n", yytext); }

%%

int main()
{
    printf("Enter the program:\n");
    yylex();
    return 0;
}
