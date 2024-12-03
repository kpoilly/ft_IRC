/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:17:53 by kpoilly           #+#    #+#             */
/*   Updated: 2024/12/03 18:49:44 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "ft_irc.hpp"

class User
{
	private:
		int				_fd;
		int				_port;
		unsigned int	_size;
		sockaddr_in		_address;
		std::string		_ip;

		std::string 	_nickname;
		std::string 	_realname;

		std::string		_buffer;

	public:
		//Constructors-Destructors
		User();
		~User();

		//Setters
		void		be_accepted(int server_fd);
		void		set_nickname(std::string const &nickname);
		void		set_realname(std::string const &realname);
		void		set_buffer(std::string const & content);
		
		//Getters
		int			get_fd() const;
		std::string	get_buffer() const;
		std::string	get_nickname() const;
		std::string	get_realname() const;

		//Exceptions
		class Quit : public std::exception {};
		class Refused : public std::exception {};
};

#endif