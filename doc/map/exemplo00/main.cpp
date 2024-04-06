#include <iostream>
#include <map>
#include <string>

int main() {
    // Declaração e inicialização de um mapa
    std::map<std::string, std::string> mapa;

    // Inserindo elementos no mapa
    mapa["casa"] = "Um";
    mapa["2"] = "Dois";
    mapa["3"] = "Três";

    // Acessando elementos do mapa
    std::cout << "mapa[1] = " << mapa["casa"] << std::endl;
    std::cout << "mapa[2] = " << mapa["2"] << std::endl;
    std::cout << "mapa[3] = " << mapa["3"] << std::endl;

    // Iterando sobre os elementos do mapa
    std::cout << "Elementos do mapa:" << std::endl;
    for (auto it = mapa.begin(); it != mapa.end(); ++it) {
        std::cout << "Chave: " << it->first << ", Valor: " << it->second << std::endl;
    }

    // Verificando se uma chave está presente no mapa
    std::string chave = "2";
    if (mapa.find(chave) != mapa.end()) {
        std::cout << "A chave " << chave << " está presente no mapa." << std::endl;
    } else {
        std::cout << "A chave " << chave << " não está presente no mapa." << std::endl;
    }

    return 0;
}
