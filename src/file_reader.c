/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:04 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/03 11:21:19 by cgelgon          ###   ########.fr       */
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
		return(printf("Error allocating memory for buffer\n"), NULL);
	content = ft_strdup("");
	byte_read = read(fd, buff, BUFFER_SIZE);
	while (byte_read > 0)
	{
		buff[byte_read] = '\0';
		content = join_and_free(content, buff);
		if (!content)
			return(free(buff), NULL);
		byte_read = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	if (byte_read < 0)
		return (printf("Error reading file\n"), free(content), NULL);
	return (content);
}

char	**make_it_split(const char *content)
{
	char	**lines;

	if (!content)
		return (printf("Nothing to split"), NULL);
	lines = ft_split(content, '\n');
	if (!lines)
		return (printf("Error splitting file content"), NULL);
	return (lines);
}



char	*get_all_content(int fd)
{
	char	*buffer;
	char	*content;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	content = ft_strdup("");
	if (!content)
	{
		free(buffer);
		return (NULL);
	}
	content = read_loop(fd, buffer, content);
	free(buffer);
	if (!content || content[0] == '\0')
	{
		free(content);
		return (NULL);
	}
	return (content);
}

char	read_it_full(const char *filename)
{
	int		fd;
	char	*content;

	if (!filename || ft_strlen(filename) == 0)
		return (printf("Error: Filename is empty or NULL\n"), NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Could not open file %s\n", filename), NULL);
	content = get_all_content(fd);
	close(fd);
	if (!content)
		return (printf("Error: Could not read file content\n"), NULL);
	if (content[0] == '\0')
		return (printf("Error: File is empty\n"), free(content), NULL);
	printf("✅ File loaded (%zu bytes)\n", ft_strlen(content));
	return (content);
}

// char	*get_all_content_from_file(char *file_path)
// {
// 	int		fd;
// 	char	*content;

// 	fd = open(file_path, O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);
// 	printf("📖 Reading entire file into memory...\n");
// 	content = get_all_content(fd);
// 	close(fd);
// 	if (!content)
// 	{
// 		printf("❌ Error: Could not read file content\n");
// 		return (NULL);
// 	}
// 	printf("✅ File loaded (%zu bytes)\n", ft_strlen(content));
// 	return (content);
// }
// static char	*read_loop(int fd, char *buffer, char *content)
// {
// 	ssize_t	count;

// 	count = 1;
// 	while (count > 0)
// 	{
// 		count = read(fd, buffer, BUFFER_SIZE);
// 		if (count < 0)
// 		{
// 			free(content);
// 			return (NULL);
// 		}
// 		if (count == 0)
// 			break ;
// 		buffer[count] = '\0';
// 		content = join_and_free(content, buffer);
// 		if (!content)
// 			return (NULL);
// 	}
// 	return (content);
// }