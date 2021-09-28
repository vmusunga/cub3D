/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:41:41 by vmusunga          #+#    #+#             */
/*   Updated: 2021/09/28 15:23:18 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "includes/get_next_line.h"
#include "includes/key_bindings.h"
#include "mlx.h"
#include "includes/cub3d.h"

char	**ft_map(int fd, t_data *data) //!\\ malloc: count lines
{
	int i;
	int x;
	char *line;

	x = 0;
	data->map = malloc(sizeof(char*) * 100);
	while(1)
	{
		i = get_next_line(fd, &line);
		data->map[x] = ft_strdup(line);
		free(line);
		x++;
		if (i == 0)
		{
			data->map[x] = 0;
			return (data->map);
		}
	}
}

int	block_pxl(t_data *data, int x, int y)
{
	int i;
	int j;
	int a;

	a = x;		//x init
	i = y + BLOCK_SIZE - 1;
	j = x + BLOCK_SIZE - 1;
	while (y < i)
	{
		x = a;
		while (a <= x && x < j)
		{
			my_mlx_pixel_put(data, x, y, 0x00FFFFEE);
			x++;
		}
		y++;
	}
	return (0);
}

void	draw_map(t_data *data)
{
	int x;
	int y;
	double bx;
	double by;

	by = BLOCK_ORIGIN;
	x = 0;
	while (data->map[x])
	{
		bx = BLOCK_ORIGIN;
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == '1')
				block_pxl(data, bx, by);
			bx += BLOCK_SIZE;
			y++;
		}
		by += BLOCK_SIZE;
		x++;
	}
	return ;
}

int	hitbox_player(t_data *data, double px, double py)
{
	double bx;
	double by;
	int x;
	int y;

	x = 0;
	by = BLOCK_ORIGIN;
	while (data->map[x])
	{
		bx = BLOCK_ORIGIN;
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == '1')
			{
				if ((bx <= px && px <= bx + BLOCK_SIZE) && (by <= py && py <= by + BLOCK_SIZE))
					return (1);
			}
			bx += BLOCK_SIZE;
			y++;
		}
		by += BLOCK_SIZE;
		x++;
	}
	return (0);
}

int	player(t_data *data)
{
	int n;
	double a;
	double min;
	double max;
	double b; //x init
	double x;
	double y;

	x = data->px;
	y = data->py;
	b = x;
	a = y + 20;
	n = 0;
	while (y <= a)
	{
		x = b;
		min = b - n;
		max = b + n;
		while (min <= x && x <= max)
		{
			/*if (hitbox_player(data, x, y) == 1) //(x pas au bon endroit)
			{
				//printf("OFF BOUNDS");
				//return(player(data, x, y));
			}*/
			my_mlx_pixel_put(data, x, y, 0x00FF0000);
			x++;
		}
		n++;
		y++;
	}
	return (0);
}

int	hitbox_ray(t_data *data)
{
	double bx;
	double by;
	int x;
	int y;

	x = 0;
	by = BLOCK_ORIGIN;
	while (data->map[x])
	{
		bx = BLOCK_ORIGIN;
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == '1')
			{
				if ((bx <= data->rot_x && data->rot_x <= bx + BLOCK_SIZE) && (by <= data->rot_y && data->rot_y <= by + BLOCK_SIZE))
					return (1);
			}
			bx += BLOCK_SIZE;
			y++;
		}
		by += BLOCK_SIZE;
		x++;
	}
	return (0);
}

int	centered_ray(t_data *data)
{
	data->rot_x = data->px; // vector's origin
	data->rot_y = data->py;
	while (hitbox_ray(data) == 0)
	{
		my_mlx_pixel_put(data, data->rot_x, data->rot_y, 0x0000FF);
		data->rot_x += cos(data->angle);
		data->rot_y += sin(data->angle);
	}
	//printf("(%f)\n", data->ray_length);
	return (0);
}

void	ft_construct(t_data *data)
{
	int fd;
	fd = open("map.cub", O_RDONLY);
	//t_keys keys;
	//ft_move(data, &keys);

	//data->ray_length = hypot(data->rot_x - data->px, data->rot_y - data->py);
	//printf("(%f)\n", data->ray_length);

	ft_map(fd, data);
	draw_map(data);
	//hitbox_player(data, data->px, data->py);
	//player(data);
	//hitbox_ray(data);
	raycasting(data, &data->win);
	centered_ray(data);

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return ;
}

int	main()
{
	t_data data;
	t_keys keys;
	ft_initialize(&data, &keys);

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.win.width, data.win.height, "MAP");
	data.img = mlx_new_image(data.mlx_ptr, data.win.width, data.win.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	ft_construct(&data);
	
	mlx_hook(data.win_ptr, 2, 1L<<0, key_pressed, &data);
	mlx_hook(data.win_ptr, 3, 1L<<1, key_release, &data);
	mlx_loop_hook(data.mlx_ptr, key_binding, &data);
	mlx_loop(data.mlx_ptr);
}