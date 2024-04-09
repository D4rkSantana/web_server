#include "Socket.hpp"

Socket::Socket(void): _listSockets(){
	FD_ZERO(&this->_readFds);
	FD_ZERO(&this->_writeFds);
}

Socket::~Socket(void){}

bool	Socket::start(std::map<int, Data>& mapServer){
	this->_mapServer = mapServer;
	int socketFd;
	int optval = 1;
	int flags;

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

			flags = fcntl(socketFd, F_GETFL, 0);
			if (flags < 0){
				throw std::runtime_error("Erro status socket");
			}

			if (fcntl(socketFd, F_SETFL, flags | O_NONBLOCK) < 0){
				throw std::runtime_error("Erro no-Block socket");
			}

			if(setListenSockets(socketFd) == false){
				throw std::runtime_error("Erro setListenSockets");
			}

			std::stringstream sk;
			sk << port;
			std::string message = sk.str();
			Logs::printLog(Logs::INFO, 5, "socket created with success " + message);
		} catch (std::runtime_error& e){
				Logs::printLog(Logs::WARNING, 4, e.what());
				close(socketFd);
				return (false);
		}
	}

////////////////////////////////////////////////////////////////////////////////

	// while (true){
	// 	sockaddr_in client_addr;
	// 	socklen_t addr_len = sizeof(client_addr);
	// 	int clientfd = accept(_listenSockets[1], (struct sockaddr*)&client_addr, &addr_len);

	// 	if (clientfd < 0) {
	// 	  std::cout << "ERROR CLIENT FD" << std::endl; // MARCAÇÃO EXCLUIR
	// 	  continue;
	// 	}else{
	// 		std::cout << "Aguardando Requisições na porta: ->>  " << std::endl;
	// 	}

	// 	// Receba a requisição
	// 	char request[1024];
	// 	int bytes_received = recv(clientfd, request, sizeof(request), 0);
	// 	if (bytes_received < 0) {
	// 		std::cout << "ERROR REQUEST" << std::endl; // MARCAÇÃO EXCLUIR
	// 		close(clientfd);
	// 		continue;
	// 	}

	// 	std::cout << "Conexão recedida com sucesso ->>  " << request << "\n\n" << std::endl;
	// };
	// return	(true);

////////////////////////////////////////////////////////////////////////////////

	return (true);
}

bool	Socket::setListenSockets(int	socketFd){
	FD_SET(socketFd, &this->_readFds);
	if (FD_ISSET(socketFd, &this->_readFds) > 0){
		this->_listSockets.push_back(socketFd);
		return (true);
	}else{
		return (false);
	}
}

fd_set*	Socket::getReadFds(void){
	return (&this->_readFds);
}

fd_set*	Socket::getWriteFds(void){
	return (&this->_writeFds);
}

std::vector<int>*	Socket::getListenSockets(void){
	return (&this->_listSockets);
}

void	Socket::closed(void){
	try{
		for (std::vector<int>::iterator it = _listSockets.begin();
				it != _listSockets.end(); ++it) {
					std::cout << _listSockets[*it] << std::endl;
		}
	}catch(const std::exception& e){
		Logs::printLog(Logs::ERROR, 6, "Erro close sockets");
	}
}