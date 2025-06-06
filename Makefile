sources = src/main.c src/event_handler.c src/raycasting_utils.c src/raycasting.c src/image_handling.c

objects = $(sources:.c=.o)

# linux compile

# libs = -Lminilibx -l:libmlx.a  -L/usr/lib -Iminilibx -lXext -lX11 -lm -lz

# includes = -Iminilibx -I/usr/include -I/opt/X11/include

# macos compile

libs = -lmlx -Lminilibx -framework OpenGL -framework AppKit

includes = -Iminilibx -I/opt/X11/include

cc = cc
cflags = -Wall -Wextra -Werror
NAME = cub3D

# Variables pour les maps
MAP_SRC = maptype.cub
MAP_NUM ?= 4  # Map par défaut (Kanye West)
MAP_DEST = current_map.cub

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

$(NAME): $(objects)
	$(cc) $(cflags) $(objects) $(libs) -o $(NAME)

all: build_mlx $(NAME)

%.o: %.c
	$(cc) $(cflags) $(includes) -c $< -o $@

	@echo "$(BLUE)Preprocessing map $(MAP_NUM)...$(RESET)"
	@chmod +x uncommenting_script.sh
	@./uncommenting_script.sh $(MAP_SRC) $(MAP_NUM) $(MAP_DEST)
	@echo "$(GREEN)✨ Map $(MAP_NUM) activated!$(RESET)"

run: all preprocess
	@echo "$(BLUE)Running with map $(MAP_NUM)...$(RESET)"
	./$(NAME) $(MAP_DEST)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(objects)
	@echo "$(GREEN)✨ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@rm -f $(MAP_DEST)
	@$(MAKE) -C minilibx/ clean
	@echo "$(GREEN)✨ Everything cleaned!$(RESET)"

re: fclean all

leak: all preprocess
	@echo "$(BLUE)Running valgrind leak check with map $(MAP_NUM)...$(RESET)"
	@valgrind --leak-check=full --show-reachable=no \
	--errors-for-leak-kinds=definite \
	--suppressions=ignore.supp \
	--track-fds=yes --trace-children=yes ./$(NAME) $(MAP_DEST)

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

debug: preprocess
	@echo "$(BLUE)Running lldb...$(RESET)"
	@lldb ./$(NAME)

build_mlx:
	@echo "$(BLUE)Building minilibx...$(RESET)"
	@$(MAKE) -C minilibx/

.PHONY: all clean fclean re build_mlx leak norm push debug
