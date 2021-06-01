/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:29:19 by vmusunga          #+#    #+#             */
/*   Updated: 2021/06/01 12:54:38 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	angle_overflow(t_data *data)
{
	if (data->ray_angle > 2 * PI)
			data->ray_angle -= 2 * PI;
	if (data->ray_angle < 0)
			data->ray_angle += 2 * PI;
	return ;
}

int	rotation_device(t_data *data)
{
	data->rot_x = data->px; // vector's origin
	data->rot_y = data->py;
	while (hitbox_ray(data) == 0)
	{
		my_mlx_pixel_put(data, data->rot_x, data->rot_y, 0x00FF0000);
		data->rot_x += cos(data->ray_angle);
		data->rot_y += sin(data->ray_angle);
	}
	data->ray_length = ft_ray_length(data);
	//printf("(%f)\n", data->ray_length);
	return (0);
}

double	ft_ray_length(t_data *data)		/** √((x_2-x_1)^2 + (y_2-y-1)^2) **/
{
	double player_x;
	double player_y;
	double ray_x;
	double ray_y;
	double x;
	double y;
	double ray_length;

	player_x = data->px;		//player position
	player_y = data->py;
	ray_x = data->rot_x;		//end of ray
	ray_y = data->rot_y;

	x = (ray_x - player_x);
	y = (ray_y - player_y);
	ray_length = hypot(x, y);
	return (ray_length);
}

int	show_3D(t_data *data, t_win *win)
{
	double len;

	len = win->height / data->ray_length;
	data->ray_y = (win->height / 2) - (len / 2);
	while (len > 0)
	{
		my_mlx_pixel_put(data, data->ray_x, data->ray_y, 0x00FFFFEE);
		len--;
		data->ray_y++;
	}
	data->ray_x++;
	return (0);
}

int	raycasting(t_data *data, t_win *win)
{
	int x;

	x = 0;
	data->ray_angle = (data->angle) - (PI / 6);
	//angle_overflow(data);
	data->ray_x = data->rot_x;
	data->ray_y = data->rot_y;
	while (x < win->width)
	{
		rotation_device(data);
		show_3D(data, win);
		data->ray_angle += (PI / 3) / (win->width);
		//angle_overflow(data);
		x++;
	}
	return (0);
}
