/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:11:26 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/18 22:06:40 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	take_res(char *str, t_all *d, int *i)
{
	int		x;
	int		y;

	if (d->scw != 0 || d->sch != 0)
		runtime_errors(d, -2);
	(*i)++;
	skip_spaces(str, i);
	x = take_num(d, str, i);
	while (ft_isdigit(str[*i]))
		(*i)++;
	y = take_num(d, str, i);
	d->tmp_scw = x;
	d->tmp_sch = y;
	mlx_get_screen_size(d->img.mlx, &x, &y);
	d->scw = (d->tmp_scw > x) ? x : d->tmp_scw;
	d->sch = (d->tmp_sch > y) ? y : d->tmp_sch;
	d->aspect_ratio = (double)d->sch / (double)d->scw;
	if (d->aspect_ratio != 0.75)
		d->aspect_ratio = 0.75 / d->aspect_ratio;
	while (ft_isdigit(str[*i]))
		(*i)++;
	if (d->scw <= 0 || d->sch <= 0 || str[*i] != '\0')
		runtime_errors(d, -2);
}

void	take_tex(t_all *d, char **file, char *str, int *i)
{
	int		j;
	int		fd;
	char	*pah_tmp;

	if (*file != NULL)
		runtime_errors(d, -2);
	(*i) += 2;
	skip_spaces(str, i);
	j = *i;
	while (str[*i] != '\0')
		(*i)++;
	if (!(pah_tmp = (char*)malloc(sizeof(char) * ((*i) - j + 1))))
		runtime_errors(d, -3);
	*i = j;
	j = 0;
	while (str[*i] != '\0')
		pah_tmp[j++] = str[(*i)++];
	pah_tmp[j] = '\0';
	if (((fd = open(pah_tmp, O_RDONLY)) < 0) || !namecheck_xpm(pah_tmp, "xpm"))
		runtime_errors(d, -12);
	close(fd);
	*file = ft_substr(pah_tmp, 0, ft_strlen(pah_tmp));
	free(pah_tmp);
}

void	take_color(t_all *d, int *color, char *str, int *i)
{
	int		r;
	int		g;
	int		b;

	if (*color != -1)
		runtime_errors(d, -2);
	find_comma(d, str);
	(*i)++;
	skip_spaces(str, i);
	if (ft_isdigit(str[*i]))
		r = take_num(d, str, i);
	(*i)++;
	skip_spaces(str, i);
	if (ft_isdigit(str[*i]))
		g = take_num(d, str, i);
	(*i)++;
	skip_spaces(str, i);
	if (ft_isdigit(str[*i]))
		b = take_num(d, str, i);
	if (r > 255 || g > 255 || b > 255 || str[*i] != '\0')
		runtime_errors(d, -2);
	*color = r * 256 * 256 + g * 256 + b;
}

void	parse_config(t_all *d, char *str, int *fd)
{
	int		i;

	i = 0;
	skip_spaces(str, &i);
	if (str[i] == 'R' && str[i + 1] == ' ')
		take_res(str, d, &i);
	else if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ')
		take_tex(d, &d->no.path, str, &i);
	else if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ')
		take_tex(d, &d->we.path, str, &i);
	else if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ')
		take_tex(d, &d->ea.path, str, &i);
	else if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ')
		take_tex(d, &d->so.path, str, &i);
	else if (str[i] == 'S' && str[i + 1] == ' ')
		take_tex(d, &d->sp.path, str, &i);
	else if (str[i] == 'F' && str[i + 1] == ' ')
		take_color(d, &d->f_color, str, &i);
	else if (str[i] == 'C' && str[i + 1] == ' ')
		take_color(d, &d->c_color, str, &i);
	else if (str[i] != '\0' && check_elem(d))
		take_map(d, str, fd);
}

void	parser(t_all *d)
{
	char	*line;
	int		fd;
	int		i;

	i = 1;
	if ((fd = open(d->cub, O_RDONLY)) < 0)
		runtime_errors(d, -1);
	while (i == 1)
	{
		if ((i = get_next_line(fd, &line)) == -1)
			runtime_errors(d, -2);
		parse_config(d, line, &fd);
		free(line);
	}
	close(fd);
	if (d->map.m == NULL)
		runtime_errors(d, -2);
	if (d->flag == 1)
	{
		d->scw = d->tmp_scw;
		d->sch = d->tmp_sch;
	}
}
