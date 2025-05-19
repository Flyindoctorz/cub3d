/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:28 by safuente          #+#    #+#             */
/*   Updated: 2025/05/19 18:36:13 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycasting.h"
#include "../parsing.h"

int	initialize(t_mlx *data, t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->fov = 70;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ERROR);
	data->mlx_window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	if (!data->mlx_window)
		return (ERROR);
	data->player = player;
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_mlx		data;
	t_player	player;
	char **map = {
		{"0","0","0"},
	}

	/*map check*/
	if (initialize(&data, &player) == ERROR)
		return (ERROR);
	(void)ac;
	(void)av;

	mlx_key_hook(data.mlx_window, check_input, &data);
	mlx_hook(data.mlx_window, 17, 1L << 3, close_window, &data);
	mlx_loop(data.mlx);

	return (SUCCESS);
}
