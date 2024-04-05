/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:57:54 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/05 10:49:57 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./library/includes/Libs.hpp"
void	handleStop(int signal);

Webserv	webServer;

int	main(int argc, char *argv[]){
	std::string confPath;

	if(argc > 2) {
		Logs::printLog(Logs::ERROR, 0, "Number of invalid arguments!");
		return (1);
	}
	if(argc ==2){
		confPath = argv[1];
	}else{
		confPath = "./default.conf";
	}
	signal(SIGINT, handleStop);
	if(!webServer.setDataServer(confPath)){
		Logs::printLog(Logs::ERROR, 1, "Erro set data server");
	}else if(!webServer.start()){
		Logs::printLog(Logs::ERROR, 2, "Erro start server");
	}
	return(0);
}

void	handleStop(int signal){
    if (signal == SIGINT) {
		webServer.stop();
		Logs::printLog(Logs::INFO, 3, "Stop server :(");
		std::exit(0);
	}
}
