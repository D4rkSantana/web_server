/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:53:27 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/09 02:35:51 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"


Webserv::Webserv(void): listSocketsPoint(_sockets.getListenSockets()){}


Webserv::~Webserv(void){}

bool	Webserv::setDataServer(std::string pathConf){

	(void)pathConf;
	// aqui vamos colocar um classe que vai fazer o parser do arquivo de configuração
    // assim todo o código abaixo será de responsabilidade dessa classe

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
	server2.setPort(59000);
	server2.setErrorPage("not_found.html");

	this->_mapServer[0] = server;
	this->_mapServer[1] = server2;

	return (true);
}

bool	Webserv::start(void){
	if (_sockets.start(_mapServer) == false){
		Logs::printLog(Logs::WARNING, 7, "socket NOT created!");
		return(false);
	}

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	while(true){
		memcpy(&readFdsCopy, _sockets.getReadFds(), sizeof(readFdsCopy));
		int maxfd = -1;
		for (int i = 0; i < 5; ++i) {
			if (FD_ISSET(i, &readFdsCopy)) {
				if (i > maxfd){
					maxfd = i;
				}
			}
		}
		int ready = select(maxfd + 1, &readFdsCopy, NULL, NULL, &timeout);
		if (ready == -1) {
			std::cerr << "Erro ao executar o select" << std::endl;
			break; // Se ocorrer um erro, sair do loop
		}
		else if (ready > 0) {
			std::cout << "Pelo menos um socket está pronto para leitura" << std::endl;
			std::vector<int>::iterator it;
			for (it = listSocketsPoint->begin(); it != listSocketsPoint->end(); ++it) {
				int sockfd = *it;
				if (FD_ISSET(sockfd, &readFdsCopy)) {
					// Este é um socket de escuta pronto para aceitar uma nova conexão
					struct sockaddr_in clientAddr;
					socklen_t clientAddrLen = sizeof(clientAddr);
					int clientSocket = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
					if (clientSocket == -1) {
						std::cerr << "Erro ao aceitar nova conexão" << std::endl;
					}
					else {
						std::cout << "***Nova conexão aceita. Socket: " << clientSocket << std::endl;

						if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1) {
                        	std::cerr << "Erro ao configurar o socket do cliente como não bloqueante" << std::endl;
                        	close(clientSocket);
                    	}
                    	else {
	                     	char buffer[1024];
						    // Receber dados do cliente
						    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
						    if (bytesReceived == -1) {
						        std::cerr << "Erro ao receber dados do cliente" << std::endl;
						        // Tratar o erro aqui, se necessário
						    }
							else if (bytesReceived == 0) {
						        std::cout << "O cliente fechou a conexão" << std::endl;
						    }
							else {
						        // Dados recebidos com sucesso
						        buffer[bytesReceived] = '\0'; // Adicione um terminador nulo ao final da string
						        std::cout << "Mensagem recebida do cliente: \n" << buffer << std::endl;
						    }

							// Mensagem de resposta simples (página HTML básica)
							std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
							response += "<html><head><title>Test Page</title></head><body><h1>Hello, World!</h1></body></html>";

							// Enviar a resposta ao cliente
							send(clientSocket, response.c_str(), response.size(), 0);
					    	// Fechar o socket do cliente

					    	close(clientSocket);
							std::cout << "\nCLIENTE <><><><><><><><> ATENDIDO\n\n" << std::endl;
						}
					}
				}
			}
		}

	// while (true){
	// 	// fd_set	readSocket = _sockets.getReadFds();
	// 	// fd_set	writeSocket = _sockets.getWriteFds();
	// 	// int	selectAcount = select(FD_SETSIZE, &readSocket, &writeSocket, NULL, NULL);
	// 	// if( selectAcount == -1){
	// 	// 	Logs::printLog(Logs::WARNING, 8, "Error monitoring sockets SELECT");
	// 	// 	return(false);
	// 	// }
	// 	// std::cout << "SELECT OK" << std::endl; // MARCAÇÃO EXCLUIR

	// 	    // Aceite uma nova conexão
	// sockaddr_in client_addr;
	// socklen_t addr_len = sizeof(client_addr);
    // int clientfd = accept((*listenSockets)[0], (struct sockaddr*)&client_addr, &addr_len);

    // if (clientfd < 0) {
    //   std::cout << "ERROR CLIENT FD" << std::endl; // MARCAÇÃO EXCLUIR
    //   continue;
    // }else{
	// 	std::cout << "Aguardando Requisições na porta: ->>  " << std::endl;
	// }

    // // Receba a requisição
    // char request[1024];
    // int bytes_received = recv(clientfd, request, sizeof(request), 0);
    // if (bytes_received < 0) {
	// 	std::cout << "ERROR REQUEST" << std::endl; // MARCAÇÃO EXCLUIR
	// 	close(clientfd);
	// 	continue;
    // }

    // std::cout << "Conexão recedida com sucesso ->>  " << request << "\n\n" << std::endl;

	// 	// for(std::vector<int>::iterator it = listenSockets->begin(); it != listenSockets->end(); ++it){
	// 	// 	if (FD_ISSET(*it, &readSocket)){
	// 	// 		std::cout << "LISTEN: " << *it << std::endl; // MARCAÇÃO EXCLUIR

	// 	// 		sockaddr_in client_addr;
	// 	// 		socklen_t addr_len = sizeof(client_addr);
	// 	// 		newClientSocket = accept(*it, (struct sockaddr*)&client_addr, &addr_len);

	// 	// 		//std::cout << "newClientSocket: " << newClientSocket << std::endl; // MARCAÇÃO EXCLUIR
	// 	// 		if (newClientSocket == -1){
	// 	// 			Logs::printLog(Logs::WARNING, 8, "Error accept new sockets");
	// 	// 			return(false);
	// 	// 		}
	// 	// 		//std::cout << "Nova conexão aceita. Socket: " << newClientSocket << std::endl;
	// 	// 		//break;
	// 	// 		//FD_SET(newClientSocket, readSocket);
	// 	// 		//this->clientListSockets.push_back(newClientSocket);
	// 	// 		if ( fcntl(newClientSocket, F_SETFL, O_NONBLOCK) == -1){
	// 	// 			Logs::printLog(Logs::WARNING, 8, "Error set non-blocking socket");
	// 	// 			return(false);
	// 	// 		}

	// 	// 		std::cout << "Nova conexão aceita. Socket: " << newClientSocket << std::endl;
	// 	// 	}
	// 	// 	std::cout << "AGUARDANDO CONEXÃO .....  " << std::endl;

	// 	// }
	// };
	}

	return	(true);
}

void	Webserv::stop(){
	_sockets.closed();
}
