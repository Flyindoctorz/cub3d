/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:18:32 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/13 12:30:03 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

static bool	check_map_content(char *line, int start_pos)
{
	int	i;
	int	map_char;
	int	total_chars;

	i = start_pos;
	map_char = 0;
	total_chars = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
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

bool	is_map_line(char *line)
{
	int		i;
	bool	has_content;

	if (!line)
		return (false);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || line[i] == '\n' || line[i] == '#')
		return (false);
	has_content = false;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			has_content = true;
			break ;
		}
		i++;
	}
	if (!has_content)
		return (false);
	return (check_map_content(line, i));
}
