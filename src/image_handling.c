/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safuente <safuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:34:46 by safuente          #+#    #+#             */
/*   Updated: 2025/06/06 11:34:46 by safuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycasting.h"

void	render_scene(t_player *player, t_data *data)
{
	raycast(player, data);
	memset(data->minimap_img.addr, 0, data->minimap_img.height
		* data->minimap_img.line_length);
	draw_map(&data->map, data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window,
		data->scene_img.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window,
		data->minimap_img.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_window,
		data->player_img.img, data->minimap_img.width / 2.0
		- data->player_img.width / 2.0, data->minimap_img.height / 2.0
		- data->player_img.height / 2.0);
}
