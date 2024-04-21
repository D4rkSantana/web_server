/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positiveResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:48:20 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/21 20:58:38 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "positiveResponse.hpp"

responseData processResponse(Request &request)
{
    responseData res;

    res = setResponseData(0, "", "", -1);

    if (!this->_verifyServerName(request, parser))
    {
        res = getErrorPageContent(request.getErrorPageConfig(), BAD_REQUEST, request.getUri(), request.getRoot());
        return (res);
    }

    if (this->_verifyRedirection(request, parser)) {
        return (this->_res);
    }
    if (!this->_methodAllowed(request)) {
        return (this->_errorPage.getErrorPageContent(
            request.getErrorPageConfig(), METHOD_NOT_ALLOWED, request.getUri(), request.getRoot()));
    }
    switch (this->_resolveOption(request.getMethod())) {
        case GET:
            this->_getHandler(request, parser);
            break;
        case POST:
            this->_postHandler(request, parser);
            break;
        case DELETE:
            this->_deleteHandler(request);
            break;
        default:
            break;
    }
    return (this->_res);
}

bool verifyServerName(Request &request)
{
    std::vector<std::string> server_names;

    server_names = webServer.getServerParam(request.getServerIndex(), "server_name");
    if (server_names.empty())
        return (true);
    for (std::vector<std::string>::iterator it = server_names.begin(); it != server_names.end();
         ++it) {
        if (*it == request.getHost() || request.getHost() == "127.0.0.1")
            return (true);
    }
    return (false);
}