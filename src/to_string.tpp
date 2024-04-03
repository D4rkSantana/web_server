/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:00:13 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/03 16:51:54 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.hpp"

//verificar melhor se esta funcionando 
template <typename T>

std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}