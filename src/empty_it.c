/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_it.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:30:52 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/11 16:54:23 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

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
