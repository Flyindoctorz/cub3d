/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:43:09 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/05 10:45:56 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

bool	is_a_valid_char(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ')
		return (true);
	return (false);
}

bool	is_valid_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	is_valid_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (!map || !map[0])
		return ("Map is NULL", (false));
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_a_valid_char(map[i][j]))
			{
				printf("Invalid character '%c' in map at line %d, column %d\n",
					map[i][j], i, j);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
// check si le joueur est dans la map
bool	where_player_at(char **map, int *p_x, int *p_y)
{
	int	i;
	int	j;

	i = 0;
	if (!map || !p_x || !p_y)
		return (printf("incorrect parameters\n"), false);
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
bool	validate_map(char **map)
{
	int	p_x;
	int	p_y;

	if (!map || !map[0])
	{
		printf("Map is empty or NULL\n");
		return (false);
	}
	if (!is_valid_map(map))
		return (printf("Map validation failed\n"), false);
	if (!where_player_at(map, &p_x, &p_y))
		return (printf("Player not found in map\n"), false);
	if (!check_map_close(map))
		return (printf("Map is not closed\n"), false);
	return (true);
}
