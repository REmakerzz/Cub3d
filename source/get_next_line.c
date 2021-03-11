/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:34:55 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/01 17:34:56 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

char	*get_remainder(char *remainder)
{
	char	*pc_res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!remainder)
		return (0);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (0);
	}
	if (!(pc_res = malloc(sizeof(char) * ((ft_strlen(remainder) - i) + 1))))
		return (0);
	i++;
	while (remainder[i])
		pc_res[j++] = remainder[i++];
	pc_res[j] = '\0';
	free(remainder);
	return (pc_res);
}

char	*get_line(const char *str)
{
	int		i;
	char	*pc_res;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(pc_res = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		pc_res[i] = str[i];
		i++;
	}
	pc_res[i] = '\0';
	return (pc_res);
}

int		get_next_line(int fd, char **line)
{
	char			*buf;
	int				i;
	static	char	*remainder;

	i = 1;
	if (fd < 0 || !line)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!newline(remainder) && i != 0)
	{
		if ((i = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			free(buf);
			return (-1);
		}
		buf[i] = '\0';
		remainder = ft_strjoin(remainder, buf);
	}
	free(buf);
	*line = get_line(remainder);
	remainder = get_remainder(remainder);
	if (i == 0)
		return (0);
	return (1);
}
