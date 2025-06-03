/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:13:17 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/03 12:35:53 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/raycasting.h"

bool	is_texture_line(char *line, t_texture_id *texture_id, int *pos)
{
	int	idlen;
	int		i;
	
	i = 0;
	idlen = strlen(texture_id->id);
	while (line[i] && (ft_isspace(line[i]) || line[i] == '\t'))
		i++;
	if (strncmp(line + i, texture_id->id, idlen) != 0)
		return (false);
	i += idlen;
	if (line[i] && !ft_isspace(line[i]) && line[i] != '\t')
		return (false);
	while (line[i] && (ft_isspace(line[i]), line[i] == '\t'))
		i++;
	pos = i;
	return (true);
}

bool	extract_texture_path(char *line, int start_pos, t_texture_id *texture_id)
{
	int	i;
	int	end;

	i = start_pos;
	while (line[i] && ft_isspace(line[i] ))
		i++;
	i += strlen(texture_id->id);
	while (line[i] && ft_isspace(line[i] && line[i] != '\t' 
		&& line[i] != '\n' && line[i] != '#'))
		i++;
	end = i;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '\t')
		i++;
	if (line[i] != '\0' && line[i] != '\n' && line[i] != '#')
		return (printf("Error: Invalid texture path format in line: %s\n", line), false);
	texture_id->path = ft_substr(line, start_pos, end - start_pos);
	if (!texture_id->path)
		return (printf("Error: Memory allocation failed for texture path\n"), false);
	return (true);
}

bool try_to_parse_texture(char *line, t_texture_id *texture_id)
{
	int	pos;

	if (!is_texture_line(line, texture_id, &pos))
		return (printf("Error: Invalid texture line format: %s\n", line), false);
	if (texture_id->path != NULL)
		return (printf("Error: Duplicate texture definition for %s\n", texture_id->id), false);
	return (extract_texture_path(line, pos, texture_id));
}

bool parse_one_texture(char *line, t_texture *texture)
{
	t_texture_id	*texture_ids[4];
	int				i;
	
	if (!line || !texture)
		return (printf("Error: Empty texture line\n"), false);
	texture_ids[0] = &texture->north;
	texture_ids[1] = &texture->south;
	texture_ids[2] = &texture->west;
	texture_ids[3] = &texture->east;
	i = 0;
	while (i < 4)
	{
		if (try_to_parse_texture(line, texture_ids[i]))
			return (true);
		i++;			
	}
	return (false);
}
