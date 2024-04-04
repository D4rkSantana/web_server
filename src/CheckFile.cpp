/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckFile.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:04:53 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/04 00:39:03 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CheckFile.hpp"


CheckFile::CheckFile(std::string path):_status(true){
    std::string  text;
    std::set<std::string> validWords;
    
    text = readFileContents(path);
    validWords = this->_getValidFirstWords( );

    if(!checkBraces(text)){
        this->_status= false;
        Logs::printLog(Logs::ERROR, 11, "The " + path  + " file is not correct closing/opening brackets");
        return;
    }
    
    if(_isFirstWordInSet(text, validWords) > -1){
        this->_status= false;
        Logs::printLog(Logs::ERROR, 11, "The " + path + " file contains an error on line "+ to_string(_isFirstWordInSet(text, validWords)) +".");
        return;
    }
        
    

}


CheckFile::~CheckFile(void){
   return;
    
}




std::set<std::string> CheckFile::_getValidFirstWords(void) {
    std::set<std::string> validWords;
    
    validWords.insert("server");
    validWords.insert("server_name");
    
    validWords.insert("listen");
    validWords.insert("host");
    validWords.insert("error_page");
    validWords.insert("index");
    validWords.insert("client_max_body_size");
    validWords.insert("root");
    validWords.insert("word");

    
    validWords.insert("location");

    validWords.insert("autoindex");
    validWords.insert("allow_method");
    validWords.insert("limit_except");
    
    validWords.insert("redirect");
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