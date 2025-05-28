/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:03:32 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/28 14:56:55 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

char	*make_it_content(int fd)
{
	int		fd;
	char	buffer[4096];
	char	*content;
	char	*tmp;
	int		bytes_read;

	content = ft_strdup("");
	if (!content)
		return (printf("Error allocating memory"), NULL);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		tmp = content;
		content = strjoin(tmp, buffer);
		free(tmp);
		if (!content)
		{
			perror("Error reallocating memory");
			return (NULL);
		}
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	}
	return (content);
}
char	*read_file_content(const char *filename)
{
	int		fd;
	char	*content;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file %s\n", filename);
		return (NULL);
	}
	content = make_it_content(fd);
	if (!content)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (content);
}
char	**make_it_split(char *filename)
{
	char	*content;
	char	**lines;

	content = read_file_content(filename);
	if (!content)
		return (false);
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
		return (printf("Error splitting file content"), false);
	return (lines);
}
bool	parse_my_lines(char **lines, t_data *data)
{
	int		i;
	bool	inside_map;

	inside_map = false;
	i = 0;
	while (lines[i])
	{
		if (!is_empty_or_comment(lines[i]))
		{
			if (!inside_map)
			{
				if (parse_a_texture_line(lines[i], data->texture))
				{
					i++;
					continue ;
				}
				if (parse_a_color_line(lines[i], data))
				{
					i++;
					continue ;
				}
				/* code */
				inside_map = true;
			}
			if (inside_map)
				printf("Parsing map line: %s\n", lines[i]);
		}
		i++;
	}
	return (true);
}
}

bool parse_cub_file(char *filename, t_data *data)
{
    char **lines;
    
    init_data(data);
    lines = make_it_split(filename);
    if (!lines)
        return (false);
    if (!parse_my_lines(lines, data))
    {
        free_split(lines);
        return (false);
    }

    free_split(lines);
    return (validate_all_data(data));
}
