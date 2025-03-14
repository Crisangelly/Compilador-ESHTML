%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h> 

  //------------------------- Tabla de etiquetas válidas
  struct etiqueta_valida {
    char *etiqueta_espanol;
    char *inicio_etiqueta_html;
    char *cierre_etiqueta_html;
  };

  struct etiqueta_valida tabla_etiquetas[] = {
    {"<aparte", "<aside", "</aside>"},
    {"<boton", "<button", "</button>"},
    {"<cabecera", "<header", "</header>"},
    {"<campo", "<input", " "},
    {"<cursiva", "<em", "</em>"},
    {"<division", "<div", "</div>"},
    {"<enlace", "<a", "</a>"},
    {"<formulario", "<form", "</form>"},
    {"<imagen", "<img", " "},
    {"<italica", "<i", "</i>"},
    {"<leyenda", "<label", "</label>"},
    {"<linea_horizontal", "<hr", " "},
    {"<lista_elemento", "<li", "</li>"},
    {"<lista_no_ordenada", "<ul", "</ul>"},
    {"<lista_ordenada", "<ol", "</ol>"},
    {"<navegacion", "<nav", "</nav>"},
    {"<negrita", "<strong", "</strong>"},
    {"<parrafo", "<p", "</p>"},
    {"<pequenio", "<small", "</small>"},
    {"<pie_de_pagina", "<footer", "</footer>"},
    {"<resaltar", "<mark", "</mark>"},
    {"<seccion", "<section", "</section>"},
    {"<seleccion", "<span", "</span>"},
    {"<tabla", "<table", "</table>"},
    {"<tabla_cabecera", "<th", "</th>"},
    {"<tabla_cabeza", "<thead", "</thead>"},
    {"<tabla_celda", "<td", "</td>"},
    {"<tabla_cuerpo", "<tbody", "</tbody>"},
    {"<tabla_fila", "<tr", "</tr>"},
    {"<tachar", "<s", "</s"},
    {"<titulo1", "<h1", "</h1>"},
    {"<titulo2", "<h2", "</h2>"},
    {"<titulo3", "<h3", "</h3>"},
    {"<titulo4", "<h4", "</h4>"},
    {"<titulo5", "<h5", "</h5>"},
    {"<titulo6", "<h6", "</h6>"},
    {NULL, NULL, NULL} // Marcador de fin de tabla
  };

  //------------------------- Tabla de atributos solos válidos
  struct atributo_valido {
    char *atributo_espanol;
    char *atributo_html;
  };

  struct atributo_valido tabla_atributos[] = {
    {":requerido", " required "},
    {":reverso", " reversed "},
    {NULL, NULL} // Marcador de fin de tabla
  };

  //------------------------- Tabla de atributos con valor válidos
  struct valor_atributo {
    char *valor_espanol;
    char *valor_html;
  };

  struct valor_atributo valores_type[] = {
    {"\"texto\"", "\"text\""},
    {"\"numero\"", "\"number\""},
    {"\"radio\"", "\"radio\""},
    {"\"caja_check\"", "\"checkbox\""},
    {"\"enviar\"", "\"submit\""},
    {"\"correo\"", "\"email\""},
    {"\"telefono\"", "\"tel\""},
    {"\"contrasenia\"", "\"password\""},
    {NULL, NULL}
  };

  struct atributo_valor_valido {
    char *atributo_valor_espanol;
    char *atributo_valor_html;
    struct valor_atributo *valores_permitidos;
  };

  struct atributo_valor_valido tabla_atributos_valor[] = {
    {":tipo", "type", valores_type},
    {":clase", "class", NULL},
    {":identificador", "id", NULL},
    {":nombre", "name", NULL},
    {":enlace_imagen", "src", NULL},
    {":enlace_externo", "href", NULL},
    {":descripcion", "alt", NULL},
    {NULL, NULL, NULL} // Marcador de fin de tabla
  };

  // Funciones de traducción

  int traducir(char *cadena_espanol, void *tabla, size_t tamano_elemento, char *atributo_espanol) {
    int i = 0;
    char *cadena_tabla;

    while (1) {
        cadena_tabla = (char *)((char *)tabla + i * tamano_elemento); // Calcula la dirección del elemento actual

        if (*(char **)cadena_tabla == NULL) { // Verifica el marcador de fin de tabla
            return -1; // Elemento no encontrado
        }

        if (strcmp(*(char **)cadena_tabla, cadena_espanol) == 0) {
            return i; // Elemento encontrado, devuelve el índice
        }

        i++;
    }
  }

  int traducir_valor(char *valor_espanol, struct valor_atributo *valores) { //para traducir los valores de atributos como type
    int i = 0; 
    for (i; valores[i].valor_espanol != NULL; i++) {
    if (strcmp(valor_espanol, valores[i].valor_espanol) == 0) {
        return i;
      }
    }
      return -1; // Atributo no encontrada
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
  if($1 != " "){
    fprintf(yyout, "%s", $1);
  }
};
 | error { yyerror(" la estructura de la etiqueta esta mal"); } ;

inicio: INICIO_ETIQUETA {
    int traduccion = traducir($1, tabla_etiquetas, sizeof(struct etiqueta_valida), "etiqueta_espanol");

    if (traduccion != -1) {
      $$ = tabla_etiquetas[traduccion].cierre_etiqueta_html;
      fprintf(yyout, "%s", tabla_etiquetas[traduccion].inicio_etiqueta_html);
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

          int traduccion = traducir(atributo, tabla_atributos_valor, sizeof(struct atributo_valor_valido), "atributo_espanol");

          if (traduccion != -1) {

            if(tabla_atributos_valor[traduccion].valores_permitidos != NULL){

              int traduccion_valor =  traducir_valor(valor, tabla_atributos_valor[traduccion].valores_permitidos);
              if (traduccion_valor != -1) {
          
                fprintf(yyout, " %s=%s ", tabla_atributos_valor[traduccion].atributo_valor_html, tabla_atributos_valor[traduccion].valores_permitidos[traduccion_valor].valor_html);

              } else {
                fprintf(stderr, "Error semantico en la linea %d: valor del atributo '%s' no valido\n", yylineno, valor, $1);
                YYABORT; // Abortar el analisis si el atributo no es valido
              }

            }else{
              fprintf(yyout, " %s=%s ",tabla_atributos_valor[traduccion].atributo_valor_html, valor);
            }


          } else {
            fprintf(stderr, "Error semantico en la linea %d: atributo '%s' no valido\n", yylineno, atributo, $1);
            YYABORT; // Abortar el analisis si el atributo no es valido
          }
          
        };
        | ATRIBUTO { 
          $$ = $1;

          int traduccion = traducir($1, tabla_atributos, sizeof(struct atributo_valido), "atributo_espanol");

          if (traduccion != -1) {
            $$ = tabla_atributos[traduccion].atributo_html;
            fprintf(yyout, "%s", tabla_atributos[traduccion].atributo_html);
          } else {
            fprintf(stderr, "Error semantico en la linea %d: atributo '%s' no valido\n", yylineno, $1);
            YYABORT; // Abortar el analisis si el atributo no es valido
          }

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

            char* first_quote = strchr($2, '"');
            char* second_quote = strrchr($2, '"');

            if (first_quote && second_quote && first_quote != second_quote) {
                *second_quote = '\0'; // Termina la cadena en la segunda comilla
                fprintf(yyout, first_quote + 1);
            }

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