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

int	key_down(int keycode, t_data *data)
{
	if (keycode == KEY_D)
		data->keys.d = 1;
	else if (keycode == KEY_A)
		data->keys.a = 1;
	else if (keycode == KEY_W)
		data->keys.w = 1;
	else if (keycode == KEY_S)
		data->keys.s = 1;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 1;
	else if (keycode == KEY_LEFT)
		data->keys.left = 1;
	else if (keycode == KEY_ESC)
		close_window(&data->mlx);
	return (SUCCESS);
}

int	key_up(int keycode, t_data *data)
{
	if (keycode == KEY_D)
		data->keys.d = 0;
	else if (keycode == KEY_A)
		data->keys.a = 0;
	else if (keycode == KEY_W)
		data->keys.w = 0;
	else if (keycode == KEY_S)
		data->keys.s = 0;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 0;
	else if (keycode == KEY_LEFT)
		data->keys.left = 0;
	return (SUCCESS);
}

void	update_coordinates(t_data *data)
{
	if (data->keys.w == 1)
	{
			data->player.px += cos(data->player.angle) * SPEED;
			data->player.py += sin(data->player.angle) * SPEED;
	}
	if (data->keys.s == 1)
	{
			data->player.px -= cos(data->player.angle) * SPEED;
			data->player.py -= sin(data->player.angle) * SPEED;
	}
	if (data->keys.a == 1)
	{
			data->player.px += cos(data->player.angle - M_PI / 2) * SPEED;
			data->player.py += sin(data->player.angle - M_PI / 2) * SPEED;
	}
	if (data->keys.d == 1)
	{
			data->player.px += cos(data->player.angle + M_PI / 2) * SPEED;
			data->player.py += sin(data->player.angle + M_PI / 2) * SPEED;
	}
}

int	update_state(t_data *data)
{
	update_coordinates(data);
	if (data->keys.right == 1)
		data->player.angle += M_PI / 180.0;
	if (data->keys.left == 1)
		data->player.angle -= M_PI / 180.0;
	if (data->player.angle < 0)
		data->player.angle += 2.0 * M_PI;
	else if (data->player.angle >= 2.0 * M_PI)
		data->player.angle -= 2.0 * M_PI;
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.mlx_window);
	memset(data->line_img.addr, 0, HEIGHT * WIDTH * sizeof(int));
	render_scene(&data->line_img, &data->player, data);
	return (SUCCESS);
}
