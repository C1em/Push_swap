/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:52:30 by coremart          #+#    #+#             */
/*   Updated: 2019/03/25 21:01:33 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

static int	usage(void)
{
	return (0);
}

int		main(int ac, char **av)
{
	t_arr		*arr;
	int			*lis;
	t_list_head	*head;
	int			*info_arr;

	if (ac < 2)
		return (usage());
	if (ac == 2)
		return (0);
	if (!(arr = pars((const char**)&av[1], ac - 1)))
		return (1);
	if (!(lis = get_lis_index(arr->arr, (arr->size + 1) >> 1)))
		return (1);
	if (!(head = transform_to_llist(arr, lis)))
		return (1);
	info_arr = transform_to_info_arr(arr, lis);
	while (head)
	{
		printf("%d\n", *(int*)(head + 1));
		head = head->next;
	}
	return (0);
}
