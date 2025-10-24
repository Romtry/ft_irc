NAME=	ircserv

VPATH= src/

SRC=	main.cpp ircserv.cpp\

OFILES= ${SRC:%.cpp=obj/%.o}

CC= 	c++ -Wextra -Wall -std=c++98
CFLAGS= -g3
RESET = \033[0m
GREEN = \033[38;5;85m

all:	${NAME}

${NAME}:		${OFILES}
	   @${CC} ${CFLAGS} ${OFILES} -o ${NAME}
	@echo "${GREEN}[✓] - ${_GREEN}${NAME}${GREEN} Successfully Compiled!${RESET}"

obj/%.o:%.cpp
	@mkdir -p obj/$(dir $<)
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -rf obj
	@rm -f ${NAME}.log

fclean:	clean
	@rm -f ${NAME}
	@${RM} ${NAME}

re:	fclean all

.PHONY:		all bonus clean fclean re
