/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_main_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:30:52 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/10 17:31:45 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"


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

bool	validate_args(int ac, char **av)
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
