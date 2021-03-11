/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:54:57 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/07 17:54:58 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int			check_border(t_all *d, int x, int y)
{
	while (d->map.m[x])
	{
		y = 0;
		while (d->map.m[x][y])
		{
			if (!ft_strchr(" 1", d->map.m[x][y]) && x == 0)
				runtime_errors(d, -10);
			else if (!ft_strchr(" 1", d->map.m[x][y]) && x == d->map.y - 1)
				runtime_errors(d, -10);
			else if (!ft_strchr(" 1", d->map.m[x][y]) && y == 0)
				runtime_errors(d, -10);
			else if (!ft_strchr(" 1", d->map.m[x][y]) && y == d->map.x - 1)
				runtime_errors(d, -10);
			y++;
		}
		x++;
	}
	return (0);
}

int			check_closed(t_all *d, int x, int y)
{
	if ((d->map.m[x][y + 1] == ' ') || (d->map.m[x][y - 1] == ' '))
		runtime_errors(d, -8);
	else if (!(d->map.m[x + 1][y]) || !(d->map.m[x - 1][y]))
		runtime_errors(d, -8);
	else if ((d->map.m[x + 1][y] == ' ') || (d->map.m[x - 1][y] == ' '))
		runtime_errors(d, -8);
	return (0);
}

void		map_validation(t_all *d)
{
	int		x;
	int		y;

	x = 0;
	check_border(d, 0, 0);
	while (d->map.m[x])
	{
		y = 0;
		if (d->map.m[x][y] == '\0')
			runtime_errors(d, -2);
		while (d->map.m[x][y])
		{
			if (ft_strchr("02NSEW", d->map.m[x][y]) && d->map.m[x][y] != '\0')
				check_closed(d, x, y);
			y++;
		}
		x++;
	}
}
