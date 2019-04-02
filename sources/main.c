/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:52:30 by coremart          #+#    #+#             */
/*   Updated: 2019/04/02 07:35:39 by coremart         ###   ########.fr       */
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
	t_llist		*ll_lis;
	t_piles		*piles;

	if (ac < 2)
		return (usage());
	if (ac == 2)
		return (0);
	if (!(arr = pars((const char**)&av[1], ac - 1)))
		return (1);
	if (!(lis = get_lis_index(arr->arr, (arr->size + 1) >> 1)))
		return (1);
	if (!(ll_lis = transform_to_ll_lis(arr, lis)))
		return (1);
	if (!(piles = transform_to_pile(arr)))
		return (1);
	order_pile(piles, ll_lis);
	// rot_pile
	return (0);
}
