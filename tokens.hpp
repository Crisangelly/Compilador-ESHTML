#include <iostream>
#include <string>

//Tokens

enum token_opciones {
  etiqueta, //0
  cadena_de_texto, //1
  atributo, //2
  error //3
};

struct token_tipo {
  std::string lexema;
  int longitud_lexema;
  enum token_opciones tipo;
  std::string mensaje_lexema;
};

typedef struct token_tipo token; 