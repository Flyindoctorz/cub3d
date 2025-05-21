sources = src/main.c src/event_handler.c src/draw.c

objects = $(sources:.c=.o)

# linux compile

# libs = -Lminilibx -lmlx_Linux -L/usr/lib -Iminilibx -lXext -lX11 -lm -lz

# includes = -Iminilibx -I/usr/include -I/opt/X11/include

# macos compile

libs = -lmlx -Lminilibx -framework OpenGL -framework AppKit

includes = -Iminilibx -I/opt/X11/include

cc = cc

cflags = -Wall -Wextra -Werror

NAME = cub3D

$(NAME): build_mlx $(objects)
	$(cc) $(cflags) $(objects) $(libs) -o $(NAME)

all: $(NAME)

%.o: %.c
	$(cc) $(cflags) $(includes) -c $< -o $@

# clean:
# 	rm -f ${objects}

# fclean: clean
# 	rm -f $(NAME)
# 	$(MAKE) -C minilibx/ clean

# re: fclean all

# build_mlx:
# 	$(MAKE) -C minilibx/

# .PHONY: all clean re fclean build_mlx

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(objects)
	@echo "$(GREEN)✨ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C minilibx/ clean
	@echo "$(GREEN)✨ Everything cleaned!$(RESET)"

re: fclean all

leak: all
	@echo "$(BLUE)Running valgrind leak check...$(RESET)"
	@valgrind --leak-check=full --show-reachable=no \
		--errors-for-leak-kinds=definite \
		--suppressions=ignore.supp \
		--track-fds=yes --trace-children=yes ./$(NAME)

norm:
	@echo "$(BLUE)Running norminette check...$(RESET)"
	@echo "$(YELLOW)Checking source files:$(RESET)"
	@python3 -m c_formatter_42 src/*.c
	@echo "$(YELLOW)Checking header files:$(RESET)"
	@python3 -m c_formatter_42 include/*.h
	@echo "$(GREEN)✨ Norminette check complete!$(RESET)"

push:
	@git add .
	@echo -n "$(BLUE)Enter your commit message: $(END)"
	@read commit_message; \
	git commit -m "$$commit_message"; \
	git push; \
	echo "$(YELLOW)All has been pushed with '$$commit_message' in commit$(END)"

debug:
	@echo "$(BLUE)Running lldb...$(RESET)"
	@lldb ./$(NAME)

.PHONY: all clean fclean re build_mlx leak norm push debug

