%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "parser.tab.h"
%}
%option noyywrap

%%

[<][a-z_]+[1-6]? { return INICIO_ETIQUETA; }
["][a-zA-Z ]+["] { return CADENA_DE_TEXTO; }
[>] { return CIERRE_ETIQUETA; }
[:][a-z_]+ { return ATRIBUTO; }
[:][a-z_]+[=]["][a-zA-Z ]+["] { return ATRIBUTO_VALOR; }

%%