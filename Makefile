CC = cc
CFLAGS = -Wall -Werror -Wextra -D_DEFAULT_SOURCE -Iinclude -I$(LIBFT_DIR)

LEXER_DIR = src/lexer/
LEXER_SRC = lexer.c lexer_utils.c

PARSER_DIR = src/parser/
PARSER_SRC = token_utils.c parser.c parser2.c token_check.c token_check2.c parser_utils.c parser_utils2.c \
	parser_utils3.c parser_arg_utils.c parser_redir_utils.c print_ast.c print_ast_utils.c \
	check_subshell_redirs.c

ENV_DIR = src/env/
ENV_SRC = env_vars_ops.c ll_ops.c utils.c env_vars_utils.c validators.c env_vars_handler.c

BUILT_INS_DIR = src/built_ins/
BUILT_INS_SRC = built_ins.c cd.c echo.c built_ins_utils.c echo_utils.c echo_utils2.c dir_check.c replace.c

SIGNAL_DIR = src/signal/
SIGNAL_SRC = signal.c child_heredoc_signal.c

GENERAL_DIR = src/general/
GENERAL_SRC = main.c error_handler.c free_memory.c free_memory2.c init.c

EXEC_DIR = src/exec/
EXEC_SRC = argv_utils.c argv_utils2.c redir_utils.c heredoc.c get_cmd.c globbing.c globbing_utils.c globbing_utils2.c \
			globbing_utils3.c add_rm_escape_char.c match_star_pattern.c print_ast_argv.c path.c exec_utils.c pipes.c \
			exec_sig_utils.c exec_utils2.c heredoc_utils.c


SRC = \
	$(addprefix $(GENERAL_DIR), $(GENERAL_SRC)) \
	$(addprefix $(SIGNAL_DIR), $(SIGNAL_SRC)) \
	$(addprefix $(PARSER_DIR), $(PARSER_SRC)) \
	$(addprefix $(ENV_DIR), $(ENV_SRC)) \
	$(addprefix $(LEXER_DIR), $(LEXER_SRC)) \
	$(addprefix $(BUILT_INS_DIR), $(BUILT_INS_SRC)) \
	$(addprefix $(EXEC_DIR), $(EXEC_SRC))
OBJS = $(SRC:.c=.o)

NAME = minishell
BONUS_NAME = minishell_bonus

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Default target
all: $(NAME)

# Bonus target
bonus: $(BONUS_NAME)

# Build the minishell
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -o $(NAME)

# Build the bonus
$(BONUS_NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -o $(BONUS_NAME)

# Compile .o files from .c files
%.o: %.c
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
	rm -f $(NAME) $(BONUS_NAME) 
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Debug target to print variables
debug:
	@echo "OBJS = $(OBJS)"
	@echo "LIBFT = $(LIBFT)"
	@echo "INCLUDE DIR = include"

.PHONY: all clean fclean re debug bonus
