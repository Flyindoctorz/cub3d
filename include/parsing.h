/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:41 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/04 16:47:05 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//#include "cub3d.h"
# include "stdbool.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "raycasting.h"


# define BUFFER_SIZE 4096

// structures
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
}				t_color;


typedef struct s_parser_status
{
	bool				all_texture_valid;
	bool				rgb_valid;
	bool				map_valid;
}					t_parser_status;


// included 
int					init_data(t_data *data);
void				init_texture (t_texture *texture);
// file reading
char				*read_file_content(int fd);
char				**read_file_lines(const char *filename);
char				*read_file_content(int fd);
char				*read_it_full(char *filename);

// map utils
char				**copy_map(char **map);
void				free_copy(char **map_copy);
int					line_width(char *line);
int					line_height(char **map);
bool				is_in_map(char **map, int x, int y);
char				is_map_char(char c);

// map validation
bool				is_a_valid_char(char c);
bool				is_valid_map(char **map);
bool				where_player_at(char **map, int *p_x, int *p_y);
bool				validate_map(char **map);

// map closure
void				flood_fill(char **map, int x, int y, int *valid);
bool				check_map_close(char **map);

// texture handling
bool				is_texture_line(char *line, t_texture_id *texture_id);
bool				extract_texture_path(char *line, t_texture_id *texture_id);
bool				parse_texture(char *line, t_texture *texture);
bool				validate_xpm(const char *path);
bool				validate_single_texture(const char *path, const char *texture_name);
bool				validate_textures(t_texture *texture);
bool				double_check_texture(t_texture *texture);

// texture parser
bool				try_to_parse_texture(char *line, t_texture_id *texture_id);
bool				parse_one_texture(char *line, t_texture *texture);
bool				parse_all_textures(char **lines, int end, t_data *data);
bool				validate_texture_file(const char *path);
bool				validate_all_textures(t_texture *texture);

// Utils for cub. line parsing
bool				is_empty_line(char *line);
bool				is_comment_line(char *line);
bool				is_config_line(char *line);
bool				is_map_line(char *line);
void				free_string_array(char **array);

// Map parser utils
int					find_map_start(char **lines);
int					find_map_end(char **lines, int start);
int					count_map_lines(char **lines, int start, int end);

// Utils for parser
bool	is_empty_or_comment(char *line);
float	calculate_map_char_percentage(char *line);
int		ft_strotoi(char *str, char **endptr);
void	init_it_all(t_data *data);
void	parse_config_section(char **lines, int map_start, t_data *data);

// parsing core I
void	clean_parsing_data(t_data *data);
bool	parse_single_cubline(char **line, t_data *data);
bool	validate_all_datas(t_data *data);

// parsing core II
bool	parse_and_config_map(const char *filename, t_data *data);
bool	parse_cub_file(char **lines, t_data *data);


#endif
