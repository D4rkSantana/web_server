/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:15:30 by lucasmar          #+#    #+#             */
/*   Updated: 2024/02/29 15:10:55 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Libs.hpp"

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
