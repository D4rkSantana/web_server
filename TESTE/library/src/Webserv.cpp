/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:53:27 by lucasmar          #+#    #+#             */
/*   Updated: 2024/02/29 16:15:27 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"

Webserv::Webserv(void){}

Webserv::~Webserv(void){}

bool	Webserv::setDataServer(std::string pathConf){

	(void)pathConf;

	Data server;
	Data server2;

	server.setServerName("Lucas.42.fr");
	server.setIndex("hello.html");
	server.setRoot("examples");
	server.setClientMaxBodySize(1024);
	server.setPort(5800);
	server.setErrorPage("not_found.html");



	server2.setServerName("Ricardo.42.fr");
	server2.setIndex("hello2.html");
	server2.setRoot("examples2");
	server2.setClientMaxBodySize(1024);
	server2.setPort(2469);
	server2.setErrorPage("not_found.html");

	this->_mapServer[0] = server;
	this->_mapServer[1] = server2;

	return (true);
}

bool	Webserv::start(void){
	if (!_sockets.start(_mapServer)){
		Logs::printLog(Logs::WARNING, 7, "socket NOT created!");
		return(false);
	}

{// novo menbro run

	struct timeval timer;
	while (true){
		timer.tv_sec = 1;
		timer.tv_usec = 0;

		if( select(
				FD_SETSIZE,
			 	&_sockets.getReadFds(),
				&_sockets.getWriteFds(),
				NULL,
				&timer)
			<= 0){
			Logs::printLog(Logs::WARNING, 8, "Error monitoring sockets SELECT");
			break;
			return(false);
		}

		for(std::vector<int>::iterator it = listenSockets.begin(); it != listenSockets.end(); ++it){
			int sockfd = *it;
			if (FD_ISSET(sockfd, &this->readSocket)){
				acceptNewClient(sockfd);
			}
	}
	};
	// server.initPoll();
	// return (server.run());
	return	(true);
}

void	Webserv::stop(){
	_sockets.closed();
}
