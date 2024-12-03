/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:30:58 by kpoilly           #+#    #+#             */
/*   Updated: 2024/12/03 18:41:57 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

//Constructors-Destructors
Server::Server(int port, std::string const &password)
{
	//Open socket on a file descriptor
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd < 0)
	{
		std::perror("socket()");
		throw std::exception();
	}

	//Configure socket and password
	this->_port = port;
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(this->_port);
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_password = password;
	this->_message_of_day = "Bienvenue sur Discord 2.0!";

	//Add socket options
	this->_socket_options = 1;
	if (setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR,
		&this->_socket_options,  sizeof(_socket_options)) < 0)
	{
		close(this->_fd);
		std::perror("setsockopt()");
		throw std::exception();
	}

	//Bing socket on a network and a port
	if (bind(this->_fd, (struct sockaddr*)&this->_address, sizeof(this->_address)))
	{
		close(this->_fd);
		std::perror("bind()");
		throw std::exception();
	}

	//Open slots for clients connections
	if (listen(this->_fd, 42) < 0)
	{
		close(this->_fd);
		std::perror("listen()");
		throw std::exception();
	}

	//Add server fd in the pollfd
	pollfd serverPollfd = {this->_fd, POLLIN, 0};
	this->_pollfd.push_back(serverPollfd);

	std::cout << "\033[1;32mServer is up and listening on port " << port << "\033[0m" << std::endl;
};

Server::~Server()
{

	for (size_t i = 0; i < this->_users.size(); ++i)
		delete this->_users[i];
	this->_users.clear();

	for (size_t i = 0; i < this->_channels.size(); ++i)
		delete this->_channels[i];
	this->_channels.clear();

	std::vector<pollfd>::iterator pollfd;
	for (pollfd = this->_pollfd.begin(); pollfd < this->_pollfd.end(); ++pollfd)
	{
		std::string quit_msg = ":localhost QUIT :Server shutting down\n";
		send(pollfd->fd, quit_msg.c_str(), quit_msg.length(), 0);
		close(pollfd->fd);
	}
	this->_pollfd.clear();
}
//------


//Getters
int Server::get_fd() const
{
	return this->_fd;
};

int Server::get_port() const
{
	return this->_port;
};

sockaddr_in Server::get_address() const
{
	return this->_address;
};

std::string Server::get_password() const
{
	return this->_password;
};

std::string Server::get_message_of_day() const
{
	return this->_message_of_day;
};

std::vector<User*> Server::get_users() const
{
	return this->_users;
};

User* Server::get_user(int user_index) const
{
	return this->_users[user_index];
};

std::vector<Channel*> Server::get_channels() const
{
	return this->_channels;
};

Channel* Server::get_channel(int channel_index) const
{
	return this->_channels[channel_index];
};

std::vector<pollfd> Server::get_pollfd() const
{
	return this->_pollfd;
};
//------


//IRC-communication
int Server::open_poll()
{
	return poll(this->_pollfd.data(), this->_pollfd.size(), -1); // -1: no timeout
}

void Server::handle_poll(int pollfd_i)
{
	if (this->_pollfd[pollfd_i].revents & POLLIN) { // There is something to read
		if (this->_pollfd[pollfd_i].fd == this->_fd) { // Read from server = new user to accept
			this->user_connect();
		}
		else { // Read from user
			int user_i = pollfd_i - 1;
			char buffer[1024];
			ssize_t bytes_read = recv(this->_users[user_i]->get_fd(), buffer, sizeof(buffer), 0);

			if (bytes_read <= 0) // Disconnection message
				throw User::Quit();
			else // Other messages
			{
				buffer[bytes_read] = '\0';

				std::string new_buffer = _users[user_i]->get_buffer() + buffer;
				_users[user_i]->set_buffer(new_buffer);
				if (new_buffer.find('\n') != std::string::npos
					|| new_buffer.find('\r') != std::string::npos)
				{
					this->communicate(_users[user_i]);
					_users[user_i]->set_buffer("");
				}
			}
		}
	}
}

void Server::communicate(User* user)
{
	Message message(user->get_buffer());

	// here, read the user message, apply the command(s) and answer what's needed...
}
//------


//Setters
void Server::user_connect()
{
	User* newUser = new User;
	newUser->be_accepted(this->_fd);
	this->_users.push_back(newUser);

	pollfd new_user_pollfd = {newUser->get_fd(), POLLIN, 0};
	this->_pollfd.push_back(new_user_pollfd);
};

void Server::user_quit(int user_index)
{
	int pollfd_index = user_index + 1;

	close(this->_pollfd[pollfd_index].fd);
	this->_pollfd.erase(this->_pollfd.begin() + pollfd_index);

	delete this->_users[user_index];
	this->_users.erase(this->_users.begin() + user_index);
};
//------


//Utils
bool Server::nickname_exists_yet(std::string nickname)
{
	for(size_t i = 0; i < this->_users.size(); i++)
	{
		if (this->_users[i]->get_nickname() == nickname)
			return true;
	}
	return false;
};
//------
