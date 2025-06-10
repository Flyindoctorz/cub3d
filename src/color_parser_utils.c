/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:33:22 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/03 13:33:37 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

bool	is_color_line(char *line, char letter, int *pos)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' '))
		i++;
	if (line[i] != letter)
		return (false);
	i++;
	if (line[i] != ' ')
		return (false);
	while (line[i] && line[i] == ' ')
		i++;
	if (!ft_isdigit(line[i]))
		return (false);
	*pos = i;
	return (true);
}

bool	is_valid_rgb_number(int value)
{
	return (value >= 0 && value <= 255);
}

void	color_to_hex(t_color *color)
{
	if (!color)
		return ;
	color->hex = (color->red << 16) | (color->green << 8) | color->blue;
}
