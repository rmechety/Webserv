/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:01:34 by rmechety          #+#    #+#             */
/*   Updated: 2022/05/24 12:39:00 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "command.hpp"
#include "string"

class Routes
{
  private:
	std::string name;
	std::vector<Command> option;

  public:
	Routes() : name("name"), option()
	{
		std::cout << option.capacity() << std::endl;
		std::cout << option.size() << std::endl;
	};
	Routes(const Routes &src) : name("name"), option()
	{
		*this = src;
	};
	~Routes(){};
	Routes &operator=(const Routes &rhs)
	{

		name = rhs.name;
		option = rhs.option;
		std::cout << option.capacity() << std::endl;
		std::cout << option.size() << std::endl;

		return *this;
	}
	std::string getName() const
	{
		return name;
	}
	void setName(const std::string &name_)
	{
		name = name_;
	}

	std::vector<Command> getOption() const
	{
		return option;
	}
	void pushOption(const Command option_)
	{
		option.push_back(option_);
	}
	void setOption(const std::vector<Command> &option_)
	{
		option = option_;
	}
	bool operator<(const Routes &rhs)
	{
		int ret = this->name.compare(rhs.getName());
		return ret < 0;
	}
};
bool operator<(const Routes &x, const Routes &y)
{
	int ret = x.getName().compare(y.getName());
	return ret < 0;
};