/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 01:47:45 by coremart          #+#    #+#             */
/*   Updated: 2019/04/03 01:51:42 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>

#include <stdio.h>

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

static void init_b(t_all_data *all_data)
{
	if (!(all_data->piles->b = (t_llist_tmp*)malloc(sizeof(t_llist_tmp))))
		exit(1);
	all_data->piles->b->nb = all_data->piles->a->nb;
	all_data->piles->b->next = all_data->piles->b;
	all_data->piles->b->prev = all_data->piles->b;
	all_data->piles->b->dest = get_dest(all_data->piles->b->nb, all_data->lis);
}

void		push_b(t_all_data *all_data)
{
	t_llist_tmp	*new;

	if (!all_data->piles->a)
		return ;
	if (!all_data->piles->b)
		init_b(all_data);
	else
	{
		if (!(new = (t_llist_tmp*)malloc(sizeof(t_llist_tmp))))
			exit (1);
		all_data->piles->b->next->prev = new;
		new->next = all_data->piles->b->next;
		all_data->piles->b->next = new;
		new->prev = all_data->piles->b;
		new->nb =all_data-> piles->a->nb;
		all_data->piles->b = all_data->piles->b->next;
		new->dest = get_dest(new->nb, all_data->lis);
	}
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

void		rot_a(t_llist *a, int len, t_data_buff *buff)
{

	int rot_count;

	rot_count = 0;
	while (a->nb > a->next->nb)
	{
		a = a->next;
		++rot_count;
	}
	a = a->next;
	++rot_count;
	if (rot_count > (len >> 1))
	{
		rot_count = len - rot_count;
		while (rot_count--)
		{
			if (buff->buff[buff->index] == RA)
				--buff->index;
			else
			{
				++buff->index;
				buff->buff[buff->index] = RRA;
			}
		}
	}
	else
	{
		while (rot_count--)
		{
			if (buff->buff[buff->index] == RRA)
				--buff->index;
			else
			{
				++buff->index;
				buff->buff[buff->index] = RA;
			}
		}
	}

}
