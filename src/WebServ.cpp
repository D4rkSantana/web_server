/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:53:27 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/13 12:53:50 by ryoshio-         ###   ########.fr       */
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

int WebServ::start(void)
{
	while (true) {
        if (this->_poll.execute() == -1) {//coloca um socket dentro da poll
            Logs::printLog(Logs::ERROR, 1, "Error creating poll");
            return (1);
        }
        for (size_t i = 0; i < this->_poll.getSize(); ++i) {
            if (this->_poll.isRead(i)) { //veridica se o socket tem alguma conexão pendente
                if (this->_poll.isSocketServer(i)){//verifica se o socket é do server ou cliente
                    if (!this->_newCliet(i))//aceita e cria o novo cliente
                        continue;
                } else {
                    int clientSocket = this->_poll.getPollFd(i);
                    if (clientSocket < 0) {
                        Logs::printLog(Logs::ERROR, 1, "I didn't find the index");
                        continue;
                    }
                    //this->_processClientData(clientSocket);
                }
            }
        }
        this->_poll.removeMarkedElements();
    }
	return (0);
}

void WebServ::stop()
{
	return;
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

bool WebServ::_newCliet(size_t i) //mudar de nome
{
    try {
        Socket *client;
        int     clientSocketFd;

        client         = new Socket();
        clientSocketFd = client->acceptClient(this->_poll.getPollFd(i));
        this->_poll.addPoll(clientSocketFd, POLLIN | POLLOUT);
        delete client;

        return (true);
    } catch (const std::exception &e) {
        Logs::printLog(Logs::ERROR, 1, e.what());
        return (false);
    }
}


int WebServ::getBytesRead(void){
    return (_bytesRead);

    
}

void WebServ::setBytesRead(int nbr){
    _bytesRead = nbr;
}



