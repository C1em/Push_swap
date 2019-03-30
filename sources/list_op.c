/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:37:54 by coremart          #+#    #+#             */
/*   Updated: 2019/03/30 19:13:58 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>

t_llist		*transform_to_ll_lis(t_arr *arr, int *lis)
{
	int			i;
	t_llist		*ll_lis;

	i = lis[-1] - 1;
	if (!(ll_lis = (t_llist*)malloc(sizeof(ll_lis) * ((arr->size + 1) >> 1))))
		return (NULL);
	ll_lis[i].nb = arr->arr[lis[i]];
	ll_lis[i].next = ll_lis;
	ll_lis->prev = &ll_lis[i];
	while (i--)
	{
		ll_lis[i].nb = arr->arr[lis[i]];
		ll_lis[i + 1].prev = &ll_lis[i];
		ll_lis[i].next = &ll_lis[i + 1];
	}
	return (ll_lis);
}

t_llist		*transform_to_pile(t_arr *arr)
{
	int		i;
	t_piles	*piles;

	i = (arr->size + 1) >> 1;
	if (!(piles->a = (t_llist*)malloc(sizeof(t_llist) * i)))
		return (NULL);
	piles->b = NULL;
	if (!(piles = (t_piles*)malloc(sizeof(t_piles))))
		return (NULL);
	--i;
	piles->a[i].nb = arr->arr[i];
	piles->a[i].next = piles->a;
	piles->a->prev = &piles->a[i];
	while (i--)
	{
		piles->a[i].nb = arr->arr[i];
		piles->a[i].next = &piles->a[i + 1];
		piles->a[i + 1].prev = &piles->a[i];
	}
	return (piles);
}
