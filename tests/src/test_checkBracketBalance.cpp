


# include "../includes/test.hpp"


void test_checkBracketBalance(void) {
    std::string filename = "file/checkBracketBalance.txt";
    std::string    text = readFileContents(filename);
    std::cout << text;
    if (checkBraces(text)) {
        std::cout << "As chaves estão balanceadas corretamente." << std::endl;
    } else {
        std::cout << "Esta Errado." << std::endl;
    }
}