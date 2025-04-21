CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC_DIR = src/
SRCS = main.c error_handler.c env_vars_ops.c free_memory.c ll_ops.c utils.c signal.c lexer.c  \
	token_utils.c lexer_utils.c

SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJS = $(SRC:.c=.o)

HEADER_PATH = include/

NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Default target
all: $(NAME)

# Bonus target (same as 'all')
bonus: all

# Build the minishell
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -I $(HEADER_PATH) -o $(NAME)

# Rule to compile .o files from .c files
%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build the libft library
$(LIBFT):
	$(MAKE) -s -C $(LIBFT_DIR) all

# Clean object files
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean all build artifacts
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Debug target to print variables
debug:
	@echo "OBJS = $(OBJS)"
	@echo "LIBFT = $(LIBFT)"

.PHONY: all clean fclean re debug bonus
