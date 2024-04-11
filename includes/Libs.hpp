/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:13:52 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/11 19:49:48 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// my libs
#include "Logs.hpp"
#include "WebServ.hpp"
#include "Data.hpp"
#include "CheckFile.hpp"
#include "ParseConf.hpp"
#include "Socket.hpp"
#include "template.tpp"

#include <arpa/inet.h>

#include <ctime>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <fcntl.h>
#include <fstream>

#include <iomanip>
#include <iostream>

#include <map>

#include <netinet/in.h>
#include <netdb.h>

#include <sys/socket.h>
#include <string>
#include <sstream>
#include <stack>
#include <set>

#include <vector>

#include <unistd.h>

// defines
#define COLOR_RED "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"
