# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 00:00:00 by student           #+#    #+#              #
#    Updated: 2025/06/02 15:02:16 by cgelgon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CFLAGS		=	-Wall -Werror -Wextra -g3
CC			=	cc

# Source files
SRC			=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putnbr_printf_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strndup.c \
				ft_strnjoin.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtok.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c

# Bonus files
BONUS		=	ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c

# Object files
OBJ			=	$(SRC:.c=.o)
BONUS_OBJ	=	$(BONUS:.c=.o)

# Library name
NAME		=	libft.a

# Default target
all: $(NAME)

# Create library
$(NAME): $(OBJ)
	@echo "Creating library $(NAME)..."
	@ar -crs $(NAME) $(OBJ)
	@echo "✅ $(NAME) created successfully!"

# Compile source files
%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@echo "✅ Object files cleaned!"

# Clean all generated files
fclean: clean
	@echo "Cleaning library..."
	@$(RM) $(NAME)
	@echo "✅ All cleaned!"

# Rebuild everything
re: fclean all

# Bonus rule
bonus: $(OBJ) $(BONUS_OBJ)
	@echo "Creating library with bonus..."
	@ar -crs $(NAME) $(OBJ) $(BONUS_OBJ)
	@echo "✅ $(NAME) with bonus created successfully!"

# Norminette check
norm:
	@echo "Running norminette..."
	@norminette $(SRC) $(BONUS) libft.h

# Test compilation
test: $(NAME)
	@echo "Testing compilation..."
	@$(CC) $(CFLAGS) -L. -lft test_main.c -o test_libft
	@echo "✅ Test compilation successful!"

# Show help
help:
	@echo "Available targets:"
	@echo "  all    - Build the library"
	@echo "  clean  - Remove object files"
	@echo "  fclean - Remove all generated files"
	@echo "  re     - Rebuild everything"
	@echo "  bonus  - Build library with bonus functions"
	@echo "  norm   - Run norminette check"
	@echo "  test   - Test compilation"
	@echo "  help   - Show this help"

# Phony targets
.PHONY: all clean fclean re bonus norm test help