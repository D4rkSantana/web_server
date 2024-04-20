/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:13:52 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/19 20:42:06 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Libs_HPP
#define Libs_HPP


#include <algorithm>
#include <arpa/inet.h>

#include <ctime>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <cstdlib>

#include <fcntl.h>
#include <fstream>

#include <iomanip>
#include <iostream>

#include <map>

#include <netdb.h>
#include <netinet/in.h>

#include <set>
#include <stack>
#include <string>
#include <sstream>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <vector>

#include <unistd.h>

// defines
#define COLOR_RED "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

//
#define DEFAULT_ROOT "www/html"

//mudar de nome?
#define OK 200
#define NO_CONTENT 204
#define PERMANENT_REDIRECT 301
#define TEMPORARY_REDIRECT 302
#define BAD_REQUEST 400
#define FORBIDDEN 403
#define NOT_FOUND 404
#define METHOD_NOT_ALLOWED 405
#define ENTITY_TOO_LARGE 413
#define INTERNAL_SERVER_ERROR 500
#define HTTP_VERSION_NOT_SUPPORTED 505

typedef std::map<std::string, std::vector<std::string> > dic;

typedef struct
{
	dic *server;
	dic **locations;
} conf_servers;

typedef struct
{
    int         status;
    std::string content;
    std::string statusCode;
    std::string contentType;
    int         contentLength;
    std::string location;
} responseData;

// my libs
#include "Logs.hpp"
#include "CheckFile.hpp"
#include "ParseConf.hpp"
#include "Socket.hpp"
#include "Poll.hpp"
#include "WebServ.hpp"
#include "clientProcess.hpp"
#include "Request.hpp"
#include "template.tpp"

extern WebServ 	webServer;


# endif