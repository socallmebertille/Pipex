NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror -g3
SRCS = utils_libft.c \
		ft_split.c \
		free_exit.c \
		command_parse.c \
		pipex.c
OBJS = ${SRCS:.c=.o}
# BONUS_SRCS = pipex_bonus.c
# BONUS_OBJS = ${BONUS_SRCS:.c=.o}

GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m
ORANGE = \033[38;5;214m
PURPLE = \033[1;35m
BOLD := \033[1m
RESET = \033[0m 

SUCCESS = [ ✔ ]
ERROR = [ ✗ ]
CLEAN = [ ♻ ]
REMOVE = [ 🗑 ]
REDO = [ 🗘 ]

all: ${NAME}

${NAME}: ${OBJS}

.c.o:
	@${CC} ${FLAGS} -c $< -o $@ || (echo "\n${RED} ============ ${ERROR} Compilation failed ! ==================== ${NC}\n"; exit 1)
	@echo "${GREEN} ============ ${SUCCESS} Successful compilation ! ================ ${RESET}"

clean:
	@rm -rf ${OBJS} ${BONUS_OBJS}
	@echo "${YELLOW} ============ ${CLEAN} Successful binary cleaning ! ============ ${RESET}"

fclean: clean
	@rm -rf ${NAME}
	@echo "${BOLD}${ORANGE} ============ ${REMOVE} Deleted executable ! ==================== ${RESET}"

# bonus: ${OBJS} ${BONUS_OBJS}

re: fclean all
	@echo "${PURPLE} ============ ${REDO} Redo completed ! ======================== ${RESET}"

.PHONY: all clean fclean bonus re