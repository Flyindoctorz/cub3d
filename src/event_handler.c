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

int	close_window(t_mlx	*data)
{
	(void)data;
	exit(SUCCESS);
}

int	check_input(int keycode, t_mlx	*data)
{
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_Right)
		data->player->x += 1;
	else if (keycode == XK_Left)
		data->player->x -= 1;
	else if (keycode == XK_Up)
		data->player->y -= 1;
	else if (keycode == XK_Down)
		data->player->y += 1;

	printf("x = %d, y = %d\n", data->player->x, data->player->y);
	return (SUCCESS);
}
