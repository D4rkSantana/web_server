/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:49:19 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/21 11:49:20 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "AResponse.hpp"
#include "Libs.hpp"
#include "Parser.hpp"
#include "Request.hpp"
#include "utils.hpp"

class CGI : public HttpRequest {
    private:
    char      **_envs;
    std::string _cgi_path;
    bool        _is_cgi;
    std::string _bin;

    public:
    CGI();
    ~CGI();

    std::map<std::string, std::string> assembleCGIHeaders(const HttpRequest &request);
    char                             **assembleCGIEnv(std::map<std::string, std::string> map_envs);
    std::string                        executeCGI(const HttpRequest &request);
    bool programExists(const std::string &path, const HttpRequest &request);
    bool isCGI(const HttpRequest &request, Parser &parser);
};

int         getSIndex(Parser &parser, int serverSize, std::string port);
std::string queryToString(std::vector<std::string> query);
