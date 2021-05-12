#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mlx.h"

#define ESC_KEY 53

typedef struct	s_vars
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int	px;
	int	py;
}				t_vars;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

int	*player(t_vars *vars, int x, int y)
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
			mlx_pixel_put(vars->mlx_ptr, vars->mlx_win, x, y, 0x000FFF00);
			x++;
		}
		n++;
		y++;
	}
	return (0);
}

int key_binding(int keycode, t_vars *vars)
{
	if (keycode)
		printf("Key pressed ==		%d\n", keycode);
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
		exit (0);
	}
	if (keycode == 2)
	{
		vars->px += 5;
		player(vars, vars->px, vars->py);
	}
	return (0);
}

int main()
{
	t_vars vars;
	//t_vars img;

	vars.px = 10;
	vars.py = 10;

	vars.mlx_ptr = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx_ptr, 640, 480, "MA BI");

	//img.img = mlx_new_image(vars.mlx_ptr, 0, 0);
	//img.addr = mlx_get_vars_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	player(&vars, vars.px, vars.py);

	mlx_key_hook(vars.mlx_win, key_binding, &vars);
	mlx_loop(vars.mlx_ptr);
}