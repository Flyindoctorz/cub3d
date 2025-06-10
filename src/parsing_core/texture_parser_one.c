/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:13:17 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/10 16:26:57 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/raycasting.h"

bool	is_texture_line(char *line, t_texture_id *texture_id, int *pos)
{
	int	idlen;
	int	i;

	i = 0;
	idlen = ft_strlen(texture_id->id);
	while (line[i] && (ft_isspace(line[i]) || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, texture_id->id, idlen) != 0)
		return (false);
	i += idlen;
	if (line[i] && !ft_isspace(line[i]) && line[i] != '\t')
		return (false);
	while (line[i] && (ft_isspace(line[i]) || line[i] == '\t'))
		i++;
	*pos = i;
	return (true);
}

// bool	extract_texture_path(char *line, int start, t_texture_id *texture_id)
// {
// 	int	end;
// 	int	len;

// 	if (!line[start] || ft_isspace(line[start]) || line[start] == '#')
// 		return (printf("Error: Invalid texture path start in line: %s\n", line),
			false);
// 	end = start;
// 	while (line[end] && !ft_isspace(line[end]) && line[end] != '\t'
// 		&& line[end] != '\n' && line[end] != '#')
// 		end++;
// 	len = end - start;
// 	if (len <= 0)
// 		return (printf("Error: Empty texture path in line: %s\n", line), false);
// 	texture_id->path = ft_substr(line, start, len);
// 	if (!texture_id->path)
// 		return (printf("Error: Memory allocation failed for texture path\n"),
			false);
// 	return (true);
// }
bool	extract_texture_path(char *line, int start, t_texture_id *texture_id)
{
	int	end;
	int	len;

	printf("Debug: extract_texture_path - line[%d] = '%c' (ASCII %d)\n", start,
		line[start], (int)line[start]);
	if (!line[start] || ft_isspace(line[start]) || line[start] == '#')
	{
		printf("Debug: Invalid start character at position %d\n", start);
		return (false);
	}
	end = start;
	while (line[end] && !ft_isspace(line[end]) && line[end] != '\t'
		&& line[end] != '\n' && line[end] != '#')
		end++;
	len = end - start;
	printf("Debug: Path from position %d to %d (length %d)\n", start, end, len);
	if (len <= 0)
		return (false);
	texture_id->path = ft_substr(line, start, len);
	if (!texture_id->path)
		return (false);
	printf("Debug: Extracted texture path: '%s'\n", texture_id->path);
	return (true);
}

bool	try_to_parse_texture(char *line, t_texture_id *texture_id)
{
	int	pos;

	if (!is_texture_line(line, texture_id, &pos))
		return (printf("Error: Invalid texture line format: %s\n", line),
			false);
	if (texture_id->path != NULL)
		return (printf("Error: Duplicate texture definition for %s\n",
				texture_id->id), false);
	printf("Debug: Parsing texture %s from line: %s\n", texture_id->id, line);
	printf("Debug: Path starts at position %d\n", pos);
	return (extract_texture_path(line, pos, texture_id));
}

bool	parse_one_texture(char *line, t_texture *texture)
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
		printf("Debug: Testing texture ID: %s\n", texture_ids[i]->id);
		if (try_to_parse_texture(line, texture_ids[i]))
		{
			printf("Debug: Successfully parsed texture %s\n",
				texture_ids[i]->id);
			return (true);
		}
		i++;
	}
	return (printf("Error: Line doesn't match any texture format: %s\n", line),
		false);
}
