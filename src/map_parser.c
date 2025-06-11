/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:52:35 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/11 16:15:22 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

char	*space_trimer(char *line)
{
	int	start;
	int	end;
	int	len;

	if (!line)
		return (NULL);
	start = 0;
	while (line[start] && (line[start] == ' ' || line[start] == '\t'))
		start++;
	if (line[start] == '\0' || line[start] == '\n')
		return (ft_strdup(""));
	end = start;
	while (line[end] && line[end] != '\n')
		end++;
	len = end - start;
	if (len <= 0)
		return (ft_strdup(""));
	return (ft_substr(line, start, len));
}

// char	**extract_map_lines(char **lines, int start, int end)
// {
// 	int		i;
// 	int		map_lines_count;
// 	char	**map;

// 	map_lines_count = count_map_lines(lines, start, end);
// 	if (!map_lines_count)
// 		return (NULL);
// 	map = malloc(sizeof(char *) * (map_lines_count + 1));
// 	if (!map)
// 		return (NULL);
// 	i = start;
// 	map_lines_count = 0;
// 	while (i <= end && lines[i])
// 	{
// 		if (!is_empty_line(lines[i]) && !is_comment_line(lines[i])
// 			&& is_map_line(lines[i]))
// 		{
// 			map[map_lines_count] = ft_strdup(lines[i]);
// 			if (!map[map_lines_count++])
// 				return (free_string_array(map), NULL);
// 		}
// 		i++;
// 	}
// 	map[map_lines_count] = NULL;
// 	return (map);
// }

char	**extract_map_lines(char **lines, int start, int end)
{
	int		i;
	int		count;
	char	**map;
	char	*trimmed;

	count = count_map_lines(lines, start, end);
	if (!count)
		return (printf("No map lines found"), NULL);
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (printf("Map malloc extraction failed"), NULL);
	i = start;
	count = 0;
	while (i <= end && lines[i] && count < count_map_lines(lines, start, end))
	{
		if (is_map_line(lines[i]))
		{
			trimmed = space_trimer(lines[i]);
			if (trimmed)
				map[count++] = trimmed;
		}
		i++;
	}
	map[count] = NULL;
	return (map);
}

static bool	get_map_data(char **line, int start, int end, t_data *data)
{
	int	i;
	int	curr_width;

	if (!line || !data)
		return (false);
	data->map.map = extract_map_lines(line, start, end);
	if (!data->map.map)
		return (false);
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

// bool	parse_map_section(char **lines, t_data *data)
// {
// 	int		start;
// 	int		end;

// 	if (!lines || !data)
// 		return (printf("Invalid input to parse_map_section"), false);
// 	start = find_map_start(lines);
// 	if (start == -1)
// 		return (printf("Map start not found"), false);
// 	end = find_map_end(lines, start);
// 	if (end == -1)
// 		return (printf("Map end not found"), false);
// 	if (!check_after_map(lines, end))
// 		return (false);
// 	return (get_map_data(lines, start, end, data));
// }

bool	parse_map_section(char **lines, t_data *data)
{
	int start;
	int end;

	if (!lines || !data)
		return (printf("Invalid input to parse_map_section"), false);
	start = find_map_start(lines);
	printf("DEBUG: map_start = %d\n", start);
	if (start == -1)
		return (printf("Map start not found"), false);
	end = find_map_end(lines, start);
	printf("DEBUG: map_end = %d\n", end);
	if (end == -1)
		return (printf("Map end not found"), false);

	// Afficher quelques lignes pour debug
	printf("DEBUG: Last map line: '%s'\n", lines[end]);
	if (lines[end + 1])
		printf("DEBUG: Line after map: '%s'\n", lines[end + 1]);
	else
		printf("DEBUG: No line after map (end of file)\n");
	if (!check_after_map(lines, end))
		return (false);
	return (get_map_data(lines, start, end, data));
}