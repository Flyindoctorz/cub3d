/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:15:41 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/12 12:15:47 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
#	define PARSING_H

//#include "cub3d.h"
# include "raycasting.h"
# include "stdbool.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef MAP_MAX_SIZE
#  define MAP_MAX_SIZE 200
# endif

/* ************************** */
/*        STRUCTURES          */
/* ************************** */

typedef struct s_parser_status
{
	bool	all_texture_valid;
	bool	rgb_valid;
	bool	map_valid;
}			t_parser_status;

/* ************************** */
/*           INIT             */
/* ************************** */

int			init_data(t_data *data);
void		init_texture(t_texture *texture);

/* ************************** */
/*       FILE READER          */
/* ************************** */

char		*read_file_content(int fd);
char		**read_file_lines(const char *filename);
char		*read_file_content(int fd);
char		*read_it_full(char *filename);

/* ************************** */
/*        MAP UTILS           */
/* ************************** */

char		**copy_map(char **map);
void		free_copy(char **map_copy);
int			line_width(char *line);
int			line_height(char **map);
bool		is_in_map(char **map, int x, int y);

/* ************************** */
/*        MAP VALID           */
/* ************************** */

bool		is_a_valid_char(char c);
bool		is_valid_map(char **map);
bool		is_valid_player(char c);
bool		where_player_at(char **map, int *p_x, int *p_y);
bool		validate_map(char **map);

/* ************************** */
/*        MAP CLOSE           */
/* ************************** */

void		flood_fill(char **map, int x, int y, int *valid);
bool		check_map_close(char **map);

/* ************************** */
/*      TEXTURE VALID         */
/* ************************** */

bool		validate_file(const char *path);
bool		validate_xpm(const char *path);
bool		validate_single_texture(const char *path, const char *texture_name);
bool		validate_textures(t_texture *texture);
bool		validate_texture_file(const char *path);
bool		validate_all_textures(t_texture *texture);
bool		double_check_texture(t_texture *texture);

/* ************************** */
/*      TEXTURE PARSER        */
/* ************************** */

bool		is_texture_line(char *line, t_texture_id *texture_id, int *pos);
bool		extract_texture_path(char *line, int start,
				t_texture_id *texture_id);
bool		try_to_parse_texture(char *line, t_texture_id *texture_id);
bool		parse_one_texture(char *line, t_texture *texture);
bool		parse_textures_line(char *line, t_texture *texture);
bool		parse_all_textures(char **lines, int end, t_data *data);

/* ************************** */
/*       COLOR PARSER         */
/* ************************** */

bool		is_color_line(char *line, char letter, int *pos);
bool		parse_rgb_component(char *line, int *pos, int *components,
				int component_id);
bool		parse_a_color_line(char *line, t_color *color);
bool		parse_color_line(char *line, t_color *color);
bool		is_valid_rgb_number(int value);
void		color_to_hex(t_color *color);

/* ************************** */
/*        MAP PARSER          */
/* ************************** */

char		**extract_map_lines(char **lines, int start, int end);
bool		parse_map_section(char **lines, t_data *data);
int			find_map_start(char **lines);
int			find_map_end(char **lines, int start);
int			count_map_lines(char **lines, int start, int end);

/* ************************** */
/*      PARSING UTILS         */
/* ************************** */

bool		is_empty_line(char *line);
bool		is_comment_line(char *line);
bool		is_config_line(char *line);
bool		is_map_line(char *line);
bool		is_empty_or_comment(char *line);
void		free_string_array(char **array);
int			ft_strotoi(char *str, char **endptr);
void		init_it_all(t_data *data);
bool		parse_config_section(char **lines, int map_start, t_data *data);
bool		validate_cub_extent(const char *filename);
bool		is_empty_or_whitespace(char *str);

/* ************************** */
/*       PARSING CORE         */
/* ************************** */

void		clean_parsing_data(t_data *data);
bool		parse_single_cubline(char *line, t_data *data);
bool		validate_all_datas(t_data *data);
bool		parse_and_config_map(const char *filename, t_data *data);
bool		parse_cub_file(char **lines, t_data *data);
char		*space_trimer(char *line);
bool		check_after_map(char **lines, int end);
bool		is_bad(char *line);
char		**split_keep_empty(char *str, char sep);
char		*is_truly_empty_line(char *line);
#endif

