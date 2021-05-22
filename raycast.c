/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:29:19 by vmusunga          #+#    #+#             */
/*   Updated: 2021/05/22 18:50:31 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

double	ft_ray_length(t_data *data)		/** √((x_2-x_1)^2 + (y_2-y-1)^2) **/
{
	double player_x;
	double player_y;
	double ray_x;
	double ray_y;
	double x;
	double y;
	double ray_length;

	player_x = data->px;
	player_y = data->py;
	ray_x = data->rot_x;
	ray_y = data->rot_y;
	x = (ray_x - player_x);
	y = (ray_y - player_y);
	ray_length = hypot(x, y);
	return (ray_length);
}