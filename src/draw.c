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

void	mlx_pixel_put_v2(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	draw_block(t_image *image, t_mlx *mlx, int size)
{
	int	y;
	int	x;

	image->img = mlx_new_image(mlx->mlx_ptr, BLOCK, BLOCK);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
			mlx_pixel_put_v2(image, x++, y, 0x00FF0000);
		y++;
	}
}

void	draw_map(char map[5][5], t_image *block, t_image *player, t_mlx *mlx)
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
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window,
					block->img, x * BLOCK, y * BLOCK);
			else if (map[y][x] == 'S' || map[y][x] == 'N' || map[y][x] == 'E'
				|| map[y][x] == 'O')
			{
				printf("%d %d\n", x * BLOCK + BLOCK / 2, y * BLOCK + BLOCK / 2);
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window,
					player->img, x * BLOCK + BLOCK / 2, y * BLOCK + BLOCK / 2);
			}
			x++;
		}
		y++;
	}
}
