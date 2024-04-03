

# include "library.hpp"


bool isFirstWordInSet(const std::string& text, const std::set<std::string>& wordSet) {
    std::istringstream iss(text); // Cria um stream de string a partir do texto
    std::string line;

    // Itera sobre cada linha do texto
    while (std::getline(iss, line)) {
        std::istringstream lineStream(line); // Cria um stream de string a partir da linha
        std::string firstWord;

        // Lê a primeira palavra da linha
        if (lineStream >> firstWord) {
            // Verifica se a primeira palavra está no conjunto de palavras
            bool found = false;
            for (std::set<std::string>::const_iterator it = wordSet.begin(); it != wordSet.end(); ++it) {
                if (*it == firstWord) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false; // Se não estiver, retorna false imediatamente
            }
        }
    }

    return true; // Se todas as primeiras palavras estiverem no conjunto, retorna true
}
