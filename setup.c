/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 13:53:24 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/11 14:17:17 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_env	setup(t_list *list)
{
	t_env	e;

	e.height_min = 0;
	e.height_max = 0;
	e.max = map_max(list, &e);
	if (e.max->x * e.max->y < 2)
		exit(EXIT_FAILURE);
	e.map = map_read(list, e.max);
	e.wires = ft_lstrev(map_wires(&e));
	e.cam = cam(&e);
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	e.bpp = 0;
	e.size_line = 0;
	mlx_key_hook(e.win, key_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	map_view(e);
	return (e);
}

void	draw_img(t_env *e)
{
	e->img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->imgpx = mlx_get_data_addr(
	e->img, &(e->bpp), &(e->size_line), &(e->endian));
	draw_wires(e, e->wires);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
}

int		expose_hook(t_env *e)
{
	draw_img(e);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	keyto(e, keycode);
	draw_img(e);
	return (0);
}
