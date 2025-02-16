#include <iostream>
#include <string>

int main() {

    std:: string palabra;

    std:: cout << "Ingresa una palabra: ";
    std:: cin >> palabra;
    //std:: getline(std::cin, palabra);  usando método del curso para contar los espacios

    std:: cout << palabra << " tiene " << palabra.length() << " letras";

    return 0;
}