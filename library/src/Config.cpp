#include "../include/Config.hpp"

Config::Config(void): _name_file("default_config"), _raw_config(" "), _raw_config_open(false)
{
	std::cout << "Config: Default constructor called" << std::endl;
}

Config::Config(std::string name_file): _name_file(name_file), _raw_config(" "), _raw_config_open(false)
{
	std::cout << "Config: Constructor with parameter called" << std::endl;
}

Config::Config(Config const &copy): _name_file(copy.getNameFile()), _raw_config(copy.getRawConfig()), _raw_config_open(copy.getRawConfigOpen())
{
	std::cout << "Config: Copy constructor called" << std::endl;
	*this = copy;
}

Config::~Config(void)
{
	std::cout << "Config: Destructor called" << std::endl;
}

Config &Config::operator=(Config const &rhs)
{
	std::cout << "Config: Copy assignment operator" << std::endl;

	if (this != &rhs)
	{
		this->_name_file = rhs._name_file;
		this->_raw_config = rhs._raw_config;
		this->_raw_config_open = rhs._raw_config_open;
	}
	return (*this);
}


// Work funcitions

bool		Config::readConfig(void)
{
	std::ifstream file(this->_name_file.c_str());

	if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo \"" << this->_name_file << "\"" << std::endl;
        return false;
    }
	std::string line;
	std::string	content;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
	this->_raw_config = content;
	this->_raw_config_open = true;

	file.close();
	return (false);
}


// Getters

std::string Config::getNameFile(void) const
{
	return (this->_name_file);
}

std::string Config::getRawConfig(void) const
{
	if (this->_raw_config_open)
		return (this->_raw_config);
	return ("none");
}

bool Config::getRawConfigOpen(void) const
{
	return (this->_raw_config_open);
}

/*
const char *Config::GradeTooHighException::what() const throw()
{
	return ("Grade too hight\n");
}

const char *Config::GradeTooLowException::what() const throw()
{
	return ("Grade too low\n");
}
*/

std::ostream &operator<<(std::ostream &o, Config const &config)
{
	o << config.getNameFile() << std::endl;
	return (o);
} 