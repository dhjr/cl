%{
    #include<stdio.h>

%}

%%
"/*"([^*]|\*+[^*/])*\*+"/"    { /* Ignore multi-line comments */ }
"//".*                        { /* Ignore single-line comments */ }

"{"|"}"|"("|")"|"["|"]"|";"|","|"." { printf("[DELIMITER]  : %s\n", yytext); }
"=="|"!="|"<="|">="|"&&"|"||"|"++"|"--"|"+"|"-"|"*"|"/"|"%"|"="|"<"|">" {
    printf("[OPERATOR]   : %s\n", yytext);
}
"int"|"float"|"char"|"double"|"if"|"else"|"while"|"for"|"return"|"void"|"break" {printf("[KEYWORD]    : %s\n", yytext); }
[a-zA-Z_][_a-zA-Z0-9]*  { printf("[IDENTIFIER]  : %s\n", yytext); }
[0-9]+  {printf("INT: %s\n", yytext); }
[0-9]+"."[0-9]+   {printf("FLOAT: %s\n", yytext); }
[ \t\n]+   ;
.  { printf("[UNKNOWN]    : %s\n", yytext); }

%%

void main()
{
    printf("Enter the program:");
    yylex();
}

int yywrap(){
    return 1;
}