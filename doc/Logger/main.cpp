/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:25:47 by ryoshio-          #+#    #+#             */
/*   Updated: 2024/02/29 05:27:22 by ryoshio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <sstream>
#include <ctime>

#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

class Logger {
    private:
        Logger(void);
        ~Logger(void);
        static std::string _timestamp(void);
        static std::string _addHeader(int code, std::string type);

    public:
        static void info(int id, const std::string message);
        static void warning(int id, const std::string message);
        static void verbose(int id, const std::string message);
        static void error(int id, const std::string message);

};

Logger::Logger() {}
Logger::~Logger() {}

std::string Logger::_timestamp() {
    std::time_t currentTime;
    std::tm    *localTime;
    char        timeStr[24];

    currentTime = std::time(0);
    localTime   = std::localtime(&currentTime);
    std::strftime(timeStr, sizeof(timeStr), "%d/%m/%Y - %H:%M:%S", localTime);
    return (std::string(timeStr));
}

std::string Logger::_addHeader(int code, std::string type) {
    std::string       header;
    std::stringstream ss;

    ss << "[" <<_timestamp() << " - " << type << ":" << code << "] - ";
    header = ss.str();
    return (header);
}

void Logger::info(int id, const std::string message) {
    std::cout << GREEN << _addHeader(id, "INFO")  << message << RESET << std::endl;
}

void Logger::warning(int id, const std::string message) {
    std::cout << YELLOW << _addHeader(id, "WARNING")  << message << RESET << std::endl;
}

void Logger::verbose(int id, const std::string message) {
    std::cout << WHITE << _addHeader(id, "VERBOSE")  << message << RESET << std::endl;
}

void Logger::error(int id, const std::string message) {
    std::cout << RED << _addHeader(id, "ERROR")  << message << RESET << std::endl;
}


int main(void)
{

    Logger::info(200, "Hello World");
    Logger::warning(404, "Not Found");
    Logger::verbose(200, "Hello World");
    Logger::error(500, "Internal Server Error");
    return (0);
}
