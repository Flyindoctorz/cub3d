/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:53:28 by safuente          #+#    #+#             */
/*   Updated: 2025/05/24 18:53:29 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include <string.h>
#include "../include/raycasting.h"

void	set_drawing_info(t_drawing *data, t_ray *ray)
{
	if (ray->axis == AXIS_Y)
		data->wall_hit_pos = (ray->x / BLOCK) - floor(ray->x / BLOCK);
	else
		data->wall_hit_pos = (ray->y / BLOCK) - floor(ray->y / BLOCK);
	data->texture_x = (int)(data->wall_hit_pos * (double)ray->texture->width);
	if (data->texture_x < 0)
		data->texture_x = 0;
	if (data->texture_x >= ray->texture->width)
		data->texture_x = ray->texture->width - 1;
	if ((ray->axis == AXIS_Y && ray->dir_y > 0) || (ray->axis == AXIS_X
			&& ray->dir_x < 0))
		data->texture_x = ray->texture->width - data->texture_x - 1;
	if (data->texture_x < 0)
		data->texture_x = 0;
	if (data->texture_x >= ray->texture->width)
		data->texture_x = ray->texture->width - 1;
	data->original_start = ((double)HEIGHT / 2.0) - (ray->height_line / 2.0);
	data->start = ((double)HEIGHT / 2.0) - (ray->height_line / 2.0);
	data->end = data->start + ray->height_line;
	if (data->start < 0)
		data->start = 0;
	if (data->end >= HEIGHT)
		data->end = HEIGHT - 1;
}

void	draw_vertical_line(t_image *image, int column, t_ray *ray)
{
	t_drawing	data;

	data.line = 0;
	set_drawing_info(&data, ray);
	while (data.line < HEIGHT)
	{
		if (data.line < data.start)
			mlx_pixel_put_v2(image, column, data.line++, 0x00FFFF00);
		else if (data.line >= data.start && data.line <= data.end)
		{
			data.full_wall_position = (double)(data.line - data.original_start)
				/ ray->height_line;
			data.texture_y = (int)(data.full_wall_position
					* ray->texture->height);
			if (data.texture_y < 0)
				data.texture_y = 0;
			if (data.texture_y >= ray->texture->height)
				data.texture_y = ray->texture->height - 1;
			data.color = get_texture_pixel(ray->texture,
					data.texture_x, data.texture_y);
			mlx_pixel_put_v2(image, column, data.line++, data.color);
		}
		else
			mlx_pixel_put_v2(image, column, data.line++, 0x0000FF00);
	}
}

int	get_direction(int axis, t_ray *ray, t_player *player, t_data *data)
{
	if (axis == AXIS_X && data->map.map[(int)(ray->y / BLOCK)][(int)(ray->x
			/ BLOCK)] == '1')
	{
		if (ray->x > player->px * BLOCK)
			ray->texture = &data->wallwest_img;
		else
			ray->texture = &data->walleast_img;
		ray->distance += RAY_STEP_SIZE;
		ray->axis = AXIS_X;
		return (EXIT_SUCCESS);
	}
	else if (axis == AXIS_Y && data->map.map[(int)(ray->y / BLOCK)][(int)(ray->x
			/ BLOCK)] == '1')
	{
		if (ray->y > player->py * BLOCK)
			ray->texture = &data->wallnorth_img;
		else
			ray->texture = &data->wallsouth_img;
		ray->distance += RAY_STEP_SIZE;
		ray->axis = AXIS_Y;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	ray_distance(t_player *player, t_data *data, t_ray *ray)
{
	ray->x = player->px * BLOCK;
	ray->y = player->py * BLOCK;
	ray->distance = 0.0;
	ray->texture = data->wallnorth_img.img;
	ray->axis = AXIS_X;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	while (ray->distance < MAX_RAY_DISTANCE)
	{
		if ((int)(ray->y / BLOCK) < 0 || (int)(ray->x / BLOCK) < 0
			|| (int)(ray->y / BLOCK) >= data->map.height || (int)(ray->x
				/ BLOCK) >= data->map.width)
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

void	render_scene(t_player *player, t_data *data)
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
		draw_vertical_line(&data->scene_img, pos_screen++, &ray);
	}
	memset(data->minimap_img.addr, 0, data->minimap_img.height * data->minimap_img.line_length);
	draw_map(&data->map, data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window, data->scene_img.img,
		0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window
		, data->minimap_img.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window, data->player_img.img
		, data->minimap_img.width / 2.0
		, data->minimap_img.height / 2.0);
}
