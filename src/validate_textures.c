/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:47:25 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/28 12:39:05 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

bool	validate_file(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Could not open file %s.\n", path);
		return (false);
	}
	close(fd);
	return (true);
}

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
	int		len;
	char	*ext;

	if (!path)
	{
		printf("Error: Texture path is NULL.\n");
		return (false);
	}
	len = ft_strlen(path);
	if (len < 4)
	{
		printf("Error: Texture path is too short.\n");
		return (false);
	}
	ext = (char *)(path + len - 4);
	if (ft_strncmp(ext, ".xpm", 4) != 0)
	{
		printf("Error: Texture file must be a .xpm file.\n");
		return (false);
	}
	return (true);
}

bool	validate_single_texture(const char *path, const char *texture_name)
{
	if (!validate_xpm(path))
		return (false);
	if (!validate_file(path))
	{
		printf("Error: %s texture file not accesible \n", texture_name);
		return (false);
	}
	return (true);
}

bool	double_check_texture(t_texture *texture)
{
	if (!validate_textures(texture))
		return (false);
	if (!validate_single_texture(texture->north.path, "North"))
		return (false);
	if (!validate_single_texture(texture->south.path, "South"))
		return (false);
	if (!validate_single_texture(texture->west.path, "West"))
		return (false);
	if (!validate_single_texture(texture->east.path, "East"))
		return (false);
	return (true);
}
