/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:17:58 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/29 14:00:49 by rdedola          ###   ########.fr       */
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
		bool		_isRegister;
		int			_clientsSocket;
		
	public:
		Client(const int fd) : _nick(""), _user(""), _pass(0), _isRegister(0), _clientsSocket(fd) {}
		~Client();

		std::string	getNick() const {return (_nick);}
		std::string getUser() const {return (_user);}
		bool		getPass() const {return (_pass);}
		bool		getisregister() const {return (_isRegister);}
		int			getClientSocket() const {return (_clientsSocket);}


		void	setNick(const std::string &nick) {_nick = nick;}
		void	setUser(const std::string &user) {_user = user;}
		void	setPass(const bool pass) {_pass = pass;}
		void	setIsRegister(const bool isRegister) {_isRegister = isRegister;}

		void	sendMessage(const std::string &message) const;
};
