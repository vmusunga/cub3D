/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:41:38 by vmusunga          #+#    #+#             */
/*   Updated: 2021/09/28 15:22:15 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"

#include "get_next_line.h"
#include "key_bindings.h"

# define BLOCK_SIZE 21
# define BLOCK_ORIGIN 0

typedef struct	s_win {
	double	height;
	double	width;
}				t_win;

typedef struct	s_data {
	void *mlx_ptr;
	void *win_ptr;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;

	double angle;
	double px;
	double py;
	double rot_x;
	double rot_y;
	double ray_x;
	double ray_y;
	double ray_angle;
	double ray_length;

	char **map;

	double wall_bottom_x;
	double wall_bottom_y;

	t_win	win;
	t_keys	keys;
}				t_data;



/*
** GRAPHIC
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_construct(t_data *data);
void	ft_initialize(t_data *data, t_keys *keys);
void	ft_move(t_data *data, t_keys *keys);
int	hitbox_ray(t_data *data);
int	hitbox_player(t_data *data, double px, double py);

/*
** KEYS
*/

int	key_pressed(int keycode, t_data *data);
int	key_release(int keycode, t_data *data);
int	key_binding(t_data *data);
void	allow_forward(t_data *data);
void	allow_backward(t_data *data);
void	allow_left(t_data *data);
void	allow_right(t_data *data);

/*
** RAYCASTING
*/

void	ft_ray_length(t_data *data);
int	raycasting(t_data *data, t_win *win);
int	rotation_device(t_data *data);
int	show_3D(t_data *data, t_win *win);

#endif