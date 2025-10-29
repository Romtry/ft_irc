/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:17:58 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/24 15:14:26 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRCServ.hpp"

class Client
{
	private:
		std::string _nick;
		std::string _user;
		bool 		_pass;
		int			_clientsSocket;
		
	public:
		Client(const int fd) : _nick(""), _user(""), _pass(0), _clientsSocket(fd) {}
		~Client();

		std::string	getNick() {return (_nick);}
		std::string getUser() {return (_user);}
		bool		getPass() const {return (_pass);}
		int			getClientSocket() const {return (_clientsSocket);}

		void	setNick(const std::string &nick) {_nick = nick;}
		void	setUser(const std::string &user) {_user = user;}
		void	setPass(const bool pass) {_pass = pass;}

		void	sendMessage(const std::string &message) const;
};
