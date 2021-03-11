/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:23:10 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/06 15:23:12 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

char		*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (c == 0)
	{
		while (s[i])
			i++;
		return ((char *)s + i);
	}
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

void		horizont(t_all *d, char ch)
{
	if (ch == 'W')
	{
		d->plr.dir_x = 0;
		d->plr.dir_y = -1;
		d->plr.pl_x = -0.66;
		d->plr.pl_x = 0;
	}
	else if (ch == 'E')
	{
		d->plr.dir_x = 0;
		d->plr.dir_y = 1;
		d->plr.pl_x = 0.66;
		d->plr.pl_y = 0;
	}
}

void		side_of_view(t_all *d, char ch)
{
	horizont(d, ch);
	if (ch == 'N')
	{
		d->plr.dir_x = -1;
		d->plr.dir_y = 0;
		d->plr.pl_x = 0;
		d->plr.pl_y = 0.66;
	}
	else if (ch == 'S')
	{
		d->plr.dir_x = 1;
		d->plr.dir_y = 0;
		d->plr.pl_x = 0;
		d->plr.pl_y = -0.66;
	}
}

void		init_player(t_all *d)
{
	int		x;
	int		y;
	int		count;

	x = -1;
	count = 0;
	while (d->map.m[++x])
	{
		y = 0;
		while (d->map.m[x][y])
		{
			if (ft_strchr("NSEW", d->map.m[x][y]) && d->map.m[x][y] != '\0')
			{
				d->plr.pos_x = x + 0.5;
				d->plr.pos_y = y + 0.5;
				side_of_view(d, d->map.m[x][y]);
				d->map.m[x][y] = '0';
				count++;
			}
			y++;
		}
	}
	if (count != 1)
		runtime_errors(d, -5);
}
