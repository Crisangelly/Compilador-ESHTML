#include <iostream>
#include <string>

/*#include "tokens.hpp"*/
#include "buscar_cadenas.cpp"

int buscar_en_el_alfabeto(int alfabeto[], int longitud, int caracter){
  int i = 0;
  for (i ; i < longitud; i++){
    if(alfabeto[i] == caracter){
      return i;
    }
  }
  return i;
}

int buscar_etiqueta(std::string posible_etiqueta);
int buscar_atributo_solo(std::string posible_atributo_solo);
int buscar_valor_atributo(std::string posible_atributo, std::string posible_valor, int indice);
int buscar_atributo(std::string posible_atributo, std::string posible_valor);


token automata(std:: string palabra_entrante){

    int automata[][40] = {
      {	1,	11,	12,	3,	5,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	0,	12	},
      {	2,	11,	1,	2,	2,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	2	},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
      {	3,	3,	3,	4,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3	},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
      {	10,	10,	5,	10,	10,	6,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	10,	10,	10,	10,	10,	10,	0,	10	},
      {	9,	9,	9,	7,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	0,	9	},
      {	7,	7,	7,	8,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7	},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
    };

    int alfabeto[] = {'<', '>', '_', '\"', ':', '=', 'a',	'b', 'c',	'd', 'e',	'f', 'g', 'h', 'i',	'j', 'k', 'l', 'm', 'n', 'o',	'p', 'q',	'r', 's', 't', 'u', 'v', 'w', 'x', 'y',	'z', '1',	'2', '3', '4', '5', '6', ' '};

    const int longitud_alfabeto = 39;
    const int cantidad_estados = 13;
    int estado = 0;

    int contador_caracter = 0;

    int indice;

    token token_momento;

    while (contador_caracter < palabra_entrante.length()){ 
      //std:: cout << "caracter ahora: " << palabra_entrante[contador_caracter] << "\n";

      indice = buscar_en_el_alfabeto(alfabeto, longitud_alfabeto, palabra_entrante[contador_caracter]);

      //std:: cout << "estado inicial: " << estado << "\n"; 

      //std:: cout << "indice: " << indice << "\n";

      estado = automata[estado][indice];

      //std:: cout << "estado: " << estado << "\n"; 

      switch (estado){
        case 0: 
          token_momento.mensaje_lexema = "la cadena no pudo ser identificada";
          token_momento.tipo = error;
        break;
        case 1:
          token_momento.mensaje_lexema = "inicio etiqueta";
          token_momento.tipo = inicio_etiqueta;
        break;
        case 2:
          token_momento.mensaje_lexema = "error etiqueta incorrecta";
          token_momento.tipo = error;
          break;
        case 3:
          token_momento.mensaje_lexema = "error, las comillas de la cadena no han sido cerradas";
          token_momento.tipo = error;
          break;
        case 4: 
          token_momento.mensaje_lexema = "cadena de texto";
          token_momento.tipo = cadena_de_texto;
          break;
        case 5:
          token_momento.mensaje_lexema = "atributo";
          token_momento.tipo = atributo;
          break;
        case 6:
          token_momento.mensaje_lexema = "error, el atributo esta incompleto";
          token_momento.tipo = error;
          break;
        case 7:  
          token_momento.mensaje_lexema = "error, el atributo esta incompleto";
          token_momento.tipo = error;
          break;
        case 8: 
          token_momento.mensaje_lexema = "atributo valor";
          token_momento.tipo = atributo_valor;
          break;
        case 9: 
          token_momento.mensaje_lexema = "error, faltan comillas";
          token_momento.tipo = error;
          break;
        case 10:
          token_momento.mensaje_lexema = "error, atributo invalido";
          token_momento.tipo = error;
          break;
        case 11:
          token_momento.mensaje_lexema = "cierre etiqueta";
          token_momento.tipo = cierre_etiqueta;
          break;
        case 12:
          token_momento.mensaje_lexema = "error, la cadena es incorrecta";
          token_momento.tipo = error;
          break;
      } 

      contador_caracter++;

    } 

    token_momento.lexema = palabra_entrante;
    token_momento.longitud_lexema = palabra_entrante.length();

    //aquí utiliza las funciones para buscar la etiqueta y el atributo

    switch (token_momento.tipo){
      case inicio_etiqueta:
        /*if (token_momento.lexema.find('>') == std::string::npos){// validación para el ">" cierre de etiqueta
          token_momento.mensaje_lexema = "error, falta '>' para cerrar la etiqueta";
          token_momento.tipo = error;
        }
        else if(buscar_etiqueta(token_momento.lexema) == -1){
          token_momento.mensaje_lexema = "error, etiqueta incorrecta";
          token_momento.tipo = error;
        }*/
        if(buscar_etiqueta(token_momento.lexema) == -1){
          token_momento.mensaje_lexema = "error, etiqueta incorrecta";
          token_momento.tipo = error;
        }
        break;
      case cierre_etiqueta:// para comprobar que la etiqueta existe
        if(buscar_etiqueta(token_momento.lexema) == -1){
          token_momento.mensaje_lexema = "error, etiqueta incorrecta";
          token_momento.tipo = error;
        }
        break;
      case atributo:
        if(buscar_atributo_solo(token_momento.lexema) == -1){
          token_momento.mensaje_lexema = "error, atributo incorrecto";
          token_momento.tipo = error;
        }
        break; 
      case atributo_valor:
        std::string atributo;
        std::string valor;
        int posicion_igual = token_momento.lexema.find('=');
      
        atributo = token_momento.lexema.substr(0, posicion_igual);
        valor = token_momento.lexema.substr(posicion_igual + 2, token_momento.lexema.length() - posicion_igual - 3);
  
        if(buscar_atributo(atributo, valor) == -1){
          token_momento.mensaje_lexema = "error, atributo incorrecto";
          token_momento.tipo = error;
        }
        break; 
    }

    
 /*    std:: cout << "token lexema: " << token_momento.lexema << "\n"; 
    std:: cout << "token longitud_lexema: " << token_momento.longitud_lexema << "\n"; 
    std:: cout << "token mensaje_lexema: " << token_momento.mensaje_lexema << "\n";  
    std:: cout << "token tipo: " << token_momento.tipo << "\n"; */

    return token_momento;

}