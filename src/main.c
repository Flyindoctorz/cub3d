/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:28 by safuente          #+#    #+#             */
/*   Updated: 2025/06/12 11:51:57 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

bool	set_player(t_data *data)
{
	int		p_x;
	int		p_y;
	char	angle;

	if (!where_player_at(data->map.map, &p_x, &p_y))
		return (printf("Error: No player found in the map.\n"), false);
	data->player.px = (double)p_x + 0.5;
	data->player.py = (double)p_y + 0.5;
	angle = data->map.map[p_y][p_x];
	if (angle == 'N')
		data->player.angle = M_PI + M_PI / 2;
	else if (angle == 'S')
		data->player.angle = M_PI / 2;
	else if (angle == 'E')
		data->player.angle = 0;
	else if (angle == 'W')
		data->player.angle = M_PI;
	else
		return (printf("Error: Invalid player direction in the map.\n"), false);
	data->map.map[p_y][p_x] = '0';
	return (true);
}

void	set_keys(t_data *data)
{
	data->keys.a = 0;
	data->keys.d = 0;
	data->keys.w = 0;
	data->keys.s = 0;
	data->keys.left = 0;
	data->keys.right = 0;
}

int	initialize(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	if (!data->mlx.mlx_ptr)
		return (ERROR);
	data->mlx.mlx_window = mlx_new_window(data->mlx.mlx_ptr, WIDTH, HEIGHT,
			"cub3d");
	if (!data->mlx.mlx_window)
		return (ERROR);
	set_images(data);
	if (!set_player(data))
		return (ERROR);
	set_keys(data);
	return (SUCCESS);
}

bool	validate_args(int ac, char **av)
{
	if (ac < 2)
		return (printf("Error: No map file provided.\nUsage: %s <map.cub>\n",
				av[0]), false);
	if (ac > 2)
		return (printf("Error: Too many arguments provided.\n"
				"Usage: %s <map.cub>\n", av[0]), false);
	if (is_empty_or_whitespace(av[1]))
		return (printf("Error: Empty filename provided.\nUsage: %s <map.cub>\n",
				av[0]), false);
	return (validate_cub_extent(av[1]));
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!validate_args(ac, av))
		return (ERROR);
	if (!parse_and_config_map(av[1], &data))
		return (printf("❌ Error: Failed to parse the map file.\n"),
			clean_parsing_data(&data), ERROR);
	printf("✅ Map parsed successfully! (%dx%d)\n", data.map.width,
		data.map.height);
	printf("🚀 Initializing graphics...\n");
	if (initialize(&data) == ERROR)
		return (printf("❌ Error: Failed to initialize graphics.\n"),
			clean_parsing_data(&data), ERROR);
	printf("✅ Graphics initialized!\n");
	printf("👤 Player: (%.1f, %.1f) facing %.2f rad\n", data.player.px,
		data.player.py, data.player.angle);
	printf("🎮 Starting game...\n");
	draw_player(&data.player_img);
	mlx_hook(data.mlx.mlx_window, 2, 1L << 0, key_down, &data);
	mlx_hook(data.mlx.mlx_window, 3, 1L << 1, key_up, &data);
	mlx_hook(data.mlx.mlx_window, 17, 1L << 3, close_window, &data);
	mlx_loop_hook(data.mlx.mlx_ptr, update_state, &data);
	mlx_loop(data.mlx.mlx_ptr);
	return (SUCCESS);
}
