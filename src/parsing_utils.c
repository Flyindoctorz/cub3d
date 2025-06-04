/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:44:28 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/04 16:26:32 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

bool	is_empty_line(char *line)
{
	int i;

	if (!line)
		return (true);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && line[i] != '\t' && line[i] != '\n'
		&& line[i] != '\r')
			return (false);
			i++;
	}
	return (true);
}

bool	is_comment_line(char *line)
{
	int i;

	if (!line)
		return (false);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '#' || line[i] == '\0');
}

bool	is_config_line(const char *line)
{
	int i;
	
	if (!line)
		return (false);
	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (true);
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (true);
	if (line[i] == 'E' && line[i + 1] == 'A')
		return (true);
	if (line[i] == 'W' && line[i + 1] == 'E')
		return (true);
	if (line[i] == 'F' || line[i] == 'C')
		return (true);
	return (false);
}

bool	is_map_line(const char *line)
{
	int	i;
	int	map_char;
	int	total_chars;

	if (is_empty_line(line) || is_comment_line(line))
		return (false);
	i = 0;
	map_char = 0;
	total_chars = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			total_chars++;
			if (is_a_valid_char(line[i]))
				map_char++;
		}
		i++;
	}
		if (total_chars == 0)
			return (false);
	return ((float)map_char / (float)total_chars >= 0.8);
}

void	free_string_array(char **array)
{
	int i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

