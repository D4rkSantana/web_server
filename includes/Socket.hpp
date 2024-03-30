/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:54:00 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/25 23:49:38 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once


#include "Libs.hpp"

class Socket {
    private:
    int              _socketFd;
    std::string      _port;
    std::string      _ip;
    struct addrinfo *_serverInfo;

    public:
    Socket(std::string port = "8080", std::string ip = IP);
    ~Socket(void);

    void  createSocket(void);
    void  bindSocket(void);
    void  listenForConnections(void);
    void *get_in_addr(struct sockaddr *sa);
    int   acceptConnection(int socketFd);
    void  closeSocket(void);

    int         getSocketFd(void) const;
    std::string getPort(void) const;
    std::string getIp(void) const;

    class SocketException : public std::exception {
        private:
        std::string _msg;

        public:
        SocketException(const char *msg);
        virtual ~SocketException() throw();
        virtual const char *what() const throw();
    };
};
