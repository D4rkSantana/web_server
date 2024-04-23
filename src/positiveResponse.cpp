/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positiveResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:48:20 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/22 23:09:19 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "positiveResponse.hpp"

responseData processResponse(Request &request)
{
    responseData res;
    responseData temp;

    res = setResponseData(0, "", "", -1, "");

    if (!verifyServerName(request))
    {
        res = getErrorPageContent(request.getErrorPageConfig(), BAD_REQUEST, request.getUri(), request.getRoot());
        return (res);
    }

    temp = verifyRedirection(request);
    
    if (temp.status != 999)
        return (temp);

    if (methodAllowed(request)) {
        res = getErrorPageContent(request.getErrorPageConfig(), METHOD_NOT_ALLOWED, request.getUri(), request.getRoot()));
        return (res);
    }

    /*
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
    */+
    return (res);
}

bool verifyServerName(Request &request)
{
    std::vector<std::string>            server_names;
    std::vector<std::string>::iterator  it;

    server_names = webServer.getServerParam(request.getServerIndex(), "server_name");
    if (server_names.empty())
        return (true);
    it = server_names.begin();
    while (it != server_names.end())
    {
        if (*it == request.getHost() || request.getHost() == "127.0.0.1")
            return (true);
        it++;
    }
    return (false);
}

responseData verifyRedirection(Request &request)
{
    std::vector<std::string>::iterator  it_s;
    std::vector<std::string>::iterator  it_p;
    std::vector<std::string>            server_redirection;
    std::vector<std::string>            location_redirection;
    responseData                        res;

    server_redirection = webServer.getServerValue(request.autoIndexServer, "redirect");
    it_s = server_redirection.begin();

    res = setResponseData(999, "", "", -1, "");

    if (!server_redirection.empty())
    {
        //pensar em como reornar esse res
        res = setResponseData(std::atoi(it_s[0].c_str()), "", "", 0, it_s[1]);
        return (res);
    }

    location_redirection = webServer.getLocationValue(request.autoIndex, request.autoIndexLoc, "redirect");
    it_p = location_redirection.begin();

    if (!location_redirection.empty())
    {
        //pensar em como reornar esse res
        res = setResponseData(std::atoi(it_p[0].c_str()), "", "", 0, it_p[1]);
        return (res);
    }
    return (res);
}

bool methodAllowed(Request &request)
{
    size_t i = 0;

    if (request.getLimitExcept().empty())
        return (true);

    while (i < request.getLimitExcept().size())
    {
        if (request.getLimitExcept()[i] == request.getMethod())
            return (true);
        i++;
    }
    return (false);
}

int resolveOption(std::string method)
{
    std::string option[] = {"GET", "POST", "DELETE"};
    int         i        = 0;

    while (i < 3 && method != option[i])
        i++;
    return (i);
}

/*
responseData getHandler(Request &request)
{
    Location        location(request);
    AutoIndex       autoIndex(request);
    responseData    res;

    res = setResponseData(0, "", "", 0);

    if (request.autoIndexServer && request.getUri() == "/autoindex")
        res = autoIndex.autoIndex(request.getRoot(), "/", request.getPort());
    else if (request.autoIndexLoc)
        res = autoIndex.autoIndex(request.getRoot(), request.getPath(), request.getPort());
    else if (Constants::isCgi(extractFileExtension(request.getUri())) && _cgi.isCGI(request, parser))
        res = getCgi(request);
    else
    {
        location.setup(parser);
        res = location.getLocationContent();
    }
    return (res);
}

responseData postHandler(Request &request)
{
    PostMethod      post_method(request);
    responseData    res;

    res = setResponseData(0, "", "", 0);

    if (Constants::isCgi(extractFileExtension(request.getUri())) && _cgi.isCGI(request, parser))
        res = getCgi(request);
    else 
        res = post_method.handleMethod();

    return (res)
}

responseData deleteHandler(Request &request)
{
    DeleteMethod delete_method(request);
    responseData    res;

    res = delete_method.handleMethod();

    //Logs::warning << "Delete Method" << std::endl;
    return (res);
}
*/