/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:09:20 by lucasmar          #+#    #+#             */
/*   Updated: 2024/02/28 16:10:31 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"

Data::Data(void){
	this->_serverName = "";
	this->_index = "";
	this->_root = "";
	this->_clientMaxBodySize = 0;
	this->_port = 0;
	this->_errorPage = "";
}

Data::~Data(void){}

void Data::setServerName(std::string serverName){
	this->_serverName = serverName;
}

void Data::setIndex(std::string index){
	this->_index = index;
}

void Data::setRoot(std::string root){
	this->_root = root;
}

void Data::setClientMaxBodySize(int clientMaxBodySize){
	this->_clientMaxBodySize = clientMaxBodySize;
}

void Data::setPort(int port){
	this->_port = port;
}

void Data::setErrorPage(std::string errorPage){
	this->_errorPage = errorPage;
}

std::string Data::getServerName(void){
	return (this->_serverName);
}

std::string Data::getIndex(void){
	return (this->_index);
}

std::string Data::getRoot(void){
	return (this->_root);
}

int Data::getClientMaxBodySize(void){
	return (this->_clientMaxBodySize);
}

int Data::getPort(void){
	return (this->_port);
}

std::string Data::getErrorPage(void){
	return (this->_errorPage);
}
