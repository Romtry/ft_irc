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

#include "Channel.hpp"
#include "IRCServ.hpp"

class Channel;

class Client
{
	private:
		std::vector<std::string>	_token;
		std::string 				_nick;
		std::string 				_user;
		bool 						_pass;
		bool						_isRegister;
		int							_clientsSocket;
		std::vector<Channel *>		_clientChannels;

	public:
		Client(const int fd) : _nick(""), _user(""), _pass(false), _isRegister(false), _clientsSocket(fd) {}
		~Client() {}

		std::string &getTokens(const unsigned int i) {return (_token[i]);};
		std::string					getNick() const {return (_nick);}
		std::string 				getUser() const {return (_user);}
		bool						getPass() const {return (_pass);}
		bool						getisregister() const {return (_isRegister);}
		int							getClientSocket() const {return (_clientsSocket);}
		std::vector<Channel *>		getChannels() const {return (_clientChannels);};

		void	addChannel(Channel *c) {_clientChannels.push_back(c);};

		void	setNick(const std::string &nick) {_nick = nick;}
		void	setUser(const std::string &user) {_user = user;}
		void	setPass(const bool pass) {_pass = pass;}
		void	setIsRegister(const bool isRegister) {_isRegister = isRegister;}

		void	pushbackTocken(const std::string &str) {_token.push_back(str);};
		void	printTocken() const;
		void	clearToken();
		void	sendMessage(const std::string &message) const;
};
