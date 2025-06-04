/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:52:35 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/04 16:32:11 by cgelgon          ###   ########.fr       */
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
		if (!is_empty_line(lines[i]) || !is_comment_line(lines[i]))
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

static bool	get_map_data(char **line, int start, int end, t_data *data)
{
	int		i;
	int		curr_width;

	if (!line || !data)
		return (printf("Invalid input to get_map_data"), false);
	data->map.map = extract_map_lines(line, start, end);
	if (!data->map.map)
		return (printf("Failed to extract map lines"), false);
	data->map.height = line_height(data->map.map);
	data->map.width = 0;
	i = 0;
	while (data->map.map[i])
	{
		curr_width = line_width(data->map.map[i]);
		if (curr_width > data->map.width)
			data->map.width = curr_width;
		i++;
	}
	return (true);
}

bool	parse_map_section(char **lines, t_data *data)
{
	int		start;
	int		end;

	if (!lines || !data)
		return (printf("Invalid input to parse_map_section"), false);
	start = find_map_start(lines);
	if (start == -1)
		return (printf("Map start not found"), false);
	end = find_map_end(lines, start);
	if (end == -1)
		return (printf("Map end not found"), false);
	return (get_map_data(lines, start, end, data));
}
