NAME = Philosopher
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = main.c \
		initialisation.c \
		utils.c \

OBJS = $(SRCS:.c=.o)

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[OK]$(RESET)\t$(MAGENTA)Philosopher built successfully!$(RESET)"

%.o: %.c
	@echo "$(CYAN)[COMPILE]$(RESET) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "$(BLUE)[CLEAN]$(RESET) Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[FCLEAN]$(RESET) Executable and object files removed."

re: fclean all

.PHONY: all clean fclean re