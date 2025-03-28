# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 15:05:03 by jgrigorj          #+#    #+#              #
#    Updated: 2025/03/07 23:25:05 by jgrigorj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Source files and object files
SRC = ft_bzero.c ft_isascii.c ft_memcpy.c ft_strchr.c ft_strlen.c \
    	ft_isalnum.c ft_isdigit.c ft_memmove.c ft_strlcat.c ft_tolower.c \
    	ft_isalpha.c ft_isprint.c ft_memset.c ft_strlcpy.c ft_toupper.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c	get_next_line.c get_next_line_utils.c ft_atof.c \
		ft_ftoa.c


PRINTF_DIR = ft_printf
PRINTF_SRC = ft_printf.c print_dec.c print_ptr.c print_undec.c utils.c \
		print_hex.c print_percent.c print_str.c get_width_precision.c \
		utils2.c
PRINTF_SRC := $(addprefix $(PRINTF_DIR)/, $(PRINTF_SRC))

OBJ = $(SRC:.c=.o)

PRINTF_OBJ = $(PRINTF_SRC:.c=.o)


# Target library
NAME = libft.a

# Default rule to build the library
all: $(NAME)

# Rule to create the library using the ar command
$(NAME): $(OBJ) $(PRINTF_OBJ)
	@echo "Creating static library in root: $(NAME)"
	ar rcs $(NAME) $(OBJ) $(PRINTF_OBJ)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJ) $(PRINTF_OBJ)

# Clean up both object files and the library
fclean: clean
	rm -f $(NAME)

# Rebuild everything from scratch
re: fclean all

bonus: all

# Phony targets
.PHONY: all clean fclean re