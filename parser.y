%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  extern int yylex(void);
  extern char *yytext;
  extern FILE *yyin;
  extern FILE *yyout;
  void yyerror(char *s);
%}

%token INICIO_ETIQUETA CADENA_DE_TEXTO CIERRE_ETIQUETA ATRIBUTO ATRIBUTO_VALOR

%left INICIO_ETIQUETA
%left ATRIBUTO
%left ATRIBUTO_VALOR
%left CADENA_DE_TEXTO
%left CIERRE_ETIQUETA

%%

documento: elemento documento | elemento ; 

elemento: INICIO_ETIQUETA atributo contenido CIERRE_ETIQUETA ;

atributo: atributo ATRIBUTO_VALOR | ATRIBUTO | /* vacío */ ;

contenido: contenido elemento | contenido CADENA_DE_TEXTO | /* vacío */ ;


%%

int main(void) {
  yyin = fopen("eshtml.txt", "r");
  int s = yyparse();  
  if(s == 0){
    printf("Todo en orden");
  }
}

void yyerror(char *s){
  printf("Error sintactico %s\n",s);
}