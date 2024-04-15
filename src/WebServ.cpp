/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:53:27 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/15 00:57:44 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"


WebServ::WebServ(void) {
    this->_setStatusCode();
}

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
            this->_poll.init(socket->getFd());
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
        sleep(1);
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
                    processClientData(clientSocket);
                }
            }
        }
        //this->_poll.removeMarkedElements();
    }
	return (0);
}

void WebServ::stop()
{
	return;
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

void WebServ::_setStatusCode(void)
{
    this->_statusCodes["100"] = "Continue";
    this->_statusCodes["101"] = "Switching Protocols";
    this->_statusCodes["102"] = "Processing";
    this->_statusCodes["103"] = "Early Hints";
    this->_statusCodes["200"] = "OK";
    this->_statusCodes["201"] = "Created";
    this->_statusCodes["202"] = "Accepted";
    this->_statusCodes["203"] = "Non-Authoritative Information";
    this->_statusCodes["204"] = "No Content";
    this->_statusCodes["205"] = "Reset Content";
    this->_statusCodes["206"] = "Partial Content";
    this->_statusCodes["207"] = "Multi-Status";
    this->_statusCodes["208"] = "Already Reported";
    this->_statusCodes["226"] = "IM Used";
    this->_statusCodes["300"] = "Multiple Choices";
    this->_statusCodes["301"] = "Moved Permanently";
    this->_statusCodes["302"] = "Found";
    this->_statusCodes["303"] = "See Other";
    this->_statusCodes["304"] = "Not Modified";
    this->_statusCodes["307"] = "Temporary Redirect";
    this->_statusCodes["308"] = "Permanent Redirect";
    this->_statusCodes["400"] = "Bad Request";
    this->_statusCodes["401"] = "Unauthorized";
    this->_statusCodes["402"] = "Payment Required";
    this->_statusCodes["403"] = "Forbidden";
    this->_statusCodes["404"] = "Not Found";
    this->_statusCodes["405"] = "Method Not Allowed";
    this->_statusCodes["406"] = "Not Acceptable";
    this->_statusCodes["407"] = "Proxy Authentication Required";
    this->_statusCodes["408"] = "Request Timeout";
    this->_statusCodes["409"] = "Conflict";
    this->_statusCodes["410"] = "Gone";
    this->_statusCodes["411"] = "Length Required";
    this->_statusCodes["412"] = "Precondition Failed";
    this->_statusCodes["413"] = "Payload Too Large";
    this->_statusCodes["414"] = "URI Too Long";
    this->_statusCodes["415"] = "Unsupported Media Type";
    this->_statusCodes["416"] = "Range Not Satisfiable";
    this->_statusCodes["417"] = "Expectation Failed";
    this->_statusCodes["418"] = "I'm a teapot";
    this->_statusCodes["421"] = "Misdirected Request";
    this->_statusCodes["422"] = "Unprocessable Content";
    this->_statusCodes["423"] = "Locked";
    this->_statusCodes["424"] = "Failed Dependency";
    this->_statusCodes["425"] = "Too Early";
    this->_statusCodes["426"] = "Upgrade Required";
    this->_statusCodes["428"] = "Precondition Required";
    this->_statusCodes["429"] = "Too Many Requests";
    this->_statusCodes["431"] = "Request Header Fields Too Large";
    this->_statusCodes["451"] = "Unavailable For Legal Reasons";
    this->_statusCodes["500"] = "Internal Server Error";
    this->_statusCodes["501"] = "Not Implemented";
    this->_statusCodes["502"] = "Bad Gateway";
    this->_statusCodes["503"] = "Service Unavailable";
    this->_statusCodes["504"] = "Gateway Timeout";
    this->_statusCodes["505"] = "HTTP Version Not Supported";
    this->_statusCodes["506"] = "Variant Also Negotiates";
    this->_statusCodes["507"] = "Insufficient Storage";
    this->_statusCodes["508"] = "Loop Detected";
    this->_statusCodes["510"] = "Not Extended";
    this->_statusCodes["511"] = "Network Authentication Required";
}

int WebServ::getBytesRead(void)
{
    return (_bytesRead);
}

void WebServ::setBytesRead(int nbr)
{
    _bytesRead = nbr;
}

std::string WebServ::getStatusCode(std::string code)
{
    std::map<std::string, std::string>::const_iterator it = this->_statusCodes.find(code);

    if (it == this->_statusCodes.end())
        return ("");
    return (it->second);
}

int                         WebServ::searchServer(std::string port)
{
    return (_data.searchServer(port));
}

int							WebServ::searchLocation(size_t iS, std::string path)
{
    int locationSize = this->getAllQtLocations()[iS];
    std::vector<std::string> locationParam;
    int i = 0;

    while (i < locationSize)
    {
        locationParam = _data.getLocationValue(iS, i, "location");
        if (std::find(locationParam.begin(), locationParam.end(), path) != locationParam.end())
            break ;
        i++;
    }
    return (i);
}

size_t                      WebServ::getQtSevers(void)
{
	return (this->_data.getQtSevers());
}

std::vector<int>            WebServ::getAllQtLocations(void)
{
    return (_data.getAllQtLocations());
}

std::vector<std::string>    WebServ::getServerValue(size_t index, std::string key)
{
	return (this->_data.getServerValue(index, key));
}

std::vector<std::string>    WebServ::getLocationValue(size_t iS, size_t iL, std::string key)
{
    return (_data.getLocationValue(iS, iL, key));
}