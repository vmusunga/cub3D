/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusunga <vmusunga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:41:34 by vmusunga          #+#    #+#             */
/*   Updated: 2021/05/27 16:32:41 by vmusunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_BINDINGS_H
# define KEY_BINDINGS_H

# define ESC_KEY 53

# define RIGHT_ARROW_KEY 124
# define LEFT_ARROW_KEY 123
# define UP_ARROW_KEY 126
# define DOWN_ARROW_KEY 125

# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2
# define Q_KEY 12
# define E_KEY 14

# define SPACEBAR_KEY 49
# define LCONTROL_KEY 256

# define WALK_SPEED 0.2
# define TURN_SPEED 0.1

# define PI 3.1415

typedef struct	s_keys {
	int horizontal_pos;
	int vertical_pos;
	int turn_direction;
	float turn_speed;
	float walk_speed;
}				t_keys;


#endif