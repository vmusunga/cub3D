#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mlx.h"

#define ESC_KEY 53

typedef struct	s_vars
{
	void	*mlx_ptr;
	void	*mlx_win;
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	*player(t_vars *vars)
{
	/*
	vars->py = 500;
	while (vars->py < 700)
	{
		vars->px = 1000;
		while (vars->px < 1200)
		{
			mlx_pixel_put(vars->mlx_ptr, vars->mlx_win, vars->px, vars->py, 0x00FFFFFF);
			vars->px++;
		}
		vars->py++;
	}*/
	mlx_pixel_put(vars->mlx_ptr, vars->mlx_win, vars->px, vars->py, 0x00FFFFFF);
	mlx_pixel_put(vars->mlx_ptr, vars->mlx_win, vars->px + 1, vars->py, 0x00FFFFFF);
	//mlx_pixel_put(vars->mlx_ptr, vars->mlx_win, vars->px + 640, vars->py, 0x00FFFFFF);
	//mlx_pixel_put(vars->mlx_ptr, vars->mlx_win, vars->px + 1, vars->py + 640, 0x00FFFFFF);
	return (0);
}

/*int		move_mtf(t_vars *vars, t_pos *pos)
{
	pos->x++;
	mlx_pixel_put(vars->mlx_ptr, vars->mlx_win, pos->x, pos->y, 0x00FFFFFF);
}*/

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
		player(vars);
	}
	return (0);

}

int main()
{
	t_vars vars;
	//t_data img;

	vars.px = 21;
	vars.py = 21;

	vars.mlx_ptr = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx_ptr, 640, 480, "MA BITE");

	//img.img = mlx_new_image(vars.mlx_ptr, 0, 0);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	player(&vars);

	mlx_key_hook(vars.mlx_win, key_binding, &vars);
	mlx_loop(vars.mlx_ptr);
}