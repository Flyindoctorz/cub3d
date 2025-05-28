/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:48:02 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/28 12:50:45 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	flood_fill(char **map, int x, int y, int *valid)
{
	if (*valid == 0)
		return ;
	if (!is_in_map(map, x, y))
		return ((void)(*valid = 0));
	if (map[y][x] == '=')
		return ((void)(*valid = 0));
	if (x >= line_width(map[y]) || map[y][x] == ' ')
		return ((void)(*valid = 0));
	if (map[y][x] == '1' || map[y][x] == '2')
		return ;
	map[y][x] = '2';
	flood_fill(map, x + 1, y, valid);
	flood_fill(map, x - 1, y, valid);
	flood_fill(map, x, y + 1, valid);
	flood_fill(map, x, y - 1, valid);
}


bool check_map_close(char **map)
{
	char **map_copy;
	int p_x;
	int p_y;
	int valid;
	bool res;
	map_copy = copy_map(map);
	if (!map_copy)
		return (false);
	if (!where_player_at(map_copy, &p_x, &p_y))
	{
		free_copy(map_copy);
		return (false);
	}
	map_copy[p_y][p_x] = '0';
	valid = 1;
	flood_fill(map_copy, p_x, p_y, &valid);
	res = (valid == 1);
	free_copy(map_copy);
	return (res);
}

