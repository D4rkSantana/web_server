/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConf.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:59:47 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/09 19:04:05 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ParseConf_HPP
#define ParseConf_HPP


#include "./library.hpp"


/* 
class ParseConf{
    private:
        ParseConf();



};
*/

std::string readFileContents(const std::string& filename);
std::string extractServerParams(const std::string& serverBlock);
std::vector<std::string> extractLocations(const std::string& serverBlock);
std::vector<std::string> separateServerBlocks(const std::string& config);
std::string getFirstWord(const std::string& text, int position);
int countWordOccurrencesLine(const std::string& text, const std::string& word);
std::string getParameterValue(const std::string& text, const std::string& parameter);


#endif
