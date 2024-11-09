#include <iostream>
#include <string>

int main() {
    std::string str = "12345";
    int num = std::stoi(str);

    std::cout << "String: " << str << std::endl;
    std::cout << "Integer: " << num << std::endl;

    return 0;
}
