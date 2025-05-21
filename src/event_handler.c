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
		data->player.x += 1;
	else if (keycode == KEY_A)
		data->player.x -= 1;
	else if (keycode == KEY_W)
		data->player.y -= 1;
	else if (keycode == KEY_S)
		data->player.y += 1;
	else if (keycode == KEY_RIGHT)
		data->player.angle += 1;
	else if (keycode == KEY_LEFT)
		data->player.angle -= 1;
	// printf("x = %f, y = %f\n", data->player.x, data->player.y);
	return (SUCCESS);
}
