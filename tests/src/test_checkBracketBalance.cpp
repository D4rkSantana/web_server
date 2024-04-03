


# include "../includes/test.hpp"


void test_checkBracketBalance(void) {
    std::string filename = "file/checkBracketBalance.txt";
    if (checkBraces(filename)) {
        std::cout << "As chaves estão balanceadas corretamente." << std::endl;
    } else {
        std::cout << "As chaves estão mal balanceadas." << std::endl;
    }
}