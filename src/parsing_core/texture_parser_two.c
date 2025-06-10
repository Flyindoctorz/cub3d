/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:36:24 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/10 11:23:46 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/raycasting.h"
#include "../../libft/libft.h"

bool	parse_all_textures(char **line, int end, t_data *data)
{
	int	i;

	if (!line || !data || end < 0)
		return (printf("Error: Invalid input to parse_all_textures\n"), false);
	i = 0;
	while (i < end && line[i])
	{
		if (is_empty_or_comment(line[i]) && !is_comment_line(line[i]))
		{
			if (!parse_one_texture(line[i], &data->texture))
				return (false);
		}
		i++;
	}
	return (true);
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
	if (ft_strncmp(ext, ".xpm", 4) != 0)
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
		return (printf("Error: One or more texture paths are not set.\n"),
			false);
	if (!validate_texture_file(texture->north.path)
		|| !validate_texture_file(texture->south.path)
		|| !validate_texture_file(texture->west.path)
		|| !validate_texture_file(texture->east.path))
		return (false);
	return (true);
}
