/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 21:28:12 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/13 22:51:41 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"

Request::

Request::Request() { init(); }

Request::~Request() {}


void Request::init()
{
    
    _allowMethods.push_back("GET");
    _allowMethods.push_back("POST");
    _allowMethods.push_back("DELETE");
    _paramQuery.clear();
    /*
    has_body       = false;
    has_form       = false;
    has_multipart  = false;
    statusCode     = 0;
    content        = "";
    _uri           = "";
    _port          = "";
    _method        = "";
    _boundary      = "";
    _httpVersion   = "";
    _maxBodySize   = 0;
    _contentLength = 0;
    
    _header.clear();
    */
}

bool Request::requestHttp(std::string request, Parser &parser)
{
    std::map<std::string, std::string>::const_iterator it;
    std::string requestLine;
    std::string headersPart;
    size_t firstLineEnd;
    

    firstLineEnd = request.find("\r\n")
    if (firstLineEnd == std::string::npos) {
        this->statusCode = BAD_REQUEST;
        return (false);
    }

    requestLine = request.substr(0, firstLineEnd);
    headersPart = request.substr(firstLineEnd + 2);

    if (!_parseFirstLine(requestLine))
        return (false);

    _parseHeaders(headersPart);
    //
    _getMaxBody(parser);
    _getServerParam(parser);
    _setAutoIndex(parser);
    _getHost();

    if (has_body) {
        has_multipart = false;
        has_form      = false;
        
        it = _header.find("Content-Type");
        if (it->second.find("multipart/form-data") != std::string::npos)
            has_multipart = true;
        if (it->second.find("application/x-www-form-urlencoded") != std::string::npos)
            has_form = true;
    }

    if (has_multipart) {
        if (_getMultipartData(request))
            return (true);
    } else if (has_body) {
        if (_getBody(request))
            return (true);
    }
    return (false);
}

bool Request::_parseFirstLine(std::string &requestLine)
{
    std::istringstream iss(requestLine);

    if (!(iss >> this->_method >> this->_uri >> this->_httpVersion)
        || requestLine != this->_method + " " + this->_uri + " " + this->_httpVersion
        || this->_uri[0] != '/'){
        this->statusCode = BAD_REQUEST;
        return (false);
    }
    if (std::find(_allowMethods.begin(), _allowMethods.end(), _method) == _allowMethods.end()){
        this->statusCode = METHOD_NOT_ALLOWED;
        return (false);
    }
    if (this->_httpVersion != "HTTP/1.1") {
        this->statusCode = HTTP_VERSION_NOT_SUPPORTED;
        return (false);
    }
    size_t pos = this->_uri.find('?');
    if (pos != std::string::npos) {
        _parseQuery();
        this->_uri.erase(pos);
    }
    return (true);
}

void Request::_parseQuery()
{
    size_t      posQuery = this->_uri.find("?");
    std::string query;

    if (posQuery != std::string::npos) {
        query = this->_uri.substr(posQuery + 1);
        std::string::size_type start = 0;
        while (start < query.length()) {
            std::string::size_type equal = query.find('=', start);
            if (equal != std::string::npos) {
                std::string::size_type ampersand = query.find('&', equal);
                if (ampersand != std::string::npos) {
                    _paramQuery.push_back(query.substr(equal + 1, ampersand - equal - 1));
                    start = ampersand + 1;
                } else {
                    _paramQuery.push_back(query.substr(equal + 1));
                    break;
                }
            } else
                break;
        }
    }
}

void Request::_parseHeaders(const std::string &request)
{
    std::istringstream iss(request);
    std::string        headerLine;
    has_body = false;

    while (std::getline(iss, headerLine, '\r')) {
        //headerLine.erase(std::remove(headerLine.begin(), headerLine.end(), '\n'), headerLine.end());
        if (headerLine[0] == '\n')
            headerLine.erase(0);

        if (headerLine.empty())
            break;

        size_t colonPos = headerLine.find(": ");
        if (colonPos != std::string::npos) {
            std::string key    = headerLine.substr(0, colonPos);
            std::string value  = headerLine.substr(colonPos + 1);
            this->_header[key] = value;
            this->_findHeaders(key, value);
        }
    }
}

void Request::_findHeaders(std::string key, std::string value)
{
    if (key == "Host") {
        size_t pos = value.find(":");
        if (pos != std::string::npos) {
            std::string tmp = value.substr(pos + 1);
            this->_port     = tmp;
        }
    }
    if (key == "Content-Length") {
        int length = atoi(value.c_str());
        if (length > 0) {
            has_body             = true;
            _contentLength = length;
        }
    }
}