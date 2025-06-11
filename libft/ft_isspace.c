/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:54:21 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/11 16:35:17 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/parsing.h"
#include "../include/raycasting.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}
char	*is_truly_empty_line(char *line)
{
	if (!line)
		return (line);
	if (line[0] == '\0')
		return (line);
	if (line[0] == '\n' && line[1] == '\0')
		return (line);
	return (NULL);
}

bool	is_bad(char *line)
{
	if (!line || line[0] == '\0')
		return (true);
	return (is_truly_empty_line(line));
}
