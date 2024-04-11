#include <iostream>
#include <string>

std::string getParameterValue(const std::string& text, const std::string& parameter) {
    // Encontra a posição do parâmetro no texto
    size_t pos = text.find(parameter);
    if (pos == std::string::npos) {
        // Se o parâmetro não for encontrado, retorna uma string vazia
        return "";
    }

    // Avança para o valor do parâmetro
    pos += parameter.length();

    // Ignora os espaços em branco
    while (pos < text.length() && text[pos] == ' ') {
        pos++;
    }

    // Encontra o fim do valor do parâmetro
    size_t end_pos = text.find("\n", pos);
    if (end_pos == std::string::npos) {
        // Se o fim do texto for alcançado, retorna o restante da string
        return text.substr(pos);
    }

    // Retorna a parte do texto contendo o valor do parâmetro
    return text.substr(pos, end_pos - pos);
}

int main() {
    std::string text = "listen 3007\n"
                       "server_name lucas.42.fr dddd.42.fr localhost\n"
                       "index hello.html\n"
                       "root examples\n"
                       "client_max_body_size 1024\n"
                       "autoindex on\n"
                       "error_page 404 notfound.htm\n";

    std::string parameter = "server_name";
    std::string value = getParameterValue(text, parameter);
    std::cout << value << std::endl; // Saída esperada: "lucas.42.fr dddd.42.fr localhost"

    return 0;
}
