/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:55:46 by vmusunga          #+#    #+#             */
/*   Updated: 2021/05/22 18:55:46 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include "includes/key_bindings.h"

void	ft_initialize(t_data *data, t_keys *keys)
{
	data->px = 100;
	data->py = 100;
	data->angle = 0;
	keys->walk_speed = WALK_SPEED;
	keys->turn_speed = TURN_SPEED;
	return ;
}