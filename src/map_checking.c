/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:48:02 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/19 16:16:05 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// copy la map pour la flood fill
char	**copy_map(char **map)
{
	int		i;
	char	**map_copy;

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
// free la map_copy
void	free_copy(char **map_copy)
{
	int	i;

	if (!map_copy)
		return ;
	i = 0;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}
// check si le joueur est dans la map
bool	where_player_at(char **map, int *p_x, int *p_y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				*p_x = j;
				*p_y = i;
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

void	flood_fill(char **map, int x, int y, int *valid)
{
	if (map[y][x] == '1' || map[y][x] == '2')
		return ;
	if (map[y][x] == ' ' || x == 0 || y == 0 || !map[y + 1] || !map[y][x + 1])
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

bool	check_map(char **map)
{
	int		**map_copy;
	int		p_x;
	int		p_y;
	int		valid;
	bool	res;

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
}
