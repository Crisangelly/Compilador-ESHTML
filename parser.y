%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h> 

  // Tabla de etiquetas válidas
  struct etiqueta_valida {
    char *etiqueta_espanol;
    char *inicio_etiqueta_html;
    char *cierre_etiqueta_html;
  };

  struct etiqueta_valida tabla_etiquetas[] = {
    {"<parrafo", "<p", "</p>"},
    // Agrega más etiquetas aquí
    {NULL, NULL} // Marcador de fin de tabla
  };


  char *traducir_etiqueta(char *etiqueta_espanol) {
    for (int i = 0; tabla_etiquetas[i].etiqueta_espanol != NULL; i++) {
      if (strcmp(etiqueta_espanol, tabla_etiquetas[i].etiqueta_espanol) == 0) {
        return tabla_etiquetas[i].inicio_etiqueta_html;
      }
    }
      return NULL; // Etiqueta no encontrada
  }


  extern int yylex(void);
  extern char *yytext;
  extern FILE *yyin;
  extern FILE *yyout;
  extern int yylineno;

  void yyerror(char *s);

%}

%union {
  char *cadena;
}


%token <cadena> INICIO_ETIQUETA <cadena> CADENA_DE_TEXTO <cadena> CIERRE_ETIQUETA <cadena> ATRIBUTO <cadena> ATRIBUTO_VALOR

%type <cadena> documento elemento inicio atributo contenido cerrar_inicio

%left INICIO_ETIQUETA
%left ATRIBUTO
%left ATRIBUTO_VALOR
%left CADENA_DE_TEXTO
%left CIERRE_ETIQUETA

%%

documento: elemento documento {
            $$ = $2;
          };
          | elemento {
            $$ = $1;
          };

elemento: inicio atributo cerrar_inicio contenido CIERRE_ETIQUETA {
  
  printf("al parecer consiguio eso'%s' \n", $1)
};
 | error { yyerror(" la estructura de la etiqueta esta mal"); } ;

inicio: INICIO_ETIQUETA {
    char *traduccion = traducir_etiqueta($1);
    if (traduccion != NULL) {
        $$ = traduccion;
    } else {
        fprintf(stderr, "Error semantico en la linea %d: etiqueta '%s' no valida\n", yylineno, $1);
        YYABORT; // Abortar el analisis si la etiqueta no es valida
    }
};

atributo: atributo ATRIBUTO_VALOR  { 
          $$ = $2;

          char *simbolo_igual = strchr($2, '=');
          char atributo[100];
          strncpy(atributo, $2, simbolo_igual - $2);
          atributo[simbolo_igual - $2] = '\0'; 
          char *valor = simbolo_igual + 1;

        };
        | ATRIBUTO { 
          $$ = $1;

        };
        | /* vacío */ { 
          $$ = " ";
        };

cerrar_inicio: { fprintf(yyout, ">"); };

contenido: contenido elemento  { 
            $$ = $2;
          };
          | contenido CADENA_DE_TEXTO { 
            $$ = $2;
          };
          | /* vacío */ {  
            $$ = " ";
          };


%%

int main(void) {
  yyin = fopen("eshtml.txt", "r");
  yyout = fopen("html.txt", "w");
  int s = yyparse();  
  if(s == 0){
    printf("Todo en orden");
  }
}

void yyerror(char *s){
  fprintf(stderr, "Error de sintaxis en la linea %d, token: %s, error: %s\n", yylineno, yytext, s);
}