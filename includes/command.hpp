/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:28:56 by rmechety          #+#    #+#             */
/*   Updated: 2022/05/24 13:56:51 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map"
#include "string"
#include "vector"

class Command
{
  private:
	std::string name;
	std::vector<std::string> param;

  public:
	Command() : name("def"), param()
	{
		;
	};
	Command(const Command &src) : name("def"), param()
	{
		*this = src;
	};
	Command &operator=(const Command &rhs)
	{
		name = rhs.name;
		param = rhs.param;
		return *this;
	};
	~Command()
	{
		param.clear();
	};

	std::string getName() const
	{
		return name;
	}
	void setName(const std::string &name_)
	{
		name = name_;
	}

	std::vector<std::string> getParam() const
	{
		return param;
	}
	void setParam(const std::vector<std::string> &param_)
	{
		param = param_;
	}
};
void print(std::string str)
{
	std::cout << str << std::endl;
}

std::ostream &operator<<(std::ostream &o, Command const &rhs)
{
	o << rhs.getName() << std::endl;
	std::vector<std::string> tmpparam = rhs.getParam();

	std::for_each(tmpparam.begin(), tmpparam.end(), print);
};