%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h> 

  #include "errores.h" // Incluir el archivo de los errores

  //Imprimir AST 
  struct ASTNodo{
    char *no_terminal; 
    char *terminal; 
  };

  struct ASTNodo nodos[100];
  int num_nodos = 0;

  void agregar_nodo(char *no_terminal, char *terminal){
    if (num_nodos < 100) {
      nodos[num_nodos].no_terminal = no_terminal;
      nodos[num_nodos].terminal= terminal;
      num_nodos++;
    } else {
      fprintf(stderr, "Demasiados nodos.\n");
      exit(1);
    }
  }

  void imprimir_AST() {
    static int inicio_arbol = 1; //imprimir un encabezado una sola vez
    if (inicio_arbol) {
      printf("\033[32m");
      printf("\n\nAnalisis Sintactico\n");
      printf("DOCUMENTO\n");
      printf("  |\n");
      inicio_arbol = 0;
    }

    if (num_nodos > 0) {
      int indentacion = 0; // Inicializamos la indentación a 0
      for (int i = 0; i < num_nodos; i++) {
        // Ajustar la indentación según el tipo de nodo
        if (strcmp(nodos[i].no_terminal, "ELEMENTO") == 0 && nodos[i].terminal[0] == '\0') {
          // Nodo ELEMENTO padre, aumentar la indentación
          indentacion++;
        } else if (strcmp(nodos[i].no_terminal, "CIERRE_ETIQUETA") == 0) {
          // Nodo CIERRE_ETIQUETA, disminuir la indentación
          indentacion--;
        }

        // Imprimir la indentación
        for (int j = 0; j < indentacion; j++) {
          printf("  "); // 2 espacios por nivel de indentación
        }

        // Imprimir el nodo
        if (nodos[i].terminal[0] == '\0') {
          printf("|____ %s \n", nodos[i].no_terminal); // Imprimir el no terminal padre
        } else {
          printf("|____ %s : %s \n", nodos[i].no_terminal, nodos[i].terminal);
        }

        // Ajustar la indentación después de imprimir el nodo
        if (strcmp(nodos[i].no_terminal, "INICIO_ETIQUETA") == 0 && strcmp(nodos[i + 1].no_terminal, "ELEMENTO") == 0 && nodos[i + 1].terminal[0] == '\0') {
          // Nodo INICIO_ETIQUETA seguido de ELEMENTO padre, aumentar la indentación
          indentacion++;
        }
      }
    }
  }

  // Función para acumular errores

  struct error_estructura errores[100];
  int num_errores = 0;

  void agregar_error(int linea, char *mensaje, int tipo, char *token) {
    if (num_errores < 100) {

      //Verificar que no hayan mensajes duplicados en los errores sintácticos (debido a la recursividad)
      if(tipo == 1){
        for (int i = 0; i < num_errores; i++) {
            if (errores[i].linea == linea && strcmp(errores[i].token, token) == 0) {
                return; // Error duplicado, no agregar
            }
        }
      }

      errores[num_errores].linea = linea;
      strcpy(errores[num_errores].mensaje, mensaje);
      errores[num_errores].tipo = tipo;
      strcpy(errores[num_errores].token, token);
      num_errores++;

    } else {
      fprintf(stderr, "Demasiados errores.\n");
      exit(1);
      }
  }


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

  void yyerror();

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
    agregar_nodo("CIERRE_ETIQUETA", $1);
  }

};
 | error { yyerror(); } ;

