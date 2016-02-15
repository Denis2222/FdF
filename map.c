/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:00:10 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/11 14:51:17 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	map_min_max(t_env *e, int height)
{
	if (height > e->height_max)
		e->height_max = height;
	if (height < e->height_min)
		e->height_min = height;
}

t_dot		*map_max(t_list *list, t_env *e)
{
	t_dot	*max;
	char	**tab;

	max = dot(0, 0, 0);
	while (list)
	{
		max->y++;
		tab = ft_strsplit(list->content, ' ');
		if (ft_tablen(tab) > max->x)
			max->x = ft_tablen(tab);
		while (*tab)
		{
			map_min_max(e, ft_atoi(*tab));
			tab++;
		}
		list = list->next;
	}
	return (max);
}

t_dot		***map_read(t_list *list, t_dot *max)
{
	t_dot	***map;
	char	**tab;
	t_dot	*c;

	map = (t_dot***)malloc(sizeof(t_dot**) * max->y + 1);
	c = dot(0, 0, 0);
	while (c->y < max->y)
	{
		tab = ft_strsplit(list->content, ' ');
		map[c->y] = (t_dot**)malloc(sizeof(t_dot*) * max->x + 1);
		c->x = 0;
		while (c->x < max->x)
		{
			if (c->x < ft_tablen(tab))
				map[c->y][c->x] = dot(c->x, c->y, ft_atoi(tab[c->x]) % 100000);
			else
				map[c->y][c->x] = NULL;
			c->x++;
		}
		c->y++;
		list = list->next;
		free(tab);
	}
	return (map);
}

void		map_view(t_env e)
{
	t_dot	*cur;

	cur = dot(0, 0, 0);
	while (cur->y < e.max->y)
	{
		cur->x = 0;
		while (cur->x < e.max->x)
		{
			if (e.map[cur->y][cur->x])
			{
				ft_putnbr(e.map[cur->y][cur->x]->z);
				ft_putchar(' ');
			}
			cur->x++;
		}
		ft_putchar('\n');
		cur->y++;
	}
}

t_list		*map_wires(t_env *e)
{
	t_dot	*c;
	t_list	*wires;

	wires = NULL;
	c = dot(0, 0, 0);
	while (c->y < e->max->y)
	{
		c->x = 0;
		while (c->x < e->max->x)
		{
			if (c->y + 1 < e->max->y)
				ft_lstadd(&wires,
				ft_lstnew(wire(e->map[c->y][c->x], e->map[c->y + 1][c->x]),
				sizeof(t_wire)));
			if (c->x + 1 < e->max->x)
				ft_lstadd(&wires,
				ft_lstnew(wire(e->map[c->y][c->x], e->map[c->y][c->x + 1]),
				sizeof(t_wire)));
			c->x++;
		}
		c->y++;
	}
	return (wires);
}
