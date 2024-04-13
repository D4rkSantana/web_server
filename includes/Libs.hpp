/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:13:52 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/13 12:17:28 by ryoshio-         ###   ########.fr       */
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






// my libs
#include "Data.hpp"
#include "Logs.hpp"
#include "CheckFile.hpp"
#include "ParseConf.hpp"
#include "Socket.hpp"
#include "Poll.hpp"
#include "clientProcess.hpp"
#include "WebServ.hpp"
#include "template.tpp"




# endif