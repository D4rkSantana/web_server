/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientProcess.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:09:57 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/15 00:11:11 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "clientProcess.hpp"

void processClientData(int fd)
{
    std::string  clientReq;
    responseData response;
    Request     reqClient;

    response       = setResponseData(0, "", "", 0, "");
    clientReq = readClientData(fd);
    if (webServer.getBytesRead() == -1) {
        Logs::printLog(Logs::INFO, 3, "Client closed: " + to_string(fd));
        return;
    }
    if (reqClient.requestStart(clientReq))
        reqClient.printInfos();
    //    response = this->_responseHandlers.exec(this->_parser, this->_request);
    /*
    else
        response = _errorPage.getErrorPageStandard(_request.statusCode);
    this->_sendClientData(fd, response);
    */
}



/* 

void  sendClientData(int fd, responseData response)
{
    char responseHeader[1024];

    if (response.contentLength < 0) {
        return;
    }
    if (response.status == PERMANENT_REDIRECT || response.status == TEMPORARY_REDIRECT) {
        sprintf(responseHeader,
                "HTTP/1.1 %s\r\nlocation: "
                "%s\r\n\r\n",
                response.statusCode.c_str(),
                response.location.c_str());
    } else if (response.contentType.empty()) {
        sprintf(responseHeader, "HTTP/1.1 %s\r\n\r\n", response.statusCode.c_str());
    } else if (response.status == METHOD_NOT_ALLOWED) {
        sprintf(responseHeader,
                "HTTP/1.1 %s\r\nAllow: %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n",
                response.statusCode.c_str(),
           //     vector_join(this->_request.getLimitExcept(), " ").c_str(),
                response.contentType.c_str(),
                response.contentLength);
    } else {
        sprintf(responseHeader,
                "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n",
                response.statusCode.c_str(),
                response.contentType.c_str(),
                response.contentLength);
    }

    int bytes_sent = send(fd, responseHeader, strlen(responseHeader), MSG_NOSIGNAL);
    if (bytes_sent == -1) {
        Logs::printLog(logs::INFO, 3, "Client connection closed:" + to_string(fd));
        //Logger::info << "Client connection closed"  << " on socket " << fd << std::endl;
        this->_poll.addFdToClose(fd);
        return;
    }
    if (response.contentLength) {
        int bytes_sent = send(fd, response.content.c_str(), response.contentLength, MSG_NOSIGNAL);
        if (bytes_sent == -1) {
             Logs::printLog(logs::INFO, 3, "Client connection closed:" + to_string(fd));
            //Logger::info << "Client connection closed"<< " on socket " << fd << std::endl;
            this->_poll.addFdToClose(fd);
            return;
        }
    }
}
*/


std::string readClientData(int fd)
{
    char        buffer[1024] = {0};
    int         bytes        = 0;
    std::string clientReq;
    int bytesRead;

    while ((bytesRead = recv(fd, buffer, sizeof(buffer), 0)) > 0) {
        		webServer.setBytesRead(bytesRead);
        if (bytesRead < 0)
            break;
        clientReq.append(buffer, bytesRead);
        if (clientReq.find("Expect: 100-continue") != std::string::npos) {
            sleep(2);
            continue;
        }
        buffer[bytesRead] = '\0';
        bytes += bytesRead;
        if (clientReq.find("multipart/form-data") != std::string::npos) {
            std::string boundary;
            size_t      contentTypePos = clientReq.find("Content-Type: ");

            if (contentTypePos != std::string::npos) {
                size_t lineEnd = clientReq.find("\r\n", contentTypePos);
                if (lineEnd != std::string::npos) {
                    std::string contentTypeLine
                        = clientReq.substr(contentTypePos, lineEnd - contentTypePos);
                    size_t boundaryPos = contentTypeLine.find("boundary=");
                    if (boundaryPos != std::string::npos) {
                        boundary = contentTypeLine.substr(boundaryPos + 9);
                    }
                }
            }
            std::string boundaryEnd = "\r\n--" + boundary + "--";
            if (clientReq.find(boundaryEnd) != std::string::npos)
                break;
        } else if (clientReq.find("\r\n\r\n") != std::string::npos) {
            break;
        }
    }
    return (clientReq);
}

std::string mergeStrVector(std::vector<std::string> vec, std::string delimiter)
{
    std::string                        result = "";
    std::vector<std::string>::iterator it = vec.begin();

    while (it != vec.end())
    {
        result += *it;
        result += delimiter;
        it++;
    }
    return (result);
}

responseData setResponseData(int status, std::string contentType, std::string content,
                             int contentLength, std::string location) 
{
    responseData response;

    std::string msg;
    std::string str_status = to_string(status);

    msg = webServer.getStatusCode(str_status);
    if (msg != "")
        str_status += " " + msg;

    response.status        = status;
    response.statusCode    = str_status;
    response.contentType   = contentType;
    response.content       = content;
    response.contentLength = contentLength;
    response.location      = location;
    return (response);
}
