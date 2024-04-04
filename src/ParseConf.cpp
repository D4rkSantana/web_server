

#include "ParseConf.hpp"




std::vector<std::string> separateServerBlocks(const std::string& config) {
    std::vector<std::string> blocks;
    std::string::size_type pos = 0;
    
    while ((pos = config.find("server {", pos)) != std::string::npos) {
        // Encontra o início do bloco
        std::string::size_type blockStart = pos;
        
        // Encontra o fim do bloco
        std::string::size_type blockEnd = config.find("}", blockStart);
        if (blockEnd == std::string::npos) {
            break; // Se não houver fechamento de bloco, termina
        }
        blockEnd = config.find("\n}", blockEnd); // Avança até a próxima linha após }
        if (blockEnd == std::string::npos) {
            break; // Se não houver fechamento de bloco, termina
        }
        blockEnd += 2; // Avança até o final do bloco

        // Adiciona o bloco encontrado ao vetor
        blocks.push_back(config.substr(blockStart, blockEnd - blockStart));

        // Move a posição de busca para após o bloco encontrado
        pos = blockEnd;
    }

    return blocks;
}


std::string extractServerParams(const std::string& serverBlock) {
    std::istringstream iss(serverBlock);
    std::string line;
    std::string serverParams;
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
        serverParams += line + "\n";
    }
    return serverParams;
}


std::vector<std::string> extractLocations(const std::string& serverBlock) {
    std::istringstream iss(serverBlock);
    std::string line;
    std::vector<std::string> locations;
    bool insideLocation = false;
    std::string currentLocation;

    while (std::getline(iss, line)) {
        if (line.find("location") != std::string::npos) {
            insideLocation = true;
            currentLocation = line + "\n";
            continue; // Ignoramos a linha que contém "location"
        }
        if (line.find("}") != std::string::npos && insideLocation) {
            insideLocation = false;
            locations.push_back(currentLocation + line); // Adicionamos a localização ao vetor
            continue; // Ignoramos a linha que contém "}"
        }
        if (insideLocation) {
            currentLocation += line + "\n"; // Adicionamos a linha à localização atual
        }
    }

    return locations;
}

