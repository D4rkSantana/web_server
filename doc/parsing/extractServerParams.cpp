#include <iostream>
#include <string>
#include <sstream>
#include <set>

std::string extractServerParams(const std::string& serverBlock) {
    std::istringstream iss(serverBlock);
    std::string line;
    std::string serverParams;
    std::set<std::string> uniqueParams; // Usaremos um conjunto para armazenar apenas os parâmetros únicos

    bool insideLocation = false;

    while (std::getline(iss, line)) {
        if (line.find("location") != std::string::npos) {
            insideLocation = true;
            continue; // Ignoramos a linha que contém "location"
        }
        if (line.find("}") != std::string::npos) {
            insideLocation = false;
            continue; // Ignoramos a linha que contém "}"
        }
        if (insideLocation) {
            continue; // Ignoramos as linhas dentro de uma localização
        }
        if (line.find("server {") != std::string::npos) {
            continue; // Ignoramos a linha "server {"
        }
/* 
        // Verificamos se o parâmetro já foi adicionado
        if (uniqueParams.find(line) == uniqueParams.end()) {
            uniqueParams.insert(line);
            
        }
*/
        serverParams += line + "\n";
    }

    return serverParams;
}

int main() {
    std::string serverBlock = R"(
        server {
            listen 3007;
            server_name new.42.fr pss.fr localhost;
            index hello.html;
            root guide;
            autoindex on;
            error_page 404 notfound.html;
            root guide;

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

    std::string serverParams = extractServerParams(serverBlock);
    std::cout << serverParams << std::endl;

    return 0;
}
