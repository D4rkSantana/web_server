/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:53:27 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/12 16:22:14 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"


WebServ::WebServ(void) {}

WebServ::~WebServ(void) {
	this->finish();
}

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
	while (true) {
        if (this->_poll.execute() == -1) {
            Logs::printLog(Logs::ERROR, 1, "Error creating poll");
            return (1);
        }
        /*
        for (size_t i = 0; i < this->_poll.getSize(); ++i) {
            if (this->_poll.isReadable(i)) {
                if (this->_poll.isListeningSocketMatch(i)) {
                    if (!this->_acceptNewConnection(i))
                        continue;
                } else {
                    int clientSocket = this->_poll.getPollFd(i);
                    if (clientSocket < 0) {
                        Logger::error << "Index out of bounds of vector _pollFds" << std::endl;
                        continue;
                    }
                    _processClientData(clientSocket);
                }
            }
        }
        this->_poll.removeMarkedElements();
    */
    
    }
    


    
	return (0);
}

void WebServ::stop()
{
	return;
}

bool WebServ::connect(void){

    size_t	qtServers;
	size_t	i = 0;
    std::vector<std::string> port;

    qtServers = this->getQtSevers();

    if (qtServers == 0) {
        Logs::printLog(Logs::ERROR, 1, "The server was not configured correctly");
        this->finish();
        exit(1);
    }

    //try {
        while (i < qtServers) {
            Socket *socket;

            port = this->getServerValue(i, "listen");

            if (port.empty())
                socket = new Socket();
            else
                socket = new Socket(port[0]);

            socket->init();
            socket->bindAddr();
            socket->listenConnections();
            this->_sockets.push_back(socket);
			i++;
        }
    /*} catch (const std::exception &e) {
        Logger::error << e.what() << std::endl;
        this->closeServer();
        exit(1);
    }*/
	return (true);
}

size_t WebServ::getQtSevers(void)
{
	return (this->_data.getQtSevers());
}

std::vector<std::string>	WebServ::getServerValue(size_t index, std::string key)
{
	return (this->_data.getServerParam(index, key));
}

void WebServ::finish(void)
{
    for (std::vector<Socket *>::iterator it = this->_sockets.begin();
			it != this->_sockets.end(); ++it) {
        delete *it;
    }
    this->_sockets.clear();
    //this->_parser.clearParams();
    //this->_poll.closePoll();
}