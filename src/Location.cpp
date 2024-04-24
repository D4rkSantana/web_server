/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:59:13 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/24 19:01:53 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





/*
Seria para fazer relocação dos arquivos

*/

#include "Location.hpp"

Location::Location(void) {}

Location::Location(HttpRequest request) : _req(request) {}

Location::~Location(void) {}




void Location::setup(void)
{
    this->_responseData = setResponseData(0, "", "", 0);

    this->_uriExtension = extractFileExtension(this->_req.getUri());

    this->_setIndexPage(parser);
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

    if (this->_uriExtension.length()) {
        this->_getFileContent();
    } else {
        this->_getIndexContent();
    }
    return (this->_responseData);
}

void Location::_getFileContent(void)
{
    this->_responseData = getContent(this->_req.getRoot(), this->_req.getUri(), OK);
    if (!this->_responseData.contentLength) {
        this->_responseData = this->_errorPage.getErrorPageContent(
            this->_req.getErrorPageConfig(), NOT_FOUND, this->_req.getUri(), this->_req.getRoot());
        return;
    }
    return;
}

void Location::_getIndexContent(void)
{
    std::string indexPath, extension, uri;

    if (this->_indexPage.empty()) {
        this->_responseData = this->_errorPage.getErrorPageContent(
            this->_req.getErrorPageConfig(), NOT_FOUND, this->_req.getUri(), this->_req.getRoot());
        return;
    }
    uri = this->_req.getUri();
    if (uri[uri.length() - 1] != '/') {
        uri += '/';
    }
    indexPath           = uri + this->_indexPage;
    this->_responseData = getContent(this->_req.getRoot(), indexPath, OK);
    if (!this->_responseData.contentLength) {
        this->_responseData = this->_errorPage.getErrorPageContent(
            this->_req.getErrorPageConfig(), FORBIDDEN, uri, this->_req.getRoot());
    }
    return;
}
