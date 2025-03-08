%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  #include "parser.tab.h"
%}
%option noyywrap
%option yylineno

%%

[<][a-z_]+[1-6]? {
  yylval.cadena = strdup(yytext); // Almacena el valor del token en yylval.cadena
  return INICIO_ETIQUETA;
}

["][a-zA-Z ]+["]  {
  yylval.cadena = strdup(yytext);
  return CADENA_DE_TEXTO;
}

[>] {
  yylval.cadena = strdup(yytext);
  return CIERRE_ETIQUETA;
}

[:][a-z_]+  {
  yylval.cadena = strdup(yytext);
  return ATRIBUTO;
}

[:][a-z_]+[=]["][a-zA-Z_ ]+["]  {
  yylval.cadena = strdup(yytext);
  return ATRIBUTO_VALOR;
}

%%