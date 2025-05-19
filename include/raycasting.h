/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:46:13 by safuente          #+#    #+#             */
/*   Updated: 2025/05/19 17:25:24 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define SUCCESS 0
# define ERROR 1

# include "../minilibx/mlx.h"
# include <X11/keysym.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_window;
}				t_mlx;

/* event handling*/

int	close_window(t_mlx	*data);
int	check_input(int keycode, t_mlx	*data);

#endif
