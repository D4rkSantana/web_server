/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:54:01 by lucasmar          #+#    #+#             */
/*   Updated: 2024/04/11 11:16:44 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Libs.hpp"

class WebServ
{

	private:
		Data _data;

	public:
		WebServ(void);
		~WebServ(void);
		bool setDataServer(const char *pathConf);
		bool connect(void);
		int start(void);
		void stop(void);
};
