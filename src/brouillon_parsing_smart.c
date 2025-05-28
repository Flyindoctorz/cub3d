/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon_parsing_smart.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:56:13 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/28 15:56:14 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:00:00 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/28 16:00:00 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

static bool	is_map_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' || c == 'N' 
		|| c == 'S' || c == 'E' || c == 'W');
}

static float	calculate_map_char_percentage(char *line)
{
	int	total_chars;
	int	map_chars;
	int	i;

	if (!line || !*line)
		return (0.0);
	total_chars = 0;
	map_chars = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
		{
			total_chars++;
			if (is_map_char(line[i]))
				map_chars++;
		}
		i++;
	}
	if (total_chars == 0)
		return (0.0);
	return ((float)map_chars / (float)total_chars);
}

static bool	is_map_line(char *line)
{
	return (calculate_map_char_percentage(line) >= 0.95);
}

static int	find_map_start(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (!is_empty_or_comment(lines[i]) && is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	find_map_end(char **lines, int start)
{
	int	i;
	int	last_map_line;

	last_map_line = start;
	i = start;
	while (lines[i])
	{
		if (!is_empty_or_comment(lines[i]))
		{
			if (is_map_line(lines[i]))
				last_map_line = i;
			else
			{
				printf("Error: Non-map line found after map start: %s\n", lines[i]);
				return (-1);
			}
		}
		i++;
	}
	return (last_map_line);
}

static char	**extract_map_section(char **lines, int start, int end)
{
	char	**map;
	int		map_lines;
	int		i;
	int		map_idx;

	map_lines = 0;
	i = start;
	while (i <= end)
	{
		if (!is_empty_or_comment(lines[i]))
			map_lines++;
		i++;
	}
	map = malloc(sizeof(char *) * (map_lines + 1));
	if (!map)
		return (NULL);
	map[map_lines] = NULL;
	i = start;
	map_idx = 0;
	while (i <= end && map_idx < map_lines)
	{
		if (!is_empty_or_comment(lines[i]))
		{
			map[map_idx] = ft_strdup(lines[i]);
			if (!map[map_idx])
			{
				free_split(map);
				return (NULL);
			}
			map_idx++;
		}
		i++;
	}
	return (map);
}

static bool	parse_config_section(char **lines, int map_start, t_data *data)
{
	int	i;

	i = 0;
	while (i < map_start)
	{
		if (!is_empty_or_comment(lines[i]))
		{
			// Vérifier si c'est une ligne de texture
			if (lines[i][0] == 'N' || lines[i][0] == 'S' 
				|| lines[i][0] == 'W' || lines[i][0] == 'E'
				|| (lines[i][0] == ' ' && (ft_strchr(lines[i], 'N') 
				|| ft_strchr(lines[i], 'S') || ft_strchr(lines[i], 'W') 
				|| ft_strchr(lines[i], 'E'))))
			{
				if (!parse_texture(lines[i], &data->texture))
				{
					printf("Error: Invalid texture line: %s\n", lines[i]);
					return (false);
				}
			}
			// Vérifier si c'est une ligne de couleur
			else if (lines[i][0] == 'F' || lines[i][0] == 'C'
				|| (lines[i][0] == ' ' && (ft_strchr(lines[i], 'F') 
				|| ft_strchr(lines[i], 'C'))))
			{
				if (!parse_a_color_line(lines[i], data))
				{
					printf("Error: Invalid color line: %s\n", lines[i]);
					return (false);
				}
				// Convertir en hex immédiatement
				if (ft_strchr(lines[i], 'F'))
					color_to_hex(&data->floor);
				else if (ft_strchr(lines[i], 'C'))
					color_to_hex(&data->ceiling);
			}
			else
			{
				printf("Error: Unknown configuration line: %s\n", lines[i]);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

static bool	validate_config_complete(t_data *data)
{
	if (!data->texture.north.path)
	{
		printf("Error: Missing NO texture\n");
		return (false);
	}
	if (!data->texture.south.path)
	{
		printf("Error: Missing SO texture\n");
		return (false);
	}
	if (!data->texture.west.path)
	{
		printf("Error: Missing WE texture\n");
		return (false);
	}
	if (!data->texture.east.path)
	{
		printf("Error: Missing EA texture\n");
		return (false);
	}
	if (data->floor.hex == -1)
	{
		printf("Error: Missing F (floor) color\n");
		return (false);
	}
	if (data->ceiling.hex == -1)
	{
		printf("Error: Missing C (ceiling) color\n");
		return (false);
	}
	return (true);
}

bool	parse_the_lines(char **lines, t_data *data)
{
	int	map_start;
	int	map_end;

	// 1. Trouver le début de la map
	map_start = find_map_start(lines);
	if (map_start == -1)
	{
		printf("Error: No map found in file\n");
		return (false);
	}
	
	// 2. Parser la section de configuration avant la map
	if (!parse_config_section(lines, map_start, data))
		return (false);
	
	// 3. Vérifier que toute la configuration est présente
	if (!validate_config_complete(data))
		return (false);
	
	// 4. Trouver la fin de la map
	map_end = find_map_end(lines, map_start);
	if (map_end == -1)
		return (false);
	
	// 5. Extraire la map
	data->map.map = extract_map_section(lines, map_start, map_end);
	if (!data->map.map)
	{
		printf("Error: Failed to extract map\n");
		return (false);
	}
	
	// 6. Calculer les dimensions
	data->map.height = line_height(data->map.map);
	data->map.width = 0;
	for (int i = 0; data->map.map[i]; i++)
	{
		int w = line_width(data->map.map[i]);
		if (w > data->map.width)
			data->map.width = w;
	}
	
	// 7. Valider la map
	if (!validate_map(data->map.map))
		return (false);
	
	printf("✅ Map parsed successfully: %dx%d\n", data->map.width, data->map.height);
	return (true);
}