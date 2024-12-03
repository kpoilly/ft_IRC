/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:17:14 by kpoilly           #+#    #+#             */
/*   Updated: 2024/11/20 18:24:36 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(){};
Channel::Channel(const Channel& copy){*this = copy;};

Channel& Channel::operator=(const Channel& copy)
{
	this->_name = copy._name;
	return *this;
};

Channel::~Channel(){};