inicio: INICIO_ETIQUETA {
    agregar_nodo("ELEMENTO","");

    int traduccion = traducir($1, tabla_etiquetas, sizeof(struct etiqueta_valida), "etiqueta_espanol");

    if (traduccion != -1) {
      $$ = tabla_etiquetas[traduccion].cierre_etiqueta_html;
      fprintf(yyout, "%s", tabla_etiquetas[traduccion].inicio_etiqueta_html);

      agregar_nodo("INICIO_ETIQUETA", tabla_etiquetas[traduccion].inicio_etiqueta_html);

    } else {
      char mensaje[256];
      sprintf(mensaje, "etiqueta '%s' no valida", $1);
      agregar_error(yylineno, mensaje, 2, yytext); // 2 para error semántico
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

                char cadena_concatenada[256];
                sprintf(cadena_concatenada, "%s=%s", tabla_atributos_valor[traduccion].atributo_valor_html, tabla_atributos_valor[traduccion].valores_permitidos[traduccion_valor].valor_html);
                agregar_nodo("ATRIBUTO", cadena_concatenada);

              } else {
                char mensaje[256];
                sprintf(mensaje, "valor del atributo '%s' no valido", valor);
                agregar_error(yylineno, mensaje, 2, yytext);
              }

            }else{
              fprintf(yyout, " %s=%s ",tabla_atributos_valor[traduccion].atributo_valor_html, valor);
              char cadena_concatenada[256];
              sprintf(cadena_concatenada, "%s=%s", tabla_atributos_valor[traduccion].atributo_valor_html, valor);
              agregar_nodo("ATRIBUTO", cadena_concatenada);
            }

          } else {
            char mensaje[256];
            sprintf(mensaje, "atributo '%s' no valido", atributo);
            agregar_error(yylineno, mensaje, 2, yytext);
          }
          
        };
        | ATRIBUTO { 
          $$ = $1;

          int traduccion = traducir($1, tabla_atributos, sizeof(struct atributo_valido), "atributo_espanol");

          if (traduccion != -1) {
            $$ = tabla_atributos[traduccion].atributo_html;
            fprintf(yyout, "%s", tabla_atributos[traduccion].atributo_html);
            
            agregar_nodo("ATRIBUTO", tabla_atributos[traduccion].atributo_html);
          } else {
            char mensaje[256];
            sprintf(mensaje, "atributo '%s' no valido", $1);
            agregar_error(yylineno, mensaje, 2, yytext);
          }

        };
        | /* vacío */ { 
          $$ = " ";
        };

cerrar_inicio: { 
  fprintf(yyout, ">"); 
  agregar_nodo("CERRAR_INICIO", ">");
};

contenido: contenido elemento  { 
            $$ = $2;
            //agregar_nodo("CONTENIDO", "");
          };
          | contenido CADENA_DE_TEXTO { 
            $$ = $2;

            char* first_quote = strchr($2, '"');
            char* second_quote = strrchr($2, '"');

            if (first_quote && second_quote && first_quote != second_quote) {
                *second_quote = '\0'; // Termina la cadena en la segunda comilla
                fprintf(yyout, first_quote + 1);
            }

            agregar_nodo("CONTENIDO", $2);

          };
          | /* vacío */ {  
            $$ = " ";
          };


%%

int main(void) {
  yyin = fopen("eshtml.txt", "r");
  yyout = fopen("html.txt", "w");
  int s = yyparse();  

  // Imprimir errores después del análisis
  if (num_errores > 0) {
    fprintf(stderr, "\033[31m");
    fprintf(stderr, "\n\nErrores encontrados:\n");
    for (int tipo_error = 0; tipo_error < 3; tipo_error++) {
        fprintf(stderr, "\n\nErrores %s:\n", tipo_error == 0 ? "lexicos" : (tipo_error == 1 ? "sintacticos" : "semanticos"));
        fprintf(stderr, "|------------|------|----------------------------------------------------------------------------------------|------------------------------------|\n");
        fprintf(stderr, "|    Linea   | Tipo |                              Mensaje                                                   |               Token                |\n");
        fprintf(stderr, "|------------|------|----------------------------------------------------------------------------------------|------------------------------------|\n");
      for (int i = 0; i < num_errores; i++) { 
        if (errores[i].tipo == tipo_error) {
          fprintf(stderr, "|   %-6d   |  %-3d | %-86s | %-34s |\n", errores[i].linea, errores[i].tipo, errores[i].mensaje, errores[i].token);
          fprintf(stderr, "|------------|------|----------------------------------------------------------------------------------------|------------------------------------|\n");
        }
      }
    }

  } else if (s == 0) {
    //Imprimir el árbol de análisis sintáctico
    imprimir_AST();

    printf("\n\nTodo en orden.\n\n\n");
  }
}

void yyerror(){
  char *s;
  if (yytext[0] == '<') {
    s = "Error en la etiqueta de inicio";
  } else if (yytext[0] == ':') {
    s = "Error en la seccion de atributos";
  } else {
    s = "Error en la seccion de contenido o cierre de etiqueta";
  }

  char mensaje[256];
  if (yytext && yytext[0] != '\0') {
    sprintf(mensaje, "token: %s, error: %s", yytext, s);
  } else {
    sprintf(mensaje, "error: %s", s); // No incluir el token si está vacío
  }
  agregar_error(yylineno, mensaje, 1, yytext); // 1 para error sintáctico
}