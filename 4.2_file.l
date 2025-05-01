%option noyywrap
%{
    #include<stdio.h>
%}

%%
charusat {printf("University");}
Charusat {printf("University");}
.   {printf("%c", yytext[0]);}
 
%%
int main(){
    printf("Enter String: ");
    yylex();
    return 0;
}