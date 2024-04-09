/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:58:34 by lucasmar          #+#    #+#             */
/*   Updated: 2024/02/26 22:24:05 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef DATA_HPP
# define DATA_HPP


#include "./library.hpp"

//padrão libs


class Data{

	private:
		std::string	_serverName;
		std::string	_index;
		std::string	_root;
		int	_clientMaxBodySize;
		int	_port;
		std::string	_errorPage;

	public:
		Data(void);
		~Data(void);

		void setServerName(std::string serverName);
		void setIndex(std::string index);
		void setRoot(std::string root);
		void setClientMaxBodySize(int clientMaxBodySize);
		void setPort(int port);
		void setErrorPage(std::string errorPage);

		std::string getServerName(void);
		std::string getIndex(void);
		std::string getRoot(void);
		int getClientMaxBodySize(void);
		int getPort(void);
		std::string getErrorPage(void);
};

#endif