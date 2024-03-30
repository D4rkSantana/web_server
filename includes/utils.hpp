/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:54:11 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/26 10:02:55 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef UTILS_HPP
#define UTILS_HPP


#include "Constants.hpp"
#include "Libs.hpp"
#include "Parser.hpp"

responseData getJson(std::string body, int status);
responseData getContent(std::string root, std::string file, int status);
std::string  extractFileExtension(std::string file);
responseData setResponseData(int         status,
                             std::string contentType,
                             std::string content,
                             int         contentLength,
                             std::string location = "");
std::string  vector_join(std::vector<std::string> vec, std::string delimiter);


std::string getDir();
std::string getBin(const std::string &url);




template <typename T>
std::string to_string(T s);
#include "../src/to_string.tpp"



#endif