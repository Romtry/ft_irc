/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:27:29 by rdedola           #+#    #+#             */
/*   Updated: 2026/02/06 12:04:10 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# define SUCCESS	"\e[32m[v] "
# define INFO		"\e[36m[i] "
# define WARNING	"\e[35m[!] "
# define ERROR		"\e[31m[x] "
# define MSG		"\e[33m[#] "
# define RESET		"\e[0m"

// ? PASS
# define ERR_NOTREGISTERED		"451 :You have not registered\r\n"
# define ERR_PASSWDMISMATCH		"464 :Password incorrect\r\n"

// ? NICK
# define ERR_NONICKNAMEGIVEN			"431 :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nickname)	"432 " + nickname + " :Erroneus nickname\r\n"
# define ERR_NICKNAMEINUSE(nickname)	"433 " + nickname + " :Nickname is already in use\r\n"

// ? TOPIC
#define ERR_NOSUCHCHANNEL(channel)		"403 " + channel + " :No such channel\r\n"

// ? PRIVMSG
#define ERR_NOSUCHNICK(nameOrChannel)	"401 " + nameOrChannel + " :No such nick/channel\r\n"

// ? OPERATOR
#define ERR_CHANOPRIVSNEEDED(channel)	"482 " + channel + " :You're not channel operator\r\n"

// ? FULL
# define ERR_CHANNELISFULL(channel)		"471 " + channel + " :Cannot join channel (+l)\r\n"

// ? INVITE
#define ERR_INVITEONLYCHAN(channel)	"473 " + channel + " :Cannot join channel (+i)\r\n"

// ? MODE
#define ERR_UNKNOWNMODE(char)		(std::string("472 ") + (char) + " :is unknown mode char to me\r\n")

// ? OTHER
# define ERR_NEEDMOREPARAMS							"461 USER :Not enough parameters\r\n"
# define ERR_ALREADYREGISTRED						"462 :Unauthorized command (already registered)\r\n"
# define ERR_UNKNOWNCOMMAND(command)				"421 " + command + " :Unknown command\r\n"

// ? RAW

# define RAW_JOIN(nickname, username, hostname, channel)\
	":" + nickname + "!~" + username + "@" + hostname + " JOIN :" + channel + "\r\n"

# define RAW_PRIVMSG(sender, hostname, receiver, message) \
	":" + sender + "!~" + sender + "@" + hostname + " PRIVMSG " + receiver + " " + message + "\r\n"

# define RPL_NOTOPIC(nickname, channel) ":ft_irc.nanachi 331 " + nickname + " " + channel + " :No topic is set\r\n"

# define RPL_TOPIC(nickname, channel, topic) \
":ft_irc.nanachi 332 " + nickname + " " + channel + " :" + topic + "\r\n"

# define RAW_TOPIC(nickname, username, hostname, channel, topic) \
":" + nickname + "!~" + username + "@" + hostname + " TOPIC " + channel + " :" + topic + "\r\n"

# define RAW_PART(nickname, username, hostname, channel, reason) \
":" + nickname + "!~" + username + "@" + hostname + " PART " + channel + " :" + reason + "\r\n"

# define RPL_KICK(kicker, target, channel, comment) \
":" + std::string(kicker) + "!~" + std::string(kicker) + "@host KICK " + std::string(channel) + " " + std::string(target) + " :" + std::string(comment) + "\r\n"

# define RPL_NAMREPLY(target, channel, names) \
":ft_irc.nanachi 353 " + target + " = " + channel + " :" + names + "\r\n"

# define RAW_QUIT(nickname, username, hostname, message) \
":" + nickname + "!~" + username + "@" + hostname + " QUIT :" + message + "\r\n"

# define RAW_NICKNAME(oldNick, newNick, username, hostname)	\
":" + oldNick + "!" + username + "@" + hostname + " NICK :" + newNick + "\r\n"

# define RAW_MODE_ADDOP(sender, username, hostname, channel, target) \
(":" + sender + "!~" + username + "@" + hostname + " MODE " + channel + " +o " + target + "\r\n")

# define RAW_MODE_REMOP(sender, username, hostname, channel, target) \
(":" + sender + "!~" + username + "@" + hostname + " MODE " + channel + " -o " + target + "\r\n")

# define RPL_ENDOFNAMES(target, channel) \
":ft_irc.nanachi 366 " + target + " " + channel + " :End of /NAMES list.\r\n"

# define RAW_MODE(nickname, username, hostname, channel, mode, arg) \
":" + nickname + "!~" + username + "@" + hostname + " MODE " + channel + " " + mode + (arg.empty() ? "" : " " + arg) + "\r\n"

# define RPL_INVITING(inviter, invited, channel) \
":ft_irc.nanachi 341 " + std::string(inviter) + " " + std::string(invited) + " " + std::string(channel) + "\r\n"

# define INVITE_MESSAGE(inviter, invited, channel) \
":" + std::string(inviter) + "!~" + inviter + "@host INVITE " + std::string(invited) + " :" + std::string(channel) + "\r\n"




































