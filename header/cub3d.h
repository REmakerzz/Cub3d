/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarchba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:37:48 by cmarchba          #+#    #+#             */
/*   Updated: 2021/03/11 17:16:06 by cmarchba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define SUCCESS	0
# define BUFFER_SIZE 32

# define MOVE	0.2
# define TURN	0.08

typedef struct		s_cam
{
	double			camera_x;
	double			r_dir_x;
	double			r_dir_y;
	double			d_dist_x;
	double			d_dist_y;
	double			wall_x;
	double			step;
	double			tex_y;
	double			t_pos;
	double			s_dist_x;
	double			s_dist_y;
	double			p_wall_dist;
	int				map_x;
	int				map_y;
	int				hit;
	int				step_x;
	int				step_y;
	int				tex_x;
	int				side;
	int				ht;
	int				d_start;
	int				d_end;
}					t_cam;

typedef struct		s_drw_sprite
{
	double			x;
	double			y;
	double			trform_x;
	double			trform_y;
	int				scr;
	int				h;
	int				w;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
}					t_drw_sprite;

typedef struct		s_window
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits;
	int				lenght;
	int				endian;
}					t_window;

typedef struct		s_bmp
{
	char			file_type[2];
	unsigned int	file_size;
	unsigned short	reserved_1;
	unsigned short	reserved_2;
	unsigned int	pixel_data_offset;
	unsigned int	header_size;
	int				image_w;
	int				image_h;
	unsigned short	planes;
	unsigned short	bpp;
	unsigned int	compression;
	unsigned int	image_size;
	int				x_pixels;
	int				y_pixels;
	unsigned int	total_color;
	unsigned int	important_colors;
}					t_bmp;

typedef struct		s_map
{
	char			**m;
	int				x;
	int				y;
}					t_map;

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			pl_x;
	double			pl_y;
}					t_player;

typedef struct		s_texture
{
	void			*img;
	void			*addr;
	char			*path;
	int				w;
	int				h;
	int				bits;
	int				len;
	int				end;
}					t_texture;

typedef struct		s_sprite
{
	int				x;
	int				y;
	int				dist;
	int				id;
}					t_sprite;

typedef struct		s_all
{
	t_window		img;
	t_texture		no;
	t_texture		so;
	t_texture		ea;
	t_texture		we;
	t_texture		sp;
	t_texture		all_tex;
	t_sprite		*sprite;
	t_drw_sprite	sprite_dr;
	t_map			map;
	t_player		plr;
	t_cam			ray;
	char			*cub;
	int				f_color;
	int				c_color;
	int				sch;
	int				tmp_sch;
	int				scw;
	int				tmp_scw;
	size_t			flag;
	int				color;
	double			aspect_ratio;
}					t_all;

char				*ft_strchr(const char *s, int c);
char				*ft_substr(char const *s, int start, size_t len);
int					namecheck_xpm(char *str, char *xpm);
int					ft_strlen(const char *str);
int					cub_check(char *src, char *needle, int flag);
int					get_next_line(int fd, char **line);
int					check_elem(t_all *d);
void				parser(t_all *d);
int					newline(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
int					skip_spaces(char *str, int *i);
int					take_num(t_all *d, char *str, int *i);
void				runtime_errors(t_all *d, int code);
int					ft_close(t_all *d);
void				init_player(t_all *d);
int					main_loop(t_all *d);
void				begin_draw(t_all *d, int x);
void				my_mlx_pixel_put(t_all *d, int x, int y, int color);
void				sprites(t_all *d, double *z_buffer);
unsigned int		my_mlx_pixel_read(t_texture *wall, int x, int y);
void				sorte_sprites(t_all *d);
void				sprite_init_param(t_all *d, int i);
void				sprite_draw(t_all *d, double step);
int					key_hook(int keycode, t_all *d);
void				take_map(t_all *d, char *str, int *fd);
void				map_validation(t_all *d);
void				screenshot_map(t_all *d);
int					ft_isdigit(char ch);
void				find_comma(t_all *d, const char *str);

#endif
