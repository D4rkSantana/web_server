#include <iostream>
#include <sstream>
#include <vector>
#include <map>

// Definição da estrutura
typedef std::map<std::string, std::vector<std::string>> params;

typedef struct {
    params *server;
    params **locations;
} conf_servers;

// Função para fazer o parsing do bloco de configuração e preencher a estrutura conf_servers
void parseConfigBlock(const std::string& configBlock, conf_servers& config) {
    std::istringstream iss(configBlock);
    std::string line;
    std::vector<std::string> serverLines;
    std::vector<std::vector<std::string>> locationLines;

    // Dividir o bloco de configuração em linhas
    while (std::getline(iss, line)) {
        if (line.find("server") != std::string::npos) {
            continue;
        } else if (line.find("location") != std::string::npos) {
            locationLines.push_back({line});
        } else if (!line.empty()) {
            if (locationLines.empty()) {
                serverLines.push_back(line);
            } else {
                locationLines.back().push_back(line);
            }
        }
    }

    // Preencher a estrutura conf_servers
    config.server = new params();
    config.locations = new params*[locationLines.size()];

    for (size_t i = 0; i < serverLines.size(); ++i) {
        std::istringstream lineStream(serverLines[i]);
        std::string key, value;
        lineStream >> key >> value;
        (*config.server)[key].push_back(value);
    }

    for (size_t i = 0; i < locationLines.size(); ++i) {
        config.locations[i] = new params();
        for (size_t j = 0; j < locationLines[i].size(); ++j) {
            std::istringstream lineStream(locationLines[i][j]);
            std::string key, value;
            lineStream >> key >> value;
            (*config.locations[i])[key].push_back(value);
        }
    }
}

int main() {
    // Bloco de configuração de exemplo
    std::string configBlock = R"(
        server {
            listen 3007;
            server_name lucas.42.fr dddd.42.fr localhost;
            index hello.html;
            root examples;
            client_max_body_size 1024;
            autoindex on;
            error_page 404 notfound.html;
        }

        location /images {
            limit_except GET POST;
            autoindex off;
            error_page 404 nocake.html;
        }

        location /pdfs {
            limit_except GET;
            index webserv.pdf;
            autoindex off;
        }

        location /session {
            index testcookie.html;
            autoindex off;
        }
    )";

    // Estrutura para armazenar os dados do parsing
    conf_servers config;

    // Chamar a função de parsing
    parseConfigBlock(configBlock, config);

    // Exibir os dados do servidor
    std::cout << "Server:" << std::endl;
    for (const auto& kv : *config.server) {
        std::cout << kv.first << ": ";
        for (const auto& val : kv.second) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // Exibir os dados das localizações
    for (size_t i = 0; i < 3; ++i) {
        std::cout << "Location " << i+1 << ":" << std::endl;
        for (const auto& kv : *config.locations[i]) {
            std::cout << kv.first << ": ";
            for (const auto& val : kv.second) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

    // Liberar a memória alocada
    delete config.server;
    for (size_t i = 0; i < 3; ++i) {
        delete config.locations[i];
    }
    delete[] config.locations;

    return 0;
}
