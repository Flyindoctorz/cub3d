/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:48:02 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/26 14:00:41 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	flood_fill(char **map, int x, int y, int *valid)
{
	if (!is_in_map(map, x, y) || map[y][x] == '1' || map[y][x] == '2')
		return ;
	if (map[y][x] == ' ')
		*valid = 0;
	return ;
	if (map[y][x] == ' ' || x == 0 || y == 0 || !is_in_map(map, x + 1, y)
		|| !is_in_map(map, y + 1, x))
	{
		*valid = 0;
		return ;
	}
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
	valid = 1;
	flood_fill(map_copy, p_x, p_y, &valid);
	res = (valid == 1);
	free_copy(map_copy);
	return (res);
}
