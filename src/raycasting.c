/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:53:28 by safuente          #+#    #+#             */
/*   Updated: 2025/05/24 18:53:29 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

void	draw_vertical_line(t_image *image, int x, double height)
{
	int	start;
	int	end;
	int	line;

	line = 0;
	start = (HEIGHT / 2) - (height / 2);
	end = start + height;
	while (line < HEIGHT)
	{
		if (line < start)
			mlx_pixel_put_v2(image, x, line++, 0x00FF0000);
		else if (line >= start && line < end)
			mlx_pixel_put_v2(image, x, line++, 0x00FFFF00);
		else if (line >= end)
			mlx_pixel_put_v2(image, x, line++, 0x0000FF00);
	}
}

double	ray_distance(t_player *player, t_data *data, double ray_angle)
{
	double	tmp_x;
	double	tmp_y;
	double	traveled;
	int		grid_x;
	int		grid_y;

	tmp_x = player->px * BLOCK + BLOCK / 2.0;
	tmp_y = player->py * BLOCK + BLOCK / 2.0;
	traveled = 0.0;
	while (traveled < MAX_RAY_DISTANCE)
	{
		grid_x = (int)(tmp_x / BLOCK);
		grid_y = (int)(tmp_y / BLOCK);
		if (grid_y < 0 || grid_x < 0 || grid_y >= data->map.height
			|| grid_x >= data->map.width
			|| data->map.map[grid_y][grid_x] == '1')
			break ;
		tmp_x += cos(ray_angle) * RAY_STEP_SIZE;
		tmp_y += sin(ray_angle) * RAY_STEP_SIZE;
		traveled += RAY_STEP_SIZE;
	}
	return (traveled);
}

void	render_scene(t_image *image, t_player *player, t_data *data)
{
	double	start_angle;
	double	ray_angle;
	double	corrected;
	double	wall_height;
	int		pos_screen;

	start_angle = player->angle - (FOV / 2.0);
	pos_screen = 0;
	while (pos_screen < WIDTH)
	{
		ray_angle = start_angle + (pos_screen * FOV_STEP);
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
		corrected = ray_distance(player, data, ray_angle)
			* cos(player->angle - ray_angle);
		wall_height = (BLOCK * HEIGHT) / corrected;
		draw_vertical_line(image, pos_screen++, wall_height);
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window, image->img,
		0, 0);
}
