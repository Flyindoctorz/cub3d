# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/02 14:30:00 by cgelgon           #+#    #+#              #
#    Updated: 2025/06/11 16:04:07 by cgelgon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables pour les sources
sources = src/main.c src/event_handler.c src/raycasting.c src/raycasting_utils.c \
		  src/init.c src/validate_all_datas.c src/validate_textures.c src/validate_map.c \
		  src/map_closure.c src/map_utils.c src/map_parser.c src/map_parser_utils.c \
		  src/file_reader.c src/parsing_utils.c src/splitter_cells.c \
		  src/color_parser.c src/color_parser_utils.c \
		  src/parsing_core/parsing_core.c src/parsing_core/parsing_core_two.c \
		  src/parsing_core/texture_parser_one.c src/parsing_core/texture_parser_two.c \
		  src/parsing_core/utils_for_parser.c \
		  src/whole_cub_parser.c \
		  src/image_handling.c

objects = $(sources:.c=.o)

# Dossiers
LIBFT_DIR = libft
MINILIBX_DIR = minilibx-linux

# Librairies
LIBFT = $(LIBFT_DIR)/libft.a

# Linux compile
# Linux compile (corrigé)
libs = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft
includes = -I$(MINILIBX_DIR) -I$(LIBFT_DIR) -Iinclude

# # macOS compile (commenté)
# libs = -lmlx -Lminilibx -framework OpenGL -framework AppKit -L$(LIBFT_DIR) -lft
# includes = -Iminilibx -I/opt/X11/include -I$(LIBFT_DIR) -Iinclude

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
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

# Règle principale
$(NAME): build_mlx build_libft $(objects)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(objects) $(libs) -o $(NAME)
	@echo "$(GREEN)✨ $(NAME) compiled successfully!$(RESET)"

all: build_mlx $(NAME)

# Compilation des fichiers objets
%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(includes) -c $< -o $@

# Construction de la libft
build_libft:
	@echo "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)✨ libft built successfully!$(RESET)"

# Construction de minilibx
build_mlx:
	@echo "$(BLUE)Building minilibx...$(RESET)"
	@$(MAKE) -C $(MINILIBX_DIR)
	@echo "$(GREEN)✨ minilibx built successfully!$(RESET)"

# Préprocessing de la map
preprocess:
	@echo "$(BLUE)Preprocessing map $(MAP_NUM)...$(RESET)"
	@chmod +x uncommenting_script.sh
	@./uncommenting_script.sh $(MAP_SRC) $(MAP_NUM) $(MAP_DEST)
	@echo "$(GREEN)✨ Map $(MAP_NUM) activated!$(RESET)"

# Exécution avec préprocessing
run: all preprocess
	@echo "$(BLUE)Running with map $(MAP_NUM)...$(RESET)"
	./$(NAME) $(MAP_DEST)

# Nettoyage des fichiers objets
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(objects)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(GREEN)✨ Object files cleaned!$(RESET)"

# Nettoyage complet
fclean: clean
	@echo "$(RED)Full cleaning...$(RESET)"
	@rm -f $(NAME)
	@rm -f $(MAP_DEST)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MINILIBX_DIR) clean
	@echo "$(GREEN)✨ Everything cleaned!$(RESET)"

# Recompilation complète
re: fclean all

# Test de fuites mémoire avec valgrind

leak: all preprocess
	@echo "$(BLUE)Running valgrind leak check with map $(MAP_NUM)...$(RESET)"
	@valgrind --leak-check=full --show-reachable=no \
	--errors-for-leak-kinds=definite \
	--suppressions=ignore.supp \
	--track-fds=yes --trace-children=yes ./$(NAME) $(MAP_DEST)

# Vérification norminette
norm:
	@echo "$(BLUE)Running norminette check...$(RESET)"
	@echo "$(YELLOW)Checking source files:$(RESET)"
	@python3 -m c_formatter_42 src/*.c src/*/*.c
	@echo "$(YELLOW)Checking header files:$(RESET)"
	@python3 -m c_formatter_42 include/*.h
	@echo "$(YELLOW)Checking libft:$(RESET)"
	@python3 -m c_formatter_42 $(LIBFT_DIR)/*.c $(LIBFT_DIR)/*.h
	@echo "$(GREEN)✨ Norminette check complete!$(RESET)"

# Push git rapide
push:
	@git add .
	@echo -n "$(BLUE)Enter your commit message: $(RESET)"
	@read commit_message; \
	git commit -m "$$commit_message"; \
	git push; \
	echo "$(YELLOW)All has been pushed with '$$commit_message' in commit$(RESET)"

# Debug avec lldb
debug: preprocess
	@echo "$(BLUE)Running lldb...$(RESET)"
	@lldb ./$(NAME)

# Test rapide avec différentes maps
test1: MAP_NUM=1
test1: run

test2: MAP_NUM=2
test2: run

test3: MAP_NUM=3
test3: run

test4: MAP_NUM=4
test4: run

test5: MAP_NUM=5
test5: run

# Affichage de l'aide
help:
	@echo "$(BLUE)Available targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)       - Build the project"
	@echo "  $(GREEN)clean$(RESET)     - Remove object files"
	@echo "  $(GREEN)fclean$(RESET)    - Remove all generated files"
	@echo "  $(GREEN)re$(RESET)        - Rebuild everything"
	@echo "  $(GREEN)run$(RESET)       - Build and run with default map"
	@echo "  $(GREEN)test1-5$(RESET)   - Run with specific map (1-5)"
	@echo "  $(GREEN)leak$(RESET)      - Run with valgrind"
	@echo "  $(GREEN)norm$(RESET)      - Check norminette"
	@echo "  $(GREEN)debug$(RESET)     - Run with lldb debugger"
	@echo "  $(GREEN)push$(RESET)      - Quick git push"
	@echo "  $(GREEN)help$(RESET)      - Show this help"

.PHONY: all clean fclean re build_mlx build_libft preprocess run leak norm push debug test1 test2 test3 test4 test5 help
