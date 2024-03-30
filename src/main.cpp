/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:55:10 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/25 16:16:46 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Parser.hpp"
#include "Server.hpp"
#include <csignal>

Server server;

void handleSignal(int signal)
{
    if (signal == SIGINT) {
        std::cout << std::endl;
        Logs::printLog(Logs::INFO, 1, "Stop Server!");
        server.closeServer();
        std::exit(0);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        Logs::printLog(Logs::ERROR, 1, "Invalid number of arguments");
        return (1);
    }

    if(argc == 3){
        std::string arg(argv[2]);
        if (arg == "-a") {
            server.setVerbose(true);
        }else{
            Logs::printLog(Logs::ERROR, 1, "Invalid value of arguments");
        }
        return(1);
    }
    signal(SIGINT, handleSignal);
    server.initParser(argv[1]);
    server.initSockets();
    server.initPoll();
    return (server.run());
}
