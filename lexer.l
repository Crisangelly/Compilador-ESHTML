%{
  #include <stdio.h>
%}
%option noyywrap

%%

[<][a-z_]+[1-6]? { fprintf(yyout, "INICIO_ETIQUETA"); }
["][a-zA-Z ]+["] { fprintf(yyout, "CADENA_DE_TEXTO"); }
[:][a-z_]+ { fprintf(yyout, "ATRIBUTO"); }
[:][a-z_]+[=]["][a-zA-Z ]+["] { fprintf(yyout, "ATRIBUTO_VALOR"); }
[>] { fprintf(yyout, "CIERRE_ETIQUETA"); }

%%

int main(){
  yyin = fopen("eshtml.txt", "r");
  yyout = fopen("html.txt", "w");
  yylex();
}