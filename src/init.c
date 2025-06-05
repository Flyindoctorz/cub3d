/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:43:15 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/05 14:57:39 by cgelgon          ###   ########.fr       */
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