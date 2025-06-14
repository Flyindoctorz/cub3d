/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:34:46 by safuente          #+#    #+#             */
/*   Updated: 2025/06/06 11:34:46 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycasting.h"

void	set_images(t_data *data)
{
	data->wallnorth_img.path = data->texture.north.path;
	data->wallsouth_img.path = data->texture.south.path;
	data->walleast_img.path = data->texture.east.path;
	data->wallwest_img.path = data->texture.west.path;
	create_image(&data->scene_img, data, WIDTH, HEIGHT);
	create_image(&data->minimap_img, data, (WIDTH / 16) * 2, (HEIGHT / 9) * 2);
	create_image(&data->player_img, data, data->minimap_img.width / 32,
		data->minimap_img.width / 32);
	create_image(&data->wallnorth_img, data, 0, 0);
	create_image(&data->walleast_img, data, 0, 0);
	create_image(&data->wallwest_img, data, 0, 0);
	create_image(&data->wallsouth_img, data, 0, 0);
}

void	paint_map(t_data *data, double mini_x, double mini_y, t_image *m_map)
{
	double	map_x;
	double	map_y;

	map_x = data->player.px - 1.5 + (mini_x * 3.0 / data->minimap_img.width);
	map_y = data->player.py - 1.5 + (mini_y * 3.0 / data->minimap_img.height);
	if (map_x > 0 && map_y > 0 && map_x < data->map.width
		&& map_y < data->map.height)
	{
		if (data->map.map[(int)map_y][(int)map_x] == '1')
			mlx_pixel_put_v2(m_map, mini_x, mini_y, 0x00FF0000);
		else if (data->map.map[(int)map_y][(int)map_x] == '0')
			mlx_pixel_put_v2(m_map, mini_x, mini_y, 0x00000000);
		else
			mlx_pixel_put_v2(m_map, mini_x, mini_y, 0x00FFFFFF);
	}
	else
		mlx_pixel_put_v2(m_map, mini_x, mini_y, 0x00FFFFFF);
}

void	draw_map(t_data *data, t_image *m_map)
{
	double	mini_x;
	double	mini_y;

	mini_y = 0;
	while (mini_y < m_map->height)
	{
		mini_x = 0;
		while (mini_x < data->minimap_img.width)
		{
			paint_map(data, mini_x, mini_y, m_map);
			mini_x++;
		}
		mini_y++;
	}
	draw_line(m_map, data);
}

void	draw_player(t_image *image)
{
	int	y;
	int	x;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
			mlx_pixel_put_v2(image, x++, y, 0x00FF0000);
		y++;
	}
}

void	draw_line(t_image *m_map, t_data *data)
{
	double	inc_x;
	double	inc_y;
	double	distance;
	double	mini_x;
	double	mini_y;

	inc_x = cos(data->player.angle) * RAY_STEP_SIZE;
	inc_y = sin(data->player.angle) * RAY_STEP_SIZE;
	distance = 0.0;
	mini_x = data->minimap_img.width / 2.0;
	mini_y = data->minimap_img.height / 2.0;
	while (distance < 20.0)
	{
		mlx_pixel_put_v2(m_map, mini_x, mini_y, 0x0000FF00);
		mini_x += inc_x;
		mini_y += inc_y;
		distance += RAY_STEP_SIZE;
	}
}
