/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:47:25 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/26 11:56:07 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	validate_textures(t_texture *texture)
{
	if (!texture->north.path || !texture->south.path
		|| !texture->west.path || !texture->east.path)
	{
		printf("Error: Missing texture path.\n");
		return (false);
	}
	return (true);
}

bool	validate_xpm(const char *path)
{
	int		fd;
	char	buffer[10];
	int		ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Unable to open texture file: %s\n", path);
		return (false);
	}
	ret = read(fd, buffer, sizeof(buffer) - 1);
	close (fd);
	if (ret < 9)
		return (false);
	buffer[9] = '\0';
	return (ft_strncmp(buffer, "/* XPM */", 9) == 0);
}
bool	double_check_texture(t_texture *texture)
{
	if (!validate_textures(texture))
		return (false);
	if (!validate_xpm(texture->north.path)
		|| !validate_xpm(texture->south.path)
		|| !validate_xpm(texture->west.path)
		|| !validate_xpm(texture->east.path))
		return (false);
	return (true);
}