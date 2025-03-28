CC = cc
CFLAGS = -Wall -Werror -Wextra -Iminilibx-linux # -Iminilibx-linux tells the compiler where to look for the mlx.h file

SRC_DIR = src/
SRCS = main.c init.c cleanup.c input_reading.c utils.c color.c color2.c calculate_fractal.c \
		zoom.c panel.c keybord_hooks.c panel_text.c

SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJS = $(SRC:.c=.o)

NAME = fractol

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# Default target
all: $(MLX) $(NAME)

# Bonus target (same as 'all')
bonus: all

# Build the fractol program
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lXext -lX11 -lbsd -lm -o $(NAME)

# Rule to compile .o files from .c files
$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clone and build MinilibX if it doesn't exist
$(MLX):
	git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

# Build the libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

# Clean object files
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

# Clean all build artifacts
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX_DIR)

# Rebuild everything
re: fclean all

# Debug target to print variables
debug:
	@echo "OBJS = $(OBJS)"
	@echo "LIBFT = $(LIBFT)"
	@echo "MLX = $(MLX)"

.PHONY: all clean fclean re debug