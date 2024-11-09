#include <iostream>
#include <string>

std::string extractQuotedString(const std::string& input) 
{
    std::size_t start = input.find('"');
    
    if (start != std::string::npos) 
    {
        std::size_t end = input.find('"', start + 1);
        if (end != std::string::npos) 
        {
            return input.substr(start + 1, end - start - 1);
        }
    }
    return "";
}

int main() {
    std::string text = "(This is a \"quoted string\" example)";
    text = extractQuotedString(text); // Orijinal stringi tırnak içindeki ifade ile değiştiriyoruz
    if (!text.empty()) {
        std::cout << "Quoted string: " << text << std::endl;
    } else {
        std::cout << "No quoted string found." << std::endl;
    }
    return 0;
}
