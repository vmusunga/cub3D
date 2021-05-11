#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "includes/get_next_line.h"
#include "mlx.h"


typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;		// bpp (3 RGB + 1 Opacity = 4bits/pixel)
	int			line_length;		// (y * line_length + x * (bits_per_pixel / 8))
	int			endian;				// 1 or 0 (depends on archi, order or sequence of bytes)
}				t_data;

void	ft_map(int fd)
{
	int i;
	int x;
	int y;
	char *line;
	char **map;

	x = 0;
	y = 0;
	map = malloc(sizeof(char) * 100);
	fd = open("map.cub", O_RDONLY);
	while(fd)
	{
		i = get_next_line(fd, &line);
		map[x] = ft_strdup(line);
		free(line);
		x++;
	}
	close(fd);
}

int	main()
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
}