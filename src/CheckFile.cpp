/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckFile.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:04:53 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/03 18:24:59 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CheckFile.hpp"


CheckFile::CheckFile(std::string path):_status(true){
    std::string  text;
    std::set<std::string> validWords;
    
    text = readFileContents(path);
    validWords = this->_getValidFirstWords( );

    if(_isFirstWordInSet(text, validWords) > -1){
        this->_status= false;
        Logs::printLog(Logs::ERROR, 11, "The" + path +"file contains an error on line"+ to_string(_isFirstWordInSet(text, validWords)) +".");
        return;
    }
        
    

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


int CheckFile::_isFirstWordInSet(const std::string& text, const std::set<std::string>& wordSet) {
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
                return nbrLine; // Se não estiver, retorna false imediatamente
            }
        }
        nbrLine ++;
    }
    return -1; // Se todas as primeiras palavras estiverem no conjunto, retorna true
}