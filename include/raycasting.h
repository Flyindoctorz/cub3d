/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:13 by safuente          #+#    #+#             */
/*   Updated: 2025/05/19 18:50:51 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define SUCCESS 0
# define ERROR 1

# define WIDTH 360
# define HEIGHT 480

# include "../minilibx/mlx.h"
# include <X11/keysym.h>


typedef struct s_player
{
	double	x;
	double	y;
	int		fov;
}				t_player;

typedef struct s_mlx
{
	t_player	*player;
	void		*mlx;
	void		*mlx_window;
	void		*mlx_map;
}				t_mlx;

/* event handling*/

int	close_window(t_mlx	*data);
int	check_input(int keycode, t_mlx	*data);

#endif
