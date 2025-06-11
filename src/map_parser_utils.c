/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:45:48 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/11 15:26:43 by cgelgon          ###   ########.fr       */
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
		if (is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}
// bool	check_after_map(char **lines, int map_end)
// {
// 	int	i;

// 	i = map_end + 1;
// 	while (lines[i])
// 	{
// 		if (!is_empty_line(lines[i]) && !is_comment_line(lines[i]))
// 		{
// 			if (is_map_line(lines[i]))
// 				return (printf("Error: Map continues after empty line at %d '%s'\n", i, lines[i]), false);
// 			else
// 				return (printf("Error: Invalid line after map at %d '%s'\n", i, lines[i]), false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }

bool	check_after_map(char **lines, int map_end)
{
	int	i;

	printf("DEBUG: check_after_map starting from line %d\n", map_end + 1);
	i = map_end + 1;
	while (lines[i])
	{
		printf("DEBUG: checking line %d: '%s'\n", i, lines[i]);
		if (!is_empty_line(lines[i]) && !is_comment_line(lines[i]))
		{
			if (is_map_line(lines[i]))
				return (printf("Error: Map continues after empty line at %d '%s'\n", i, lines[i]), false);
			else
				return (printf("Error: Invalid line after map at %d '%s'\n", i, lines[i]), false);
		}
		i++;
	}
	return (true);
}

// int	find_map_end(char **lines, int start)
// {
// 	int		i;
// 	int		last_map_line;


// 	if (!lines || start < 0)
// 		return (-1);
// 	last_map_line = start;
// 	i = start;
// 	while (lines[i])
// 	{
// 		if (is_empty_line(lines[i]) || is_comment_line(lines[i]))
// 			break;
// 		else if (!is_map_line(lines[i]))
// 			return (printf("Error: Invalid map line at %d '%s'\n", i, lines[i]),
// 				-1);
// 		else
// 			last_map_line = i;
// 		i++;
// 	}

// 	return (last_map_line);
// }

int find_map_end(char **lines, int start)
{
    int i;
    int last_map_line;
    
    if (!lines || start < 0)
        return (-1);
    last_map_line = start;
    i = start;
    
    while (lines[i])
    {
        printf("DEBUG: line %d: '%s' - empty=%d, comment=%d, map=%d\n", 
               i, lines[i], 
               is_empty_line(lines[i]), 
               is_comment_line(lines[i]), 
               is_map_line(lines[i]));
               
        if (is_empty_line(lines[i]) || is_comment_line(lines[i]))
        {
            printf("DEBUG: Breaking at line %d (empty or comment)\n", i);
            break;
        }
        else if (!is_map_line(lines[i]))
            return (printf("Error: Invalid map line at %d '%s'\n", i, lines[i]), -1);
        else
            last_map_line = i;
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
