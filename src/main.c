/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:28 by safuente          #+#    #+#             */
/*   Updated: 2025/05/21 12:50:31 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

void	set_images(t_data *data)
{
	data->wallnorth_img.path = "assets/wall_north.xpm";
	data->wallsouth_img.path = "assets/wall_south.xpm";
	data->walleast_img.path = "assets/wall_east.xpm";
	data->wallwest_img.path = "assets/wall_west.xpm";
	create_image(&data->scene_img, data, WIDTH, HEIGHT);
	create_image(&data->minimap_img, data, WIDTH / 8, WIDTH / 8);
	create_image(&data->player_img, data
		, data->minimap_img.width / 16 , data->minimap_img.width / 16);
	create_image(&data->wallnorth_img, data, 0, 0);
	create_image(&data->walleast_img, data, 0, 0);
	create_image(&data->wallwest_img, data, 0, 0);
	create_image(&data->wallsouth_img, data, 0, 0);
}

void	set_player(t_data *data)
{
	data->player.px = 2;
	data->player.py = 2;
	data->player.angle = M_PI / 2.0 + M_PI;
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
	set_player(data);
	set_keys(data);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	char map[8][5] = {
		{'1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1'},
		{'1', '1', '0', '0', '1'},
		{'1', '0', '1', '0', '1'},
		{'1', '0', '1', '0', '1'},
		{'1', '1', '1', '1', '1'},
	};
	data.map.map = malloc(sizeof(char *) * 8);
	for (int i = 0; i < 8; i++)
		data.map.map[i] = malloc(sizeof(char) * 5);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++)
			data.map.map[i][j] = map[i][j];
	data.map.height = 8;
	data.map.width = 5;
	(void)ac;
	(void)av;
	// securiser le cas ou il n'y a pas d'argument
	// securiser le cas ou il y a trop d'argument
	// securiser le cas ou on retire l'environnement de force (env -i ou unset)
	// check if the file is a .cub
	// check if the file is a valid map
	if (initialize(&data) == ERROR)
		return (ERROR);
	draw_player(&data.player_img);
	render_scene(&data.player, &data);
	mlx_hook(data.mlx.mlx_window, 2, 1L << 0, key_down, &data);
	mlx_hook(data.mlx.mlx_window, 3, 1L << 1, key_up, &data);
	mlx_hook(data.mlx.mlx_window, 17, 1L << 3, close_window, &data);
	mlx_loop_hook(data.mlx.mlx_ptr, update_state, &data);
	mlx_loop(data.mlx.mlx_ptr);
	return (SUCCESS);
}
