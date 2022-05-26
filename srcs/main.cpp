/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:37:42 by rmechety          #+#    #+#             */
/*   Updated: 2022/05/25 16:37:34 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WHITESPACE "\t "

#include "command.hpp"
#include "fstream"
#include "iostream"
#include "servers.hpp"
#include "sstream"
#include <algorithm>

/**
 * > This function takes a string as an argument and prints it to the console
 *
 * @param str The string to be printed.
 */
void function_name(std::string str)
{
	std::cout << "> : " << str << std::endl;
}
void printc(Command c)
{
	std::cout << "CMD : " << c << std::endl;
}
/**
 * It takes a pair of string and Routes, and prints out the name of the route and the commands in
 * the route
 *
 * @param r This is the pair that is passed in.
 */
void printr(std::pair<std::string, Routes> r)
{
	std::cout << "Name : " << r.second.getName() << std::endl;
	std::vector<Command> c = r.second.getOption();
	std::for_each(c.begin(), c.end(), printc);
}

/**
 * It removes all whitespace from the beginning of a string
 *
 * @param str The string to be trimmed
 */
void skipwp(std::string &str)
{
	int fnof = str.find_first_not_of(WHITESPACE);
	str = str.substr(fnof, str.length() - fnof);
}

/**
 * It takes a string and a delimiter, and returns a vector of strings, each of which is a substring
 * of the original string, delimited by the delimiter
 *
 * @param tosplit The string to split.
 * @param del the delimiter to split on
 *
 * @return A vector of strings
 */
std::vector<std::string> split(std::string tosplit, std::string del)
{
	std::vector<std::string> ret;
	std::string str = tosplit;
	skipwp(str);
	size_t pos = str.find(del);

	while (pos != std::string::npos)
	{
		std::cout << "str : "
				  << ">" << str << "<" << std::endl;
		ret.push_back(str.substr(0, pos));
		str.erase(0, pos + 1);
		pos = str.find(del);
	};
	ret.push_back(str);
	std::for_each(ret.begin(), ret.end(), function_name);
	return ret;
}
void createroute(servers &serv, Routes &actual, std::string &line, bool &inlocation)
{
	Routes r;
	r.setName(line);
	actual = r;
	serv.pushroute(r);
	inlocation = true;
}
void addoptinroutes(servers &serv, Routes &actual, std::string &line)
{
	std::map<std::string, Routes>::iterator it = serv.getRoutes().find(actual.getName());
	if (it == serv.getRoutes().end())
	{
		std::cerr << "No matching road" << std::endl;
		return;
	}
	else
	{

		Command c;
		std::cerr << "ADDR = " << &((*it).second) << std::endl;
		size_t pos = line.find(" ");
		if (pos == std::string::npos)
		{
			std::cerr << "parameters not found for line" << std::endl;
		}
		else
		{
			c.setName(line.substr(0, pos));
			c.setParam(split(line.substr(pos, line.length() - pos), " "));
			(*it).second.pushOption(c);
		}
	};
}

/**
 * It parses the file and creates the server object
 *
 * @param serv the server object that will be filled with the data from the file
 * @param configfile the file to parse
 */
void parsefile(servers &serv, std::fstream &configfile)
{
	bool inserver = false;
	bool inlocation = false;
	std::string line;

	Routes actual;

	while (std::getline(configfile, line))
	{
		std::cout << "line : " << line << std::endl;
		if (line.find("{") != std::string::npos)
		{
		}
		else if (line.find("}") != std::string::npos)
		{
			if (inlocation)
			{
				inlocation = false;
			}
			else if (inserver)
			{
				inserver = false;
			}
		}
		else if (!inserver)
		{
			serv.setName(line);
			inserver = true;
		}
		else if (!inlocation && line.find("location") != std::string::npos)
		{
			createroute(serv, actual, line, inlocation);
		}
		else if (inlocation)
		{
			addoptinroutes(serv, actual, line);
		}
		else if (!inlocation && line.find("location") == std::string::npos)
		{
			Command c;
			std::string name = line.substr(0, line.find(" "));
			std::string param = line.substr(name.length());
			std::cout << "Name = >" << name << "<" << std::endl;
			std::cout << "param = " << param << std::endl;
			c.setName(name);
			c.setParam(split(
				line.substr(((line.find(" ") == std::string::npos) ? 0 : line.find(" "))), " "));
			serv.pushOption(c);
		}
	};
}

/**
 * It reads a file and parses it to create a server object
 *
 * @param ac The number of arguments passed to the program.
 * @param av The argument vector. This is an array of strings, each of which is one of the arguments
 * passed to the program.
 *
 * @return A vector of strings
 */
int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Wrong argument number" << std::endl;
		return 0;
	}
	std::fstream configfile;
	configfile.open(av[1]);
	servers serv;

	parsefile(serv, configfile);

	std::cout << av[1] << std::endl;

	std::cout << "ROUTE :" << std::endl;
	std::for_each(serv.getRoutes().begin(), serv.getRoutes().end(), printr);
	std::vector<Command> c = serv.getoptions();
	std::for_each(c.begin(), c.end(), printc);

	std::cout << "" << std::endl;

	return 0;
}
