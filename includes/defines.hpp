/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:27:29 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/30 12:27:32 by rdedola          ###   ########.fr       */
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

// ? USER
#define ERR_NEEDMOREPARAMS		"461 USER :Not enough parameters\r\n"

// ? TOPIC
#define ERR_NOSUCHCHANNEL(channel)		"403 " + channel + " :No such channel\r\n"

// ? OTHER
# define ERR_ALREADYREGISTRED				"462 :Unauthorized command (already registered)\r\n"
# define ERR_UNKNOWNCOMMAND(command)		"421 " + command + " :Unknown command\r\n"
