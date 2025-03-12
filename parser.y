%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h> 

  extern int yylex(void);
  extern char *yytext;
  extern FILE *yyin;
  extern FILE *yyout;
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

  if(strcmp($1, "<titulo1") == 0){
    fprintf(yyout, "</h1>");
  }
  if(strcmp($1, "<titulo2") == 0){
    fprintf(yyout, "</h2>");
  }
  if(strcmp($1, "<titulo3") == 0){
    fprintf(yyout, "</h3>");
  }
  if(strcmp($1, "<titulo4") == 0){
    fprintf(yyout, "</h4>");
  }
  if(strcmp($1, "<titulo5") == 0){
    fprintf(yyout, "</h5>");
  }
  if(strcmp($1, "<titulo6") == 0){
    fprintf(yyout, "</h6>");
  }
  if(strcmp($1, "<negrita") == 0){
    fprintf(yyout, "</strong>");
  }
  if(strcmp($1, "<italica") == 0){
    fprintf(yyout, "</i>");
  }
  if(strcmp($1, "<resaltar") == 0){
    fprintf(yyout, "</mark>");
  }
  if(strcmp($1, "<pequenio") == 0){
    fprintf(yyout, "</small>");
  }
  if(strcmp($1, "<cursiva") == 0){
    fprintf(yyout, "</em>");
  }
  if(strcmp($1, "<tachar") == 0){
    fprintf(yyout, "</s>");
  }
  if(strcmp($1, "<lista_no_ordenada") == 0){
    fprintf(yyout, "</ul>");
  }
  if(strcmp($1, "<lista_ordenada") == 0){
    fprintf(yyout, "</ol>");
  }
  if(strcmp($1, "<lista_elemento") == 0){
    fprintf(yyout, "</li>");
  }
  if(strcmp($1, "<division") == 0){
    fprintf(yyout, "</div>");
  }
  if(strcmp($1, "<seccion") == 0){
    fprintf(yyout, "</section>");
  }
  if(strcmp($1, "<pie") == 0){
    fprintf(yyout, "</footer>");
  }
  if(strcmp($1, "<cabecera") == 0){
    fprintf(yyout, "</header>");
  }
   if(strcmp($1, "<navegacion") == 0){
    fprintf(yyout, "</nav>");
  }
  if(strcmp($1, "<aparte") == 0){
    fprintf(yyout, "</aside>");
  }
  if(strcmp($1, "<seleccion") == 0){
    fprintf(yyout, "</span>");
  }
  if(strcmp($1, "<tabla") == 0){
    fprintf(yyout, "</table>");
  }
  if(strcmp($1, "<tabla_cabeza") == 0){
    fprintf(yyout, "</thead>");
  }
  if(strcmp($1, "<tabla_cuerpo") == 0){
    fprintf(yyout, "</tbody>");
  }
  if(strcmp($1, "<tabla_fila") == 0){
    fprintf(yyout, "</tr>");
  }
  if(strcmp($1, "<tabla_celda") == 0){
    fprintf(yyout, "</td>");
  }
  if(strcmp($1, "<tabla_cabecera") == 0){
    fprintf(yyout, "</th>");
  }
  if(strcmp($1, "<formulario") == 0){
    fprintf(yyout, "</form>");
  }
  if(strcmp($1, "<boton") == 0){
    fprintf(yyout, "</button>");
  }
  if(strcmp($1, "<leyenda") == 0){
    fprintf(yyout, "</label>");
  }
  if(strcmp($1, "<parrafo") == 0){
    fprintf(yyout, "</p>");
  }
  if(strcmp($1, "<division") == 0){
    fprintf(yyout, "</div>");
  }

};

