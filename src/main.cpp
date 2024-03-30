/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:55:10 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/03/30 01:36:04 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "library.hpp"


int main(int argc, char *argv[])
{
   CheckArg  checkarg(argc, argv);

   if(!checkarg.getStatus())
        return (1);
    
    return (1);
}
