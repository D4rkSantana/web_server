/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckFile.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:04:53 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/03 14:39:31 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CheckFile.hpp"


CheckFile::CheckFile(std::string path):_status(true){
    std::string  text;
    
    text = readFileContents(path);
    

    

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
    return validWords;
}
