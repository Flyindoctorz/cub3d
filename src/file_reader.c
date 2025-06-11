/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:04 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/11 16:02:37 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

static char	*join_and_free(char *content, char *buffer)
{
	char	*temp;
	char	*res;

	temp = content;
	res = ft_strjoin(content, buffer);
	free(temp);
	return (res);
}

char	*read_file_content(int fd)
{
	char	*buff;
	char	*content;
	ssize_t	byte_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (printf("Error allocating memory for buffer\n"), NULL);
	content = ft_strdup("");
	byte_read = read(fd, buff, BUFFER_SIZE);
	while (byte_read > 0)
	{
		buff[byte_read] = '\0';
		content = join_and_free(content, buff);
		if (!content)
			return (free(buff), NULL);
		byte_read = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	if (byte_read < 0)
		return (printf("Error reading file\n"), free(content), NULL);
	return (content);
}

/// @brief 
/// Covered cases:
/// - Empty line
/// @param line 
/// @return 
bool	is_bad(char *line)
{
	char *trimmed_line;

	if (!line || line[0] == '\0' || line[0] == '\n')
		return (true);
	trimmed_line = space_trimer(line);		
	if (!trimmed_line || trimmed_line[0] == '\0')
	{
		if (trimmed_line)
			free(trimmed_line);
		return (true);
	}
	return (false);
}

char	**make_it_split(const char *content)
{
	char	**lines;
	int	i;

	if (!content)
		return (printf("Nothing to split"), NULL);
	lines = split_keep_empty((char *)content, '\n');
	if (!lines)
		return (printf("Error splitting file content"), NULL);
	i = 0;
	while (lines[i])
	{
		if (is_bad(lines[i]) == true)
		{
			free_string_array(lines);
			return (printf("Error: Invalid character in line %d: '%s'\n", i, lines[i]), NULL);
		}
		i++;
	}

	return (lines);
}



char	**read_file_lines(const char *filename)
{
	int		fd;
	char	*content;
	char	**lines;

	if (!filename || ft_strlen(filename) == 0)
		return (printf("Error: Filename is empty or NULL\n"), NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Could not open file %s\n", filename), NULL);
	content = read_file_content(fd);
	close(fd);
	if (!content)
		return (printf("Error: Could not read file content\n"), NULL);
	if (content[0] == '\0')
		return (printf("Error: File is empty\n"), free(content), NULL);
	lines = make_it_split(content);
	free(content);
	if (!lines)
		return (printf("Error: Could not split file content into lines\n"),
			NULL);
	return (lines);
}

char	*read_it_full(char *filename)
{
	int		fd;
	char	*content;

	if (!filename || ft_strlen(filename) == 0)
		return (printf("Error: Filename is empty or NULL\n"), NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Could not open file %s\n", filename), NULL);
	content = read_file_content(fd);
	close(fd);
	if (!content)
		return (printf("Error: Could not read file content\n"), NULL);
	if (content[0] == '\0')
		return (printf("Error: File is empty\n"), free(content), NULL);
	printf("✅ File loaded (%zu bytes)\n", ft_strlen(content));
	return (content);
}
