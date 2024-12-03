/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:16:24 by kpoilly           #+#    #+#             */
/*   Updated: 2024/11/20 17:08:58 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"

class Channel
{
	private:
		std::string _name;

	public:
		Channel();
		Channel(const Channel& copy);
		Channel& operator=(const Channel& copy);
		~Channel();
};

#endif