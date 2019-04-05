/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:52:30 by coremart          #+#    #+#             */
/*   Updated: 2019/04/05 02:18:41 by coremart         ###   ########.fr       */
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
	t_data_buff data_buff;
	t_all_data	all_data;

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
	piles = transform_to_pile(arr);
	data_buff.index = 0;
	all_data.buff = &data_buff;
	all_data.piles = piles;
	all_data.lis = ll_lis;

/*	t_llist *end_lis = all_data.lis;
	do
	{
		printf("lis :%d\n", all_data.lis->nb);
		all_data.lis = all_data.lis->next;
	}
	while (all_data.lis != end_lis);
*/
	order_pile(&all_data);
	rot_a(&piles->a, (arr->size + 1) >> 1, &data_buff);

	t_llist *end_a = piles->a;
	do
	{
		printf("%d\n", piles->a->nb);
		piles->a = piles->a->next;
	}
	while (piles->a != end_a);

	return (0);
}
