/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:02:42 by rmechety          #+#    #+#             */
/*   Updated: 2022/05/24 12:55:57 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "command.hpp"
#include "map"
#include "routes.hpp"
#include "string"
#include "vector"

class servers
{

  private:
	std::string name;
	std::map<std::string, Routes> routes;
	std::vector<Command> options;

  public:
	servers() : name("default"), routes(), options(){};
	servers(const servers &src) : name("default"), routes(), options()
	{
		*this = src;
	};
	servers(std::string name)
	{
		this->name = name;
	};
	~servers()
	{
		routes.clear();
		options.clear();
	};
	servers &operator=(const servers &rhs)
	{
		this->name = rhs.name;
		this->routes = rhs.routes;
		this->options = rhs.options;
		return *this;
	};

	std::string getName() const
	{
		return name;
	}
	void setName(const std::string &name_)
	{
		name = name_;
	}

	std::map<std::string, Routes> &getRoutes()
	{
		return routes;
	}
	void setRoutes(const std::map<std::string, Routes> &routes_)
	{
		routes = routes_;
	}
	void pushroute(Routes &opt)
	{
		routes.insert(std::make_pair(opt.getName(), opt));
	}

	std::vector<Command> getoptions() const
	{
		return options;
	}
	void pushOption(const Command opt)
	{
		options.push_back(opt);
	}

	void setOptions(const std::vector<Command> &options_)
	{
		options = options_;
	}
};