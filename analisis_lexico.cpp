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
  /*char lexema[100];*/
  int longitud_lexema;
  enum token_opciones tipo;
  std::string mensaje_lexema;
};

typedef struct token_tipo token;


int buscar_en_el_alfabeto(int alfabeto[], int longitud, int caracter){
  int i = 0;
  for (i ; i < longitud; i++){
    if(alfabeto[i] == caracter){
      return i;
    }
  }
  return i;
}


int buscar_etiqueta(std::string posible_etiqueta){
  std::string etiquetas[] = {"<titulo1>", "<titulo2>", "<titulo3>", "<titulo4>", "<titulo5>", "<titulo6>", 
    "<parrafo>", "<negrita>", "<italica>", "<resaltar>", "<pequenio>", "<lista_no_ordenada>", "<lista_ordenada>", "<lista_elemento>",
    "<cursiva>", "<tachar>", "<vinculo>", "<dividir>", "<seccion>", "<pie>", "<cabecera>", "<navegacion>", "<aparte>",
    "<seleccion>", "<linea_horizontal>", "<tabla>", "<tabla_fila>", "<tabla_celda>", "<tabla_cabecera>", "<formulario>",
    "<boton>", "<leyenda>", "<campo>", "<imagen>"
  };
  int canditad_etiquetas = sizeof(etiquetas) / sizeof(std::string);
  int i = 0;
  for (i; i < canditad_etiquetas; i++){
    if(etiquetas[i] == posible_etiqueta){
      return i;
    }
  }
  return -1;
}

int buscar_atributo(std::string posible_atributo){
  //std:: cout << "llega: " << posible_atributo << "\n"; 
  std::string atributos[] = {":enlace", ":tipo", ":texto_alternativo"};
  int canditad_atributos = sizeof(atributos) / sizeof(std::string);

  int i = 0;
  for (i; i < canditad_atributos; i++){
    if(atributos[i] == posible_atributo){
      return i;
    }
  }
  return -1;

}


void automata(std:: string palabra_entrante){
   // std:: cout << "aca va el automata \n";

   // std:: cout << "palabra: " << palabra_entrante << "\n";

    int automata[][40] = {
      {	1,	12,	12,	4,	6,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	0, 12},
      {	3,	2,	1,	3,	3,	3,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0, 3},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
      {	4,	4,	4,	5,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
      {	11,	11,	6,	11,	11,	7,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	11,	11,	11,	11,	11,	11,	0, 11},
      {	10,	10,	10,	8,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	0, 10},
      {	8,	8,	8,	9,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	0, 8},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
      {	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}
    };

    int alfabeto[] = {'<', '>', '_', '\"', ':', '=', 'a',	'b', 'c',	'd', 'e',	'f', 'g', 'h', 'i',	'j', 'k', 'l', 'm', 'n', 'o',	'p', 'q',	'r', 's', 't', 'u', 'v', 'w', 'x', 'y',	'z', '1',	'2', '3', '4', '5', '6', ' '};

    const int longitud_alfabeto = 39;
    const int cantidad_estados = 13;
    int estado = 0;

    int contador_caracter = 0;

    int indice;

    token token_momento;

    while ((contador_caracter < palabra_entrante.length()) && (estado != 2 && estado != 3 && estado != 5 && estado != 9 && estado != 10 && estado != 11 && estado != 12)){ 
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
          token_momento.mensaje_lexema = "la etiqueta no a sido cerrada";
          token_momento.tipo = error;
        break;
        case 2:
          token_momento.mensaje_lexema = "etiqueta";
          token_momento.tipo = etiqueta;
          break;
        case 3:
          token_momento.mensaje_lexema = "error, etiqueta incorrecta";
          token_momento.tipo = error;
          break;
        case 4: 
          token_momento.mensaje_lexema = "las comillas de la cadena no han sido cerradas";
          token_momento.tipo = error; 
          break;
        case 5:
          token_momento.mensaje_lexema = "cadena de texto";
          token_momento.tipo = cadena_de_texto;
          break;
        case 6:
          token_momento.mensaje_lexema = "el atributo esta incompleto";
          token_momento.tipo = error; 
          break;
        case 7:  
          token_momento.mensaje_lexema = "el atributo esta incompleto";
          token_momento.tipo = error; 
          break;
        case 8: 
          token_momento.mensaje_lexema = "las comillas del valor del atributo no han sido cerradas"; 
          token_momento.tipo = error; 
          break;
        case 9: 
          token_momento.mensaje_lexema = "atributo";
          token_momento.tipo = atributo; 
          break;
        case 10:
          token_momento.mensaje_lexema = "error, faltan comillas";
          token_momento.tipo = error; 
          break;
        case 11:
          token_momento.mensaje_lexema = "error, atributo invalido";
          token_momento.tipo = error; 
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
    case etiqueta:
      if(buscar_etiqueta(token_momento.lexema) == -1){
        token_momento.mensaje_lexema = "error, etiqueta incorrecta";
        token_momento.tipo = error;
      } 
      break;
    case atributo:
      std::string atributo;
      std::string valor;
      int posicion_igual = token_momento.lexema.find('=');
    
      atributo = token_momento.lexema.substr(0, posicion_igual);
      valor = token_momento.lexema.substr(posicion_igual + 2, token_momento.lexema.length() - posicion_igual - 3);

      if(buscar_atributo(atributo) == -1){
        token_momento.mensaje_lexema = "error, atributo incorrecto";
        token_momento.tipo = error;
      }
    
      //std:: cout << "atributo: " << atributo << "\n"; 
      //std:: cout << "valor: " << valor << "\n"; 

      break; 
    }

    //std:: cout << "identificado: " << token_momento.mensaje_lexema << "\n"; // muestra las palabras que contiene el array

    //std:: cout << "token lexema: " << token_momento.lexema << "\n"; 
   // std:: cout << "token longitud: " << token_momento.longitud_lexema << "\n";
    std:: cout << "token tipo: " << token_momento.tipo << "\n"; 

}