/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:11:35 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/11 17:28:20 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Socket.hpp"

Socket::Socket(std::string port, std::string ip) :
    _socketFd(-1), _port(port), _ip(ip), _serverInfo(NULL)
{
}

Socket::~Socket(void)
{
    this->closeSocket();
}

void Socket::init(void)
{
    struct addrinfo hints;//            hints é uma struct necessaria para configurar o socket
    std::string     msg;
    int             active = 1;
    int result;//                       recebe a saida de getaddrinfo para checkar se ouve erro

    memset(&hints, 0, sizeof hints);//  zera a memoria

    hints.ai_family   = AF_UNSPEC;//    configura constantes em hints
    hints.ai_socktype = SOCK_STREAM;//  configura o tipo do socket para stream
    hints.ai_flags    = AI_PASSIVE;//   configura constantes em hints

    //obtem informações do servidor e grava no serverInfo
    result = getaddrinfo(this->_ip.c_str(), this->_port.c_str(), &hints, &this->_serverInfo);

    //checa se ouve um erro nas informações
    if (result != 0) {
        msg = "Error getting address information: " + std::string(gai_strerror(result));
        throw Socket::SocketException(msg.c_str());
    }

    //cria o socket cru
    this->_fd = socket( this->_serverInfo->ai_family,
                        this->_serverInfo->ai_socktype,
                        this->_serverInfo->ai_protocol);

    //verifica se ouve erro ao criar o socket
    if (this->_socketFd < 0) {
        msg = "Error creating server socket: " + std::string(strerror(errno));
        throw Socket::SocketException(msg.c_str());
    }

    //configura o socket;
    setsockopt(this->_socketFd, SOL_SOCKET, SO_REUSEADDR, &active, sizeof(int));
}

void Socket::bindSocket(void)
{
    std::string msg;//      para possivel erro
    int         result;

    //  configura o endereço que o socket ira utilizar
    result = bind(this->_socketFd, this->_serverInfo->ai_addr, this->_serverInfo->ai_addrlen);

    //  checa se ouve algum erro 
    if (result < 0)
    {
        msg = "Error binding socket to port: " + std::string(strerror(errno));
        throw Socket::SocketException(msg.c_str());
    }

    //  limpa as informaçoes de _serverInfo
    freeaddrinfo(this->_serverInfo);
    this->_serverInfo = NULL;
}

void Socket::listenForConnections(void)
{
    std::string msg;
    int         result;

    //  coloca o socket em modo de escuta, onde ele espera por conexões
    //  o parametro SOMAXCONN limita a quantidade de conexoes pendentes
    //      de acordo com o limite do sistema operacional.
    result = listen(this->_socketFd, SOMAXCONN);
    
    //  checa se ouve algum erro
    if (result < 0) {
        msg = "Error listening for connections: " + std::string(strerror(errno));
        throw Socket::SocketException(msg.c_str());
    }
    Logger::info << "Listening at " << this->_ip << ":" << this->_port << std::endl;
}