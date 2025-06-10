/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whole_cub_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:57:43 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/10 11:35:21 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

bool	parse_cub_file(char **lines, t_data *data)
{
	int map_start;
	int i;

	if (!lines || !data)
		return (printf("Invalid input to parse_cub_file"), false);
	map_start = find_map_start(lines);
	if (map_start < 0)
		return (printf("No map start found"), false);
	i = 0;
	while (i < map_start && lines[i])
	{
		if (!parse_single_cubline(lines[i], data))
			return (printf("Failed to parse line: %s\n", lines[i]), false);
		i++;
	}
	return (true);
}