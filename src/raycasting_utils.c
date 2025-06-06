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

/*void	draw_line(t_image *image, t_player *player, t_data *data)
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
*/

// int	draw_x;
// int	draw_y;
// draw_y = data->player.py * BLOCK + ((BLOCK - BLOCK / 4.0) / 2);
// draw_x = data->player.px * BLOCK + ((BLOCK - BLOCK / 4.0) / 2);
// mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, data->line_img.img,
// 	0, 0);
// mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, data->player_img.img,
// 	draw_x, draw_y);
// if (map[y][x] == '1')
// 	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window,
// 		data->block_img.img, x * BLOCK, y * BLOCK);
// else if (map[y][x] == 'S' || map[y][x] == 'N' || map[y][x] == 'E'
// 	|| map[y][x] == 'O')
// {
// 	// printf("%d %d\n", x * BLOCK + BLOCK / 2, y * BLOCK + BLOCK / 2);
// 	// mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window,
// 	// 	data->player_img.img, x * BLOCK + BLOCK / 2, y * BLOCK + BLOCK / 2);
// }
