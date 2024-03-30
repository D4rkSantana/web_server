/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:00:13 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/29 22:48:52 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.hpp"


template <typename T>
std::string to_string(T s)
{
    std::ostringstream oss;
    oss << s;
    return oss.str();
}
