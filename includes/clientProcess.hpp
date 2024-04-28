/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientProcess.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:10:21 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/28 13:55:54 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef clientProcess_HPP
#define clientProcess_HPP

#include "./Libs.hpp"

void        processClientData(int fd);
std::string getStatusCodes(std::string status);
std::string readClientData(int fd);
std::string mergeStrVector(std::vector<std::string> vec, std::string delimiter);
void        sendResponse(int fd, responseData res);

#endif
