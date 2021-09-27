/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:29:19 by vmusunga          #+#    #+#             */
/*   Updated: 2021/09/27 16:40:25 by vmusunga         ###   ########.fr       */
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
	return (0);
}

void	ft_ray_length(t_data *data)		/** √((x_2-x_1)^2 + (y_2-y-1)^2) **/
{

 
	
	//double ray_x;
	//double ray_y;
	double x;
	double y;
	//data->px;		//player position
	//data->py;
	//ray_x = data->rot_x;		//end of ray
	//ray_y = data->rot_y;

	x = (data->rot_x - data->px);
	y = (data->rot_y - data->py);
	data->ray_length = sqrt(pow(x, 2) + pow(y, 2));
	//printf("(%f)\n", data->ray_length);
	return ;
}		//data->ray_length = hypot(data->rot_x - data->px, data->rot_y - data->py);		

/*
** Hauteur des murs trops faible
** Affichage a gauche hors fov
*/

int	show_3D(t_data *data, t_win *win)
{
	double len;

	//data->ray_length *= cos(data->ray_angle);
	len = win->height / (data->ray_length);
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
		data->ray_length = hypot(data->rot_x - data->px, data->rot_y - data->py);			// origin(px/py) & end(rot)
		//ft_ray_length(data);
		rotation_device(data);
		//ft_ray_length(data);
		
		show_3D(data, win);
		data->ray_angle += (PI / 3) / (win->width);
		//angle_overflow(data);
		x++;
	}
	return (0);
}
