#include <iostream>
#include <string>
#include <sstream>
#include <vector>



std::string getFirstWord(const std::string& text, int position) {
    std::istringstream iss(text); // Cria um stream de string a partir do texto
    std::string line;
    int nbrLine;
    
    // Itera sobre cada linha do texto
    nbrLine = 0;
    while (std::getline(iss, line)) {
        std::istringstream lineStream(line); // Cria um stream de string a partir da linha
        std::string firstWord;
    
        if(nbrLine == position){
            lineStream >> firstWord;
            return firstWord;
        }
        nbrLine ++;
    }
    return "";
}

int main() {
    std::string str =  R"(
        server {
            listen 3007;
            server_name new.42.fr pss.fr localhost;
            index hello.html;
            root guide;
            autoindex on;
            error_page 404 notfound.html;

            location /images {
                limit_except GET POST;
                autoindex off;
                error_page 404 nocake.html;
            }

            location /method {
                limit_except GET POST;
                error_page 404 notfound.html;
            }
            client_max_body_size 1024;
            location /pdfs {
                limit_except GET;
                index webserv.pdf;
            }
        }
    )";
    
    // Chama a função para obter a primeira palavra na posição 3
    std::string primeiraPalavra = getFirstWord(str, 6);
    
    // Imprime o resultado
    std::cout << "A primeira palavra na posição 3 é: " << primeiraPalavra << std::endl;

    return 0;
}