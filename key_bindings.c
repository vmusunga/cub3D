/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:55:15 by vmusunga          #+#    #+#             */
/*   Updated: 2021/06/07 15:22:45 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
//#include "includes/key_bindings.h"

int	key_pressed(int keycode, t_data *data)
{
	if (keycode)
		printf("Key pressed =	%d\n", keycode);
	if (keycode == ESC_KEY)
		data->keys.esc = 1;
	if (keycode == W_KEY)
		data->keys.w = 1;
	if (keycode == A_KEY)
		data->keys.a = 1;
	if (keycode == S_KEY)
		data->keys.s = 1;
	if (keycode == D_KEY)
		data->keys.d = 1;
	if (keycode == RIGHT_ARROW_KEY)
		data->keys.turn_right = 1;
	if (keycode == LEFT_ARROW_KEY)
		data->keys.turn_left = 1;
	//ft_construct(&data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->keys.w = 0;
	if (keycode == A_KEY)
		data->keys.a = 0;
	if (keycode == S_KEY)
		data->keys.s = 0;
	if (keycode == D_KEY)
		data->keys.d = 0;
	if (keycode == RIGHT_ARROW_KEY)
		data->keys.turn_right = 0;
	if (keycode == LEFT_ARROW_KEY)
		data->keys.turn_left = 0;
	return (0);
}

int key_binding(t_data *data)
{
	float dep;

	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, data->win.width, data->win.height);
	dep = 7 * WALK_SPEED;
	if (data->keys.d == 1)
		allow_right(data);
	if (data->keys.a == 1)
		allow_left(data);
	if (data->keys.w == 1)
		allow_forward(data);
	if (data->keys.s == 1)
		allow_backward(data);
	if (data->keys.turn_right == 1)
	{
		data->angle += TURN_SPEED;
		printf("(%f ; %f)\n", data->rot_x, data->rot_y);
		printf("(%f)\n", data->ray_length);
	}
	if (data->keys.turn_left == 1)
	{
		data->angle -= TURN_SPEED;
		printf("(%f ; %f)\n", data->rot_x, data->rot_y);
		printf("(%f)\n", data->ray_length);	
		printf("SQRT(%f)\n", sqrt(data->rot_x));
	}
	if (data->keys.esc == 1)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit (0);
	}
	ft_construct(data);
	return (0);
}

void	allow_forward(t_data *data)
{
	float dep;
	double testx;
	double testy;

	dep = 7 * WALK_SPEED;
	testx = data->px + dep * cosf(data->angle);
	testy = data->py + dep * sinf(data->angle);
	if (hitbox_player(data, testx, data->py) == 0)
		data->py += dep * sinf(data->angle);
	if (hitbox_player(data, data->px, testy) == 0)
		data->px += dep * cosf(data->angle);
	return ;
}

void	allow_backward(t_data *data)
{
	float dep;
	double testx;
	double testy;

	dep = 7 * WALK_SPEED;
	testx = data->px - dep * cosf(data->angle);
	testy = data->py - dep * sinf(data->angle);
	if (hitbox_player(data, testx, data->py) == 0)
		data->px -= dep * cosf(data->angle);
	if (hitbox_player(data, data->px, testy) == 0)
		data->py -= dep * sinf(data->angle);
	return ;
}

void	allow_left(t_data *data)
{
	float dep;
	float side_angle;
	
	dep = 7 * WALK_SPEED;
	side_angle = data->angle + (PI / 2);
	
	if (hitbox_player(data, data->px - dep * cosf(side_angle), data->py) == 0)
		data->px -= dep * cosf(side_angle);
	if (hitbox_player(data, data->px, data->py - dep * sinf(side_angle)) == 0)
		data->py -= dep * sinf(side_angle);
	return ;
}

void	allow_right(t_data *data)
{
	float dep;
	float side_angle;

	dep = 7 * WALK_SPEED;
	side_angle = data->angle + (PI / 2);

	if (hitbox_player(data, data->px + dep * cosf(side_angle), data->py) == 0)
		data->py += dep * sinf(side_angle);
	if (hitbox_player(data, data->px, data->py + dep * sinf(side_angle)) == 0)
		data->px += dep * cosf(side_angle);
	return ;
}

/*void	define_step(t_data *data)		//THOM
{
	data->keys.stepX = 0;
	data->keys.stepY = 0;
	if ((data->angle > 0 && data->angle < (PI / 2)))
	{
		data->keys.stepX = 1;
		data->keys.stepY = 1;
	}
	if ((data->angle > (PI / 2) && data->angle < PI))
	{
		data->keys.stepX = -1;
		data->keys.stepY = 1;
	}
	if ((data->angle > PI && data->angle < (3 * PI / 2)))
	{
		data->keys.stepX = -1;
		data->keys.stepY = -1;
	}
	if ((data->angle > (3 * PI / 2) && data->angle < (2 * PI)))
	{
		data->keys.stepX = 1;
		data->keys.stepY = -1;
	}
	return ;
}
void	allow_forward(t_data *data)
{
	float dep;
	int x;
	int y;
	
	define_step(data);
	dep = 7 * WALK_SPEED;
	x = (int)((data->px / BLOCK_SIZE) + (dep * data->keys.stepX));
	y = (int)((data->py / BLOCK_SIZE) + (dep * data->keys.stepY));
	if (data->map[x][(int)data->py / BLOCK_SIZE] == '0')
		data->px += dep * cosf(data->angle);
	if (data->map[(int)data->px / BLOCK_SIZE][y] == '0')
		data->py += dep * sinf(data->angle);
	return ;
}*/
