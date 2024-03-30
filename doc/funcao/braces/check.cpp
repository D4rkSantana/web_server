#include <iostream>
#include <fstream>
#include <stack>
#include <string>

bool checkBracesBalance(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return false;
    }

    std::stack<char> braces;
    char ch;
    int lineNum = 1;

    while (file.get(ch)) {
        if (ch == '{') {
            braces.push(ch);
        } else if (ch == '}') {
            if (braces.empty() || braces.top() != '{') {
                std::cerr << "Erro de fechamento de chave na linha " << lineNum << std::endl;
                return false;
            }
            braces.pop();
        } else if (ch == '\n') {
            lineNum++;
        }
    }

    if (!braces.empty()) {
        std::cerr << "Erro: chaves mal balanceadas" << std::endl;
        return false;
    }

    return true;
}

int main() {
    std::string filename = "arquivo.txt";
    if (checkBracesBalance(filename)) {
        std::cout << "As chaves estão balanceadas corretamente." << std::endl;
    } else {
        std::cout << "As chaves estão mal balanceadas." << std::endl;
    }

    return 0;
}
