/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:55:15 by vmusunga          #+#    #+#             */
/*   Updated: 2021/06/01 13:14:53 by vmusunga         ###   ########.fr       */
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
	{
		data->px += dep * cosf(data->angle + PI / 2);
		data->py += dep * sinf(data->angle + PI / 2);
	}
	if (data->keys.a == 1)
	{
		data->px -= dep * cosf(data->angle + PI / 2);
		data->py -= dep * sinf(data->angle + PI / 2);
	}
	if (data->keys.w == 1)
	{
		data->px += dep * cosf(data->angle);
		data->py += dep * sinf(data->angle);
	}
	if (data->keys.s == 1)
	{
		data->px -= dep * cosf(data->angle);
		data->py -= dep * sinf(data->angle);
	}
	if (data->keys.turn_right == 1)
	{
		data->angle += TURN_SPEED;
		//printf("(%f ; %f)\n", data->rot_x, data->rot_y);
	}
	if (data->keys.turn_left == 1)
	{
		data->angle -= TURN_SPEED;
		//printf("(%f ; %f)\n", data->rot_x, data->rot_y);
	}
	if (data->keys.esc == 1)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit (0);
	}
	ft_construct(data);
	return (0);
}

void	ft_move(t_data *data, t_keys *keys)
{}
