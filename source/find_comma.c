/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_comma.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:01:05 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/18 22:07:14 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	find_comma(t_all *d, const char *str)
{
	int		j;
	int		count;

	j = 0;
	count = 0;
	while (str[j] != '\0')
	{
		if (str[j] == ',')
			count++;
		j++;
	}
	if (count != 2)
		runtime_errors(d, -2);
}
