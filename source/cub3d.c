/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:49:36 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/01 15:49:37 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void		init_xpm(t_all *d)
{
	if (!(d->no.img = mlx_xpm_file_to_image(d->img.mlx, d->no.path, &d->no.w,
		&d->no.h)))
		runtime_errors(d, -4);
	d->no.addr = mlx_get_data_addr(d->no.img, &d->no.bits, &d->no.len,
		&d->no.end);
	if (!(d->so.img = mlx_xpm_file_to_image(d->img.mlx, d->so.path, &d->so.w,
		&d->so.h)))
		runtime_errors(d, -4);
	d->so.addr = mlx_get_data_addr(d->so.img, &d->so.bits, &d->so.len,
		&d->so.end);
	if (!(d->we.img = mlx_xpm_file_to_image(d->img.mlx, d->we.path, &d->we.w,
		&d->we.h)))
		runtime_errors(d, -4);
	d->we.addr = mlx_get_data_addr(d->we.img, &d->we.bits, &d->we.len,
		&d->we.end);
	if (!(d->ea.img = mlx_xpm_file_to_image(d->img.mlx, d->ea.path, &d->ea.w,
		&d->ea.h)))
		runtime_errors(d, -4);
	d->ea.addr = mlx_get_data_addr(d->ea.img, &d->ea.bits, &d->ea.len,
		&d->ea.end);
	if (!(d->sp.img = mlx_xpm_file_to_image(d->img.mlx, d->sp.path, &d->sp.w,
		&d->sp.h)))
		runtime_errors(d, -4);
	d->sp.addr = mlx_get_data_addr(d->sp.img, &d->sp.bits, &d->sp.len,
		&d->sp.end);
}

void		cub3d(t_all *d)
{
	if (!(d->img.mlx = mlx_init()))
		runtime_errors(d, -3);
	parser(d);
	init_xpm(d);
	init_player(d);
	if (d->flag == 0)
		if (!(d->img.win = mlx_new_window(d->img.mlx, d->scw, d->sch, "game")))
			runtime_errors(d, -6);
	if (!(d->img.img = mlx_new_image(d->img.mlx, d->scw, d->sch)))
		runtime_errors(d, -7);
	d->img.addr = mlx_get_data_addr(d->img.img, &d->img.bits, &d->img.lenght,
		&d->img.endian);
	main_loop(d);
	if (d->flag == 1)
		screenshot_map(d);
	else
	{
		mlx_loop_hook(d->img.mlx, &main_loop, d);
		mlx_hook(d->img.win, 33, 0, &ft_close, d);
		mlx_hook(d->img.win, 2, 1L << 0, &key_hook, d);
		mlx_loop(d->img.mlx);
	}
}

int			initialization(char *cub, int flag)
{
	t_all	d;

	d.map.m = NULL;
	d.map.x = 0;
	d.map.y = 0;
	d.img.mlx = NULL;
	d.img.img = NULL;
	d.img.win = NULL;
	d.img.addr = NULL;
	d.flag = flag;
	d.sch = 0;
	d.scw = 0;
	d.no.path = NULL;
	d.so.path = NULL;
	d.we.path = NULL;
	d.ea.path = NULL;
	d.sp.path = NULL;
	d.f_color = -1;
	d.c_color = -1;
	d.cub = cub;
	cub3d(&d);
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	if (argc == 3 && cub_check(argv[1], "cub", 0) && cub_check(argv[2],
															"--save", 1))
		initialization(argv[1], 1);
	else if (argc == 2 && cub_check(argv[1], "cub", 0))
		initialization(argv[1], 0);
	else
		write(1, "ERROR\nInvalid arguments", 24);
	return (0);
}
