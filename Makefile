NAME = pipex
CC = cc
FLAGS = -g3 -Wall -Wextra -Werror
SRCS = pipex.c pipex_utils_1.c pipex_utils_2.c  pipex_utils_3.c

GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m
ORANGE = \033[38;5;214m
PURPLE = \033[1;35m
BOLD := \033[1m
RESET = \033[0m 

SUCCESS = [✔]
ERROR = [✗]
CLEAN = [♻]
REMOVE = [🗑]
REDO = [🗘]

all: ${NAME}

${NAME}: ${SRCS}
	@${CC} ${FLAGS} ${SRCS} -o ${NAME} || (echo "\n${RED} ============ ${ERROR} Compilation failed ! ============ ${NC}\n"; exit 1)
	@echo "${GREEN} ============ ${SUCCESS} Successful compilation ! ============ ${RESET}"

clean:
	@echo "${YELLOW} ============ ${CLEAN} Successful binary cleaning ! ============ ${RESET}"

fclean: clean
	@rm -f ${NAME}
	@echo "${BOLD}${ORANGE} ============ ${REMOVE} Deleted executable ! ============ ${RESET}"

re: fclean all
	@echo "${PURPLE} ============ ${REDO} Redo completed ! ============ ${RESET}"

.PHONY: all clean fclean re