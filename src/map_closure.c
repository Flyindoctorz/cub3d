/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:48:02 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/11 11:47:20 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	flood_fill(char **map, int x, int y, int *valid)
{
	if (*valid == 0)
		return ;
	if (y < 0 || !map[y] || x < 0)
		return ((void)(*valid = 0));
	if (x >= line_width(map[y]))
		return ((void)(*valid = 0));
	if (map[y][x] == ' ')
		return ((void)(*valid = 0));
	if (map[y][x] == '1' || map[y][x] == '2')
		return ;
	map[y][x] = '2';
	flood_fill(map, x + 1, y, valid);
	flood_fill(map, x - 1, y, valid);
	flood_fill(map, x, y + 1, valid);
	flood_fill(map, x, y - 1, valid);
}

bool	check_border(char **map, int i, int j, int height)
{
	if (map[i][j] == '0' || is_valid_player(map[i][j]))
	{
		if (i == 0 || i == height - 1 || j == 0
			|| j == line_width(map[i]) - 1)
			return (false);
		if ((j > 0 && map[i][j - 1] == ' ') || (map[i][j + 1]
				&& map[i][j + 1] == ' ') || (i > 0
				&& j < line_width(map[i - 1]) && map[i - 1][j] == ' ')
			|| (map[i + 1] && j < line_width(map[i + 1]) && map[i
				+ 1][j] == ' '))
			return (false);
	}
	return (true);
}

static bool	check_map_borders(char **map)
{
	int	i;
	int	j;
	int	height;
	int	res;

	height = line_height(map);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] && map[i][j] != '\n')
		{
			res = check_border(map, i, j, height);
		}
	}
	return (res);
}

bool	check_map_close(char **map)
{
	char	**map_copy;
	int		p_x;
	int		p_y;
	int		valid;
	bool	res;

	if (!check_map_borders(map))
		return (false);
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
