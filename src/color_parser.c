/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:39:29 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/10 17:12:51 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"
#include "../libft/libft.h"

bool	parse_rgb_component(char *line, int *pos, int *components,
		int component_id)
{
	char	*end_ptr;

	if (component_id >= 3)
		return (true);
	components[component_id] = ft_strotoi(line + *pos, &end_ptr);
	if (end_ptr == line + *pos)
		return (printf("Invalid num format"), false);
	if (!is_valid_rgb_number(components[component_id]))
		return (printf("RGB value is wrong dude. make it 0 - 255"), false);
	*pos += (end_ptr - (line + *pos));
	if (component_id < 2)
	{
		while (line[*pos] && (line[*pos] == ' ' || line[*pos] == '\t'))
			(*pos)++;
		if (line[*pos] != ',')
			return (printf("Expected a comma after RGB component %d",
					component_id + 1), false);
		(*pos)++;
		while (line[*pos] && (line[*pos] == ' ' || line[*pos] == '\t'))
			(*pos)++;
		return (parse_rgb_component(line, pos, components, component_id + 1));
	}
	return (true);
}

bool	parse_color_line(char *line, t_color *color)
{
	int		pos;
	int		components[3];
	char	letter;

	if (!line || !color)
		return (printf("Error: Invalid input to parse_color\n"), false);
	// Déterminer si c'est F ou C
	pos = 0;
	while (line[pos] && (line[pos] == ' ' || line[pos] == '\t'))
		pos++;
	letter = line[pos];
	if (letter != 'F' && letter != 'C')
		return (printf("Error: Expected F or C, got %c\n", letter), false);
	if (!is_color_line(line, letter, &pos))
		return (printf("Error: Invalid color line format\n"), false);
	if (color->hex != -1)
		return (printf("Error: Color already set\n"), false);
	if (!parse_rgb_component(line, &pos, components, 0))
		return (false);
	while (line[pos] && (line[pos] == ' ' || line[pos] == '\t'))
		pos++;
	if (line[pos] && line[pos] != '\n' && line[pos] != '#')
		return (printf("Error: Extra characters after RGB values\n"), false);
	color->red = components[0];
	color->green = components[1];
	color->blue = components[2];
	color_to_hex(color);
	return (true);
}

