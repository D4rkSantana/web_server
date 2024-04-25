/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:59:13 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/25 11:31:24 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





/*
Seria para fazer relocação dos arquivos

*/

#include "Location.hpp"

Location::Location(void) {}

Location::Location(Request request) : _req(request) {}

Location::~Location(void) {}

void Location::setup(void)
{
    this->_uriExtension = extractFileExtension(this->_req.getUri());

    this->_setIndexPage();
}

void Location::_setIndexPage(void)
{
    std::vector<std::string> indexParam;

    if (this->_req.getQtLocationsInServer() != this->_req.getLocationIndex())
    {
        indexParam = webServer.getLocationValue(this->_req.getServerIndex(), this->_req.getLocationIndex(), "index");
        if (!indexParam.empty())
        {
            this->_indexPage = indexParam[0];
            return;
        }
    }
    indexParam = webServer.getServerValue(this->_req.getServerIndex(), "index");
    if (!indexParam.empty())
        this->_indexPage = indexParam[0];
    else
        this->_indexPage = "index.html";
    return;
}

responseData Location::getLocationContent(void)
{
    responseData    res;

    res = setResponseData(0, "", "", 0, "");
    if (this->_uriExtension.length())
        res = this->_getFileContent();
    else
        res = this->_getIndexContent();

    return (res);
}

responseData Location::_getFileContent(void)
{
    responseData    res;

    res = setResponseData(0, "", "", 0, "");
    res = getContent(this->_req.getRoot(), this->_req.getUri(), OK);

    if (!res.contentLength)
        res = getErrorPageContent(  this->_req.getErrorPageConfig(), NOT_FOUND,
                                    this->_req.getUri(), this->_req.getRoot());
    return (res);
}

responseData Location::_getIndexContent(void)
{
    std::string     indexPath;
    std::string     extension;
    std::string     uri;
    responseData    res;

    res = setResponseData(0, "", "", 0, "");
    uri = this->_req.getUri();

    if (this->_indexPage.empty()) {
        res = getErrorPageContent(  this->_req.getErrorPageConfig(), NOT_FOUND,
                                    uri, this->_req.getRoot());
        return (res);
    }

    if (uri[uri.length() - 1] != '/')
        uri += '/';

    indexPath = uri + this->_indexPage;
    res = getContent(this->_req.getRoot(), indexPath, OK);
    //std::cout << std::endl << indexPath << std::endl << std::endl;
    if (!res.contentLength)
        res = getErrorPageContent(  this->_req.getErrorPageConfig(), FORBIDDEN,
                                    uri, this->_req.getRoot());
    return (res);
}
