#include <stdio.h>

void
yyerror(const char *str)
{
    fprintf(stderr, "%s\n", str);

}

int
yywrap()
{
    return 0;
}