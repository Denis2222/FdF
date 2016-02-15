/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 13:43:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/08 14:59:01 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*read_file(int ac, char **av)
{
	t_list	*list;
	t_list	*l;
	int		fd;
	char	*line;

	list = NULL;
	if (ac == 2)
		if ((fd = open(av[1], O_RDONLY)))
		{
			while (get_next_line(fd, &line) > 0)
			{
				l = ft_lstnew(line, sizeof(char) * ft_strlen(line) + 1);
				ft_lstpush(&list, l);
			}
			if (list)
				return (list);
		}
	exit(EXIT_FAILURE);
}
