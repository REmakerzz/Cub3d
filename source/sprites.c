/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:52:32 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/06 15:52:33 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void		sprite_init_param(t_all *d, int i)
{
	double		invdet;

	d->sprite_dr.x = d->sprite[i].x - d->plr.pos_x + 0.5;
	d->sprite_dr.y = d->sprite[i].y - d->plr.pos_y + 0.5;
	invdet = 1.0 / (d->plr.pl_x * d->ray.r_dir_y - d->ray.r_dir_x *
			d->plr.pl_y);
	d->sprite_dr.trform_x = invdet * (d->plr.dir_y * d->sprite_dr.x -
			d->plr.dir_x * d->sprite_dr.y);
	d->sprite_dr.trform_y = invdet * (-d->plr.pl_y * d->sprite_dr.x +
			d->plr.pl_x * d->sprite_dr.y);
	d->sprite_dr.scr = (int)((d->scw / 2) * (1 + d->sprite_dr.trform_x /
			d->sprite_dr.trform_y));
	d->sprite_dr.w = abs((int)((d->sch) * d->aspect_ratio /
			d->sprite_dr.trform_y));
	d->sprite_dr.h = abs((int)((d->sch) * d->aspect_ratio /
			d->sprite_dr.trform_y));
}

int			number_of_sprites(t_all *d)
{
	int			x;
	int			y;
	int			num;

	x = 0;
	num = 0;
	while (d->map.m[x])
	{
		y = 0;
		while (d->map.m[x][y])
		{
			if (d->map.m[x][y] == '2')
				num++;
			y++;
		}
		x++;
	}
	return (num);
}

void		sprite_dist(t_all *d)
{
	int			i;

	i = 0;
	while (d->sprite[i].id != -1)
	{
		d->sprite[i].dist = pow(d->plr.pos_x - d->sprite[i].x, 2) +
							pow(d->plr.pos_y - d->sprite[i].y, 2);
		i++;
	}
}

void		sprite_init(t_all *d)
{
	int			x;
	int			y;
	int			i;

	i = 0;
	x = -1;
	if (!(d->sprite = malloc(sizeof(t_sprite) * (number_of_sprites(d) + 1))))
		runtime_errors(d, -3);
	while (d->map.m[++x])
	{
		y = 0;
		while (d->map.m[x][y])
		{
			if (d->map.m[x][y] == '2')
			{
				d->sprite[i].x = x;
				d->sprite[i].y = y;
				d->sprite[i].id = i;
				i++;
			}
			y++;
		}
	}
	d->sprite[i].id = -1;
}

void		sorte_sprites(t_all *d)
{
	int			i;
	int			j;
	int			count;
	t_sprite	tmp;

	j = 0;
	sprite_init(d);
	sprite_dist(d);
	count = number_of_sprites(d);
	while (j < count)
	{
		i = 0;
		while (d->sprite[i + 1].id != -1)
		{
			if (d->sprite[i].dist < d->sprite[i + 1].dist)
			{
				tmp = d->sprite[i];
				d->sprite[i] = d->sprite[i + 1];
				d->sprite[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}
