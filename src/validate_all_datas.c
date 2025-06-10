/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_all_datas.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:53:32 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/10 16:29:00 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

// bool	validate_all_datas(t_data *data)
// {
// 	if (data->map.map == NULL || data->map.height == 0 || data->map.width == 0)
// 	{
// 		printf("Error: Map is not initialized or empty.\n");
// 		return (false);
// 	}
// 	if (data->floor.hex == -1 || data->ceiling.hex == -1)
// 	{
// 		printf("Error: Floor or ceiling color not set.\n");
// 		return (false);
// 	}
// 	if (data->texture.north.path == NULL || data->texture.south.path == NULL
// 		|| data->texture.west.path == NULL || data->texture.east.path == NULL)
// 	{
// 		printf("Error: One or more texture paths are not set.\n");
// 		return (false);
// 	}
// 	if (!is_valid_map(data->map.map))
// 	{
// 		printf("Error: Invalid characters in map.\n");
// 		return (false);
// 	}
// 	return (true);
// }

#include "../include/parsing.h"
#include "../include/raycasting.h"

bool	validate_all_datas(t_data *data)
{
	printf("Debug: validate_all_datas called\n");
	printf("Debug: data->map.map = %p\n", (void *)data->map.map);
	printf("Debug: data->map.height = %d\n", data->map.height);
	printf("Debug: data->map.width = %d\n", data->map.width);

	if (data->map.map == NULL || data->map.height == 0 || data->map.width == 0)
	{
		printf("Error: Map is not initialized or empty.\n");
		return (false);
	}

	printf("Debug: data->floor.hex = %d\n", data->floor.hex);
	printf("Debug: data->ceiling.hex = %d\n", data->ceiling.hex);

	if (data->floor.hex == -1 || data->ceiling.hex == -1)
	{
		printf("Error: Floor or ceiling color not set.\n");
		return (false);
	}

	printf("Debug: Texture paths:\n");
	printf("  North: %s\n", data->texture.north.path);
	printf("  South: %s\n", data->texture.south.path);
	printf("  West: %s\n", data->texture.west.path);
	printf("  East: %s\n", data->texture.east.path);

	if (data->texture.north.path == NULL || data->texture.south.path == NULL
		|| data->texture.west.path == NULL || data->texture.east.path == NULL)
	{
		printf("Error: One or more texture paths are not set.\n");
		return (false);
	}

	printf("Debug: Calling is_valid_map\n");
	if (!is_valid_map(data->map.map))
	{
		printf("Error: Invalid characters in map.\n");
		return (false);
	}
	return (true);
}