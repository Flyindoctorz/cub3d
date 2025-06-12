/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:51:19 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/12 11:51:31 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

bool	is_empty_or_whitespace(char *str)
{
	int	i;

	if (!str)
		return (true);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && str[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

bool	validate_cub_extent(const char *filename)
{
	int	len;

	if (!filename)
		return (printf("Invalid filename"), false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (printf("File must have a .cub extension"), false);
	return (true);
}
