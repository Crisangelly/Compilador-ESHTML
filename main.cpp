#include <iostream>
#include <string>

int main() {

    int contador = 0;

    std:: string palabra;

    std:: cout << "Ingresa una palabra: ";
    //std:: cin >> palabra;
    std:: getline(std::cin, palabra);  //usando método del curso para contar los espacios
    
    for (int i = 0; i < palabra.length(); i++) {
        //std::cout << palabra[i] << "\n";
        contador++;
    }

    std::cout << contador << "";
     
    //std:: cout << palabra << " tiene " << palabra.length() << " letras";

    return 0;
}