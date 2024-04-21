/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientProcess.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:09:57 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/21 20:45:09 by esilva-s         ###   ########.fr       */
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
        //this->_poll.addFdToClose(fd);
        return;
    }
    /*
    if (!reqClient.requestStart(clientReq))
    {
        response = getErrorPageStandard(reqClient.statusCode);
        reqClient.printInfos();
    }
    */
    if (reqClient.requestStart(clientReq))
    {
        response = getErrorPageStandard(404);
        reqClient.printInfos();
    }
    //else
    //    res = this->_responseHandlers.exec(this->_parser, this->_request);
    sendResponse(fd, response);
}

void  sendResponse(int fd, responseData res)
{
    std::string response_header = "";
    int bytes_sent;

    response_header =  "HTTP/1.1 " + res.statusCode + "\r\n";
    if (res.contentLength < 0)
        return;

    if (res.status == PERMANENT_REDIRECT || res.status == TEMPORARY_REDIRECT)
        response_header += "location: " + res.location + "\r\n\r\n";
    else if (res.contentType.empty())
        response_header += "\r\n";
    else if (res.status == METHOD_NOT_ALLOWED)
    {
        response_header += "Allow: GET\r\nContent-Type: " + res.contentType;
        response_header += "\r\nContent-Length: " + to_string(res.contentLength) + "\r\n\r\n";
    }
    else
    {
        response_header += "Content-Type: " + res.contentType;
        response_header += "\r\nContent-Length: " + to_string(res.contentLength) + "\r\n\r\n";
    }

    bytes_sent = send(fd, response_header.c_str(), strlen(response_header.c_str()), MSG_NOSIGNAL);
    if (bytes_sent == -1)
    {
        Logs::printLog(Logs::INFO, 3, "Client connection closed:" + to_string(fd));
        //this->_poll.addFdToClose(fd);
        return;
    }

    if (res.contentLength)
    {
        bytes_sent = send(fd, res.content.c_str(), res.contentLength, MSG_NOSIGNAL);
        if (bytes_sent == -1)
        {
            Logs::printLog(Logs::INFO, 3, "Client connection closed:" + to_string(fd));
            //this->_poll.addFdToClose(fd);
        }
    }
}

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
/*
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
*/
