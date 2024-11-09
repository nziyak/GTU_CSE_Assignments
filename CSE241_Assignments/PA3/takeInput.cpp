#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string line;
    std::cout << "Satiri girin: ";
    std::getline(std::cin, line); // Satırı kullanıcıdan al

    std::istringstream iss(line); // Satırı bir akışa dönüştür

    std::string kelime1, kelime2, kelime3;
    int sayi1;

    // İlk iki kelimeyi aldık
    iss >> kelime1 >> kelime2;

    // Satırdaki geri kalanı bir değişkene alalım
    std::string remaining;
    std::getline(iss, remaining);

    // Geri kalanı da bir akışa dönüştürelim
    std::istringstream iss_remaining(remaining);

    // Kelime sayısı 3 ise, üçüncü kelimeyi ve sayıyı alalım
    if (iss_remaining >> kelime3 >> sayi1) {
        std::cout << "Kelime 1: " << kelime1 << std::endl;
        std::cout << "Kelime 2: " << kelime2 << std::endl;
        std::cout << "Kelime 3: " << kelime3 << std::endl;
        std::cout << "Sayi 1: " << sayi1 << std::endl;
    } 
    
    else { // Kelime sayısı 2 ise, ikinci kelimeyi ve sayıyı alalım
        std::istringstream iss_remaining2(remaining);
        if (iss_remaining2 >> sayi1) {
            std::cout << "Kelime 1: " << kelime1 << std::endl;
            std::cout << "Kelime 2: " << kelime2 << std::endl;
            std::cout << "Sayi 1: " << sayi1 << std::endl;
        } else {
            std::cerr << "Geçersiz giriş!" << std::endl;
        }
    }

    return 0;
}
