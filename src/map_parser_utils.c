/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:45:48 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/03 13:52:18 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

int	find_map_start(char **lines)
{
	int	i;

	if (!lines)
		return (-1);
	i = 0;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]) && !is_comment_line(lines[i])
			&& is_config_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	find_map_end(char **lines, int start)
{
	int	i;
	int	last_map_line;

	if (!lines || start < 0)
		return (-1);
	last_map_line = start;
	i = start;
	while (lines[i])
	{
		if (is_empty_line(lines[i]) || is_comment_line(lines[i]))
		{
			if (is_map_line(lines[i]))
				last_map_line = i;
			else
				return(printf("Error: Invalid map line at %d\n", i), -1);
		}	
		i++;
	}
	return (last_map_line);
}

int	count_map_lines(char **lines, int start, int end)
{
	int	count;
	int	i;

	if (!lines || start < 0 || end < start)
		return (0);
	count = 0;
	i = start;
	while (i <= end && lines[i])
	{
		if (!is_empty_line(lines[i]) && !is_comment_line(lines[i])
			&& is_map_line(lines[i]))
			count++;
		i++;
	}
	return (count);
}
