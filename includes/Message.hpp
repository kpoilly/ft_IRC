/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:16:24 by kpoilly           #+#    #+#             */
/*   Updated: 2024/11/30 20:31:31 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# define ERR_UNKNOWNCOMMAND	421
# define ERR_NEEDMOREPARAMS	461

# include "ft_irc.hpp"

class Message
{
	private:
		std::string					_prefix;	// optional
		std::string					_command;	// e.g. JOIN, PRIVMSG, PING
		std::vector<std::string>	_parameters;// e.g. message content
	
	public:
		//Constructors-Destructors
		Message(std::string const & message);
		~Message();
		
		//Operator overloads
		Message& operator=(const Message& copy);

		//Exceptions
		class Parsing : public std::exception {};
		class Parsing : public std::exception {
			public:
				Parsing(int type) throw() : _type(type) {}
				~Parsing() throw() {}

				int get_type() const { return _type; }

			private:
				int _type;
		};
};

#endif