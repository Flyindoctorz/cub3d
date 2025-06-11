/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:17:50 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/11 16:27:41 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

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

int	line_width(char *line)
{
	if (!line)
		return (0);
	return (ft_strlen(line));
}

int	line_height(char **map)
{
	int	h;

	if (!map)
		return (0);
	h = 0;
	while (map[h])
		h++;
	return (h);
}
bool	is_in_map(char **map, int x, int y)
{
	int	map_h;
	int	map_w;

	if (y < 0 || !map[y])
		return (false);
	map_h = line_height(map);
	if (y >= map_h)
		return (false);
	if (x < 0)
		return (false);
	map_w = line_width(map[y]);
	if (x >= map_w)
		return (false);
	return (true);
}
