/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:15:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/11 13:03:28 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	keyto_angle(t_env *e, int keycode)
{
	if (keycode == KEY_PADUP)
		e->cam->rx += 0.1;
	if (keycode == KEY_PADDOWN && e->cam->rx > 0.2)
		e->cam->rx -= 0.1;
	if (keycode == KEY_PADLEFT)
		e->cam->ry += 0.1;
	if (keycode == KEY_PADRIGHT && e->cam->ry > 0.2)
		e->cam->ry -= 0.1;
}

static void	keyto_zoom(t_env *e, int keycode)
{
	if (keycode == KEY_PLUS)
		e->cam->zoom *= 1.1;
	if (keycode == KEY_MINUS)
		e->cam->zoom *= 0.9;
}

static void	keyto_depth(t_env *e, int keycode)
{
	if (keycode == KEY_PAD0 && e->cam->depth < 20)
		e->cam->depth *= 1.1;
	if (keycode == KEY_PADDOT && e->cam->depth > 0.0001)
		e->cam->depth *= 0.9;
}

static void	keyto_offset(t_env *e, int keycode)
{
	if (keycode == KEY_UP)
		e->cam->offsy += e->cam->zoom * 10;
	if (keycode == KEY_DOWN)
		e->cam->offsy -= e->cam->zoom * 10;
	if (keycode == KEY_LEFT)
		e->cam->offsx += e->cam->zoom * 10;
	if (keycode == KEY_RIGHT)
		e->cam->offsx -= e->cam->zoom * 10;
}

int			keyto(t_env *e, int keycode)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_CTRL)
		cam_calibrate_center(e);
	if (keycode == KEY_SHIFT)
		cam_calibrate_zoom(e);
	keyto_angle(e, keycode);
	keyto_zoom(e, keycode);
	keyto_offset(e, keycode);
	keyto_depth(e, keycode);
	return (0);
}
