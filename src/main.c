/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:28 by safuente          #+#    #+#             */
/*   Updated: 2025/06/10 16:34:17 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

void	set_images(t_data *data)
{
	data->wallnorth_img.path = data->texture.north.path;
	data->wallsouth_img.path = data->texture.south.path;
	data->walleast_img.path = data->texture.east.path;
	data->wallwest_img.path = data->texture.west.path;
	create_image(&data->scene_img, data, WIDTH, HEIGHT);
	create_image(&data->minimap_img, data, WIDTH / 8, WIDTH / 8);
	create_image(&data->player_img, data, data->minimap_img.width / 32,
		data->minimap_img.width / 32);
	create_image(&data->wallnorth_img, data, 0, 0);
	create_image(&data->walleast_img, data, 0, 0);
	create_image(&data->wallwest_img, data, 0, 0);
	create_image(&data->wallsouth_img, data, 0, 0);
}

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

bool	validate_cub_extent(const char *filename)
{
	int	len;

	if (!filename)
		return (printf("Invalid filename"), false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (printf("File must have a .cub extension"), false);
	return (true);
}

static bool	validate_args(int ac, char **av)
{
	if (ac < 2)
		return (printf("Error: No map file provided.\nUsage: %s <map.cub>\n",
				av[0]), false);
	if (ac > 2)
		return (printf("Error: Too many arguments provided.\n"
						"Usage: %s <map.cub>\n",
						av[0]),
				false);
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
// char		map[8][5] = {
// 	{'1', '1', '1', '1', '1'},
// 	{'1', '0', '0', '0', '1'},
// 	{'1', '0', '0', '0', '1'},
// 	{'1', '0', '0', '0', '1'},
// 	{'1', '1', '0', '0', '1'},
// 	{'1', '0', '1', '0', '1'},
// 	{'1', '0', '1', '0', '1'},
// 	{'1', '1', '1', '1', '1'},
// };
// data.map.map = malloc(sizeof(char *) * 8);
// for (int i = 0; i < 8; i++)
// 	data.map.map[i] = malloc(sizeof(char) * 5);
// for (int i = 0; i < 8; i++)
// 	for (int j = 0; j < 5; j++)
// 		data.map.map[i][j] = map[i][j];
// data.map.height = 8;
// data.map.width = 5;
// (void)ac;
// (void)av;
// // securiser le cas ou il n'y a pas d'argument
// // securiser le cas ou il y a trop d'argument
// // securiser le cas ou on retire l'environnement de force (env -i ou unset)
// // check if the file is a .cub
// // check if the file is a valid map
// if	(initialize(&data) == ERROR)
// 	return (ERROR);
// render_scene(&data.scene_img, &data.player, &data);
// mlx_hook(data.mlx.mlx_window, 2, 1L << 0, key_down, &data);
// mlx_hook(data.mlx.mlx_window, 3, 1L << 1, key_up, &data);
// mlx_hook(data.mlx.mlx_window, 17, 1L << 3, close_window, &data);
// mlx_loop_hook(data.mlx.mlx_ptr, update_state, &data);
// mlx_loop(data.mlx.mlx_ptr);
// return (SUCCESS);
