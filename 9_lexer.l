%{
#include "y.tab.h"
%}

%%
[0-9]*[02468]"\n" { return EVEN; }
[0-9]*[13579]"\n" { return ODD; }
%%
int main(void)
{
yyparse();
return 0;
}

int yywrap(void)
{
return 0;
}

int yyerror(void)
{
printf("Error\n");
exit(1);
}

// %{
// #include "y.tab.h"
// %}

// %%

// i       { return I; }
// a       { return A; }
// b       { return B; }
// t       { return T; }
// e       { return E; }
// [ \t\n] { /* ignore whitespace */ }

// %%

// int yywrap() {
//     return 1;
// }
