/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positiveResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:48:20 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/25 19:21:19 by esilva-s         ###   ########.fr       */
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

    if (!methodAllowed(request))
    {
        res = getErrorPageContent(request.getErrorPageConfig(), METHOD_NOT_ALLOWED, request.getUri(), request.getRoot());
        return (res);
    }

    int opt = resolveOption(request.getMethod());

    if (opt == 0)
        res = getHandler(request);
    else if (opt == 1)
        res = postHandler(request);
    //else if (opt == 2)
        //res = deleteHandler(request);

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
    int i        = 0;

    while (i < 3 && method != option[i])
        i++;
    return (i);
}

responseData getHandler(Request &request)
{
    Location        location(request);
    responseData    res;
 
    res = setResponseData(0, "", "", 0, ""); 

    if (request.autoIndexServer && request.getUri() == "/autoindex" && !request.autoIndexLoc)
        res = autoIndex(request.getRoot(), "/", request.getPort(), request);
    else if (request.autoIndexLoc)
        res = autoIndex(request.getRoot(), request.getPath(), request.getPort(), request);
    //else if (Constants::isCgi(extractFileExtension(request.getUri())) && _cgi.isCGI(request, parser))
    //    res = getCgi(request);
    else
    {
        location.setup();
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

/*
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
    std::string     dirPath = root + path;
    std::string     entryPath;
    std::string     content;
    struct dirent   *entry;
    responseData    res;
    DIR             *dir;

    dir = opendir(dirPath.c_str());
    
    if (dir == NULL)
    {
        res = getErrorPageContent(request.getErrorPageConfig(), NOT_FOUND, request.getUri(), request.getRoot());
        return (res);
    }

    content = "<html><body><h2>Index of: " + dirPath + "</h2><ul>";
    
    entry = readdir(dir);
    while (entry)
    {
        entryPath = port + path;
        if (path[path.size() - 1] != '/')
            entryPath += "/";
        entryPath = std::string(entry->d_name);
        content += "<li><a href=\"http://localhost:" + entryPath + "\">" + std::string(entry->d_name) + "</a></li>\n";
        entry = readdir(dir);
    }

    content += "</ul></body></html>";
    res = setResponseData(OK, "text/html", content, content.length(), path );

    closedir(dir);
    return (res);
}

responseData PostMethod::handleMethod()
{
    created = false;

    if (_req.has_body)
    {
        if (_req.has_multipart)
        {
            if (handleMultipart())
            {
                _res = getErrorPageContent(_req.getErrorPageConfig(), ENTITY_TOO_LARGE, _req.getUri(), _req.getRoot());
                Logger::error << "Request Entity Too Large." << std::endl;
                return (_res);
            }

            if (created && _file == true)
            {
                _res = getJson(
                    "{\"status\": \"success\", \"message\": \"Resource created successfully\"}",
                    201);
                Logger::info << "File created." << std::endl;
                return (_res);
            } else if (!created && _file == true) {
                _res = _errorPage.getErrorPageContent(_req.getErrorPageConfig(),
                                                      INTERNAL_SERVER_ERROR,
                                                      _req.getUri(),
                                                      _req.getRoot());
                Logger::error << "Unable to create file." << std::endl;
                return (_res);
            }
        }
        if (_req.has_form)
            handleForm();
        else
            std::cout << "Body: " << _req.getBody() << "\n";

        _res = getJson("{\"status\": \"success\", \"message\": \"Successful operation\"}", OK);
        Logger::info << "Post request completed successfully." << std::endl;
    } else if (!_req.has_body) {
        _res = _errorPage.getErrorPageContent(
            _req.getErrorPageConfig(), BAD_REQUEST, _req.getUri(), _req.getRoot());
        Logger::info << "No content." << std::endl;
    } else {
        _res = _errorPage.getErrorPageContent(
            _req.getErrorPageConfig(), INTERNAL_SERVER_ERROR, _req.getUri(), _req.getRoot());
        Logger::error << "Internal Server Error." << std::endl;
    }
    return (_res);
}

bool PostMethod::handleMultipart()
{
    std::string boundary = _req.getBoundary();
    std::string body     = _req.getBody();

    _formData.clear();
    _file       = false;
    size_t pos  = 0;
    _bodySize   = 0;
    while ((pos = body.find(boundary, pos)) != std::string::npos) {
        pos += boundary.length();
        size_t endPos = body.find(boundary, pos);
        if (endPos != std::string::npos)
            parseMultipartFormData(pos, endPos);
    }
    if (verifyLimit())
        return (true);
    if (_file == false)
        print();
    return (false);
}