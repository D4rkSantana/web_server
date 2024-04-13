



# include"clientProcess.hpp"

/* 

void processClientData(int fd)
{
    std::string  clientReq;
    responseData response;

    response       = setResponseData(0, "", "", 0);
    clientReq = this->_readClientData(fd);
    if (WebServ->getBytesRead() == -1) {
        Logs::printLog(Logs::INFO, 3, "Client closed: " + to_string(fd));
        return;
    }
    if (this->_request.requestHttp(clientReq, this->_parser)) {
        response = _errorPage.getErrorPageStandard(_request.statusCode);
    } else {
        response = this->_responseHandlers.exec(this->_parser, this->_request);
    }
    this->_sendClientData(fd, response);

}
*/



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














































std::string vector_join(std::vector<std::string> vec, std::string delimiter)
{
    std::string                        result = "";
    std::vector<std::string>::iterator it;

    for (it = vec.begin(); it != vec.end(); ++it) {
        result += *it;
        result += delimiter;
    }
    return (result);
}












responseData setResponseData(int         status,
                             std::string contentType,
                             std::string content,
                             int         contentLength,
                             std::string location) {
    responseData response;

    response.status        = status;
    response.statusCode    = getStatusCodes(to_string(status));
    response.contentType   = contentType;
    response.content       = content;
    response.contentLength = contentLength;
    response.location      = location;
    return (response);
}








std::string getStatusCodes(std::string status)
{
     std::map<std::string, std::string> statusCodes;

    statusCodes["100"] = "Continue";
    statusCodes["101"] = "Switching Protocols";
    statusCodes["102"] = "Processing";
    statusCodes["103"] = "Early Hints";
    statusCodes["200"] = "OK";
    statusCodes["201"] = "Created";
    statusCodes["202"] = "Accepted";
    statusCodes["203"] = "Non-Authoritative Information";
    statusCodes["204"] = "No Content";
    statusCodes["205"] = "Reset Content";
    statusCodes["206"] = "Partial Content";
    statusCodes["207"] = "Multi-Status";
    statusCodes["208"] = "Already Reported";
    statusCodes["226"] = "IM Used";
    statusCodes["300"] = "Multiple Choices";
    statusCodes["301"] = "Moved Permanently";
    statusCodes["302"] = "Found";
    statusCodes["303"] = "See Other";
    statusCodes["304"] = "Not Modified";
    statusCodes["307"] = "Temporary Redirect";
    statusCodes["308"] = "Permanent Redirect";
    statusCodes["400"] = "Bad Request";
    statusCodes["401"] = "Unauthorized";
    statusCodes["402"] = "Payment Required";
    statusCodes["403"] = "Forbidden";
    statusCodes["404"] = "Not Found";
    statusCodes["405"] = "Method Not Allowed";
    statusCodes["406"] = "Not Acceptable";
    statusCodes["407"] = "Proxy Authentication Required";
    statusCodes["408"] = "Request Timeout";
    statusCodes["409"] = "Conflict";
    statusCodes["410"] = "Gone";
    statusCodes["411"] = "Length Required";
    statusCodes["412"] = "Precondition Failed";
    statusCodes["413"] = "Payload Too Large";
    statusCodes["414"] = "URI Too Long";
    statusCodes["415"] = "Unsupported Media Type";
    statusCodes["416"] = "Range Not Satisfiable";
    statusCodes["417"] = "Expectation Failed";
    statusCodes["418"] = "I'm a teapot";
    statusCodes["421"] = "Misdirected Request";
    statusCodes["422"] = "Unprocessable Content";
    statusCodes["423"] = "Locked";
    statusCodes["424"] = "Failed Dependency";
    statusCodes["425"] = "Too Early";
    statusCodes["426"] = "Upgrade Required";
    statusCodes["428"] = "Precondition Required";
    statusCodes["429"] = "Too Many Requests";
    statusCodes["431"] = "Request Header Fields Too Large";
    statusCodes["451"] = "Unavailable For Legal Reasons";
    statusCodes["500"] = "Internal Server Error";
    statusCodes["501"] = "Not Implemented";
    statusCodes["502"] = "Bad Gateway";
    statusCodes["503"] = "Service Unavailable";
    statusCodes["504"] = "Gateway Timeout";
    statusCodes["505"] = "HTTP Version Not Supported";
    statusCodes["506"] = "Variant Also Negotiates";
    statusCodes["507"] = "Insufficient Storage";
    statusCodes["508"] = "Loop Detected";
    statusCodes["510"] = "Not Extended";
    statusCodes["511"] = "Network Authentication Required";


    std::map<std::string, std::string>::const_iterator it = statusCodes.find(status);
    std::string                                        statusText;
    std::string                                        statusCode;

    if (it != statusCodes.end()) {
        statusText = it->second;
        statusCode = status + " " + statusText;
    }
    return (statusCode);
}
