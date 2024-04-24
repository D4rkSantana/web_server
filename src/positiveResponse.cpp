/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positiveResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:48:20 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/24 16:45:50 by ryoshio-         ###   ########.fr       */
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

    if (methodAllowed(request))
    {
        res = getErrorPageContent(request.getErrorPageConfig(), METHOD_NOT_ALLOWED, request.getUri(), request.getRoot());
        return (res);
    }

    /*
    switch (this->_resolveOption(request.getMethod())) {
        case GET:
            this->_getHandler(request, parser); //parse
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
    */
    return (res);
}

bool verifyServerName(Request &request)
{
    std::vector<std::string>            server_names;
    std::vector<std::string>::iterator  it;

    server_names = webServer.getServerValue(request.getServerIndex(), "server_name");
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

    server_redirection = webServer.getServerValue(request.getServerIndex(), "redirect");
    it_s = server_redirection.begin();

    res = setResponseData(999, "", "", -1, "");

    if (!server_redirection.empty())
    {
        res = setResponseData(std::atoi(it_s[0].c_str()), "", "", 0, it_s[1]);
        return (res);
    }

    location_redirection = webServer.getLocationValue(request.getServerIndex(), request.getLocationIndex(), "redirect");
    it_p = location_redirection.begin();

    if (!location_redirection.empty())
    {
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


responseData autoIndex(std::string root, std::string path, std::string port, Request request)
{
    std::string dirPath = root + path; // ok
    responseData resp;
    struct dirent *entry;
    DIR *dir;
    std::string    content;
    std::string entryPath;

    
    dir = opendir(dirPath.c_str()); // abrir diretorio 
    
    if (dir == NULL) { // erro ao abrir o diretorio 
        resp = getErrorPageContent(request.getErrorPageConfig(),
                                                       NOT_FOUND,
                                                       request.getUri(),
                                                       request.getRoot());
        return (resp);
    }

    content = "<html><body><h2>Index of: " + dirPath + "</h2><ul>";
    
    for (entry = readdir(dir); entry; entry = readdir(dir)) {
        entryPath
            = port + path + (path[path.size() - 1] != '/' ? "/" : "") + std::string(entry->d_name);
        content += "<li><a href=\"http://localhost:" + entryPath + "\">"
            + std::string(entry->d_name) + "</a></li>\n";
    }

    content += "</ul></body></html>";
    resp = setResponseData(OK, "text/html", content, content.length(), path );

    closedir(dir);
    return (resp);
}

