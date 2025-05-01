%option noyywrap
%{
    #include<stdio.h>
    int w=0, c=0, l=0;
%}

%%
[\n]     {l++;}
[ \t]     {c+=yyleng;}
[^ \t\n]+    {w++; c+=yyleng;}

%%
int main(){
    printf("Enter String: ");
    yylex();
    printf("no of line : %d\n",l);
    printf("no of words : %d\n",w);
    printf("no of char : %d",c);
    return 0;
}