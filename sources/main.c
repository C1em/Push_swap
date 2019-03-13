/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:52:30 by coremart          #+#    #+#             */
/*   Updated: 2019/03/13 09:47:37 by coremart         ###   ########.fr       */
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
	int		*lis;

	if (ac < 2)
		return (usage());
	arr = pars((const char**)&av[1], ac - 1);

	arr->size = 9;
	arr->arr[0] = 0;
	arr->arr[1] = 1;
	arr->arr[2] = 2;
	arr->arr[3] = 3;
	arr->arr[4] = 4;
	arr->arr[5] = 0;
	arr->arr[6] = 1;
	arr->arr[7] = 2;
	arr->arr[8] = 3;

	lis = get_lis(arr->arr, arr->size);
	printf("%d, %d, %d, %d, %d\n", lis[0], lis[1], lis[2], lis[3], lis[4]);
	return (0);
}
