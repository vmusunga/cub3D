/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:55:15 by vmusunga          #+#    #+#             */
/*   Updated: 2021/05/21 17:01:30 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
//#include "includes/key_bindings.h"

int	key_pressed(int keycode, t_keys *keys)
{
	t_data data;
	if (keycode == W_KEY)
		keys->vertical_pos = 1;
	if (keycode == A_KEY)
		keys->horizontal_pos = -1;
	if (keycode == S_KEY)
		keys->vertical_pos = -1;
	if (keycode == D_KEY)
		keys->horizontal_pos = 1;
	if (keycode == RIGHT_ARROW_KEY)
		keys->turn_direction = 1;
	if (keycode == LEFT_ARROW_KEY)
		keys->turn_direction = -1;
	ft_construct(&data);
	return (0);
}

int	key_release(int keycode, t_keys *keys)
{
	if (keycode == W_KEY)
		keys->vertical_pos = 0;
	if (keycode == A_KEY)
		keys->horizontal_pos = 0;
	if (keycode == S_KEY)
		keys->vertical_pos = 0;
	if (keycode == D_KEY)
		keys->horizontal_pos = 0;
	if (keycode == RIGHT_ARROW_KEY)
		keys->turn_direction = 0;
	if (keycode == LEFT_ARROW_KEY)
		keys->turn_direction = 0;
	return (0);
}

void	ft_move(t_data *data, t_keys *keys)
{
	data->px += keys->horizontal_pos * keys->walk_speed;
	data->py += keys->vertical_pos * keys->walk_speed;
	data->angle += keys->turn_direction * keys->turn_speed;
	return ;
}

/*int key_bindings(int keycode, t_data *data, t_keys *keys) 	//!! test keybindingSSSS
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, 640, 480);
	if (keycode)
		printf("Key pressed ==		%d\n", keycode);
	if (keys->move_up == 1)
		data->py -= 5;
	if (keys->move_left == 1)
		data->px -= 5;
	if (keys->move_down == 1)
		data->py += 5;
	if (keys->move_right == 1)
		data->px += 5;
	if (keys->turn_right == 1)
	{
		data->angle += 0.07;
		printf("(%f ; %f)\n", data->rot_x, data->rot_y);
	}
	if (keys->turn_right == 1)
	{
		data->angle -= 0.07;
		printf("(%f ; %f)\n", data->rot_x, data->rot_y);
	}
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit (0);
	}
	ft_construct(data);
	return (0);
}*/
