NAME = pipex

#NAME_BONUS = checker

CC = cc

FLAGS = -Wall -Wextra -Werror

SRC =  pipex.c functions.c split.c error.c norm_func.c fork_functions.c check.c close.c

#BONUS = 

OBJS = ${SRC:.c=.o}

#Bonus_OBJS = ${BONUS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} pipex.h Makefile
	${CC} ${FLAGS} ${OBJS} -o ${NAME} 

bonus: ${NAME}

#${NAME_BONUS}: ${Bonus_OBJS}  pipex.h Makefile
#	${CC} ${FLAGS} ${Bonus_OBJS} -o ${NAME_BONUS}

%.o:%.c
	${CC} ${FLAGS} -c  $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all bonus

.PHONY: all clean fclean re #bonus