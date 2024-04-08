/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckArg.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:46:52 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/08 00:32:33 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "CheckArg.hpp"

bool CheckArg::check(int argc, char *argv[]){

    if(!_checkArgc(argc))
        return false;
    
    return _checkArgv(argv);
}

bool CheckArg::_checkArgc(int argc){
    if (argc < 2){
        Logs::printLog(Logs::INFO, 1, "./webserv path/name.conf");
        Logs::printLog(Logs::ERROR, 1, "Invalid number of arguments");
        return false;
    }
    else if(argc > 2){
        Logs::printLog(Logs::INFO, 1, "does not accept any type of flag");
        Logs::printLog(Logs::ERROR, 1, "Invalid number of arguments");
        return false;
    }
    return true;
}

bool CheckArg::_checkArgv(char *argv[]){
    if (!fileExists(argv[1])){
        Logs::printLog(Logs::INFO, 1, "file is not exists");
        Logs::printLog(Logs::ERROR, 1, "failed to read file");
        return false;
    }
    return true;
}


bool checkBraces(const std::string& text) {
    std::stack<char> stack;
    char c;
    size_t i;

    i = 0;
    while (i < text.length()) {
        c = text[i];
        if (c == '{') {
            stack.push(c);
        } else if (c == '}') {
            if (stack.empty() || stack.top() != '{') {
                return false; 
            }
            stack.pop();
        }
        i ++;
    }

    return stack.empty(); 
}

bool fileExists(char *path) {
    std::ifstream file(path);
    bool exists = file.good();
    file.close(); 
    return exists; 
}

std::string readFileContents(const std::string& filename) {
    std::ifstream file(filename.c_str());
    std::stringstream buffer;

    if (file) {
        buffer << file.rdbuf();
        file.close(); 
        return buffer.str();
    } else {
        return "";
    }
}

bool isLineEmpty(const std::string& text) {
    size_t  i;
    
    i  = 0;
    while(i < text.length()){
        if (!isspace(text[i]))
            return false;
        i ++;
    } 
    return true;
}