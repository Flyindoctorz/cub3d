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

#include "../include/raycasting.h"
#include "../include/parsing.h"

void	set_images(t_data *data)
{
	data->line_img.img = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	data->line_img.addr = mlx_get_data_addr(data->line_img.img,
			&data->line_img.bits_per_pixel, &data->line_img.line_length,
			&data->line_img.endian);
	data->player_img.img = mlx_new_image(data->mlx.mlx_ptr, BLOCK / 4, BLOCK
			/ 4);
	data->player_img.addr = mlx_get_data_addr(data->player_img.img,
			&data->player_img.bits_per_pixel, &data->player_img.line_length,
			&data->player_img.endian);
	data->block_img.img = mlx_new_image(data->mlx.mlx_ptr, BLOCK, BLOCK);
	data->block_img.addr = mlx_get_data_addr(data->block_img.img,
			&data->block_img.bits_per_pixel, &data->block_img.line_length,
			&data->block_img.endian);
}

void	set_player(t_data *data)
{
	data->player.px = 1;
	data->player.py = 1;
	data->player.angle = 0;
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
	draw_block(&data->block_img, BLOCK);
	draw_block(&data->player_img, BLOCK / 4);
	draw_line(&data->line_img, &data->player, data);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	char	map[5][5] = {{'1', '1', '1', '1', '1'}, {'1', '0', '0', '0', '1'},
			{'1', '0', '1', '1', '1'}, {'1', '0', '0', '0', '1'}, {'1', '1',
			'1', '1', '1'}};

	// data.map = malloc(sizeof(char *) * 6);
	// data.map[5] = NULL;
	// for (int i = 0; i < 5; i++)
	// 	data.map[i] = malloc(sizeof(char) * 5);
	// for (int i = 0; i < 5; i++)
	// 	for (int j = 0; j < 5; j++)
	// 		data.map[i][j] = map[i][j];

	// securiser le cas ou il n'y a pas d'argument
	// securiser le cas ou il y a trop d'argument
	// securiser le cas ou on retire l'environnement de force (env -i ou unset)
	// check if the file is a .cub
	// check if the file is a valid map
	if (initialize(&data) == ERROR)
		return (ERROR);
	render_scene(&data.line_img, &data.player, &data);
	// draw_map(data.map, &data, &data.mlx);
	(void)ac;
	(void)av;
	mlx_hook(data.mlx.mlx_window, 2, 1L << 0, key_down, &data);
	mlx_hook(data.mlx.mlx_window, 3, 1L << 1, key_up, &data);
	mlx_hook(data.mlx.mlx_window, 17, 1L << 3, close_window, &data);
	mlx_loop_hook(data.mlx.mlx_ptr, update_state, &data);
	mlx_loop(data.mlx.mlx_ptr);
	return (SUCCESS);
}
