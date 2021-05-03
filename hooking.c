#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mlx.h"

#define ESC_KEY 53

typedef struct	s_vars
{
	void	*mlx_ptr;
	void	*mlx_win;
}				t_vars;

typedef struct	s_pos
{
	int	x;
	int y;
}				t_pos;

int	*player(t_vars *vars, t_pos *pos)
{
	pos->x = 21;
	pos->y = 21;
	mlx_pixel_put(vars->mlx_ptr, vars->mlx_win, pos->x, pos->y, 0x00FFFFFF);
}

int key_binding(int keycode, t_vars *vars, t_pos *pos)
{
	if (keycode == ESC_KEY)
		mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
	if (keycode)
		printf("Key pressed ==		%d\n", keycode);
	//if (keycode == 2)

}
/*int		move_mtf(t_vars *vars, int x, int y)
{
	mlx_loop_hook(vars->mlx_win, player, &vars);
}*/

int main()
{
	t_vars vars;
	t_pos pos;

	vars.mlx_ptr = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx_ptr, 640, 480, "MA BITE");
	player(&vars,&pos);
	//mlx_loop_hook(vars.mlx_win, key_binding, &vars);


	mlx_key_hook(vars.mlx_win, key_binding, &vars);
	mlx_loop(vars.mlx_ptr);
}