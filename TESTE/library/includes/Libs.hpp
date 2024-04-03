/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:13:52 by lucasmar          #+#    #+#             */
/*   Updated: 2024/03/01 17:25:21 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// my libs
#include "Logs.hpp"
#include "Webserv.hpp"
#include "Socket.hpp"
#include "Data.hpp"


//padrão libs

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <csignal>
#include <cstdlib>
#include <map>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <vector>


// defines

#define COLOR_RED     "\x1b[31m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"
