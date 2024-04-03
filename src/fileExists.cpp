/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileExists.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:02:45 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/04/03 18:32:03 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.hpp"

bool fileExists(char *path) {
    std::ifstream file(path);
    bool exists = file.good();
    file.close(); 
    return exists; 
}