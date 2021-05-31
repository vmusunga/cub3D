/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:55:46 by vmusunga          #+#    #+#             */
/*   Updated: 2021/05/31 16:26:28 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include "includes/key_bindings.h"

void	ft_initialize(t_data *data, t_keys *keys)
{
	data->px = 30;
	data->py = 30;
	data->angle = 0;
	keys->walk_speed = WALK_SPEED;
	keys->turn_speed = TURN_SPEED;
	data->win.width = 1950;
	data->win.height = 1080;
	return ;
}