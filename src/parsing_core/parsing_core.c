/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:37:08 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/10 11:38:33 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

void	clean_parsing_data(t_data *data)
{
	if (!data)
		return;
	if (data->texture.north.path)
		free(data->texture.north.path);
	if (data->texture.south.path)
		free(data->texture.south.path);
	if (data->texture.west.path)
		free(data->texture.west.path);
	if (data->texture.east.path)
		free(data->texture.east.path);
	if (data->map.map)
		free_string_array(data->map.map);
}

bool	parse_a_color_line(char *line, t_color *color)
{
	return (parse_color_line(line, color));
}

bool	parse_textures_line(char *line, t_texture *texture)
{
	return (parse_one_texture(line, texture));
}

bool	parse_single_cubline(char *line, t_data *data)
{
	if (is_empty_line(line) || is_comment_line(line))
		return (true);
	if (!is_config_line(line))
		return(printf("Error: Invalid configuration line: %s\n", line), false);
	if (line[0] == 'F' || ft_strchr(line, 'F'))
		return (parse_a_color_line(line, &data->floor));
	if (line[0] == 'C' || ft_strchr(line, 'C'))
		return (parse_a_color_line(line, &data->ceiling));
	else
		return (parse_textures_line(line, &data->texture));
}





