/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:53:27 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/05 15:21:48 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"
Webserv::Webserv(void): listSocketsPoint(_sockets.getListenSockets()){}


Webserv::~Webserv(void){}

bool	Webserv::setDataServer(std::string pathConf){
	(void) pathConf;
	return(true);

}

int	Webserv::start(void){
	//Logs::printLog(Logs::ERROR, 2, "Erro start server");
	return	(0);
}

void	Webserv::stop(){
	_sockets.closed();
}
