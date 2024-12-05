/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpoilly <kpoilly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:08:36 by kpoilly           #+#    #+#             */
/*   Updated: 2024/12/05 15:55:20 by kpoilly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# include <iostream>
# include <sstream>
# include <cstring>
# include <vector>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <poll.h>
# include <csignal>
# include <cstdio>
# include <stdlib.h>
# include <signal.h>

# include "server.hpp"
# include "client.hpp"
# include "channel.hpp"
# include "user.hpp"

# define DEFAULT_IRC_PORT	6667
# define MAX_CLIENTS_NB		5

//codes
# define RPL_VERSION		"1.0"
# define RPL_ISUPPORT		"005"
# define RPL_MOTDSTART		"375"
# define RPL_WHOISUSER		"311"
# define RPL_WHOISCHANNELS	"319"
# define RPL_ENDOFWHOIS		"318"
# define RPL_CHANNELMODEIS	"324"
# define RPL_UMODEIS		"221"

//errors
# define ERR_NICKNAMEINUSE		"433"
# define ERR_NONICKNAMEGIVEN	"431"
# define ERR_NOSUCHNICK 		"401"
# define ERR_NOSUCHCHANNEL		"403"
# define ERR_NOMOTD				"422"

class Server;

void	parsing(Server& server, int client_fd, std::string cmd);

//utils
void	stoc(int client_fd, std::string msg);
void	manage_signals(void);
void 	disconnectServer(Server &server);

//commands
void	cap(int client_fd, std::string arg);
void	pong(int client_fd, std::string arg);
void	version(int client_fd);
void	motd(Server &server, int client_fd);
void	user(Server& server, int client_fd, std::string name, std::string IP, std::string real);
void	nick(Server& server, int client_fd, std::string arg);
void	whois(Server &server, int client_fd, std::string arg);

#endif