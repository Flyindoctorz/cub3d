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


int	get_texture_pixel(t_image *texture, int x, int y)
{
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	return (*(int *)(texture->addr + y * (texture->line_length / 4) + x));
}

void	draw_vertical_line(t_image *image, int x, t_ray *ray, t_data *data)
{
	int	start;
	int	end;
	int	line;

	line = 0;
	start = ((double)HEIGHT / 2) - (ray->height_line / 2);
	end = start + ray->height_line;
	(void)data;
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

int	get_direction(int axis, t_ray *ray, t_player *player, t_data *data)
{
	if (axis == 0 && data->map.map[(int)(ray->y / BLOCK)][(int)(ray->x / BLOCK)] == '1')
	{
		if (ray->x > player->px * BLOCK + BLOCK / 2.0)
			ray->direction = WEST;
		else
			ray->direction = EAST;
		return (EXIT_SUCCESS);
	}
	else if (axis == 1 && data->map.map[(int)(ray->y / BLOCK)][(int)(ray->x / BLOCK)] == '1')
	{
		if (ray->y > player->py * BLOCK + BLOCK / 2.0)
			ray->direction = NORTH;
		else
			ray->direction = SOUTH;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	ray_distance(t_player *player, t_data *data, t_ray *ray)
{
	ray->x = player->px * BLOCK + BLOCK / 2.0;
	ray->y = player->py * BLOCK + BLOCK / 2.0;
	ray->distance = 0.0;
	ray->direction = NORTH;
	while (ray->distance < MAX_RAY_DISTANCE)
	{
		if ((int)(ray->y / BLOCK) < 0 || (int)(ray->x / BLOCK) < 0
			|| (int)(ray->y / BLOCK) >= data->map.height
			|| (int)(ray->x / BLOCK) >= data->map.width)
			break ;
		if (data->map.map[(int)(ray->y / BLOCK)][(int)(ray->x / BLOCK)] == '1')
			break ;
		ray->x += cos(ray->angle) * RAY_STEP_SIZE;
		if (get_direction(0, ray, player, data) == EXIT_SUCCESS)
			break ;
		ray->y += sin(ray->angle) * RAY_STEP_SIZE;
		if (get_direction(1, ray, player, data) == EXIT_SUCCESS)
			break ;
		ray->distance += RAY_STEP_SIZE;
	}
}

void	render_scene(t_image *image, t_player *player, t_data *data)
{
	t_ray	ray;
	int		pos_screen;

	ray.start_angle = player->angle - (FOV / 2.0);
	pos_screen = 0;
	while (pos_screen < WIDTH)
	{
		ray.angle = ray.start_angle + (pos_screen * FOV_STEP);
		if (ray.angle < 0)
			ray.angle += 2 * M_PI;
		if (ray.angle > 2 * M_PI)
			ray.angle -= 2 * M_PI;
		ray_distance(player, data, &ray);
		ray.corrected = ray.distance * cos(player->angle - ray.angle);
		ray.height_line = (BLOCK * HEIGHT) / ray.corrected;
		draw_vertical_line(image, pos_screen++, &ray, data);
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window, image->img,
		0, 0);
}
