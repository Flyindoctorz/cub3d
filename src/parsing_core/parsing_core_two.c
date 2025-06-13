/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:15:33 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/12 12:02:09 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/raycasting.h"
#include "../../libft/libft.h"
#include <stdbool.h>

static bool	pre_cub_parse(const char *filename, t_data *data)
{
	char	**lines;
	int		map_start;

	if (!validate_cub_extent(filename))
		return (printf("Invalid file extension: %s\n", filename), false);
	init_data(data);
	lines = read_file_lines(filename);
	if (!lines)
		return (printf("Failed to read file: %s\n", filename), false);
	map_start = find_map_start(lines);
	if (map_start < 0)
		return (printf("No map found in file: %s\n", filename),
			free_string_array(lines), false);
	if (!parse_cub_file(lines, data))
		return (free_string_array(lines), false);
	if (!parse_map_section(lines, data))
		return (free_string_array(lines), false);
	free_string_array(lines);
	return (true);
}

bool	parse_and_config_map(const char *filename, t_data *data)
{
	if (!pre_cub_parse(filename, data))
		return (false);
	if (validate_all_datas(data) == true
		&& validate_map(data->map.map) == true
		&& validate_all_textures(&data->texture) == true)
		return (true);
	else
	{
		clean_parsing_data(data);
		return (false);
	}
}
