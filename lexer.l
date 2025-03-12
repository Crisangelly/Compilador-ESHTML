%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  #include "parser.tab.h"
  int line_num = 1;
%}
%option noyywrap
%option yylineno

%%

[<][a-z_]+[1-6]? {
  yylval.cadena = strdup(yytext); // Almacena el valor del token en yylval.cadena
  return INICIO_ETIQUETA;
}

["][^"]*["]  {
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

[:][a-z_]+[=]["][^"]*["]   {
  yylval.cadena = strdup(yytext);
  return ATRIBUTO_VALOR;
}

[ \t] { /* Ignorar espacios en blanco */ }

\n  { line_num++; /* Incrementar el número de línea */ }

. { printf("Error lexico en linea %d: caracter no reconocido '%c'\n", line_num, yytext[0]); }

%%