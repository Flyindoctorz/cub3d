/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:03:04 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/26 14:38:55 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_a_cub(char *filename)
{
	char	*ext;
	int		len;

	if (filename == NULL)
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	ext = filename + len - 4;
	return (ft_strcmp(ext, ".cub") == 0);
}

bool	is_empty_or_comment(char *line)
{
	if (line == NULL || *line == '\0')
		return (true);
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '\0' || *line == '#')
		return (true);
	return (false);
}

bool	parse_a_color_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == 'F')
	{
		if (data->floor.hex != -1)
			return (false);
		return (parse_color(line, &data->floor));
	}
	else if (line[i] == 'C')
	{
		if (data->ceiling.hex != -1)
			return (false);
		return (parse_color(line, &data->ceiling));
	}
	return (false);
}
bool	add_a_line(char *line, t_data *data)
{
	char **
}