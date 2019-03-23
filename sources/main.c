/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:52:30 by coremart          #+#    #+#             */
/*   Updated: 2019/03/23 22:04:12 by coremart         ###   ########.fr       */
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
	if (ac == 2)
		return (0);
	arr = pars((const char**)&av[1], ac - 1);
	lis = get_lis(arr->arr, (arr->size + 1) >> 1);
/*	int i = -1;
	while(++i < lis[-1])
		printf("%d : %d \n", lis[i], arr->arr[lis[i]]);
*/	return (0);
}
