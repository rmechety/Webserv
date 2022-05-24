/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:37:42 by rmechety          #+#    #+#             */
/*   Updated: 2022/05/24 12:58:45 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"
#include "fstream"
#include "iostream"
#include "servers.hpp"
#include "sstream"
#include <algorithm>

void function_name(std::string str)
{
	std::cout << "> : " << str << std::endl;
}
void print(Routes r)
{
	std::cout << "Name : " << r.getName() << std::endl;
	std::for_each();
}

std::vector<std::string> split(std::string tosplit, std::string del)
{
	std::vector<std::string> ret;
	std::string str = tosplit;
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

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Wrong argument number" << std::endl;
		return 0;
	}
	std::fstream configfile;
	configfile.open(av[1]);
	std::string line;
	servers serv;

	bool inserver = false;
	bool inlocation = false;
	Routes actual;

	while (std::getline(configfile, line))
	{
		std::cout << "line : " << line << std::endl;
		if (line.find("{") != std::string::npos)
		{
			;
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
			Routes r;
			r.setName(line);
			actual = r;
			serv.pushroute(r);
			inlocation = true;
		}
		else if (inlocation)
		{
			std::map<std::string, Routes>::iterator it = serv.getRoutes().find(actual.getName());
			if (it == serv.getRoutes().end())
			{
				std::cout << "No matching road" << std::endl;
			}
			else
			{
				Command c;
				std::cout << "ADDR = " << &((*it).second) << std::endl;
				size_t pos = line.find(" ");
				if (pos == std::string::npos)
				{
					std::cout << "parameters not found for line" << std::endl;
				}
				c.setName(line.substr(0, pos));
				c.setParam(split(line.substr(pos, line.length() - pos), " "));
				(*it).second.pushOption(c);
			}
		}
		else if (!inlocation && line.find("location") == std::string::npos)
		{
			Command c;
			c.setName(line.substr(0, line.find(" ")));
			serv.pushOption(c);
		}
	}

	std::cout << av[1] << std::endl;

	std::cout << "ROUTE :" << std::endl;
	std::for_each(serv.getRoutes().begin(), serv.getRoutes().end(), print);
	std::cout << "" << std::endl;

	return 0;
}
