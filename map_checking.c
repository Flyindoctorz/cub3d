/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:48:02 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/19 14:28:36 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char **copy_map(char **map)
{
	int i;
	char **map_copy;

	i = 0;
	while (map[i])
		i++;
	map_copy = malloc(sizeof(char *) * (i + 1));
	if (!map_copy)
		return (NULL);
	map_copy[i] = NULL;
	i = 0;
	while (map[i])
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			while (i > 0)
				free(map_copy[--i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	return (map_copy);
}


void flood_fill(char **map, int x, int y, int *valid)
{
	if (map[y][x] == '1' || map[y][x] == '2')
		return;
	if (map[y][x] == ' ' || x == 0 || y == 0 || !map[y+1] ||!map[y][x+1])
	{
		*valid = 0;
		return;
	}
	map[y][x] = '2';
	flood_fill(map, x + 1, y, valid);
	flood_fill(map, x - 1, y, valid);
	flood_fill(map, x, y + 1, valid);
	flood_fill(map, x, y - 1, valid);
}

bool check_map(char **map, int *valid)
{
	int i;
	int j;
	bool found_player;

	*valid = 1;
	found_player = false;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				found_player = true;
				flood_fill(map, j, i, valid);
			}
			j++;
		}
		i++;
	}
	return (*valid);
	if (!found_player)
	{
		*valid = 0;
		printf("Error: No player found in the map.\n");
		return (*valid);
	}
}
