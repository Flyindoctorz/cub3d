/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:28 by safuente          #+#    #+#             */
/*   Updated: 2025/05/19 18:50:55 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycasting.h"
#include "../parsing.h"

int	initialize(t_data *data)
{
	data->player.x = 1;
	data->player.y = 1;
	data->player.angle = 0;
	data->player.fov = 70;
	data->mlx.mlx_ptr = mlx_init();
	if (!data->mlx.mlx_ptr)
		return (ERROR);
	data->mlx.mlx_window = mlx_new_window(data->mlx.mlx_ptr, WIDTH, HEIGHT,
			"cub3d");
	if (!data->mlx.mlx_window)
		return (ERROR);
	draw_block(&data->block_img, &data->mlx, BLOCK);
	draw_block(&data->player_img, &data->mlx, BLOCK/4);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	char map[5][5] = {
		{'1','1','1','1','1'},
		{'1','0','0','0','1'},
		{'1','0','N','0','1'},
		{'1','0','0','0','1'},
		{'1','1','1','1','1'}
	};
	if (initialize(&data) == ERROR)
		return (ERROR);
	draw_map(map, &data.block_img, &data.player_img, &data.mlx);
	(void)ac;
	(void)av;
	mlx_key_hook(data.mlx.mlx_window, check_input, &data);
	mlx_hook(data.mlx.mlx_window, 17, 1L << 3, close_window, &data);
	mlx_loop(data.mlx.mlx_ptr);
	return (SUCCESS);
}
