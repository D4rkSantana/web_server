/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:24:34 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/11 09:24:35 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FT_TO_STRING_TPP
#define FT_TO_STRING_TPP

#include "./Libs.hpp"

template <typename T>

std::string to_string(const T &value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

#endif