/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_all_datas.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:53:32 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/10 17:28:39 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

bool	validate_all_datas(t_data *data)
{
	if (data->map.map == NULL || data->map.height == 0 || data->map.width == 0)
	{
		printf("Error: Map is not initialized or empty.\n");
		return (false);
	}
	if (data->floor.hex == -1 || data->ceiling.hex == -1)
	{
		printf("Error: Floor or ceiling color not set.\n");
		return (false);
	}
	if (data->texture.north.path == NULL || data->texture.south.path == NULL
		|| data->texture.west.path == NULL || data->texture.east.path == NULL)
	{
		printf("Error: One or more texture paths are not set.\n");
		return (false);
	}
	if (!is_valid_map(data->map.map))
	{
		printf("Error: Invalid characters in map.\n");
		return (false);
	}
	return (true);
}
