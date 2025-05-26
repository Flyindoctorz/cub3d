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
#include "../include/parsing.h"

void	mlx_pixel_put_v2(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_image *image, t_player *player, t_data *data)
{
	double	tmp_x;
	double	tmp_y;
	double	inc_x;
	double	inc_y;
	double	max_distance;
	double	traveled;
	double	step_size;
	int		grid_x;
	int		grid_y;

	tmp_x = player->px * BLOCK + BLOCK / 2.0;
	tmp_y = player->py * BLOCK + BLOCK / 2.0;
	inc_x = cos(player->angle);
	inc_y = sin(player->angle);
	max_distance = 1000.0;
	traveled = 0.0;
	step_size = 1.0;
	while (traveled < max_distance)
	{
		grid_x = (int)(tmp_x / BLOCK);
		grid_y = (int)(tmp_y / BLOCK);
		if (grid_y < 0 || grid_x < 0 || grid_y >= 5 || grid_x >= 5)
			break ;
		if (data->map.map[grid_y][grid_x] == '1')
			break ;
		mlx_pixel_put_v2(image, (int)tmp_x, (int)tmp_y, 0x0000FF00);
		tmp_x += inc_x * step_size;
		tmp_y += inc_y * step_size;
		traveled += step_size;
	}
}
