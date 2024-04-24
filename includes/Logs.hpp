/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:15:30 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/24 11:11:40 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LOGS_HPP
#define LOGS_HPP


#include "./library.hpp"

#define COLOR_RED     "\x1b[31m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

class Logs{

	public:
		enum typeLog{
			INFO,
			WARNING,
			ERROR,
			VERBOSE
		};

		Logs(void);
		~Logs(void);
		static void	printLog(typeLog type, int numberLog, std::string message);

	private:
		static	std::string _fullData;
		static 	std::string	_getFullData(void);

};

#endif