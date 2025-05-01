%{
    #include<stdio.h>
    int lengthOfPassword=0,lowerCaseCount=0,upperCaseCount=0,digitCount=0,symbolCount=0,extraCharCount=0;
%}

%%
[a-z]       {lowerCaseCount++;lengthOfPassword++;}
[A-Z]       {upperCaseCount++;lengthOfPassword++;}
[0-9]       {digitCount++;lengthOfPassword++;}
[*,;#$@]    {symbolCount++;lengthOfPassword++;}
[\n]        {
                if(lowerCaseCount>0 && upperCaseCount>0 && digitCount>0 && symbolCount++ && extraCharCount==0 && lengthOfPassword>=9 && lengthOfPassword<=15){
                    printf("Valid Password.");
                }
                else{
                    printf("Invalid Password.");
                }
                printf("\n");
                lengthOfPassword=0,lowerCaseCount=0,upperCaseCount=0,digitCount=0,symbolCount=0,extraCharCount=0;
            }
.           {extraCharCount++;}
%%
int yywrap(){
    
}
int main(){
    printf("Enter Password : ");
    yylex();
    return 0;
}