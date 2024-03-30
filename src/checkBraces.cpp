/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkBraces.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:28:41 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/29 22:28:44 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "library.hpp"

bool checkBraces(const std::string& text) {
    std::stack<char> stack;
    char c;
    size_t i;

    i = 0;
    while (i < text.length()) {
        c = text[i];
        if (c == '{') {
            stack.push(c);
        } else if (c == '}') {
            if (stack.empty() || stack.top() != '{') {
                return false; 
            }
            stack.pop();
        }
        i ++;
    }

    return stack.empty(); 
}