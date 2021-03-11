/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:30:31 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/09 08:30:32 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

unsigned int	get_color_from_img(t_all *d, int x, int y)
{
	char	*dst;

	dst = d->img.addr + (y * d->img.lenght + x * (d->img.bits / 8));
	return (*(unsigned int*)dst);
}

void			bmp_content(t_bmp screenshot, int fd)
{
	write(fd, &screenshot.file_type, sizeof(screenshot.file_type));
	write(fd, &screenshot.file_size, sizeof(screenshot.file_size));
	write(fd, &screenshot.reserved_1, sizeof(screenshot.reserved_1));
	write(fd, &screenshot.reserved_2, sizeof(screenshot.reserved_2));
	write(fd, &screenshot.pixel_data_offset,
		sizeof(screenshot.pixel_data_offset));
	write(fd, &screenshot.header_size, sizeof(screenshot.header_size));
	write(fd, &screenshot.image_w, sizeof(screenshot.image_w));
	write(fd, &screenshot.image_h, sizeof(screenshot.image_h));
	write(fd, &screenshot.planes, sizeof(screenshot.planes));
	write(fd, &screenshot.bpp, sizeof(screenshot.bpp));
	write(fd, &screenshot.compression, sizeof(screenshot.compression));
	write(fd, &screenshot.image_size, sizeof(screenshot.image_size));
	write(fd, &screenshot.x_pixels, sizeof(screenshot.x_pixels));
	write(fd, &screenshot.y_pixels, sizeof(screenshot.y_pixels));
	write(fd, &screenshot.total_color, sizeof(screenshot.total_color));
	write(fd, &screenshot.important_colors,
		sizeof(screenshot.important_colors));
}

void			bmp_header(t_all *d, t_bmp *screenshot)
{
	screenshot->file_type[0] = 0x42;
	screenshot->file_type[1] = 0x4D;
	screenshot->file_size = 4 * (d->scw * d->sch) + 54;
	screenshot->reserved_1 = 0;
	screenshot->reserved_2 = 0;
	screenshot->pixel_data_offset = 54;
	screenshot->header_size = 40;
	screenshot->image_w = d->scw;
	screenshot->image_h = d->sch;
	screenshot->planes = 1;
	screenshot->bpp = 32;
	screenshot->compression = 0;
	screenshot->image_size = 4 * (d->scw * d->sch) + 54;
	screenshot->x_pixels = 0;
	screenshot->y_pixels = 0;
	screenshot->total_color = 0;
	screenshot->important_colors = 0;
}

void			screenshot_map(t_all *d)
{
	int				x;
	int				y;
	unsigned int	color;
	int				fd;
	t_bmp			screenshot;

	fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		runtime_errors(d, -11);
	bmp_header(d, &screenshot);
	bmp_content(screenshot, fd);
	y = d->sch;
	while (y > 0)
	{
		x = 0;
		while (x < d->scw)
		{
			color = get_color_from_img(d, x, y);
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
	close(fd);
}
