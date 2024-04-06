#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Estrutura para representar uma configuração de servidor
struct ServerConfig {
    std::string listen;
    std::string root;
    std::vector<std::string> locations;
};

// Função para fazer o parsing do arquivo de configuração
std::vector<ServerConfig> parseConfigFile(const std::string& filename) {
    std::vector<ServerConfig> configs;
    std::ifstream file(filename);
    std::string line;
    ServerConfig currentConfig;

    while (std::getline(file, line)) {
        // Verifica se a linha começa com "server {"
        if (line.find("server {") != std::string::npos) {
            currentConfig = ServerConfig();
        }
        // Verifica se a linha começa com "listen"
        else if (line.find("listen") != std::string::npos) {
            std::istringstream iss(line);
            std::string listen, port;
            iss >> listen >> port;
            currentConfig.listen = port;
        }
        // Verifica se a linha começa com "root"
        else if (line.find("root") != std::string::npos) {
            std::istringstream iss(line);
            std::string root, path;
            iss >> root >> path;
            currentConfig.root = path;
        }
        // Verifica se a linha começa com "location"
        else if (line.find("location") != std::string::npos) {
            std::istringstream iss(line);
            std::string location, path;
            iss >> location >> path;
            currentConfig.locations.push_back(path);
        }
        // Verifica se a linha termina com "}"
        else if (line.find("}") != std::string::npos) {
            configs.push_back(currentConfig);
        }
    }

    return configs;
}

int main() {
    std::vector<ServerConfig> configs = parseConfigFile("config.txt");

    // Exemplo de como usar as informações obtidas
    for (const auto& config : configs) {
        std::cout << "Listen: " << config.listen << std::endl;
        std::cout << "Root: " << config.root << std::endl;
        std::cout << "Locations:" << std::endl;
        for (const auto& location : config.locations) {
            std::cout << " - " << location << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
