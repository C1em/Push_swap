/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 01:47:45 by coremart          #+#    #+#             */
/*   Updated: 2019/04/05 06:09:51 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>

#include <stdio.h>

int			len_b(t_llist_tmp *b)
{
	t_llist_tmp *end_b;
	int i;

	if (!b)
		return (0);
	end_b = b->prev;
	i = 0;
	while (end_b != b)
	{
		++i;
		b = b->next;
	}
	return (i + 1);
}

void		push_a(t_piles *piles, t_data_buff *buff)
{
	t_llist *new;

/*	printf("\n\nbefore push a :\n\n");
	print_list((void*)piles->a);
*/	if (!piles->b)
		return ;
	if (!(new = (t_llist*)malloc(sizeof(t_llist))))
		exit(1) ;
	new->nb = piles->b->nb;
	piles->a->prev->next = new;
	new->next = piles->a;
	new->prev = piles->a->prev;
	piles->a->prev = new;
	piles->a = new;
	if (piles->b == piles->b->next)
	{
		free(piles->b);
		piles->b = NULL;
	}
	else
	{
		piles->b->next->prev = piles->b->prev;
		piles->b = piles->b->next;
		free(piles->b->prev->next);
		piles->b->prev->next = piles->b;
	}
	if (buff->buff[buff->index] == PB)
	{
		--buff->index;
		return ;
	}
/*	printf("\n\nafter push a :\n\n");
	print_list((void*)piles->a);
*/	++buff->index;
	buff->buff[buff->index] = PA;
}

static int	get_dest(int nb, t_llist *lis)
{
	while (nb > lis->nb || nb < lis->prev->nb)
	{
		if (lis->nb > lis->next->nb && (nb > lis->nb || nb < lis->next->nb))
			return (lis->next->nb);
		lis = lis->next;
	}
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
		new->nb = all_data->piles->a->nb;
		all_data->piles->b->prev->next = new;
		new->next = all_data->piles->b;
		new->prev = all_data->piles->b->prev;
		all_data->piles->b->prev = new;
		new->dest = get_dest(new->nb, all_data->lis);
		all_data->piles->b = new;
	}
	all_data->piles->a = all_data->piles->a->prev;
	all_data->piles->a->next = all_data->piles->a->next->next;
	all_data->piles->a->next->prev = all_data->piles->a;
	if (all_data->buff->buff[all_data->buff->index] == PA)
		--all_data->buff->index;
	else
	{
		++all_data->buff->index;
		all_data->buff->buff[all_data->buff->index] = PB;
	}
}

void		rot_a(t_llist **ptr_a, int len, t_data_buff *buff)
{

	int rot_count;

	rot_count = 0;
	while ((*ptr_a)->nb > (*ptr_a)->prev->nb)
	{
		*ptr_a = (*ptr_a)->next;
		++rot_count;
	}
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
		return ;
	}
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
