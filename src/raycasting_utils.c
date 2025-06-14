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

#include "../include/parsing.h"
#include "../include/raycasting.h"

void	mlx_pixel_put_v2(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_pixel(t_image *texture, int x, int y)
{
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	return (((unsigned int *)texture->addr)[y * (texture->line_length / 4)
		+ x]);
}

void	render_scene(t_player *player, t_data *data)
{
	draw_map(data, &data->minimap_img);
	raycast(player, data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window,
		data->scene_img.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window,
		data->minimap_img.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window,
		data->player_img.img, data->minimap_img.width / 2.0
		- data->player_img.width / 2.0, data->minimap_img.height / 2.0
		- data->player_img.height / 2.0);
}

void	create_image(t_image *image, t_data *data, int width, int height)
{
	if (width == 0 || height == 0)
	{
		image->img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, image->path,
				&image->width, &image->height);
	}
	else
	{
		image->img = mlx_new_image(data->mlx.mlx_ptr, width, height);
		image->width = width;
		image->height = height;
	}
	if (image->img == NULL)
	{
		printf("Error loading texture\n");
		close_window(data);
	}
	image->addr = mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
}
