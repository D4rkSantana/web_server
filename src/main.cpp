/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:55:10 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/24 11:34:36 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "library.hpp"


int main(int argc, char *argv[])
{
	const char*	confPath;

	if(argc > 2) {
		Logs::printLog(Logs::ERROR, 0, "Number of invalid arguments!");
		return (1);
	}
	if(argc ==2){
		confPath = argv[1];
	}else{
		confPath = "./config/default.conf";
	}
	if(!CheckFile::check(confPath))
		return(1);

    
    return (1);
}
