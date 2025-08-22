NAME = Philosopher
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
LIBS = -L./Libft -lft
SRCS = main.c \
		initialisation.c \
		philosopher.h \
		utils.c 

OBJS = $(SRCS:.c=.o)

all:
	@echo "\033[1;93m [WAIT] \033[0m\t\033[1;35mBuilding Philosopher...\033[0m"
	@$(MAKE) --no-print-directory $(NAME)


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[1;32m [OK]   \033[0m\t\033[1;35mPhilosopher built successfully!\033[0m"

%.o: %.c
	@echo "\033[1;90m [COMPILE] \033[0m $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C clean --no-print-directory
	@echo "\033[1;34m [CLEAN] \033[0m Object files removed."

fclean: clean
	@rm -f $(NAME)
	@make -C fclean --no-print-directory
	@echo "\033[1;31m [FCLEAN] \033[0m Executable and object files removed."

re: fclean all

.PHONY: all clean fclean re