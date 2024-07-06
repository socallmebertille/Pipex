NAME = pipex
CC = cc
FLAGS = -g3 -Wall -Wextra -Werror -I./libft
LDFLAGS = -Llibft -lft
SRCS = pipex.c

GREEN = \033[0;32m
RESET = \033[0m

SUCCESS = ✔
CLEAN = 🧹
REMOVE = 🗑️

all: ${NAME}

${NAME}: ${SRCS}
	@make -s -C libft
	@${CC} ${FLAGS} ${SRCS} ${LDFLAGS} -o ${NAME}
	@echo "${GREEN} ============ ${SUCCESS} Compilation réussie ! ============ ${RESET}"

clean:
	@make clean -s -C libft
	@echo "${GREEN} ============ ${CLEAN} Nettoyage binaire réussie ! ============ ${RESET}"

fclean: clean
	@rm -f ${NAME}
	@echo "${GREEN} ============ ${REMOVE}  Exécutable supprimé ! ============ ${RESET}"

re: fclean all

.PHONY: all clean fclean re