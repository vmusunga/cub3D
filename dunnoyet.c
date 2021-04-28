/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dunnoyet.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:22:43 by vmusunga          #+#    #+#             */
/*   Updated: 2021/04/28 16:34:22 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;		// bpp (3 RGB + 1 Opacity = 4bits/pixel)
	int			line_length;		// (y * line_length + x * (bits_per_pixel / 8))
	int			endian;				// 1 or 0 (depends on archi, order or sequence of bytes)
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main()
{
	void *mlx_ptr;
	void *win_ptr;
	//void *img_ptr;
	//int pxl_ptr;
	t_data img;
	int x;
	int y;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1950, 1080, "bite");

	img.img = mlx_new_image(mlx_ptr, 200, 100);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	y = 100;
	while (y < 300)
	{
		x = 1000;
		while (x < 1200)
		{
			mlx_pixel_put(&img, win_ptr, x, y, 0x00FFFFEE);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);

	mlx_loop(mlx_ptr);
}
