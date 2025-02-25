#include <iostream>
#include <string>

int buscar_en_el_alfabeto(int alfabeto[], int longitud, int caracter){
  int i = 0;
  for (i ; i < longitud; i++){
    if(alfabeto[i] == caracter){
      return i;
    }
  }
  return i;
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
      {	11,	11,	11,	11,	11,	7,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	11,	11,	11,	11,	11,	11,	0, 11},
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

    std:: string identificado;

    /*

    (X) 1) Buscar el modo que acepte otros caracteres que no estén en el alfabeto cuando revise una cadena de texto !!!!!!!!!!!!!!!!
    (X) 2) Ver que pasa con los errores personalizados del automata
    (X +-) 3) Revisar que ocurre cuando no se cierra una etiqueta o una cadena
      4) Crear una función para ver si la etiqueta ingresada existe en el lenguaje
      5) Hacer otra función similar para los atributos
      6) hacer los tokens con la siquiente estructura: 
        token = {
          tipo: etiqueta/atributo/etc,
          contenido: <parrafo> lo qu haya escrito el usuario 
        }

    */


    while ((contador_caracter < palabra_entrante.length()) && (estado != 2 && estado != 3 && estado != 5 && estado != 9 && estado != 10 && estado != 11 && estado != 12)){ 
      //std:: cout << "caracter ahora: " << palabra_entrante[contador_caracter] << "\n";

      indice = buscar_en_el_alfabeto(alfabeto, longitud_alfabeto, palabra_entrante[contador_caracter]);

      //std:: cout << "estado inicial: " << estado << "\n"; 

      //std:: cout << "indice: " << indice << "\n";

      estado = automata[estado][indice];

      //std:: cout << "estado: " << estado << "\n"; 

      switch (estado){
        case 0: //Prueba
          //std:: cout << "la cadena no pudo ser identificada \n";
          identificado = "la cadena no pudo ser identificada \n";
        break;
        case 1: //Prueba
          //std:: cout << "la etiqueta no a sido cerrada \n";
          identificado = "la etiqueta no a sido cerrada \n";
        break;
        case 2:
          //std:: cout << "etiqueta \n"; 
          identificado = "etiqueta \n";
          break;
        case 3:
          //std:: cout << "error, etiqueta incorrecta \n";
          identificado = "error, etiqueta incorrecta \n";
          break;
        case 4: //Prueba
          //std:: cout << "las comillas de la cadena no han sido cerradas \n"; 
          identificado = "las comillas de la cadena no han sido cerradas \n"; 
          break;
        case 5:
          //std:: cout << "cadena de texto \n";
          identificado = "cadena de texto \n";
          break;
        case 6: //Prueba
          //std:: cout << "el atributo esta incompleto \n";
          identificado = "el atributo esta incompleto \n";
          break;
        case 7: //Prueba
          //std:: cout << "el atributo esta incompleto \n"; 
          identificado = "el atributo esta incompleto \n";
          break;
        case 8: //Prueba
          //std:: cout << "las comillas del valor del atributo no han sido cerradas \n"; 
          identificado = "las comillas del valor del atributo no han sido cerradas \n"; 
          break;
        case 9:
          //std:: cout << "atributo \n"; 
          identificado = "atributo \n";
          break;
        case 10:
          //std:: cout << "error, faltan comillas \n";
          identificado = "error, faltan comillas \n";
          break;
        case 11:
          //std:: cout << "error, atributo invalido \n";
          identificado = "error, atributo invalido \n";
          break;
        case 12:
          //std:: cout << "error, la cadena es incorrecta \n"; 
          identificado = "error, la cadena es incorrecta \n"; 
          break;
      } 

      contador_caracter++;

      //estado = 0;

    } 
    
    std:: cout << "identificado: " << identificado << "\n"; // muestra las palabras que contiene el array

}