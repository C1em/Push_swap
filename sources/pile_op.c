/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 01:47:45 by coremart          #+#    #+#             */
/*   Updated: 2019/04/02 07:38:05 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>

void		push_a(t_piles *piles, t_data_buff *buff)
{
	t_llist *new;

	if (!piles->b)
		return ;
	if (!(new = (t_llist*)malloc(sizeof(t_llist))))
		exit(1) ;
	piles->a->next->prev = new;
	new->next = piles->a->next;
	piles->a->next = new;
	new->prev = piles->a;
	new->nb = piles->b->nb;
	piles->a = piles->a->next;
	piles->b = piles->b->prev;
	piles->b->next = piles->b->next->next;
	free(piles->b->next->prev);
	piles->b->next->prev = piles->b;
	if (buff->buff[buff->index] == PB)
	{
		--buff->index;
		return ;
	}
	++buff->index;
	buff->buff[buff->index] = PA;
}

static int	get_dest(int nb, t_llist *lis)
{
	while (nb < lis->nb)
		lis = lis->prev;
	while (nb > lis->nb)
		lis = lis->next;
	return (lis->nb);
}

void		push_b(t_all_data *all_data)
{
	t_llist_tmp	*new;

	if (!all_data->piles->a)
		return ;
	if (!(new = (t_llist_tmp*)malloc(sizeof(t_llist_tmp))))
		exit (1);
	all_data->piles->b->next->prev = new;
	new->next = all_data->piles->b->next;
	all_data->piles->b->next = new;
	new->prev = all_data->piles->b;
	new->nb =all_data-> piles->a->nb;
	all_data->piles->b = all_data->piles->b->next;
	new->dest = get_dest(new->nb, all_data->lis);
	all_data->piles->a = all_data->piles->a->prev;
	all_data->piles->a->next = all_data->piles->a->next->next;
	all_data->piles->a->next->prev = all_data->piles->a;
	if (all_data->buff->buff[all_data->buff->index] == PA)
	{
		--all_data->buff->index;
		return ;
	}
	++all_data->buff->index;
	all_data->buff->buff[all_data->buff->index] = PB;
}
