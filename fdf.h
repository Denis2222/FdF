/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 13:34:12 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/11 14:17:15 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "minilibx/mlx.h"
# include <math.h>
# include "libft/libft.h"

# define WIN_WIDTH 2000
# define WIN_HEIGHT 1400

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_PADUP 91
# define KEY_PADDOWN 84
# define KEY_PADLEFT 86
# define KEY_PADRIGHT 88
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_PAD0 82
# define KEY_PADDOT 65
# define KEY_CTRL 269
# define KEY_SHIFT 258

typedef struct	s_dot
{
	int			x;
	int			y;
	int			z;
}				t_dot;

typedef struct	s_wire
{
	t_dot		*d1;
	t_dot		*d2;
}				t_wire;

typedef struct	s_cam
{
	double		zoom;
	double		depth;
	double		rx;
	double		ry;
	int			offsx;
	int			offsy;
}				t_cam;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_dot		***map;
	t_dot		*max;
	int			height_min;
	int			height_max;
	t_list		*wires;
	void		*img;
	char		*imgpx;
	int			bpp;
	int			size_line;
	int			endian;
	t_cam		*cam;
}				t_env;

t_list			*read_file(int ac, char **av);
t_env			setup(t_list *list);

t_dot			*dot(int x, int y, int z);
void			freedot(t_dot *d1, t_dot *d2, t_dot *d3, t_dot *d4);

t_wire			*wire(t_dot *d1, t_dot *d2);

t_dot			*map_max(t_list *list, t_env *e);
t_dot			***map_read(t_list *list, t_dot *max);
void			map_view(t_env e);
t_list			*map_wires(t_env *e);

t_cam			*cam(t_env *e);
void			cam_calibrate_center(t_env *e);
void			cam_calibrate_zoom(t_env *e);

void			draw_line(t_env *e, t_dot *p0, t_dot *p1, int color);
void			draw_wires(t_env *e, t_list *wires);

int				mouse_hook(int button, int x, int y, t_env *e);
int				expose_hook(t_env *e);

int				key_hook(int keycode, t_env *e);
int				keyto(t_env *e, int keycode);

#endif
