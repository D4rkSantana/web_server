/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:53:27 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/11 11:12:04 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"
Webserv::Webserv(void) {}

Webserv::~Webserv(void) {}

bool Webserv::setDataServer(const char *pathConf)
{
	if (_data.start(pathConf))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

int Webserv::start(void)
{
	// Logs::printLog(Logs::ERROR, 2, "Erro start server");
	return (0);
}

void Webserv::stop()
{
	return;
}

bool Webserv::connect(void){
	std::cout << _data.getServerParam(1, "listen")[0]; 

	return (true);
}