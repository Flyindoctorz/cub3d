/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:13:17 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/02 14:07:55 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/raycasting.h"

bool	is_texture_line(char *line, t_texture_id *texture_id)
{
	int	idlen;
	int		i;
	
	i = 0;
	idlen = strlen(texture_id->id);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (strncmp(line + i, texture_id->id, idlen) != 0)
		return (false);
	i += idlen;
	if (line[i] && !ft_isspace(line[i]))
		return (false);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i] || line[i] == '#')
		return (false);
	while (line[i] && !ft_isspace(line[i]) && line[i] != '#')
		i++;
	return (line[i] == '\0' || line[i] == '\n');
}

bool	extract_texture_path(char *line, t_texture_id *texture_id)
{
	int	i;
	int	start;
	int	end;
	int	j;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	i += strlen(texture_id->id);
	while (line[i] && ft_isspace(line[i]))
		i++;
	start = i;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '#')
		i++;
	end = i;
	if (end <= start)
		return (printf("Error: Empty texture path\n"), false);
	texture_id->path = malloc(sizeof (char) * (end - start + 1));
	if (!texture_id->path)
		return (printf("Error: Memory allocation failed for texture path\n"), false);
	j = 0;
	while (start < end)
		texture_id->path[j++] = line[start++];
	texture_id->path[j] = '\0';
	return (true);
}

bool parse_one_texture(char *line, t_texture *texture)
{
	t_texture_id	*texture_ids[4];
	int				i;
	
	texture_ids[0] = &texture->north;
	texture_ids[1] = &texture->south;
	texture_ids[2] = &texture->west;
	texture_ids[3] = &texture->east;
	i = 0;
	while (i < 4)
	{
		if (is_texture_line(line, texture_ids[i]))
		{
			if (texture_ids[i]->path != NULL)
				return (printf("Error: Duplicate texture definition for %s\n", texture_ids[i]->id), false);
			return (extract_texture_path(line, texture_ids[i]));
		}
		i++;
	}
	return (printf("Error: Invalid texture line: %s\n", line), false);
}

bool	parse_all_textures(char **lines, int end, t_data *data)
{
	int	i;
	int	j;
	t_texture_id	*texture_ids[4];
	
	texture_ids[0] = &data->texture.north;
	texture_ids[1] = &data->texture.south;
	texture_ids[2] = &data->texture.west;
	texture_ids[3] = &data->texture.east;
	i = 0;
	while (i < end)
	{
		if (!is_empty_line_or_comment(lines[i]))
		{
			j = 0;
			while (j < 4 && !is_texture_line(lines[i], texture_ids[j]))
				j++;
			if (j == 4)
				return (printf("Error: Unkwnown confing line: %s\n", lines[i]), false);
			if (!parse_one_texture(lines[i], &data->texture))
				return (false);
		}
		i++;
	}
	return (true);
}
