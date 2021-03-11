/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:20:29 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/01 16:20:30 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int			skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\n' || str[*i] == '\t')
		(*i)++;
	return (1);
}

int			take_num(char *str, int *i)
{
	int		res;

	res = 0;
	skip_spaces(str, i);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		res = res * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (res);
}

int			ft_strlen(const char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int			cub_check(char *src, char *needle, int flag)
{
	int		i;

	i = ft_strlen(src);
	if (flag == 0 && i > 4 && src[i - 1] == needle[2] && src[i - 2] == needle[1]
		&& src[i - 3] == needle[0] && src[i - 4] == '.')
		return (1);
	else if (flag == 1)
	{
		i = 0;
		while (src[i] == needle[i])
		{
			if (src[i] == '\0' && needle[i] == '\0')
				return (1);
			i++;
		}
	}
	return (0);
}

char		*ft_substr(char const *s, int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (i < len)
		{
			str[i] = s[start];
			start++;
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
