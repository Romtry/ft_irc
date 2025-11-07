/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:27:36 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/30 15:17:54 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <poll.h>
#include <exception>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include <algorithm>
#include <sstream>

#include "Client.hpp"
#include "defines.hpp"

class Client;
class Channel;

class IRCServ
{
	public:
		IRCServ(const unsigned int port, const std::string &password);

		void Start();
		void AddClient();
		void Message(unsigned int i);

		void parseCommand(Client *client, const std::string &buffer);
		void CMDpass(unsigned int clientindex, std::string &buffer);
		void CMDnick(unsigned int clientindex, std::string &buffer);
		void CMDuser(unsigned int clientindex, std::string &buffer);
		void CMDjoin(unsigned int clientindex, std::string &buffer);

	private:
		const unsigned int			_port;
		const std::string			_password;
		std::vector<pollfd>			_socket;
		std::vector<Client *>		_clients;
		std::vector<Channel *>		_channels;
};
