%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  #include "parser.tab.h"
  #include "errores.h" // Incluir el archivo de los errores

  void imprimir_tabla(const char *lexema, const char *token) {
    printf("|       Lexema         |         Token           |\n");
    printf("|----------------------|-------------------------|\n");
    printf("| %-21s | %-21s |\n", lexema, token);
    printf("|----------------------|-------------------------|\n");
  }

%}
%option noyywrap
%option yylineno

%%

[<][a-z_]+[1-6]? {
  yylval.cadena = strdup(yytext); // Almacena el valor del token en yylval.cadena
  imprimir_tabla(yytext, "INICIO_ETIQUETA");
  return INICIO_ETIQUETA;
}

["][^"]*["]  {
  yylval.cadena = strdup(yytext);
  imprimir_tabla(yytext, "CADENA_DE_TEXTO");
  return CADENA_DE_TEXTO;
}

[>] {
  yylval.cadena = strdup(yytext);
  imprimir_tabla(yytext, "CIERRE_ETIQUETA");
  return CIERRE_ETIQUETA;
}

[:][a-z_]+  {
  yylval.cadena = strdup(yytext);
  imprimir_tabla(yytext, "ATRIBUTO");
  return ATRIBUTO;
}

[:][a-z_]+[=]["][^"]*["]   {
  yylval.cadena = strdup(yytext);
  imprimir_tabla(yytext, "ATRIBUTO_VALOR");
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