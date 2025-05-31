/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:41 by cgelgon           #+#    #+#             */
/*   Updated: 2025/05/31 10:11:33 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//#include "cub3d.h"
# include "stdbool.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

// stucture
typedef struct s_map
{
	char			**map;
	int				width;
	int				height;
}					t_map;

typedef struct s_texture_id
{
	char			*path;
	char			*id;
	// int		width;
	// int		height;
}					t_texture_id;

typedef struct s_texture
{
	t_texture_id	north;
	t_texture_id	south;
	t_texture_id	west;
	t_texture_id	east;
	// t_texture_id	door;
}					t_texture;

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
	int				hex;
}					t_color;

typedef struct s_parser_status
{
	bool				all_texture_valid;
	bool				rgb_valid;
	bool				map_valid;
}					t_parser_status;

// map utils
char				**copy_map(char **map);
void				free_copy(char **map_copy);
int					line_width(char *line);
int					line_height(char **map);
bool				is_in_map(char **map, int x, int y);

// map validation
bool				is_a_valid_char(char c);
bool				is_valid_map(char **map);
bool				where_player_at(char **map, int *p_x, int *p_y);
bool				validate_map(char **map);

// map closure
void				flood_fill(char **map, int x, int y, int *valid);
bool				check_map_close(char **map);

#endif
