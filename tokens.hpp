#include <iostream>
#include <string>

//Tokens

enum token_opciones {
  inicio_etiqueta, //0
  cierre_etiqueta, //1
  cadena_de_texto, //2
  atributo, //3
  atributo_valor, //4
  error //5
};

struct token_tipo {
  std::string lexema;
  int longitud_lexema;
  enum token_opciones tipo;
  std::string mensaje_lexema;
};

typedef struct token_tipo token; 