/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:48:45 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/04 15:51:00 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_CORE_H
#define PARSING_CORE_H

#include "parsing.h"
#include "raycasting.h"

// parsing core I
void	clean_parsing_data(t_data *data);
bool	parse_single_cubline(char **line, t_data *data);
bool	validate_all_datas(t_data *data);

// parsing core II
bool	parse_and_config_map(const char *filename, t_data *data);


#endif