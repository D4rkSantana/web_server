/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isLineEmpty.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:28:53 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/29 22:28:57 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.hpp"

bool isLineEmpty(const std::string& text) {
    size_t  i;
    
    i  = 0;
    while(i < text.length()){
        if (!isspace(text[i]))
            return false;
        i ++;
    } 
    return true;
}
