/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positiveResponse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilva-s <esilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:51:33 by esilva-s          #+#    #+#             */
/*   Updated: 2024/04/22 23:17:03 by esilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef positiveResponse_HPP
#define positiveResponse_HPP

#include "./Libs.hpp"

responseData    processResponse(Request &request);
bool            verifyServerName(Request &request);
bool            verifyRedirection(Request &request);//Não esta correto
bool            methodAllowed(Request &request);
/*
responseData    getHandler(Request &request);//ko
responseData    postHandler(Request &request);//ko
responseData    deleteHandler(Request &request);//ko
*/

#endif