/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:23:50 by safuente          #+#    #+#             */
/*   Updated: 2025/05/19 18:50:53 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycasting.h"
#include "../parsing.h"

int	close_window(t_mlx *data)
{
	(void)data;
	exit(SUCCESS);
}

int	check_input(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(&data->mlx);
	else if (keycode == KEY_D)
		data->player.px += 1;
	else if (keycode == KEY_A)
		data->player.px -= 1;
	else if (keycode == KEY_W)
		data->player.py -= 1;
	else if (keycode == KEY_S)
		data->player.py += 1;
	else if (keycode == KEY_RIGHT)
		data->player.angle += M_PI / 180.0;
	else if (keycode == KEY_LEFT)
		data->player.angle -= M_PI / 180.0;

	if (data->player.angle < 0)
		data->player.angle += 2.0 * M_PI;
	else if (data->player.angle >= 2.0 * M_PI)
		data->player.angle -= 2.0 * M_PI;

	// printf("%f\n",data->player.angle);
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.mlx_window);
	mlx_destroy_image(data->mlx.mlx_ptr, data->line_img.img);
	draw_line(&data->line_img, BLOCK, &data->player, data);
	draw_map(data->map, data, &data->mlx);
	return (SUCCESS);
}
