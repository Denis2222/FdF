/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cam.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 12:46:39 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/09 19:28:13 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cam_calibrate_center(t_env *e)
{
	double	width;
	double	height;

	width = (e->max->y - 1 + e->max->x - 1) * e->cam->zoom;
	height = (((e->max->x - 1) / e->cam->rx) +
	((e->max->y - 1) / e->cam->ry)) * e->cam->zoom;
	e->cam->offsx = (e->max->y - 1) * e->cam->zoom;
	e->cam->offsy = 0;
	e->cam->offsx -= (width / 2);
	e->cam->offsx += (WIN_WIDTH / 2);
	e->cam->offsy -= (height / 2);
	e->cam->offsy += (WIN_HEIGHT / 2);
}

void	cam_calibrate_zoom(t_env *e)
{
	double	width;
	double	height;
	double	ratiow;
	double	ratioh;

	width = (e->max->y - 1 + e->max->x - 1) * e->cam->zoom;
	height = (((e->max->x - 1) / e->cam->rx) +
	((e->max->y - 1) / e->cam->ry)) * e->cam->zoom;
	ratiow = WIN_WIDTH / width;
	ratioh = WIN_HEIGHT / height;
	if (ratiow <= ratioh)
		e->cam->zoom = (double)WIN_WIDTH / (e->max->y - 1 + e->max->x - 1);
	else
		e->cam->zoom = (double)WIN_HEIGHT / (((e->max->x - 1) / e->cam->rx) +
		((e->max->y - 1) / e->cam->ry));
	cam_calibrate_center(e);
}

t_cam	*cam(t_env *e)
{
	t_cam	*camera;

	camera = (t_cam*)malloc(sizeof(t_cam));
	e->cam = camera;
	camera->zoom = 10;
	camera->depth = 0.1;
	camera->rx = 1.3;
	camera->ry = 1.3;
	camera->offsx = 0;
	camera->offsy = 0;
	cam_calibrate_zoom(e);
	cam_calibrate_center(e);
	return (camera);
}
