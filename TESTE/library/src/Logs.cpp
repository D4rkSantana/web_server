/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logs.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasmar < lucasmar@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:13:52 by lucasmar          #+#    #+#             */
/*   Updated: 2024/02/26 20:35:54 by lucasmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libs.hpp"


Logs::Logs(void){};
Logs::~Logs(void){};


std::string Logs::_getFullData(void){
	std::time_t currentTime;
	std::tm    *localTime;
	char        timeStr[24];

	currentTime = std::time(0);
	localTime   = std::localtime(&currentTime);
	std::strftime(timeStr, sizeof(timeStr), "[%d/%m/%Y - %H:%M:%S]", localTime);
	return (std::string(timeStr));
}

void Logs::printLog(typeLog type, int numberLog, std::string message){
	std::string color;
	std::string strType;

	switch (type){
		case Logs::ERROR:
			color = COLOR_RED;
			strType = "ERROR";
			break;
		case Logs::INFO:
			color = COLOR_BLUE;
			strType = "INFO";
			break;
		case Logs::WARNING:
			color = COLOR_YELLOW;
			strType = "WARNING";
			break;
		case Logs::VERBOSE:
			color = COLOR_GREEN;
			strType = "VERBOSE";
			break;
		default:
			break;
	}

	std::cout
		<< color
		<< "\n - "
		<< Logs::_getFullData()
		<< " "
		<< strType
		<< ": "
		<< numberLog
		<< " - "
		<< message
		<< "\n"
		<< COLOR_RESET
		<< std::endl;
}


// std::string Ierror::LogEntry::_timestamp(void){
//     std::time_t currentTime;
//     std::tm    *localTime;
//     char        timeStr[24];

//     currentTime = std::time(0);
//     localTime   = std::localtime(&currentTime);
//     std::strftime(timeStr, sizeof(timeStr), "[%d/%m/%Y - %H:%M:%S]", localTime);
//     return (std::string(timeStr));
// }



// const std::string Ierror::_colors[4]={
// 	"\033[36m",
// 	"\033[33m",
// 	"\033[31m",
// 	"\033[32m"};


// const std::string Ierror::_levelStrings[4]={
// 	"INFO",
// 	"WARNING",
// 	"ERROR",
// 	"VERBOSE"};

// Ierror::LogEntry Ierror::info(INFO);
// Ierror::LogEntry Ierror::warning(WARNING);
// Ierror::LogEntry Ierror::error(ERROR);
// Ierror::LogEntry Ierror::verbose(VERBOSE);

// Ierror::Ierror(void) {}

// Ierror::~Ierror(void) {}

// std::string Ierror::LogEntry::_timestamp(void){
//     std::time_t currentTime;
//     std::tm    *localTime;
//     char        timeStr[24];

//     currentTime = std::time(0);
//     localTime   = std::localtime(&currentTime);
//     std::strftime(timeStr, sizeof(timeStr), "[%d/%m/%Y - %H:%M:%S]", localTime);
//     return (std::string(timeStr));
// }

// std::string Ierror::LogEntry::_addHeader(void)
// {
//     std::string       header;
//     std::stringstream ss;

//     ss << _colors[_level] << _timestamp() << "  ";
//     ss << std::left << std::setw(8) << _levelStrings[_level] << ": ";
//     header = ss.str();
//     return (header);
// }

// Ierror::LogEntry::LogEntry(LogLevel level) : _level(level) {}

// Ierror::LogEntry::~LogEntry(void) {}

// Ierror::LogEntry &Ierror::LogEntry::operator<<(std::ostream &(*manipulator)(std::ostream &))
// {
//     if (_level == ERROR)
//         std::cerr << _addHeader() << _stream.str() << RESET_COLOR << manipulator;
//     else
//         std::cout << _addHeader() << _stream.str() << RESET_COLOR << manipulator;
//     _stream.str("");
//     _stream.clear();
//     return (*this);
// }
