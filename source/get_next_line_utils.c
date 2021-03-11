/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:34:59 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/01 17:35:00 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int					newline(char *str)
{
	int				i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;
	size_t			i;

	pdst = (unsigned char*)dst;
	psrc = (unsigned char*)src;
	i = 0;
	if (len == 0 || pdst == psrc)
		return (pdst);
	if (pdst < psrc)
		while (i < len)
		{
			pdst[i] = psrc[i];
			i++;
		}
	else
	{
		i = len;
		while (i > 0)
		{
			pdst[i - 1] = psrc[i - 1];
			i--;
		}
	}
	return (pdst);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*sum_str;
	size_t			s1_len;
	size_t			s2_len;
	size_t			sum_len;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	sum_len = s1_len + s2_len + 1;
	sum_str = malloc(sizeof(char) * sum_len);
	if (NULL == sum_str)
		return (NULL);
	ft_memmove(sum_str, s1, s1_len);
	ft_memmove(sum_str + s1_len, s2, s2_len);
	sum_str[sum_len - 1] = '\0';
	free((char *)s1);
	return (sum_str);
}
