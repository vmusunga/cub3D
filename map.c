/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:41:41 by vmusunga          #+#    #+#             */
/*   Updated: 2021/05/19 13:11:08 by vmusunga         ###   ########.fr       */
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


typedef struct	s_map {
	float rot_x;
	float rot_y;
}				t_map;



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

char	**ft_map(int fd)
{
	int i;
	int x;
	char *line;
	char **map;

	x = 0;
	map = malloc(sizeof(char*) * 100);
	while(1)
	{
		i = get_next_line(fd, &line);
		map[x] = ft_strdup(line);
		free(line);
		x++;
		if (i == 0)
		{
			map[x] = 0;
			return (map);
		}
	}
}

int	block_pxl(t_data *data, int x, int y)
{
	int i;
	int j;
	int a;

	a = x;		//x init
	i = y + 60;
	j = x + 60;
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

int	draw_map(t_data *data)
{
	char **map;
	int fd;
	int x;
	int y;
	int bx;
	int by;

	by = 10;
	x = 0;
	fd = open("map.cub", O_RDONLY);
	map = ft_map(fd);
	while (map[x])
	{
		bx = 10;
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '1')
				block_pxl(data, bx, by);
			bx += 61;
			y++;
		}
		by += 61;
		x++;
	}
	return (0);
}

int	player(t_data *data, int x, int y)
{
	int n;
	int a;
	int min;
	int max;
	int b; //x init
	float rot_x;
	float rot_y;

	b = x;
	a = y + 20;
	n = 0;
	while (y <= a)
	{
		x = b;
		min = b - n;
		max = b + n;
		rot_x = data->px;
		rot_y = data->py;
		while (min <= x && x <= max)
		{
			my_mlx_pixel_put(data, x, y, 0x00FF0000);
			x++;
		}
		n++;
		y++;
	}
	return (0);
}

int	hitbox(t_data *data)
{
	char **map;
	int fd;
	int bx;
	int by;
	int x;
	int y;

	fd = open("map.cub", O_RDONLY);
	map = ft_map(fd);
	x = 0;
	by = 10;
	while (map[x])
	{
		bx = 10;
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '1')
			{
				if ((bx <= data->rot_x && data->rot_x <= bx + 60) || (by <= data->rot_y && data->rot_y <= by + 60))
					return (1);
			}
			bx += 61;
			y++;
		}
		by += 61;
		x++;
	}
	return (0);
}

int	rotation_buisness(t_data *data)
{
	int i;
	//float rot_x;
	//float rot_y;

	i = 0;
	data->rot_x = data->px + 10;
	data->rot_y = data->py + 10;
	while (hitbox(data) == 0)
	{
		my_mlx_pixel_put(data, data->rot_x, data->rot_y, 0x00FF0000);
		data->rot_x += cosf(data->angle);
		data->rot_y += sinf(data->angle);
		//i++;
	}
	return(0);
}

int	ft_construct(t_data *data)
{
	draw_map(data);
	player(data, data->px, data->py);
	rotation_buisness(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}

int key_binding(int keycode, t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, 640, 480);
	if (keycode)
		printf("Key pressed ==		%d\n", keycode);
	if (keycode == D_KEY)
		data->px += 5;
	if (keycode == A_KEY)
		data->px -= 5;
	if (keycode == W_KEY)
		data->py -= 5;
	if (keycode == S_KEY)
		data->py += 5;
	if (keycode == RIGHT_ARROW_KEY)
		data->angle += 0.1;
	if (keycode == LEFT_ARROW_KEY)
		data->angle -= 0.1;
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit (0);
	}
	ft_construct(data);
	return (0);
}

int	main()
{
	t_data data;
	data.px = 100;
	data.py = 100;
	data.angle = 1;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 640, 480, "MAP");
	data.img = mlx_new_image(data.mlx_ptr, 640, 480);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	ft_construct(&data);
	mlx_hook(data.win_ptr, 2, 1L<<0, key_binding, &data);
	mlx_loop(data.mlx_ptr);
}
