/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:41:38 by vmusunga          #+#    #+#             */
/*   Updated: 2021/05/22 18:31:14 by vmusunga         ###   ########.fr       */
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

# define BLOCK_SIZE 71
# define BLOCK_ORIGIN 10

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
	double ray_length;

	char **map;
}				t_data;

/*
** GRAPHIC
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_construct(t_data *data);
void	ft_initialize(t_data *data, t_keys *keys);
void	ft_move(t_data *data, t_keys *keys);

/*
** KEYS
*/

int	key_pressed(int keycode, t_keys *keys);
int	key_release(int keycode, t_keys *keys);
int	key_bindings(int keycode, t_data *data, t_keys *keys);

/*
** RAYCASTING
*/

double	ft_ray_length(t_data *data);

#endif