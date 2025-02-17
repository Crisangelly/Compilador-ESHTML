#include <iostream>
#include <string>

int main() {

    int contador = 0;

    std:: string palabra;

    std:: string palabras[15]; // almacenar máximo 15 palabras 

    int num_palabras = 0;

    std:: cout << "Ingresa una palabra: ";
    //std:: cin >> palabra;
    std:: getline(std::cin, palabra); 

    std:: string palabra_nueva; // para ingresar las palabras
    
    for (int i = 0; i < palabra.length(); i++) {
        //std::cout << palabra[i] << "\n";
        contador++;

        if  (palabra[i] != ' '){        // sí dentro de la palabra alguno de sus caracteres no es un espacio, se agrega a palabra_nueva
            palabra_nueva += palabra[i];

        }else{
            if (!palabra_nueva.empty() && num_palabras < 15){   // si palabra_nueva no está vacia, se guarda en el array
                palabras[num_palabras] = palabra_nueva;
                num_palabras++;                 
                palabra_nueva = ""; // reinicia la variable

            }
        }
    }

    if (!palabra_nueva.empty() && num_palabras < 15) { // almacena la última palabra que no termina en espacio
        palabras[num_palabras] = palabra_nueva;
        num_palabras++;
    }


    std::cout << contador << "\n";;

    for (int i = 0; i < num_palabras; i++ ){ //recorre el array
        std:: cout << "palabra: " << palabras[i] << "\n"; // muestra las palabras que contiene el array
    }
    
    //std:: cout << palabra << " tiene " << palabra.length() << " letras";

    return 0;
}