/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:49:24 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/06 15:49:25 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

unsigned int	my_mlx_pixel_read(t_texture *wall, int x, int y)
{
	char	*dst;

	dst = wall->addr + (y * wall->len + x * (wall->bits / 8));
	return (*(unsigned int*)dst);
}

void			my_mlx_pixel_put(t_all *d, int x, int y, int color)
{
	char	*dst;

	dst = d->img.addr + (y * d->img.lenght + x * (d->img.bits / 8));
	*(unsigned int*)dst = color;
}

void			begin_draw(t_all *d, int x)
{
	d->ray.d_start = -d->ray.ht / 2 + d->sch / 2;
	if (d->ray.d_start < 0)
		d->ray.d_start = 1;
	d->ray.d_end = d->ray.ht / 2 + d->sch / 2;
	if (d->ray.d_end >= d->sch)
		d->ray.d_end = d->sch - 1;
	if (d->ray.side == 0)
		d->ray.wall_x = d->plr.pos_y + d->ray.p_wall_dist * d->ray.r_dir_y;
	else
		d->ray.wall_x = d->plr.pos_x + d->ray.p_wall_dist * d->ray.r_dir_x;
	d->ray.wall_x -= floor(d->ray.wall_x);
	d->ray.tex_x = (int)(d->ray.wall_x * (double)d->all_tex.w);
	if (d->ray.side == 0 && d->ray.r_dir_x > 0)
		d->ray.tex_x = d->all_tex.w - d->ray.tex_x - 1;
	if (d->ray.side == 1 && d->ray.r_dir_y < 0)
		d->ray.tex_x = d->all_tex.w - d->ray.tex_x - 1;
	d->ray.step = 1.0 * d->all_tex.h / d->ray.ht;
	d->ray.t_pos = (d->ray.d_start - d->sch / 2 + d->ray.ht / 2) * d->ray.step;
	while (d->ray.d_start < d->ray.d_end)
	{
		d->ray.tex_y = (int)d->ray.t_pos;
		d->ray.t_pos += d->ray.step;
		d->color = my_mlx_pixel_read(&d->all_tex, d->ray.tex_x, d->ray.tex_y);
		my_mlx_pixel_put(d, x, d->ray.d_start++, d->color);
	}
}

void			start_and_init(t_all *d)
{
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;

	draw_start_x = -d->sprite_dr.w / 2 + d->sprite_dr.scr;
	draw_end_x = d->sprite_dr.w / 2 + d->sprite_dr.scr;
	if (draw_start_x < 0)
		draw_start_x = 0;
	if (draw_end_x >= d->scw)
		draw_end_x = d->scw - 1;
	draw_start_y = -d->sprite_dr.h / 2 + d->sch / 2;
	draw_end_y = d->sprite_dr.h / 2 + d->sch / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	if (draw_end_y >= d->sch)
		draw_end_y = d->sch - 1;
	d->sprite_dr.start_x = draw_start_x;
	d->sprite_dr.end_x = draw_end_x;
	d->sprite_dr.start_y = draw_start_y;
	d->sprite_dr.end_y = draw_end_y;
}

void			sprites(t_all *d, double *z_buffer)
{
	int		i;
	double	step;

	i = 0;
	sorte_sprites(d);
	while (d->sprite[i].id != -1)
	{
		sprite_init_param(d, i);
		start_and_init(d);
		step = d->sp.h / (double)d->sprite_dr.h;
		while (d->sprite_dr.start_x < d->sprite_dr.end_x)
		{
			if (d->sprite_dr.trform_y > 0 && d->sprite_dr.start_x > 0 &&
				d->sprite_dr.start_x < d->scw && d->sprite_dr.trform_y <
				z_buffer[d->sprite_dr.start_x])
				sprite_draw(d, step);
			d->sprite_dr.start_x++;
		}
		i++;
	}
	free(d->sprite);
	d->sprite = NULL;
}
