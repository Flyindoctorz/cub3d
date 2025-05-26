/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:39:29 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/26 11:39:02 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

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

int	ft_strotoi(char *str, char **endptr)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (endptr)
		*endptr = (char *)(str + i);
	return (result);
}

bool	parse_rgb_component(char *line, int *pos, int *components,
		int component_id)
{
    char *end_ptr;

    if (component_id >= 3)
        return (true);
    components[component_id] = ft_strotoi(line + *pos, &end_ptr);
    if (components[component_id] < 0 || components[component_id] > 255)
        return (false);
    *pos += (end_ptr - (line + *pos));
    if (component_id < 2)
    {
        if (line[*pos] != ',')
            return (false);
        (*pos)++;
    }
    return parse_rgb_component(line, pos, components, component_id + 1);
}

bool parse_color(char *line, t_color *color)
{
    int pos;
    int components[3];

    if (!is_color_line(line, 'F', &pos) && !is_color_line(line, 'C', &pos))
        return (false);
    if (!parse_rgb_component(line, &pos, components, 0))
        return (false);
    color->red = components[0];
    color->green = components[1];
    color->blue = components[2];

    return (true);
}
void color_to_hex(t_color *color)
{
	color->hex = (color->red << 16) | (color->green << 8) | color->blue;
}
