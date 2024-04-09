/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckFile.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:04:53 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/08 21:27:31 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CheckFile.hpp"


bool CheckFile::check(std::string path){
    long unsigned int i;
    std::string  text;
    std::set<std::string> validWords;
    std::vector<std::string> separateServer;
    
    text = readFileContents(path);
    
    // verifica se {} esta correto
    if(!checkBraces(text)){
        Logs::printLog(Logs::ERROR, 11, "The " + path  + " file is not correct closing/opening brackets");
        return false;
    }
    
    // verifica se existe um elemento difente no arquivo, so se ele for a primeira palavra
    // o restante vou verificar na hora de ver os valores
    validWords = _getValidFirstWords( );
    if(_isFirstWordInSet(text, validWords) > -1){
        Logs::printLog(Logs::ERROR, 12, "The " + path + " file contains an error on line "+ to_string(_isFirstWordInSet(text, validWords)) +".");
        return false;
    }

    separateServer  =  separateServerBlocks(text);
    if(separateServer.size() < 1){
        Logs::printLog(Logs::ERROR, 13, "Server not found or in the wrong position.");
        return false;
    }
       
    i = 0;
    while(i < separateServer.size())
    {
        if(!_checkServerParams(separateServer[i])){
            return false;
        }
            
        i ++;
    }
    

   // verifica se o elemento do bloco esta correto, 
    
    // verifica se existe elemento necessario 
        
    return true;    

}



// palavras chaves que sao aceita, que pertece a primeira linha
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




bool CheckFile::_checkServerParams(std::string element){
    std::string serverParams;
    std::set<std::string> validWords;
    
    serverParams = extractServerParams(element);

    if(serverParams.length() < 1)
        return false;
    
    validWords.insert("server_name");
    validWords.insert("listen");
    validWords.insert("host");
    validWords.insert("error_page");
    validWords.insert("index");
    validWords.insert("client_max_body_size");
    validWords.insert("root");
    validWords.insert("word");
    validWords.insert("autoindex");

    if(_isFirstWordInSet(serverParams, validWords) != -1){
        Logs::printLog(Logs::ERROR, 14, "This element is in the wrong position: "+ getFirstWord(serverParams , _isFirstWordInSet(serverParams, validWords)-1));
        return false;
    }

    // fazer para os outros!
    if(countWordOccurrencesLine(element, "serve_name") != 1){
        Logs::printLog(Logs::ERROR, 14,"server_name is duplicated or missing");
        return false;
    }
       
        
    return true;
    
}

