/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:54:01 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/11 20:03:19 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Libs.hpp"

class Socket;

class WebServ
{

	private:
		Data						_data;
		std::vector<Socket *>		_sockets;

	public:
		WebServ(void);
		~WebServ(void);
		bool						setDataServer(const char *pathConf);
		bool						connect(void);
		int							start(void);
		void						stop(void);
		void						finish(void);
		size_t						getQtSevers(void);
		std::vector<std::string>	getServerValue(size_t index, std::string key);
};
