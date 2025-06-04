/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:15:33 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/04 15:51:01 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

static bool	validate_cub_extent(const char *filename)
{
	int	len;

	if (!filename)
		return (printf("Invalid filename"), false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (printf("File must have a .cub extension"), false);
	return (true);
}

static bool	pre_cub_parse(const char *filename, t_data *data)
{
	char	**lines;
	int		map_start;
	char	*content;

	if (!validate_cub_extent(filename))
		return (false);
	init_data(data);
	content = read_file_content(filename);
	if (!content)
		return (printf("Failed to read file: %s\n", filename), false);
	lines = read_file_lines(filename);
	free(content);
	if (!lines)
		return (printf("Failed to read file: %s\n", filename), false);
	map_start = find_map_start(lines);
	if (map_start < 0)
		return (printf("No map found in file: %s\n", filename),
			free_string_array(lines), false);
	if (!parse_cub_file(lines, data))
		return(free_string_array(lines), false);
	if (!parse_map_section(lines, map_start, data))
		return (free_string_array(lines), false);
	free_string_array(lines);
	return (true);
}

bool	parse_and_config_map(const char *filename, t_data *data)
{
	bool	res;
	
	if (!pre_cub_parse(filename, data))
		return (false);
	res = validate_all_datas(data) && validate_map(data->map.map);
	if (!res)
		clean_parsing_data(data);
	return (res);
}
