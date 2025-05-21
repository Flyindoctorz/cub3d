/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:41 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/21 17:00:30 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//#include "cub3d.h"
# include "stdbool.h"
# include <stdlib.h>
# include <stdio.h>

// stucture
typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture_id
{
	char	*path;
	char	*id;
	// int		width;
	// int		height;
}	t_texture_id;

typedef struct s_texture
{
	t_texture_id	north;
	t_texture_id	south;
	t_texture_id	west;
	t_texture_id	east;
	//t_texture_id	door;
}	t_texture;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_data
{
	t_map		map;
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
}	t_data;

// typedef struct s_player
// {
// 	int		x;
// 	int		y;
// 	char	direction;
// }	t_player;

#endif
