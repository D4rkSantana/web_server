/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:53:27 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/11 11:18:01 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"


WebServ::WebServ(void) {}

WebServ::~WebServ(void) {}

bool WebServ::setDataServer(const char *pathConf)
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

int WebServ::start(void)
{
	// Logs::printLog(Logs::ERROR, 2, "Erro start server");
	return (0);
}

void WebServ::stop()
{
	return;
}

bool WebServ::connect(void){
	std::cout << _data.getServerParam(1, "listen")[0]; 

	return (true);
}