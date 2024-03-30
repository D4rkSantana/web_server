/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:00:13 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/26 10:03:18 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"


template <typename T>
std::string to_string(T s)
{
    std::ostringstream oss;
    oss << s;
    return oss.str();
}
