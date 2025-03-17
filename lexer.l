%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  #include "parser.tab.h"
  #include "errores.h" // Incluir el archivo de los errores

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

\n { /* Reconocer saltos de línea */ }

. { 
  char mensaje[256];
  sprintf(mensaje, "caracter no reconocido '%c'", yytext[0]);
  agregar_error(yylineno, mensaje, 0, yytext); // 0 para error léxico
}

%%