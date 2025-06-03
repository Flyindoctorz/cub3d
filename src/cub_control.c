/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:03:04 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/03 10:45:19 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

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
