/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:53:27 by lucasmar          #+#    #+#             */
/*   Updated: 2024/03/01 17:40:56 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"
Webserv::Webserv(void): listenSockets(_sockets.getListenSockets()){}


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
		fd_set readSocket = _sockets.getReadFds();
		fd_set writeSocket = _sockets.getWriteFds();
		if( select(
				FD_SETSIZE,
			 	&readSocket,
				&writeSocket,
				NULL,
				&timer)
			== -1){
			Logs::printLog(Logs::WARNING, 8, "Error monitoring sockets SELECT");
			return(false);
		}
////////////////////////////////////////////////////////////////////////////////
//accept new sockets
		int newClientSocket;
		for(std::vector<int>::iterator it = listenSockets.begin();
			it != listenSockets.end(); ++it){
			//if (FD_ISSET(*it, &readSocket)){
			std::cout << "LISTEN: " << *it << std::endl;

				sockaddr_in client_addr;
				socklen_t addr_len = sizeof(client_addr);
				newClientSocket = accept(*it, (struct sockaddr*)&client_addr, &addr_len);

				std::cout << "newClientSocket: " << newClientSocket << std::endl;

				if (newClientSocket != -1){
					FD_SET(newClientSocket, &readSocket);
					this->clientListSockets.push_back(newClientSocket);
				} else{
					Logs::printLog(Logs::WARNING, 8, "Error accept new sockets");
				}
			//}
		}
////////////////////////////////////////////////////////////////////////////////
//process cliente deve ser feito aqui!
		// for (size_t i = 0; i < this->listclientSocket.size(); ++i){
		// 	RequestValidator requestValidator;
		// 	Request request;
		// 	int clientSocket = this->clienstSocks[i];
		// 	if (FD_ISSET(clientSocket, &this->readSocket))
		// 	{
		// 		processClientRequest(clientSocket, i,  request, requestValidator);
		// 	}
		// 	if (FD_ISSET(clientSocket, &writeSocket))
		// 	{
		// 		sendClientResponse(clientSocket, i, request, requestValidator);
		// 	}
		// }
		std::cout << "Recebido: " << std::endl;

		if (FD_ISSET(3, &readSocket)){
			std::cout << "entrei: " << std::endl;
			char buffer[1024];
			int readBytes = recv(3, &buffer, 1024, 0);
			if(readBytes < 0){
				std::cout << "erro buffer\n\n\n" << std::endl;
			}else{
				std::cout << "Recebido: " << buffer << std::endl;
			}
			std::cout << "sai: " << std::endl;

		}


	};

}
	return	(true);
}

void	Webserv::stop(){
	_sockets.closed();
}
