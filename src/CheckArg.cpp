/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckArg.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:46:52 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/30 01:34:01 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "CheckArg.hpp"


CheckArg::CheckArg(int argc, char *argv[]):_status(true){

    if(!_checkArgc(argc))
        return;
    _checkArgv(argv);

}

CheckArg::~CheckArg(void){
    return;
}

bool CheckArg::_checkArgc(int argc){
    if (argc < 2){
        Logs::printLog(Logs::INFO, 1, "./webserv path/name.conf");
        Logs::printLog(Logs::ERROR, 1, "Invalid number of arguments");
        this->_status = false;
        return false;
    }
    else if(argc > 2){
        Logs::printLog(Logs::INFO, 1, "does not accept any type of flag");
        Logs::printLog(Logs::ERROR, 1, "Invalid number of arguments");
        this->_status = false;
        return false;
    }
    return true;
}

bool CheckArg::_checkArgv(char *argv[]){
    if (!fileExists(argv[1])){
        Logs::printLog(Logs::INFO, 1, "file is not exists");
        Logs::printLog(Logs::ERROR, 1, "failed to read file");
        this->_status = false;
        return false;
    }
    return true;
}

bool CheckArg::getStatus(void){
    return (this->_status);
}