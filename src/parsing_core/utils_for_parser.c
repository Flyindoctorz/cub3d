/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:58:42 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/02 14:06:35 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/raycasting.h"

bool	is_empty_or_comment(char *line)
{
	int	i;
	
	if (!line || !*line)
		return (true);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '\0' || *line == '#');
}

static float	calculate_map_char_percentage(char *line)
{
	int	total_chars;
	int	map_chars;
	int	i;

	if (!line || !*line)
		return (0.0);
	total_chars = 0;
	map_chars = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
		{
			total_chars++;
			if (is_map_char(line[i]))
				map_chars++;
		}
		i++;
	}
	if (total_chars == 0)
		return (0.0);
	return ((float)map_chars / (float)total_chars);
}

int	ft_strotoi(char *str, char **endptr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (endptr)
		*endptr = (char *)(str + i);
	return (result);
}

void	init_it_all(t_data *data)
{
	data->texture.north.path = NULL;
	data->texture.south.path = NULL;
	data->texture.west.path = NULL;
	data->texture.east.path = NULL;
	data->texture.north.id = "NO";
	data->texture.south.id = "SO";
	data->texture.west.id = "WE";
	data->texture.east.id = "EA";
	data->floor.r = 0;
	data->floor.g = 0;
	data->floor.b = 0;
	data->floor.hex = -1;
	data->ceiling.r = 0;
	data->ceiling.g = 0;
	data->ceiling.b = 0;
	data->ceiling.hex = -1;
	data->map.map = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->player.px = 0.0;
	data->player.py = 0.0;
	data->player.angle = 0.0;	
}





