/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:52:30 by coremart          #+#    #+#             */
/*   Updated: 2019/03/09 07:41:00 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>

#include <stdio.h>

static int	usage(void)
{
	return (0);
}

int		main(int ac, char **av)
{
	t_arr	*arr;
	int		*sorted;

	if (ac < 2)
		return (usage());
	arr = pars((const char**)&av[1], ac - 1);

	arr->size = 5;
	arr->arr[0] = 10;
	arr->arr[1] = 65;
	arr->arr[2] = 351;
	arr->arr[3] = -96;
	arr->arr[4] = 0;

	sorted = sort_array(arr);
	simplify_arr(arr->arr, sorted, arr->size);
	free(sorted);
//	printf("%d|%d|%d|%d|%d\n", arr->arr[0], arr->arr[1], arr->arr[2], arr->arr[3], arr->arr[4]);
	mark_the_ones_to_move(arr);
	return (0);
}
