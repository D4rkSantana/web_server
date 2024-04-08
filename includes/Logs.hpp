/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:15:30 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/07 20:24:05 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LOGS_HPP
#define LOGS_HPP


#include "./library.hpp"

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