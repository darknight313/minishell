# Compiler and flags
CC = cc -g
# CFLAGS = -Wall -Wextra -Werror

# Name of the library
NAME = minishell

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c

PAR_DIR = parsing
PAR_SRC = $(PAR_DIR)/token.c $(PAR_DIR)/utils.c $(PAR_DIR)/create_list.c $(PAR_DIR)/expand.c

LIBFT_DIR = libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)

# Source files and objects

SRC_OBJS = $(SRCS:.c=.o)
PAR_OBJS = $(PAR_SRC:.c=.o)

# ANSI color codes
GREEN = \033[0;32m
RED = \033[0;30m
NC = \033[0m

# Target: Build the library and, optionally, the executable
all: $(LIBFT) $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)%.c
	@echo "$(GREEN)Compiling $<$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

$(PAR_DIR)/%.o: $(PAR_DIR)/%.c
	@echo "$(GREEN)Compiling $<$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(NAME): $(SRC_OBJS) $(PAR_OBJS)
	@echo "$(GREEN)Archiving object files$(NC)"
	$(CC) $(SRC_OBJS) $(PAR_OBJS) $(LIBFT) -lreadline -o $(NAME)

# Clean up
clean:
	@echo "$(RED)Cleaning up$(NC)"
	rm -f $(SRC_OBJS) $(PAR_OBJS)
	make clean -C $(LIBFT_DIR)
# Force clean, including the library and executable
fclean: clean
	@echo "$(RED)Force cleaning$(NC)"
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
# Rebuild
re: fclean all
	@echo "$(GREEN)Rebuild complete$(NC)"

.PHONY: all clean fclean re
