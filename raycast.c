/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:29:19 by vmusunga          #+#    #+#             */
/*   Updated: 2021/09/28 17:34:20 by vmusunga         ###   ########.fr       */
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

int	rotation_device(t_data *data)					//** GIVES END COORD (rot_x;rot_y) OF VECTOR + DRAWS IT
{
	data->rot_x = data->px; // vector's origin
	data->rot_y = data->py;
	data->wall_bottom_x = 0;
	//data->ray_length = 0;
	while (hitbox_ray(data) == 0)
	{
		my_mlx_pixel_put(data, data->rot_x, data->rot_y, 0x00FF0000);
		//data->ray_length++;
		data->rot_x += cos(data->ray_angle);
		data->rot_y += sin(data->ray_angle);
	}

	//data->wall_bottom_x = data->rot_x;
	//data->wall_bottom_y = data->rot_y;
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
	//double wall_start;

	//data->ray_length *= cos(data->ray_angle);

	data->posy = 0;
	len = win->height / (data->ray_length);
	if (len > win->height)
		len = win->height;
	data->posy = (win->height / 2) - (len / 2);
	while (len > 0)
	{
		my_mlx_pixel_put(data, data->posx, data->posy, 0x00FFFFEE);
		len--;
		data->posy++;
	}
	data->posx++;
	return (0);
}


int	raycasting(t_data *data, t_win *win)
{
	int x;
	x = 0;

	data->ray_angle = (data->angle) - (PI / 6);
	//data->ray_angle = (data->angle);
	//angle_overflow(data);
	data->ray_x = data->rot_x;						//RAY TOUCHING WALL COORD
	data->ray_y = data->rot_y;
	rotation_device(data);
	//len = hypotf();
	
	//data->ray_length = hypot(data->rot_x - data->px, data->rot_y - data->py);
	if (!win->width)
		return (0);
	data->posx = 0;
	while (x < win->width)
	{
		rotation_device(data);
		data->ray_length = hypot(data->rot_x - data->px, data->rot_y - data->py);			// origin(px/py) & end(rot)
		//ft_ray_length(data);
		//ft_ray_length(data);
		
		show_3D(data, win);
		data->ray_angle += (PI / 3) / (win->width);
		//angle_overflow(data);
		data->wall_bottom_x = 0;
		data->wall_bottom_y = 0;
		x++;
	}
	
	return (0);
}

/*	
double len;
	double distx;
	double disty;
printf("len:%f\n",len);
printf("distf:%f\n", distx);

	printf("distx:%f\n", distx);
	printf("disty:%f\n", disty);

		printf("distx:%f\n", distx);
	printf("disty:%f\n", disty);
	
	distx = data->rot_x - data->px;
	disty = data->rot_y - data->py;

	distx *= distx;
	disty *= disty;

	distx += disty;
	
	len = sqrt(distx);
		printf("pos_mur_x:%f\n", data->rot_x);
	printf("pos_mur_y:%f\n", data->rot_y);
	printf("pos_me_x:%f\n", data->px);
	printf("pos_me_y:%f\n", data->py);*/