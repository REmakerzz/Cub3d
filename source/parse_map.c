/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:59:17 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/05 13:59:19 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

char		*write_map(char *str)
{
	char	*line;
	int		j;
	int		i;

	if (!(line = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr("NSEW012 ", str[i]))
			line[j++] = str[i++];
		else
			return (NULL);
	}
	line[j] = '\0';
	return (line);
}

void		parse_map(t_all *d, char *str)
{
	char	**tmp_arr;
	int		j;
	int		len_x;

	j = -1;
	if (!(tmp_arr = malloc(sizeof(char *) * (d->map.y + 2))))
		runtime_errors(d, -3);
	while (++j < d->map.y)
		tmp_arr[j] = d->map.m[j];
	tmp_arr[d->map.y] = write_map(str);
	if (tmp_arr[d->map.y] == NULL)
	{
		free(tmp_arr);
		runtime_errors(d, -2);
	}
	tmp_arr[d->map.y + 1] = NULL;
	if (d->map.y > 0)
		free(d->map.m);
	d->map.m = tmp_arr;
	d->map.y++;
	len_x = ft_strlen(str);
	if (len_x > d->map.x)
		d->map.x = len_x;
}

void		take_map(t_all *d, char *str, int *fd)
{
	char	*line;
	int		j;

	j = 1;
	parse_map(d, str);
	while (j == 1)
	{
		j = get_next_line(*fd, &line);
		parse_map(d, line);
		free(line);
	}
	map_validation(d);
}
