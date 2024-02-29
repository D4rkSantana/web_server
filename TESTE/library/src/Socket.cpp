/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:58:31 by lucasmar          #+#    #+#             */
/*   Updated: 2024/02/29 15:58:19 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"

Socket::Socket(void){}

Socket::~Socket(void){}

bool	Socket::start(std::map<int, Data>& mapServer){
	this->_mapServer = mapServer;
	int socketFd;
	int optval = 1;

	FD_ZERO(&this->_readFds);
	FD_ZERO(&this->_writeFds);

	for(std::map<int, Data>::iterator it = _mapServer.begin();
		 it != _mapServer.end(); ++it){

		int port = it->second.getPort();

		try{
			socketFd = socket(AF_INET, SOCK_STREAM, 0);
			if(socketFd < 0){
				throw std::runtime_error("Erro create socket");
			}
			if(setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR,
					 &optval, sizeof(optval)) < 0){
				throw std::runtime_error("Erro setsockopt");
			}

			_sockaddr.sin_family = AF_INET;
			_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
			_sockaddr.sin_port = htons(port);

			if(bind(socketFd, (const struct sockaddr*)&_sockaddr,
				 	sizeof(_sockaddr)) < 0){
				throw std::runtime_error("Erro blind socket");
			}

			if (listen(socketFd, 10)){
				throw std::runtime_error("Erro listen socket");
			}

			if (fcntl(socketFd, F_SETFL, O_NONBLOCK) < 0){
				throw std::runtime_error("Erro no-Block socket");
			}

			FD_SET(socketFd, &this->_readFds);
			this->_listenSockets.push_back(socketFd);

			} catch (std::runtime_error& e){
				Logs::printLog(Logs::WARNING, 4, e.what());
				close(socketFd);
				break;
				return false;
			}
	}
	Logs::printLog(Logs::INFO, 5, "socket created with success");
	return (true);
}

fd_set	Socket::getReadFds(void){
	return (this->_readFds);
}

fd_set	Socket::getWriteFds(void){
	return (this->_writeFds);
}

void	Socket::closed(void){
	try{
		for (std::vector<int>::iterator it = _listenSockets.begin();
				it != _listenSockets.end(); ++it) {
					std::cout << _listenSockets[*it] << std::endl;
		}
	}catch(const std::exception& e){
		Logs::printLog(Logs::ERROR, 6, "Erro close sockets");
	}
}



