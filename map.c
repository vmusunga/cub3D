/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:41:41 by vmusunga          #+#    #+#             */
/*   Updated: 2021/05/21 17:00:55 by vmusunga         ###   ########.fr       */
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

char	**ft_map(int fd, t_data *data)
{
	int i;
	int x;
	char *line;
	//char **map;

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

void	draw_map(t_data *data)
{
	//char **map;
	//int fd;
	int x;
	int y;
	int bx;
	int by;

	by = 10;
	x = 0;
	//fd = open("map.cub", O_RDONLY);
	//map = ft_map(fd);
	while (data->map[x])
	{
		bx = 10;
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == '1')
				block_pxl(data, bx, by);
			bx += 61;
			y++;
		}
		by += 61;
		x++;
	}
	return ;
}

int	hitbox_player(t_data *data, int player_x,int player_y)
{
	int bx;
	int by;
	int x;
	int y;

	x = 0;
	by = 10;
	while (data->map[x])
	{
		bx = 10;
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == '1')
			{
				if ((bx <= player_x && player_x <= bx + 61) && (by <= player_y && player_y <= by + 61))
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

int	player(t_data *data, int x, int y)
{
	int n;
	int a;
	int min;
	int max;
	int b; //x init

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
			if (hitbox_player(data, x, y) == 1) //(x pas au bon endroit)
			{
				//printf("OFF BOUNDS");
				//return(player(data, x, y));
			}
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
	//char **map;
	//int fd;
	int bx;
	int by;
	int x;
	int y;

	//fd = open("map.cub", O_RDONLY);
	//map = ft_map(fd);
	x = 0;
	by = 10;
	while (data->map[x])
	{
		bx = 10;
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == '1')
			{
				if ((bx <= data->rot_x && data->rot_x <= bx + 61) && (by <= data->rot_y && data->rot_y <= by + 61))
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
	//float rot_x;
	//float rot_y;

	data->rot_x = data->px + 10;
	data->rot_y = data->py + 10;
	while (hitbox_ray(data) == 0)
	{
		my_mlx_pixel_put(data, data->rot_x, data->rot_y, 0x00FF0000);
		data->rot_x += cosf(data->angle);
		data->rot_y += sinf(data->angle);
	}
	return(0);
}

int	ft_construct(t_data *data)
{
	int fd;
	fd = open("map.cub", O_RDONLY);
	ft_map(fd, data);
	draw_map(data);
	hitbox_ray(data);
	hitbox_player(data, data->px, data->py);
	//ft_move(data, keys);
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
	{
		data->angle += 0.07;
		printf("(%f ; %f)\n", data->rot_x, data->rot_y);
	}
	if (keycode == LEFT_ARROW_KEY)
	{
		data->angle -= 0.07;
		printf("(%f ; %f)\n", data->rot_x, data->rot_y);
	}
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
	t_keys keys;
	//data.px = 100;
	//data.py = 100;
	//data.angle = 0;
	ft_initialize(&data, &keys);

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 640, 480, "MAP");
	data.img = mlx_new_image(data.mlx_ptr, 640, 480);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	ft_construct(&data);
	
	//mlx_hook(data.win_ptr, 2, 1L<<0, key_pressed, &keys);
	//mlx_hook(data.win_ptr, 3, 1L<<1, key_release, &keys);
	mlx_hook(data.win_ptr, 2, 1L<<0, key_binding, &data);
	mlx_loop(data.mlx_ptr);
}
