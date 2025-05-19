/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:28 by safuente          #+#    #+#             */
/*   Updated: 2025/05/19 18:49:23 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycasting.h"
#include "../parsing.h"

void	find_pos(char map[5][5], t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (y < 6)
	{
		x = 0;
		while (x < 6)
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'O')
			{
				printf("%d %d\n", x, y);
				player->x = x;
				player->y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	initialize(t_mlx *data, t_player *player, char map[5][5])
{
	find_pos(map, player);
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

	char map[5][5] = {
		{'1','1','1','1','1'},
		{'1','S','0','0','1'},
		{'1','0','0','0','1'},
		{'1','0','0','0','1'},
		{'1','1','1','1','1'}
	};

	/*map check*/
	if (initialize(&data, &player, map) == ERROR)
		return (ERROR);
	(void)ac;
	(void)av;

	mlx_key_hook(data.mlx_window, check_input, &data);
	mlx_hook(data.mlx_window, 17, 1L << 3, close_window, &data);
	mlx_loop(data.mlx);

	return (SUCCESS);
}
