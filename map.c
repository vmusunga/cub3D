#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "includes/get_next_line.h"
#include "mlx.h"


typedef struct	s_data {
	void *mlx_ptr;
	void *win_ptr;
	void		*img;
	char		*addr;
	int			bits_per_pixel;		// bpp (3 RGB + 1 Opacity = 4bits/pixel)
	int			line_length;		// (y * line_length + x * (bits_per_pixel / 8))
	int			endian;				// 1 or 0 (depends on archi, order or sequence of bytes)
	int px;
	int py;
}				t_data;

typedef struct s_vars {
	int x_max;
	int x_min;
	int y_max;
	int y_min;
}				t_vars;

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
void	ft_classic_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 640, 480, "MAP");
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	*block_pxl(t_data *data, int x, int y)
{
	int i;
	int j;
	int a;

	a = x;		//x init
	i = y + 30;
	j = x + 30;
	while (y < i)
	{
		x = a;
		while (a <= x && x < j)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00FFFFEE);
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_map(t_data *data, int fd)
{
	char **map;
	int x;
	int y;
	int bx;
	int by;

	by = 10;
	x = 0;
	map = ft_map(fd);
	while (map[x])
	{
		bx = 10;
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '1')
				block_pxl(data, bx, by);
			bx += 31;
			y++;
		}
		by += 31;
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
	a = y + 5;
	n = 0;
	while (y <= a)
	{
		x = b;
		min = b - n;
		max = b + n;
		while (min <= x && x <= max)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x000FFF00);
			x++;
		}
		n++;
		y++;
	}
	return (0);
}
int	*player_test(t_data *data)
{
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->px, data->py, 0xFFF00000);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->px + 1, data->py, 0xFFF00000);
	//mlx_pixel_put(data->mlx_ptr, data->mlx_win, data->px + 640, data->py, 0x00FFFFFF);
	//mlx_pixel_put(data->mlx_ptr, data->mlx_win, data->px + 1, data->py + 640, 0x00FFFFFF);
	return (0);
}

int	main()
{
	t_data data;
	int fd;
	data.px = 21;
	data.py = 21;

	fd = open("map.cub", O_RDONLY);
	ft_classic_window(&data);
	draw_map(&data, fd);
	player(&data, 60, 60);
	//player_test(&data);

	mlx_loop(data.mlx_ptr);
}

/*int	main()
{
	void *mlx_ptr;
	void *win_ptr;

	t_data img;
	int x;
	int y;
	int x_max = 1200;
	int x_min = 1000;
	int y_max = 300;
	int y_min = 100;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1950, 1080, "MAP");

	img.img = mlx_new_image(mlx_ptr, 200, 100);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	y = 100;
	while (y <= 300)
	{
		x = 1000;
		if (y == y_min || y == y_max)
		{
			while (x <= x_max)
			{
				mlx_pixel_put(&img, win_ptr, x, y, 0x00FFFFEE);
				x++;
			}
		}
		else
		{
			mlx_pixel_put(&img, win_ptr, x_min, y, 0x00FFFFEE);
			mlx_pixel_put(&img, win_ptr, x_max, y, 0x00FFFFEE);
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);

	mlx_loop(mlx_ptr);
}*/