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

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

# include "../minilibx/mlx.h"
# include "math.h"
# include <string.h>

// # include <X11/keysym.h>


typedef struct s_player
{
	double	px;
	double	py;
	double	angle;
	int		fov;
}				t_player;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*mlx_window;
}				t_mlx;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_data {
	t_player	player;
	t_mlx		mlx;
	t_image		block_img;
	t_image		player_img;
	t_image		line_img;
	char		**map;
}				t_data;

/* event handling*/

int	close_window(t_mlx	*data);
int	check_input(int keycode, t_data	*data);

/* drawing */

void	mlx_pixel_put_v2(t_image *image, int px, int py, int color);
void	draw_block(t_image *image, t_mlx *mlx, int size);
void	draw_map(char **map, t_data *data, t_mlx *mlx);
void	draw_line(t_image *image, int size, t_player *player, t_data *data);

#endif
