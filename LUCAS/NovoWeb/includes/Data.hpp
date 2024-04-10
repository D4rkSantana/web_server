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


#pragma once

#include "./Libs.hpp"

class Data{

	//private:

	public:
		Data(void);
		~Data(void);
		bool	start(std::string pathConf);
};
