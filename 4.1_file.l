%option noyywrap
%{
#include <stdio.h>
int v = 0, c = 0;
%}

%%
[aeiouAEIOU] { v++; }
[a-zA-Z]     { c++; }
[ \t\n]      ;
.            ;
%%

int main() {
  printf("Enter String: ");
  yylex();
  printf("No. of Vowels : %d\n", v);
  printf("No. of Consonant : %d\n", c);
  return 0;
}
