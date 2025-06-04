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

#include "../include/parsing.h"
#include "../include/raycasting.h"

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx_ptr, data->scene_img.img);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.mlx_window);
	// mlx_destroy_display(data->mlx.mlx_ptr);
	while (0 < data->map.height--)
		free(data->map.map[data->map.height]);
	free(data->map.map);
	free(data->mlx.mlx_ptr);
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
		close_window(data);
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
	double	next_px;
	double	next_py;

	next_px = data->player.px;
	next_py = data->player.py;
	if (data->keys.w == 1)
		next_px += cos(data->player.angle) * PLAYER_SPEED;
	if (data->keys.s == 1)
		next_px -= cos(data->player.angle) * PLAYER_SPEED;
	if (data->keys.a == 1)
		next_px += cos(data->player.angle - M_PI / 2) * PLAYER_SPEED;
	if (data->keys.d == 1)
		next_px += cos(data->player.angle + M_PI / 2) * PLAYER_SPEED;
	if (next_px >= 0 && next_px < data->map.width
		&& data->map.map[(int)data->player.py][(int)next_px] != '1')
		data->player.px = next_px;
	if (data->keys.w == 1)
		next_py += sin(data->player.angle) * PLAYER_SPEED;
	if (data->keys.s == 1)
		next_py -= sin(data->player.angle) * PLAYER_SPEED;
	if (data->keys.a == 1)
		next_py += sin(data->player.angle - M_PI / 2) * PLAYER_SPEED;
	if (data->keys.d == 1)
		next_py += sin(data->player.angle + M_PI / 2) * PLAYER_SPEED;
	if (next_py >= 0 && next_py < data->map.height
		&& data->map.map[(int)next_py][(int)data->player.px] != '1')
		data->player.py = next_py;
}

int	update_state(t_data *data)
{
	update_coordinates(data);
	if (data->keys.right == 1)
		data->player.angle += (M_PI / 180.0) * PLAYER_ROTATION_SPEED;
	if (data->keys.left == 1)
		data->player.angle -= (M_PI / 180.0) * PLAYER_ROTATION_SPEED;
	if (data->player.angle < 0)
		data->player.angle += 2.0 * M_PI;
	else if (data->player.angle >= 2.0 * M_PI)
		data->player.angle -= 2.0 * M_PI;
	render_scene(&data->player, data);
	return (SUCCESS);
}
