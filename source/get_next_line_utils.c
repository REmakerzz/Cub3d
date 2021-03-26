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

void	*ft_memcpy(void *dst, const void *src, int len)
{
	char *pdst;
	char *psrc;

	if (!len || dst == src)
		return (dst);
	pdst = (char*)dst;
	psrc = (char*)src;
	while (len--)
		*pdst++ = *psrc++;
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*sum_str;
	int			s1_len;
	int			s2_len;
	int			sum_len;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	sum_len = s1_len + s2_len + 1;
	if (!(sum_str = malloc(sizeof(char) * sum_len)))
		return (NULL);
	ft_memcpy(sum_str, s1, s1_len);
	ft_memcpy(sum_str + s1_len, s2, s2_len);
	sum_str[sum_len - 1] = '\0';
	free((char *)s1);
	return (sum_str);
}

int		newline(const char *str)
{
	int			i;

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
