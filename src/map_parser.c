/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:52:35 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/03 14:18:13 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

char	**extract_map_lines(char **lines, int start, int end)
{
	int		i;
	int		map_lines_count;
	char	**map;
	char	*dup;

	map_lines_count = count_map_lines(lines, start, end);
	if (!map_lines_count)
		return (printf("No map lines found"), NULL);
	map = malloc(sizeof(char *) * (map_lines_count + 1));
	if (!map)
		return (printf("Map malloc extraction faild"), NULL);
	i = start;
	map_lines_count = 0;
	while (i <= end && map_lines_count >= 0)
	{
		if (is_empty_line(lines[i]) || is_comment_line(lines[i]))
		{
			dup = ft_strdup(lines[i]);
			if (!dup)
				return (free_string_array(map), printf("Invalid map line"), NULL);
			map[map_lines_count++] = dup;
		}
		i++;
	}
	return (map);
}
