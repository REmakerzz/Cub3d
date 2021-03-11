/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:44:58 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/06 15:44:59 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

t_texture	walltex(t_all *d, int side)
{
	t_texture	wall;

	if (side && d->ray.r_dir_y > 0)
		wall = d->ea;
	else if (side && d->ray.r_dir_y < 0)
		wall = d->we;
	else if (!side && d->ray.r_dir_x > 0)
		wall = d->so;
	else
		wall = d->no;
	return (wall);
}

void		fov_init(t_all *d, int x)
{
	d->ray.camera_x = 2 * x / (double)d->scw - 1;
	d->ray.r_dir_x = d->plr.dir_x + d->plr.pl_x * d->ray.camera_x;
	d->ray.r_dir_y = d->plr.dir_y + d->plr.pl_y * d->ray.camera_x;
	d->ray.map_x = (int)d->plr.pos_x;
	d->ray.map_y = (int)d->plr.pos_y;
	d->ray.d_dist_x = fabs(1 / d->ray.r_dir_x);
	d->ray.d_dist_y = fabs(1 / d->ray.r_dir_y);
	d->ray.step_x = 1;
	d->ray.step_y = 1;
	if (d->ray.r_dir_x < 0)
	{
		d->ray.step_x = -1;
		d->ray.s_dist_x = (d->plr.pos_x - d->ray.map_x) * d->ray.d_dist_x;
	}
	else
		d->ray.s_dist_x = (d->ray.map_x + 1.0 - d->plr.pos_x) * d->ray.d_dist_x;
	if (d->ray.r_dir_y < 0)
	{
		d->ray.step_y = -1;
		d->ray.s_dist_y = (d->plr.pos_y - d->ray.map_y) * d->ray.d_dist_y;
	}
	else
		d->ray.s_dist_y = (d->ray.map_y + 1.0 - d->plr.pos_y) * d->ray.d_dist_y;
}

void		draw_floor(t_all *d)
{
	int		height;
	int		width;

	height = 0;
	while (height < d->sch / 2)
	{
		width = 0;
		while (width < d->scw)
		{
			my_mlx_pixel_put(d, width, height, d->c_color);
			width++;
		}
		height++;
	}
	while (height < d->sch)
	{
		width = 0;
		while (width < d->scw)
		{
			my_mlx_pixel_put(d, width, height, d->f_color);
			width++;
		}
		height++;
	}
}

void		search_wall(t_all *d)
{
	d->ray.hit = 0;
	while (d->ray.hit == 0)
	{
		if (d->ray.s_dist_x < d->ray.s_dist_y)
		{
			d->ray.s_dist_x += d->ray.d_dist_x;
			d->ray.map_x += d->ray.step_x;
			d->ray.side = 0;
		}
		else
		{
			d->ray.s_dist_y += d->ray.d_dist_y;
			d->ray.map_y += d->ray.step_y;
			d->ray.side = 1;
		}
		if (d->map.m[d->ray.map_x][d->ray.map_y] == '1')
			d->ray.hit = 1;
	}
	if (d->ray.side == 0)
		d->ray.p_wall_dist = (d->ray.map_x - d->plr.pos_x +
				(1 - d->ray.step_x) / 2) / d->ray.r_dir_x;
	else
		d->ray.p_wall_dist = (d->ray.map_y - d->plr.pos_y +
				(1 - d->ray.step_y) / 2) / d->ray.r_dir_y;
	d->ray.ht = (int)(d->sch / d->ray.p_wall_dist) * d->aspect_ratio;
}

int			main_loop(t_all *d)
{
	int			x;
	double		*z_buffer;

	x = -1;
	if (!(z_buffer = malloc(sizeof(double) * (d->scw))))
		runtime_errors(d, -3);
	draw_floor(d);
	while (++x < d->scw)
	{
		fov_init(d, x);
		search_wall(d);
		d->all_tex = walltex(d, d->ray.side);
		begin_draw(d, x);
		z_buffer[x] = d->ray.p_wall_dist;
	}
	sprites(d, z_buffer);
	free(z_buffer);
	if (d->flag == 0)
		mlx_put_image_to_window(d->img.mlx, d->img.win, d->img.img, 0, 0);
	return (0);
}
