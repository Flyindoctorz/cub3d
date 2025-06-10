/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:43:15 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/10 16:58:48 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/raycasting.h"

int	init_data(t_data *data)
{
	data->map.map = NULL;
	data->map.height = 0;
	data->map.width = 0;
	data->floor.hex = -1;
	data->ceiling.hex = -1;
	init_texture(&data->texture);
	return (SUCCESS);
}

void	init_texture(t_texture *texture)
{
	texture->north.path = NULL;
	texture->north.id = "NO";
	texture->south.path = NULL;
	texture->south.id = "SO";
	texture->west.path = NULL;
	texture->west.id = "WE";
	texture->east.path = NULL;
	texture->east.id = "EA";
}
