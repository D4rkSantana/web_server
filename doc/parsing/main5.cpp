#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>



int countWordOccurrencesLine(const std::string& text, const std::string& word) {
    std::istringstream iss(text); // Cria um stream de string a partir do texto
    std::string line;
    int  count;
    
    // Itera sobre cada linha do texto
    count = 0;
    while (std::getline(iss, line)) {
        std::istringstream lineStream(line); // Cria um stream de string a partir da linha
        std::string firstWord;
       
        lineStream >> firstWord;
        if(firstWord == word){
            count ++;
        }
    }
    return count;
}

int main() {
    std::string text = "listen 307\nserver_name new.42.fr pss.fr localhost;\nindex hello.html;\nroot guide;\nautoindex on;\nerror_page 404 notfound.html;\nroot guide;\nclient_max_body_size 1024;";
    std::string word = "root";

    int occurrences = countWordOccurrencesLine(text, word);
    
    std::cout << "A palavra \"" << word << "\" ocorre " << occurrences << " vezes." << std::endl;

    return 0;
}
