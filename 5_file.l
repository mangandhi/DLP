%option noyywrap
%{
    #include<stdio.h>
    #include<stdlib.h>
%}

%%

[ ] {} 

"//".*  {}

"/"([^]|\+[^/])\+"/"  {}

auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while { printf("Keyword: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]* { 
    printf("Identifier : %s\n", yytext); 
}

"++"|"+"|"--"|"-"|"*"|"/"|"=="|"="|"!="|"<="|">="|"<<"|">>"|"<"|">"|"&&"|"||"|"&"|"|"|"!"|"%="|"%"|"^"|"~" { printf("Operator: %s\n", yytext); }

[(){}\[\],;]  { printf("Punctuation : %s\n", yytext); }

[0-9]+\.[0-9]+ {printf("Float Constant : %s\n", yytext);}

[0-9]+ {printf("Integer Constant : %s\n", yytext);}

\"[^\"]*\" {printf("String Constant : %s\n", yytext);}

\'.\'   { printf("Char Constant : %s\n", yytext); }

. {printf("Invalid Symbol : %s\n", yytext);}

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    
    yyin = file;
    yylex();
    fclose(file);
    return 0;
}