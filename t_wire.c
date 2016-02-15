/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_wire.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:11:52 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/09 19:28:05 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_wire	*wire(t_dot *d1, t_dot *d2)
{
	t_wire *wire;

	wire = (t_wire*)malloc(sizeof(t_wire));
	if (!wire)
		return (NULL);
	wire->d1 = d1;
	wire->d2 = d2;
	return (wire);
}
