#include <iostream>
#include <string>
#include <fstream>

//Funciones del compilador
#include "tokens.hpp"
#include "analisis_lexico.cpp"
token automata(std:: string palabra_entrante); 

#include "analisis_sintactico.cpp"
void parser();

using namespace std;

int main() {

    std:: string linea;
    std:: string palabra;

    ifstream archivo("eshtml.txt");

    while(getline(archivo, linea)){
        palabra=palabra+" "+linea;
    }

    archivo.close();

    //std:: cout << "texto: " << palabra << "\n"; 

    int contador = 0;

    std:: string palabras[200]; // almacenar máximo 30 palabras 

    int num_palabras = 0;

    std:: string palabra_nueva; // para ingresar las palabras

    bool detectar_comillas = false; // detectar inicio y fin de comillas

        
    for (int i = 0; i < palabra.length(); i++) {
        //std::cout << palabra[i] << "\n";
        contador++;

        if(palabra[i] == '\"'){

            palabra_nueva += palabra[i];

            detectar_comillas = !detectar_comillas; //cambiar bandera para detectar apertura o cierre de comillas

        } else if  (palabra[i] != ' '){ // sí dentro de la palabra alguno de sus caracteres no es un espacio, se agrega a palabra_nueva
 
            palabra_nueva += palabra[i];

        } else if (detectar_comillas && palabra[i] == ' '){ //detectar espacios entre comillas

            palabra_nueva += palabra[i];

        } else if (!detectar_comillas){

            if (!palabra_nueva.empty() && num_palabras < 200){   // si palabra_nueva no está vacia, se guarda en el array
                //std::cout << "espacio \n";
                palabras[num_palabras] = palabra_nueva;
                num_palabras++;                 
                palabra_nueva = ""; // reinicia la variable
            }

        }
    }

    if (!palabra_nueva.empty() && num_palabras < 200) { // almacena la última palabra que no termina en espacio
        palabras[num_palabras] = palabra_nueva;
        num_palabras++;
    }


    std::cout << contador << "\n";

/*     for (int i = 0; i < num_palabras; i++ ){ //recorre el array
        std:: cout << "palabra: " << palabras[i] << "\n"; // muestra las palabras que contiene el array
        std::cout << "-------------------------------------------------------------------\n"; 
    } */
 

    token tokens_lexicos[200];
    int num_tokens = 0;

    for (int i = 0; i < num_palabras; i++ ){ //recorre el array
        //std:: cout << "palabra: " << palabras[i] << "\n"; // muestra las palabras que contiene el array

        tokens_lexicos[i] = automata(palabras[i]);
        num_tokens++;
    }

    std:: cout << "cantidad de tokens: " << num_tokens << "\n"; 


    bool bandera_sintactica= true; 

    for (int i = 0; i < num_tokens; i++) { //Imprimir Tokens léxicos de momento

        if (tokens_lexicos[i].tipo == error) { // Si el token es de tipo 'error', mostramos el mensaje de error
            std::cout << " token mensaje_lexema: " << tokens_lexicos[i].mensaje_lexema << "\n";
            std::cout << " token tipo: " << tokens_lexicos[i].tipo << "\n";
            std::cout << " token lexema: " << tokens_lexicos[i].lexema << "\n";
            std::cout << "-------------------------------------------------------------------\n"; 
        } 
        else {  
            std::cout << "token lexema: " << tokens_lexicos[i].lexema << "\n";
            std::cout << "token longitud_lexema: " << tokens_lexicos[i].longitud_lexema << "\n";
            std::cout << "token mensaje_lexema: " << tokens_lexicos[i].mensaje_lexema << "\n";
            std::cout << "token tipo: " << tokens_lexicos[i].tipo << "\n";
            std::cout << "-------------------------------------------------------------------\n"; 
        } 
        if (tokens_lexicos[i].tipo == 5) {
            bandera_sintactica = false;
        }

    }

    if (!bandera_sintactica) {
        std::cout << "Se encontraron errores de sintaxis en el codigo.\n";
    } else {
        std::cout << "No se encontraron errores de sintaxis en el codigo.\n";
        parser();
    }  

    return 0;
}