inicio: INICIO_ETIQUETA {

  if(strcmp($1, "<division") == 0){
    fprintf(yyout, "<div");
  }
  if(strcmp($1, "<parrafo") == 0){
    fprintf(yyout, "%s", "<p");
  }
  if(strcmp($1, "<titulo1") == 0){
    fprintf(yyout, "<h1");
  }
  if(strcmp($1, "<titulo2") == 0){
    fprintf(yyout, "<h2");
  }
  if(strcmp($1, "<titulo3") == 0){
    fprintf(yyout, "<h3");
  }
  if(strcmp($1, "<titulo4") == 0){
    fprintf(yyout, "<h4");
  }
  if(strcmp($1, "<titulo5") == 0){
    fprintf(yyout, "<h5");
  }
  if(strcmp($1, "<titulo6") == 0){
    fprintf(yyout, "<h6");
  }
  if(strcmp($1, "<negrita") == 0){
    fprintf(yyout, "<strong");
  }
  if(strcmp($1, "<italica") == 0){
    fprintf(yyout, "<i");
  }
  if(strcmp($1, "<resaltar") == 0){
    fprintf(yyout, "<mark");
  }
  if(strcmp($1, "<pequenio") == 0){
    fprintf(yyout, "<small");
  }
  if(strcmp($1, "<cursiva") == 0){
    fprintf(yyout, "<em");
  }
  if(strcmp($1, "<tachar") == 0){
    fprintf(yyout, "<s");
  }
  if(strcmp($1, "<lista_no_ordenada") == 0){
    fprintf(yyout, "<ul");
  }
  if(strcmp($1, "<lista_ordenada") == 0){
    fprintf(yyout, "<ol");
  }
  if(strcmp($1, "<lista_elemento") == 0){
    fprintf(yyout, "<li");
  }
  if(strcmp($1, "<seccion") == 0){
    fprintf(yyout, "<section");
  }
  if(strcmp($1, "<pie") == 0){
    fprintf(yyout, "<footer");
  }
  if(strcmp($1, "<cabecera") == 0){
    fprintf(yyout, "<header");
  }
  if(strcmp($1, "<navegacion") == 0){
    fprintf(yyout, "<nav");
  }
  if(strcmp($1, "<aparte") == 0){
    fprintf(yyout, "<aside");
  }
  if(strcmp($1, "<seleccion") == 0){
    fprintf(yyout, "<span");
  }
  if(strcmp($1, "<linea_horizontal") == 0){
    fprintf(yyout, "<hr");
  }
  if(strcmp($1, "<tabla") == 0){
    fprintf(yyout, "<table");
  }
  if(strcmp($1, "<tabla_cabeza") == 0){
    fprintf(yyout, "<thead");
  }
  if(strcmp($1, "<tabla_cuerpo") == 0){
    fprintf(yyout, "<tbody");
  }
  if(strcmp($1, "<tabla_fila") == 0){
    fprintf(yyout, "<tr");
  }
  if(strcmp($1, "<tabla_celda") == 0){
    fprintf(yyout, "<td");
  }
  if(strcmp($1, "<tabla_cabecera") == 0){
    fprintf(yyout, "<th");
  }
  if(strcmp($1, "<formulario") == 0){
    fprintf(yyout, "<form");
  }
  if(strcmp($1, "<boton") == 0){
    fprintf(yyout, "<button");
  }
  if(strcmp($1, "<leyenda") == 0){
    fprintf(yyout, "<label");
  }
  if(strcmp($1, "<campo") == 0){
    fprintf(yyout, "<input");
  }
  if(strcmp($1, "<imagen") == 0){
    fprintf(yyout, "<img");
  }
  
};

atributo: atributo ATRIBUTO_VALOR  { 
          $$ = $2;

          char *simbolo_igual = strchr($2, '=');
          char atributo[100];
          strncpy(atributo, $2, simbolo_igual - $2);
          atributo[simbolo_igual - $2] = '\0'; 
          char *valor = simbolo_igual + 1;

          if(strcmp(atributo, ":enlace_imagen") == 0){
            fprintf(yyout, " src=\"%s\"", valor);
          }
          if(strcmp(atributo, ":id") == 0){
            fprintf(yyout, " id=\"%s\"", valor);
          };
          if(strcmp(atributo, ":clase") == 0){
            fprintf(yyout, " class=\"%s\"", valor);
          };
          if(strcmp(atributo, ":nombre") == 0){
            fprintf(yyout, " name=\"%s\"", valor);
          };

          if(strcmp(atributo, ":tipo") == 0){
            char *type_prefix = "type=";
            if(strcmp(valor, "\"texto\"") == 0){
              fprintf(yyout, "%s\"text\"", type_prefix);
            };
            if(strcmp(valor, "\"numero\"") == 0){
              fprintf(yyout, "%s\"number\"", type_prefix);
            };
            if(strcmp(valor, "\"radio\"") == 0){
              fprintf(yyout, "%s\"radio\"", type_prefix);
            };
            if(strcmp(valor, "\"caja_check\"") == 0){
              fprintf(yyout, "%s\"checkbox\"", type_prefix);
            };
            if(strcmp(valor, "\"enviar\"") == 0){
              fprintf(yyout, "%s\"submit\"", type_prefix);
            };
            if(strcmp(valor, "\"correo\"") == 0){
              fprintf(yyout, "%s\"email\"", type_prefix);
            };
            if(strcmp(valor, "\"telefono\"") == 0){
              fprintf(yyout, "%s\"tel\"", type_prefix);
            };
            if(strcmp(valor, "\"contrasenia\"") == 0){
              fprintf(yyout, "%s\"password\"", type_prefix);
            };
          };

        };
        | ATRIBUTO { 
          $$ = $1;
          if(strcmp($1, ":reverso") == 0){
            fprintf(yyout, "reversed");
          }
          if(strcmp($1, ":requerido") == 0){
            fprintf(yyout, "required");
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
            fprintf(yyout, "%s", $2);
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
  printf("Error sintactico %s\n",s);
}