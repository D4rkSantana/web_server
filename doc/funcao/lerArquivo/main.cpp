#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string readWholeFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    std::ostringstream buffer;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            buffer << line << '\n'; // Adiciona cada linha ao stringstream
        }
        file.close();
        return buffer.str(); // Retorna o conteúdo do stringstream como uma string
    } else {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return ""; // Retorna uma string vazia se o arquivo não puder ser aberto
    }
}

int main() {
    std::string content = readWholeFile("server_config.txt");
    std::cout << "Conteúdo do arquivo:" << std::endl;
    std::cout << content << std::endl;
    return 0;
}
