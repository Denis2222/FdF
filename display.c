/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:45:30 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/11 16:02:50 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_dot(t_env *e, int x, int y, int color)
{
	char	b;
	char	g;
	char	r;
	int		i;

	b = color % 256;
	g = (color / 256) % 256;
	r = (color / 256 / 256) % 256;
	if (x < WIN_WIDTH && x > 0 && y < WIN_HEIGHT && y > 0)
	{
		i = (e->size_line * y) + (x * (e->bpp / 8));
		e->imgpx[i] = b;
		e->imgpx[i + 1] = g;
		e->imgpx[i + 2] = r;
	}
}

void	draw_line(t_env *e, t_dot *p0, t_dot *p1, int color)
{
	t_dot	*d;
	t_dot	*s;
	int		err;
	int		e2;

	d = dot(ft_abs(p1->x - p0->x), ft_abs(p1->y - p0->y), 0);
	s = dot((p0->x < p1->x ? 1 : -1), (p0->y < p1->y ? 1 : -1), 0);
	err = (d->x > d->y ? d->x : -d->y) / 2;
	while (!(p0->x == p1->x && p0->y == p1->y))
	{
		if (p0->x < WIN_WIDTH && p0->x > 0 && p0->y < WIN_HEIGHT && p0->y > 0)
			draw_dot(e, p0->x, p0->y, color);
		e2 = err;
		if (e2 > -d->x)
		{
			err -= d->y;
			p0->x += s->x;
		}
		if (e2 < d->y)
		{
			err += d->x;
			p0->y += s->y;
		}
	}
	freedot(p0, p1, d, s);
}

int		colorh(int height)
{
	if (height < -255)
		return (0);
	if (height <= 0)
		return (255 + height);
	if (height <= 1)
		return (15392803);
	if (height < 154)
		return (256 * 256 * 100 + 256 * (200 - height) + 1);
	else
		return (0xFFFFFF);
}

t_dot	*to2d(t_dot *d, t_env *e)
{
	double		x;
	double		y;
	t_dot		*point;

	x = d->x - d->y;
	y = -d->z * e->cam->depth + (d->x / e->cam->rx) + (d->y / e->cam->ry);
	x = x * e->cam->zoom + e->cam->offsx;
	y = y * e->cam->zoom + e->cam->offsy;
	point = dot(x, y, 0);
	return (point);
}

void	draw_wires(t_env *e, t_list *wires)
{
	t_dot	*start;
	t_dot	*end;
	int		color;

	while (wires)
	{
		start = ((t_wire*)wires->content)->d1;
		end = ((t_wire*)wires->content)->d2;
		if (start && end)
		{
			color = colorh((start->z + end->z) / 2);
			draw_line(e, to2d(start, e), to2d(end, e), color);
		}
		wires = wires->next;
	}
}
