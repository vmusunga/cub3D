/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:41:38 by vmusunga          #+#    #+#             */
/*   Updated: 2021/05/14 16:09:59 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"

#include "get_next_line.h"
/*
typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;		// bpp (3 RGB + 1 Opacity = 4bits/pixel)
	int			line_length;		// (y * line_length + x * (bits_per_pixel / 8))
	int			endian;				// 1 or 0 (depends on archi, order or sequence of bytes)
}				t_data;
*/

typedef struct	s_data {
	void *mlx_ptr;
	void *win_ptr;
	void		*img;
	char		*addr;
	int			bits_per_pixel;		// bpp (3 RGB + 1 Opacity = 4bits/pixel)
	int			line_length;		// (y * line_length + x * (bits_per_pixel / 8))
	int			endian;				// 1 or 0 (depends on archi, order or sequence of bytes)
	float angle;
	int px;
	int py;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);