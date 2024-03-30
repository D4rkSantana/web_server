/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:55:58 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/26 09:21:56 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils.hpp"

responseData getJson(std::string body, int status)
{
    responseData data;

    data = setResponseData(status, "application/json", body, (int)body.length());
    return (data);
}

responseData getContent(std::string root, std::string file, int status)
{
    std::stringstream fullPathStream;
    std::string       fullPath;
    responseData      data;
    std::string       extension;

    data      = setResponseData(0, "", "", 0);
    extension = extractFileExtension(file);
    fullPathStream << root << file;
    fullPath = fullPathStream.str();
    std::ifstream ifs(fullPath.c_str());
    if (ifs.is_open()) {
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            std::istreambuf_iterator<char>());
        data = setResponseData(
            status, Constants::getMimeTypes(extension), content, (int)content.length());
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

std::string getDir()
{
    char        cwd[1024];
    std::string rPath = "webserv";

    if (getcwd(cwd, 1024) != NULL) {
        std::string dir(cwd);
        size_t      pos = dir.find(rPath);
        if (pos != std::string::npos)
            dir = dir.substr(0, pos + 7);
        return dir;
    } else {
         Logs::printLog(Logs::ERROR, 13, "Getting current working directory");
      
        return "";
    }
}

std::string extentionToBin(std::string extention)
{
    if (extention == "php")
        return "php";
    else if (extention == "py")
        return "python3";
    else if (extention == "rb")
        return "ruby";
    else if (extention == "pl")
        return "perl";
    else
        return "";
}

std::string getBin(const std::string &url)
{

    const char *binName;
    std::string command = "which ";

    std::string::size_type pos_slash = url.find_last_of('/');
    std::string::size_type pos_query = url.find_first_of('?');

    if (pos_slash != std::string::npos && pos_slash < url.length() - 1) {
        std::string            bin_tmp = url.substr(pos_slash + 1, pos_query - pos_slash - 1);
        std::string::size_type pos_dot = bin_tmp.find_last_of('.');
        std::string            bin     = bin_tmp.substr(pos_dot + 1, bin_tmp.length() - 1);
        bin                            = extentionToBin(bin);
        command += bin;
        binName      = command.c_str();
        FILE *stream = popen(binName, "r");
        if (!stream) {
             Logs::printLog(Logs::INFO, 13, "Getting Binary name");
            return "";
        }
        char buffer[1024];
        while (fgets(buffer, 1024, stream) != NULL) {
            pclose(stream);
            std::string bin(buffer);
            bin.erase(std::remove(bin.begin(), bin.end(), '\n'), bin.end());
            return bin;
        }
         Logs::printLog(Logs::INFO, 13, "It doesn't get binary name");
      
        return "";
    } else {
         Logs::printLog(Logs::INFO, 13, "It doesn't get binary name");
        return "";
    }
}

responseData setResponseData(int         status,
                             std::string contentType,
                             std::string content,
                             int         contentLength,
                             std::string location)
{
    responseData res;

    res.status        = status;
    res.statusCode    = Constants::getStatusCodes(to_string(status));
    res.contentType   = contentType;
    res.content       = content;
    res.contentLength = contentLength;
    res.location      = location;
    return (res);
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


