/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:27:36 by rdedola           #+#    #+#             */
/*   Updated: 2026/02/04 13:12:50 by rdedola          ###   ########.fr       */
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
#include <stdlib.h>
#include <sstream>

#include "Client.hpp"
#include "defines.hpp"

class Client;
class Channel;

class IRCServ
{
	public:
		IRCServ(const unsigned int port, const std::string &password);
		~IRCServ();

		void		Start();
		void		AddClient();
		void		Message(unsigned int i);

		void		parseCommand(Client *client, const std::string &buffer);
		void		execCommand(Client *client);

		void		CMDpass(Client *client, const std::string &buffer) const;
		void		CMDnick(Client *client, const std::string &buffer) const;
		static void CMDuser(Client *client);
		void		CMDjoin(Client *client, std::string &buffer);
		static void CMDtopic(const Client *client, std::string &buffer) ;

		void		CMDpart(Client *client, const std::string &buffer);
		void		ActuChan(const Channel *channel, Client *client, unsigned int index_chan);



		void		CMDkick(Client *client, std::string &buffer);
		void		CMDprivmsg(const Client *client, std::string &buffer) const;
		void		CMDmode(const Client *client, std::string &buffer);
		void		CMDinvite(Client *client, std::string &buffer);

	private:
		const unsigned int			_port;
		const std::string			_password;
		std::vector<pollfd>			_socket;
		std::vector<Client *>		_clients;
		std::vector<Channel *>		_channels;
};
