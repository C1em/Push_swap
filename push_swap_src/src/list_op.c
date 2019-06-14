/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:37:54 by coremart          #+#    #+#             */
/*   Updated: 2019/06/14 02:06:44 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

#include <stdio.h>

t_llist		*add_elem(t_llist *pile, int nb)
{
	if (!(pile->prev->next = (t_llist*)malloc(sizeof(t_llist))))
		exit(1);
	pile->prev->next->prev = pile->prev;
	pile->prev = pile->prev->next;
	pile->prev->next = pile;
	pile->prev->nb = nb;
	return (pile->prev);
}

/*
**	take the int* lis and return it as a doubly linked list
*/

t_llist		*transform_to_ll_lis(t_arr *arr, int *lis)
{
	int			i;
	int			min_index;
	t_llist		*ll_lis;
	t_llist		*ll_lis_res;

	i = lis[-1] - 1;
	if (!(ll_lis = (t_llist*)malloc(sizeof(t_llist))))
		exit(1);
	ll_lis->nb = arr->arr[lis[i]];
	ll_lis->next = ll_lis;
	ll_lis->prev = ll_lis;
	ll_lis_res = ll_lis;
	min_index = lis[i] % ((arr->size + 1) >> 1);
	while (i--)
	{
		ll_lis = add_elem(ll_lis, arr->arr[lis[i]]);
		if (lis[i] % ((arr->size + 1) >> 1) < min_index)
		{
			min_index = lis[i] % ((arr->size + 1) >> 1);
			ll_lis_res = ll_lis;
		}
	}
	return (ll_lis_res);
}

/*
**	take the array of nb and return a t_piles within a doubly linked list
**	a that have all the nb in it
*/

t_piles		*transform_to_pile(t_arr *arr)
{
	int		i;
	t_piles	*piles;

	i = (arr->size + 1) >> 1;
	if (!(piles = (t_piles*)malloc(sizeof(t_piles))))
		exit(1);
	if (!(piles->a = (t_llist*)malloc(sizeof(t_llist))))
		exit(1);
	piles->b = NULL;
	--i;
	piles->a->nb = arr->arr[i];
	piles->a->next = piles->a;
	piles->a->prev = piles->a;
	while (i--)
		piles->a = add_elem(piles->a, arr->arr[i]);
	return (piles);
}

/*
**	add an elem the lis
**	this function is called after a push_a to because the elem is now at
**	his place and won't move after
*/

void		add_to_lis(t_llist *lis, int nb)
{
	t_llist *new;

	if (!(new = (t_llist*)malloc(sizeof(t_llist))))
		exit(1);
	while (nb > lis->nb || nb < lis->prev->nb)
	{
		lis = lis->next;
		if (lis->prev->nb > lis->nb && (nb > lis->prev->nb || nb < lis->nb))
			break ;
	}
	lis->prev->next = new;
	new->prev = lis->prev;
	new->next = lis;
	lis->prev = new;
	new->nb = nb;
}
