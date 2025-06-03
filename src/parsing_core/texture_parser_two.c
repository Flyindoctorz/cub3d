/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:36:24 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/03 13:09:53 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/raycasting.h"
#include "../../libft/libft.h"


bool	parse_textures_line(char *line, t_texture *texture)
{
	int	i;
	t_texture_id	*texture_ids[4];
	
	if (!line || !texture)
		return (printf("Error: Invalid input to parse_all_textures\n"), false);
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

bool	validate_texture_file(const char *path)
{
	int		fd;
	int		len;
	char	*ext;

	if (!path)
		return (printf("Error: Texture path is empty or NULL\n"), false);
	len = ft_strlen(path);
	if (len < 4)
		return (printf("Error: Texture path is too short\n"), false);
	ext = (char *)(path + len - 4);
	if (ft_strncmp(ext, ".xpm") != 0)
		return (printf("Error: Texture file must be a .xpm file\n"), false);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Could not open texture file %s\n", path), false);
	close(fd);
	return (true);
}

bool	validate_all_textures(t_texture *texture)
{
	if (!texture || !texture->north.path || !texture->south.path
		|| !texture->west.path || !texture->east.path)
		return(printf("Error: One or more texture paths are not set.\n"), false);
	if (!validate_texture_file(texture->north.path)
		|| !validate_texture_file(texture->south.path)
		|| !validate_texture_file(texture->west.path)
		|| !validate_texture_file(texture->east.path))
		return (false);
	return (true);
}
