/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_logger.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:42:26 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/02/29 17:30:06 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/test.hpp"

void test_logs(void)
{
    std::cout << "Test Logs" << std::endl;
    Logs::printLog(Logs::INFO, 200, "Hello World");
    Logs::printLog(Logs::WARNING, 404, "Not Found");
    Logs::printLog(Logs::VERBOSE,200, "Hello World");
    Logs::printLog(Logs::ERROR, 500, "Internal Server Error");
    std::cout << "End Logger" << std::endl;
}