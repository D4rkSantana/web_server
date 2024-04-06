#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


int main(void){
    std::ifstream file("config.txt");
    std::string line;
    while (std::getline(file, line)) {
        // Verifica se a linha começa com "server {"
        if (line.find("server {") != std::string::npos) {
                std::cout << "Espaço faz direreça";
        }
    }
     return (1);
}
