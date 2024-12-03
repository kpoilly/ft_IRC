/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:20:15 by kpoilly           #+#    #+#             */
/*   Updated: 2024/12/03 18:43:16 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

class User;

class Server
{
	private:
		int						_fd;
		int						_port;
		int						_socket_options;
		sockaddr_in				_address;
		std::string				_password;
		std::string				_message_of_day;

		std::vector<User*>		_users;
		std::vector<Channel*> 	_channels;

		std::vector<pollfd>		_pollfd;

	public:
		//Constructors-Destructors
		Server(int port, std::string const &password = NULL);
		~Server();

		//Getters
		int						get_fd() const;
		int						get_port() const;
		int						get_socket_options() const;
		sockaddr_in				get_address() const;
		std::string				get_password() const;
		std::string				get_message_of_day() const;

		std::vector<User*>		get_users() const;
		User*					get_user(int user_index) const;
		std::vector<Channel*>	get_channels() const;
		Channel*				get_channel(int channel_index) const;

		std::vector<pollfd>		get_pollfd() const;

		//Utils
		bool					nickname_exists_yet(std::string nickname);

		//IRC-communication
		int						open_poll();
		void					handle_poll(int index);
		void					communicate(User* user);
		void					send_to_all(std::string arg);

		//Setters
		void					user_connect();
		void					user_quit(int user_index);

		//Prints
		void					print_channels() const;	// To be implemented...
		void					print_users() const;	// To be implemented...
};

#endif