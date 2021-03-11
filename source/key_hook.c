/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:33:47 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/01 17:33:48 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void		move_forward(int keycode, t_all *d)
{
	if (keycode == KEY_W)
	{
		if (d->map.m[(int)(d->plr.pos_x + d->plr.dir_x * MOVE)][(int)
				d->plr.pos_y] == '0')
			d->plr.pos_x += d->plr.dir_x * MOVE;
		if (d->map.m[(int)d->plr.pos_x][(int)(d->plr.pos_y + d->plr.dir_y *
			MOVE)] == '0')
			d->plr.pos_y += d->plr.dir_y * MOVE;
	}
	if (keycode == KEY_S)
	{
		if (d->map.m[(int)(d->plr.pos_x - d->plr.dir_x * MOVE)][(int)
				d->plr.pos_y] == '0')
			d->plr.pos_x -= d->plr.dir_x * MOVE;
		if (d->map.m[(int)d->plr.pos_x][(int)(d->plr.pos_y - d->plr.dir_y *
			MOVE)] == '0')
			d->plr.pos_y -= d->plr.dir_y * MOVE;
	}
}

void		move_side(int keycode, t_all *d)
{
	if (keycode == KEY_A)
	{
		if (d->map.m[(int)(d->plr.pos_x - d->plr.pl_x * MOVE)][(int)
				d->plr.pos_y] == '0')
			d->plr.pos_x -= d->plr.pl_x * MOVE;
		if (d->map.m[(int)d->plr.pos_x][(int)(d->plr.pos_y - d->plr.pl_y *
			MOVE)] == '0')
			d->plr.pos_y -= d->plr.pl_y * MOVE;
	}
	if (keycode == KEY_D)
	{
		if (d->map.m[(int)(d->plr.pos_x + d->plr.pl_x * MOVE)][(int)
				d->plr.pos_y] == '0')
			d->plr.pos_x += d->plr.pl_x * MOVE;
		if (d->map.m[(int)d->plr.pos_x][(int)(d->plr.pos_y + d->plr.pl_y *
			MOVE)] == '0')
			d->plr.pos_y += d->plr.pl_y * MOVE;
	}
}

void		move_turn(int keycode, t_all *d)
{
	double	dir_x_old;
	double	pl_x_old;

	if (keycode == KEY_RIGHT)
	{
		dir_x_old = d->plr.dir_x;
		d->plr.dir_x = d->plr.dir_x * cos(-TURN) - d->plr.dir_y * sin(-TURN);
		d->plr.dir_y = dir_x_old * sin(-TURN) + d->plr.dir_y * cos(-TURN);
		pl_x_old = d->plr.pl_x;
		d->plr.pl_x = d->plr.pl_x * cos(-TURN) - d->plr.pl_y * sin(-TURN);
		d->plr.pl_y = pl_x_old * sin(-TURN) + d->plr.pl_y * cos(-TURN);
	}
	if (keycode == KEY_LEFT)
	{
		dir_x_old = d->plr.dir_x;
		d->plr.dir_x = d->plr.dir_x * cos(TURN) - d->plr.dir_y * sin(TURN);
		d->plr.dir_y = dir_x_old * sin(TURN) + d->plr.dir_y * cos(TURN);
		pl_x_old = d->plr.pl_x;
		d->plr.pl_x = d->plr.pl_x * cos(TURN) - d->plr.pl_y * sin(TURN);
		d->plr.pl_y = pl_x_old * sin(TURN) + d->plr.pl_y * cos(TURN);
	}
}

int			key_hook(int keycode, t_all *d)
{
	move_forward(keycode, d);
	move_side(keycode, d);
	move_turn(keycode, d);
	if (keycode == KEY_ESC)
		ft_close(d);
	return (0);
}
