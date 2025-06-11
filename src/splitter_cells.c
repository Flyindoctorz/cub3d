/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_cells.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:00:34 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/11 16:01:03 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/parsing.h"
#include "../include/raycasting.h"


static int	count_splits(char *str, char sep)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i])
		if (str[i++] == sep)
			count++;
	return (count);
}

static char	**fill_result(char *str, char sep, char **result)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == sep)
		{
			str[i] = '\0';
			result[count++] = ft_strdup(str);
			str[i] = sep;
			str = str + i + 1;
			i = 0;
		}
		else
			i++;
	}
	result[count++] = ft_strdup(str);
	result[count] = NULL;
	return (result);
}

char	**split_keep_empty(char *str, char sep)
{
	char	**result;
	int		count;

	count = count_splits(str, sep);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	return (fill_result(str, sep, result));
}