/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckFile.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:04:53 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/03 17:53:54 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CheckFile.hpp"


CheckFile::CheckFile(std::string path):_status(true){
    std::string  text;
    std::set<std::string> validWords;
    
    text = readFileContents(path);
    validWords = this->_getValidFirstWords( );

    if(!_isFirstWordInSet(text, validWords))
        this->_status= false;
    

}


CheckFile::~CheckFile(void){
   return;
    
}




std::set<std::string> CheckFile::_getValidFirstWords(void) {
    std::set<std::string> validWords;
    
    validWords.insert("server");
    
    validWords.insert("listen");
    validWords.insert("host");
    validWords.insert("error_page");
    validWords.insert("index");
    validWords.insert("client_max_body_siz");
    validWords.insert("root");
    validWords.insert("word");

    
    validWords.insert("location");

    validWords.insert("autoindex");
    validWords.insert("allow_method");
    validWords.insert("return");
    validWords.insert("alias");
    validWords.insert("cgi_path");
    validWords.insert("cgi_ext");

    validWords.insert("}");
    return validWords;
}


bool CheckFile::_isFirstWordInSet(const std::string& text, const std::set<std::string>& wordSet) {
    std::istringstream iss(text); // Cria um stream de string a partir do texto
    std::string line;
    int nbrLine;
    
    
    // Itera sobre cada linha do texto
    nbrLine = 1;
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
                std::string str = to_string(nbrLine);
                
                Logs::printLog(Logs::ERROR, 10, "Line");
                return false; // Se não estiver, retorna false imediatamente
            }
        }
        nbrLine ++;
    }
    return true; // Se todas as primeiras palavras estiverem no conjunto, retorna true
}