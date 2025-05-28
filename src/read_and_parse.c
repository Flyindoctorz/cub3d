/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:03:32 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/28 15:26:43 by cgelgon          ###   ########.fr       */
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
bool parse_my_cub(char *filename, t_data *data)
{
    char **lines;
	bool res;
    
	if (init_data(data) != SUCCESS)
		return (false);
    lines = make_it_split(filename);
    if (!lines)
        return (false);
	res = parse_the_lines(lines, data);
	free_split(lines);
	if (!res)
		return (false);
    return (validate_all_data(data));
}
