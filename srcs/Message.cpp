/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:16:24 by kpoilly           #+#    #+#             */
/*   Updated: 2024/12/02 18:24:57 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Message.hpp"

//Constructors-Destructors
Message::Message(std::string const & content)
{
	std::vector<std::string>	elements;
	std::stringstream			stream(content, std::stringstream::in);
	std::string					element;

	while (stream >> element)
		elements.push_back(element);

	if (elements.size() == 0 || (elements.size() == 1 && elements[0][0] == ':'))
		throw Parsing(ERR_NEEDMOREPARAMS);
	
	
	if (elements[0][0] == ':')
	{
		this->_prefix = elements[0];
		this->_command = elements[1];
	}
	else
	{
		this->_prefix = "";
		this->_command = elements[0];
	}

	elements.erase(elements.begin());
	elements.erase(elements.begin());

	std::vector<std::string>::const_iterator it;
	for (it = elements.begin(); it < elements.end(); ++it)
		this->_parameters.push_back(*it);
};

Message::~Message() {};
//------


//Operator overloads
Message& Message::operator=(const Message& copy)
{
	_prefix = copy._prefix;
	_command = copy._command;
	_parameters = copy._parameters;
};
//------
