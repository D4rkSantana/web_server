

# include "../includes/test.hpp"

void test_isFirstWordinSet() {
    std::string texto = "Esta é uma linha válida\nEsta é outra linha válida\n\nsta é uma linha inválida";

    // Inicializando o conjunto de palavras válidas em etapas separadas
    std::set<std::string> palavrasValidas;
    palavrasValidas.insert("Esta");
    palavrasValidas.insert("outra");
    palavrasValidas.insert("linha");
    palavrasValidas.insert("válida");

    if (isFirstWordInSet(texto, palavrasValidas)) {
        std::cout << "Todas as primeiras palavras são válidas." << std::endl;
    } else {
        std::cout << "Algumas das primeiras palavras não são válidas." << std::endl;
    }
}