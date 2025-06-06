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

# define AXIS_X 0
# define AXIS_Y 1

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define FOV (M_PI / 3)
# define FOV_STEP (FOV / WIDTH)
# define PLAYER_SPEED 0.02
# define PLAYER_ROTATION_SPEED 1
# define MAX_RAY_DISTANCE 10000.0
# define RAY_STEP_SIZE 1.0

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

// # define KEY_W 119
// # define KEY_A 97
// # define KEY_S 115
// # define KEY_D 100
// # define KEY_LEFT 65361
// # define KEY_RIGHT 65363
// # define KEY_ESC 65307

# include "../minilibx/mlx.h"
# include "math.h"
# include "parsing.h"
// # include <X11/keysym.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_tuple
{
	int	x;
	int	y;
}				t_tuple;

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
	char		*path;
	void		*img;
	char		*addr;
	int 		width;
	int 		height;
	int			bpp;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_data
{
	t_player	player;
	t_mlx		mlx;
	t_image		minimap_img;
	t_image		scene_img;
	t_image		player_img;
	t_image		wallnorth_img;
	t_image		wallsouth_img;
	t_image		walleast_img;
	t_image		wallwest_img;
	t_keys		keys;
	t_map		map;
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
}				t_data;

typedef struct s_ray
{
	double				x;
	double				y;
	double				dir_x;
	double				dir_y;
	double				distance;
	double				start_angle;
	double				angle;
	double				corrected;
	double				height_line;
	int					axis;
	t_image				*texture;

}				t_ray;

typedef struct s_drawing
{
	int		start;
	int		end;
	int		line;
	int		texture_x;
	int		original_start;
	int		texture_y;
	int		color;
	double	wall_hit_pos;
	double	full_wall_position;
}				t_drawing;

/* event handling*/

int				close_window(t_data *data);
int				key_down(int keycode, t_data *data);
int				key_up(int keycode, t_data *data);
int				update_state(t_data *data);

/* raycasting_utils */

void			mlx_pixel_put_v2(t_image *image, int px, int py, int color);
void			draw_line(t_image *image, t_player *player, t_data *data);
void			create_image(t_image *image, t_data *data, int width, int height);
int				get_texture_pixel(t_image *texture, int x, int y);

/* image handling */

void			draw_player(t_image *image);
void			draw_map(t_map *map, t_data *data);
void			render_scene(t_player *player, t_data *data);

/* raycasting */

void			raycast(t_player *player, t_data *data);
void			ray_distance(t_player *player, t_data *data, t_ray *ray);
void			render_scene(t_player *player, t_data *data);
void			draw_vertical_line(t_image *image, int column, t_ray *ray);
int				get_direction(int axis, t_ray *ray, t_player *player, t_data *data);


#endif
