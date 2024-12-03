/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:31:27 by kpoilly           #+#    #+#             */
/*   Updated: 2024/12/03 18:49:54 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

//Constructors-Destructors
User::User() : _size(sizeof(this->_address))
{
	memset(&this->_address, 0, this->_size);
};

User::~User() {};
//------


//Setters
void User::be_accepted(int server_fd)
{
	this->_fd = accept(server_fd, (struct sockaddr*) &this->_address, &this->_size);
	if (_fd >= 0)
	{
		this->_ip = inet_ntoa(this->_address.sin_addr);
		this->_port = ntohs(this->_address.sin_port);

		//To be deleted
		std::cout << "Server accepted a new client:" << std::endl;
		std::cout << "fd: " << this->_fd << std::endl;
		std::cout << "memoryAdress: " << static_cast<void*>(&this->_address) << std::endl;
		std::cout << "size: " << this->_size << std::endl;
		std::cout << "ip: " << this->_ip << std::endl;
		std::cout << "port: " << this->_port << std::endl << std::endl;
		//------
	}
	else
		throw Refused();
};

void User::set_nickname(std::string const & nickname)
{
	this->_nickname = nickname;
};

void User::set_realname(std::string const & realname)
{
	this->_realname = realname;
};

void User::set_buffer(std::string const & content)
{
	this->_buffer = content;
};
//------


//Getters
int User::get_fd() const
{
	return this->_fd;
};

std::string User::get_buffer() const
{
	return this->_buffer;
};

std::string User::get_nickname() const
{
	return this->_nickname;
};

std::string User::get_realname() const
{
	return this->_realname;
};
//------
