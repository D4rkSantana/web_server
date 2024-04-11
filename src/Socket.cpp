/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:11:35 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/11 18:53:15 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Socket.hpp"

Socket::Socket(std::string port, std::string ip) :
    _fd(-1), _port(port), _ip(ip), _serverInfo(NULL)
{
}

Socket::~Socket(void)
{
    this->finish();
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
        //throw Socket::SocketException(msg.c_str());
        std::cout << msg << std::endl;
        exit(1);
    }

    //cria o socket cru
    this->_fd = socket( this->_serverInfo->ai_family,
                        this->_serverInfo->ai_socktype,
                        this->_serverInfo->ai_protocol);

    //verifica se ouve erro ao criar o socket
    if (this->_fd < 0) {
        msg = "Error creating server socket: " + std::string(strerror(errno));
        //throw Socket::SocketException(msg.c_str());
        std::cout << msg << std::endl;
        exit(1);
    }

    //configura o socket;
    setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &active, sizeof(int));
}

void Socket::bindAddr(void)
{
    std::string msg;//      para possivel erro
    int         result;

    //  configura o endereço que o socket ira utilizar
    result = bind(this->_fd, this->_serverInfo->ai_addr, this->_serverInfo->ai_addrlen);

    //  checa se ouve algum erro 
    if (result < 0)
    {
        msg = "Error binding socket to port: " + std::string(strerror(errno));
        //throw Socket::SocketException(msg.c_str());
        std::cout << msg << std::endl;
        exit(1);
    }

    //  limpa as informaçoes de _serverInfo
    freeaddrinfo(this->_serverInfo);
    this->_serverInfo = NULL;
}

void Socket::listenConnections(void)
{
    std::string msg;
    int         result;

    //  coloca o socket em modo de escuta, onde ele espera por conexões
    //  o parametro SOMAXCONN limita a quantidade de conexoes pendentes
    //      de acordo com o limite do sistema operacional.
    result = listen(this->_fd, SOMAXCONN);
    
    //  checa se ouve algum erro
    if (result < 0) {
        msg = "Error listening for connections: " + std::string(strerror(errno));
        //throw Socket::SocketException(msg.c_str());
        std::cout << msg << std::endl;
        exit(1);
    }
    Logs::printLog(Logs::INFO, 1, "Listening at " + to_string(this->_ip) + ":" + to_string(this->_port));
}

void Socket::finish(void)
{
    if (this->_fd != -1) {
        close(this->_fd);
        this->_fd = -1;
    }
    if (this->_serverInfo != NULL) {
        freeaddrinfo(this->_serverInfo);
        this->_serverInfo = NULL;
    }
}