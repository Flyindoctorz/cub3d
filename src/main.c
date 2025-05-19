/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:28 by safuente          #+#    #+#             */
/*   Updated: 2025/05/19 17:25:01 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycasting.h"
#include "../parsing.h"

#include <stdio.h>

int	main(int ac, char **av)
{
	t_mlx	data;

	(void)ac;
	(void)av;
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ERROR);
	data.mlx_window = mlx_new_window(data.mlx, 1000, 4000, "cub3d");

	mlx_key_hook(data.mlx_window, check_input, &data);
	mlx_hook(data.mlx_window, 17, 1L << 3, close_window, &data);
	mlx_loop(data.mlx);

	return (SUCCESS);
}
