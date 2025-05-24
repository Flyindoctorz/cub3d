sources = src/main.c src/event_handler.c src/draw.c src/raycasting.c

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

clean:
	rm -f ${objects}

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C minilibx/ clean

re: fclean all

build_mlx:
	$(MAKE) -C minilibx/

.PHONY: all clean re fclean build_mlx
