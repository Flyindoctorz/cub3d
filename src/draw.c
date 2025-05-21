/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:50:15 by safuente          #+#    #+#             */
/*   Updated: 2025/05/20 20:50:16 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycasting.h"
#include "../parsing.h"
#include <math.h>

void	mlx_pixel_put_v2(t_image *image, int x, int y, int color)
{
		char	*dst;

		dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
}

void	draw_line(t_image *image, int size, t_player *player, t_data *data)
{
	double	end_x;
	double	end_y;
	double	tmp_x;
	double	tmp_y;
	double	inc_x;
	double	inc_y;
	double	steps;
	double	dx;
	double	dy;
	end_x = (player->px * BLOCK) + cos(player->angle) * size;
	end_y = (player->py * BLOCK) + sin(player->angle) * size;
	dx = end_x - (player->px * BLOCK);
	dy = end_y - (player->py * BLOCK);
	steps = fmax(fabs(dx), fabs(dy));
	inc_x = dx / steps;
	inc_y = dy / steps;
	tmp_x = player->px * BLOCK;
	tmp_y = player->py * BLOCK;

	image->img = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	image->addr = mlx_get_data_addr(image->img,
		&image->bits_per_pixel, &image->line_length,
		&image->endian);

	for (int i = 0; i <= steps; i++)
	{
		mlx_pixel_put_v2(image, roundf(tmp_x), roundf(tmp_y), 0x0000FF00);
		tmp_x += inc_x;
		tmp_y += inc_y;
	}
}

void	draw_block(t_image *image, t_mlx *mlx, int size)
{
	int	y;
	int	x;

	image->img = mlx_new_image(mlx->mlx_ptr, size, size);
	image->addr = mlx_get_data_addr(image->img,
			&image->bits_per_pixel, &image->line_length,
			&image->endian);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
			mlx_pixel_put_v2(image, x++, y, 0x00FF0000);
		y++;
	}
}

void	draw_map(char **map, t_data *data, t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			if (map[y][x] == '1')
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, data->block_img.img, x*BLOCK, y*BLOCK);
			else if (map[y][x] == 'S' || map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'O')
			{
				// printf("%d %d\n", x * BLOCK + BLOCK/2, y *BLOCK - BLOCK/2);
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, data->player_img.img, x*BLOCK + BLOCK/2, y*BLOCK + BLOCK/2);
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, data->line_img.img, x*BLOCK + BLOCK/2 + BLOCK/8, y*BLOCK + BLOCK/2);
			}
			x++;
		}
		y++;
	}
}
