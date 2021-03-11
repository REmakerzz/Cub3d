/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:22:59 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/01 16:23:00 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int		ft_close(t_all *d)
{
	int		i;

	i = 0;
	if (d->map.m)
	{
		while (i < d->map.y)
			free(d->map.m[i++]);
		free(d->map.m[i]);
	}
	if (d->img.win)
		mlx_destroy_window(d->img.mlx, d->img.win);
	if (d->img.img)
		mlx_destroy_image(d->img.mlx, d->img.img);
	free(d->no.path);
	free(d->so.path);
	free(d->we.path);
	free(d->ea.path);
	free(d->sp.path);
	free(d->img.mlx);
	exit(SUCCESS);
}

int		check_elem(t_all *d)
{
	if (d->no.path == NULL)
		return (0);
	else if (d->so.path == NULL)
		return (0);
	else if (d->we.path == NULL)
		return (0);
	else if (d->ea.path == NULL)
		return (0);
	else if (d->sp.path == NULL)
		return (0);
	else if (d->sch == 0 || d->scw == 0)
		return (0);
	else if (d->f_color == 0 || d->c_color == 0)
		return (0);
	return (1);
}

void	runtime_errors(t_all *d, int code)
{
	if (code == -1)
		write(1, "ERROR\nCan't open .cub", 22);
	else if (code == -2)
		write(1, "ERROR\nInvalid config map", 25);
	else if (code == -3)
		write(1, "ERROR\nMalloc error", 19);
	else if (code == -4)
		write(1, "ERROR\nInvalid texture", 22);
	else if (code == -5)
		write(1, "ERROR\nInvalid count of player", 30);
	else if (code == -6)
		write(1, "ERROR\nCan't create a window", 28);
	else if (code == -7)
		write(1, "ERROR\nCan't create a new image", 31);
	else if (code == -8)
		write(1, "ERROR\nMap must be closed", 25);
	else if (code == -9)
		write(1, "ERROR\nWrong map element", 24);
	else if (code == -10)
		write(1, "ERROR\nCan be only 1 or a space behind the map", 46);
	else if (code == -11)
		write(1, "ERROR\nCan't create a BMP file", 30);
	else if (code == -12)
		write(1, "ERROR\nInvalid Texture", 22);
	ft_close(d);
}

void	sprite_draw(t_all *d, double step)
{
	double	tex_x;
	double	tex_y;
	int		y;
	int		s;
	int		color;

	tex_x = (int)((d->sprite_dr.start_x - (-d->sprite_dr.w / 2 +
			d->sprite_dr.scr)) * d->sp.w / d->sprite_dr.w);
	y = d->sprite_dr.start_y;
	s = (y) * 256 - d->sch * 128 + d->sprite_dr.h * 128;
	tex_y = (int)(((s * d->sp.h) / d->sprite_dr.h) / 256);
	while (y < d->sprite_dr.end_y)
	{
		color = my_mlx_pixel_read(&d->sp, tex_x, tex_y);
		if (color != 0)
			my_mlx_pixel_put(d, d->sprite_dr.start_x, y, color);
		y++;
		tex_y += step;
	}
}
