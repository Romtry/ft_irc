# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 15:09:31 by rdedola           #+#    #+#              #
#    Updated: 2025/10/30 14:22:51 by rdedola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			:=	ircserv

# Files
SRC			:=	src/main.cpp \
				src/IRCServ.cpp \
				src/Client.cpp \
				src/Channel.cpp \
				src/cmds/handleCommand.cpp \
				src/cmds/nick.cpp \
				src/cmds/pass.cpp \
				src/cmds/user.cpp \
				src/cmds/join.cpp \
				src/cmds/topic.cpp \
				src/cmds/part.cpp \
				src/cmds/kick.cpp \
				src/cmds/privmsg.cpp \
				src/cmds/mode.cpp \
				src/cmds/invite.cpp


# Variables
CC			:=	c++
CFLAGS		:=	-Wall -Wextra -Werror -std=c++98 -Iincludes  -g3

# Colors
DEF_COLOR	= \033[0;39m
COLOR		= \033[1;32m

# Makefile
all			:	${EXE}

${EXE}		:	${SRC}
				@${CC} ${CFLAGS} ${SRC} -o ${EXE}
				@echo "${COLOR}╔══════════════════════════╗${DEF_COLOR}"
				@echo "${COLOR}║    IRC Server compiled   ║${DEF_COLOR}"
				@echo "${COLOR}╚══════════════════════════╝${DEF_COLOR}"


clean		:
				@rm -rf ${EXE}
				@echo "${COLOR}╔══════════════════════════╗${DEF_COLOR}"
				@echo "${COLOR}║    IRC Server cleaned!   ║${DEF_COLOR}"
				@echo "${COLOR}╚══════════════════════════╝${DEF_COLOR}"

re			:	clean all

.PHONY		:	all clean re
