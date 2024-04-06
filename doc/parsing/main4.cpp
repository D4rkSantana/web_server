#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

void parseConfigFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return;
    }

    std::string line;
    std::map<std::string, std::map<std::string, std::string> > serverConfigs;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        iss >> key >> value;

        if (key == "server") {
            std::string serverName;
            iss >> serverName;
            serverConfigs[serverName];
        }
        else if (key == "listen" || key == "root" || key == "body_size_limit" || key == "redirect") {
            std::string serverName;
            iss >> serverName;
            serverConfigs[serverName][key] = value;
        }
        else if (key == "location") {
            std::string serverName, location;
            iss >> serverName >> location;
            serverConfigs[serverName][location] = value;
        }
        else if (key == "index" || key == "cgi_pass" || key == "directory_listing" || key == "http_methods" || key == "404") {
            std::string serverName, location;
            iss >> serverName >> location;
            serverConfigs[serverName][location] = value;
            iss >> serverConfigs[serverName][key];
        }
    }

    for (std::map<std::string, std::map<std::string, std::string> >::iterator it = serverConfigs.begin(); it != serverConfigs.end(); ++it) {
        std::cout << "Configurações para o servidor " << it->first << ":" << std::endl;
        for (std::map<std::string, std::string>::iterator inner_it = it->second.begin(); inner_it != it->second.end(); ++inner_it) {
            std::cout << inner_it->first << ": " << inner_it->second << std::endl;
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string filename = "server_config.txt";
    parseConfigFile(filename);
    return 0;
}
