/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negativeResponse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:39:55 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/20 11:45:45 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/negativeResponse.hpp"

responseData getErrorPageStandard(int statusCode)
{
    responseData res;
    std::string file;

    file = "/";
    file += to_string(statusCode);
    file += ".html";
    res = getContent(DEFAULT_ERROR_ROOT, file, statusCode);
    
    if (res.contentLength)
        return (res);

    res = getContent(DEFAULT_ERROR_ROOT, "not_configured.html", statusCode);
    return (res);
}

responseData getContent(std::string root, std::string file, int status)
{
    std::stringstream fullPathStream;
    std::string       fullPath;
    responseData      data;
    std::string       extension;

    data      = setResponseData(0, "", "", 0 , "");
    extension = extractFileExtension(file);
    fullPathStream << root << file;
    fullPath = fullPathStream.str();
    std::ifstream ifs(fullPath.c_str());
    if (ifs.is_open()) {
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            std::istreambuf_iterator<char>());
        data = setResponseData(status, getTypes(extension, webServer.getDicTypes()), content, (int)content.length(), "");
        ifs.close();
    }
    return (data);
}

std::string extractFileExtension(std::string file)
{
    size_t dotPos = file.rfind('.');

    if (dotPos != std::string::npos) {
        std::string extension = file.substr(dotPos);
        return extension;
    }
    return "";
}

responseData setResponseData(int         status, std::string contentType, std::string content,
                             int         contentLength, std::string location)
{
    responseData res;

    res.status        = status;
    res.statusCode    = getStatus(to_string(status), webServer.getDicStatusCodes());
    res.contentType   = contentType;
    res.content       = content;
    res.contentLength = contentLength;
    res.location      = location;
    return (res);
}