/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:38:52 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/26 11:43:43 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_texture_(t_texture *texture)
{
	texture->north.path = NULL;
	texture->south.path = NULL;
	texture->west.path = NULL;
	texture->east.path = NULL;
	texture->north.id = "NO";
	texture->south.id = "SO";
	texture->west.id = "WE";
	texture->east.id = "EA";
}

bool	is_texture_line(char *line, char *id, int *pos)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' '))
		i++;
	if (ft_strncmp(line + i, id, ft_strlen(id)) != 0)
		return (false);
	i += ft_strlen(id);
	if (line[i] != ' ')
		return (false);
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '#')
		i++;
	if (!line[i] && line[i] != '\n')
		return (false);
	*pos = i;
	return (true);
}

bool	extract_texture_path(char *line, t_texture_id *texture_id)
{
	int	pos;
	int	i;

	if (!is_texture_line(line, texture_id->id, &pos))
		return (false);
	i = pos;
	while (line[i] && line[i] == ' ')
		i++;
	texture_id->path = ft_strdup(line + i);
	if (!texture_id->path)
		return (false);
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i])
		return (false);
	return (true);
}

bool	parse_texture(char *line, t_texture *texture)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '#')
		return (true);
	if (extract_texture_path(line, &texture->north))
		return (true);
	if (extract_texture_path(line, &texture->south))
		return (true);
	if (extract_texture_path(line, &texture->west))
		return (true);
	if (extract_texture_path(line, &texture->east))
		return (true);
	/*if (extract_texture_path(line, &texture->door))
		return (true);*/
	return (false);
}
