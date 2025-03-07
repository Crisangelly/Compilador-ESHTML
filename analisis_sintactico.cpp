#include <iostream>
#include <string>

/*#include "tokens.hpp"*/

//Prueba de función para regresar token en parser

void regresar_token( token tokens[], int i, int num_tokens){
  if (i >= num_tokens){
    return;
  }

  //mensajes para los tokens
  std::cout << "token lexema: " << tokens[i].lexema << "\n";
  std::cout << "token longitud_lexema: " << tokens[i].longitud_lexema << "\n";
  std::cout << "token mensaje_lexema: " << tokens[i].mensaje_lexema << "\n";
  std::cout << "token tipo: " << tokens[i].tipo << "\n";
  std::cout << "-------------------------------------------------------------------\n"; 

  regresar_token(tokens, i + 1, num_tokens);
}


void parser(token tokens[], int num_tokens){
  std::cout << "Iniciando el parser ...\n \n \n \n";
  regresar_token(tokens, 0, num_tokens);
  /*std::cout << "por aqui deberia de ir el parser\n";*/
}