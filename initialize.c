/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:55:46 by vmusunga          #+#    #+#             */
/*   Updated: 2021/09/28 16:50:48 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include "includes/key_bindings.h"

void	ft_initialize(t_data *data, t_keys *keys)
{
	data->px = 50;
	data->py = 50;
	data->angle = 0;
	keys->walk_speed = WALK_SPEED;
	keys->turn_speed = TURN_SPEED;
	data->win.width = 1950;
	data->win.height = 1080;
	//data->ray_length = hypot(data->rot_x - data->px, data->rot_y - data->py);    //---> PAS ARRONDI WTF?
	return ;
}