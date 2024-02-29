/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:54:01 by lucasmar          #+#    #+#             */
/*   Updated: 2024/02/29 13:33:14 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Libs.hpp"

class Webserv{

	private:
		std::map<int, Data>	_mapServer;
		Socket				_sockets;

	public:
		Webserv(void);
		~Webserv(void);
		bool	setDataServer(std::string pathConf);
		bool	start(void);
		void	stop(void);
};
