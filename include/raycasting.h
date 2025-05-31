/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:13 by safuente          #+#    #+#             */
/*   Updated: 2025/05/19 18:50:51 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define SUCCESS 0
# define ERROR 1

# define WIDTH 480
# define HEIGHT 320
# define BLOCK 32
# define FOV (M_PI / 3)
# define PLAYER_SPEED 0.002
# define PLAYER_ROTATION_SPEED 0.1
# define MAX_RAY_DISTANCE 10000.0
# define RAY_STEP_SIZE 1.0

// # define KEY_W 13
// # define KEY_A 0
// # define KEY_S 1
// # define KEY_D 2
// # define KEY_LEFT 123
// # define KEY_RIGHT 124
// # define KEY_ESC 53

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# include "../minilibx/mlx.h"
# include "math.h"
# include "parsing.h"
# include <X11/keysym.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_player
{
	double		px;
	double		py;
	double		angle;
}				t_player;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*mlx_window;
}				t_mlx;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_data
{
	t_player	player;
	t_mlx		mlx;
	t_image		line_img;
	t_keys		keys;
	t_map		map;
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
}				t_data;

/* event handling*/

int				close_window(t_mlx *data);
int				key_down(int keycode, t_data *data);
int				key_up(int keycode, t_data *data);
int				update_state(t_data *data);

/* drawing */

void			mlx_pixel_put_v2(t_image *image, int px, int py, int color);
void			draw_line(t_image *image, t_player *player, t_data *data);

/*line calculation */

double			ray_distance(t_player *player, t_data *data, double ray_angle);
void			render_scene(t_image *image, t_player *player, t_data *data);
void			draw_vertical_line(t_image *image, int x, int height);

#endif
