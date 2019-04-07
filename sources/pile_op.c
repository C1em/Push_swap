/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 01:47:45 by coremart          #+#    #+#             */
/*   Updated: 2019/04/07 11:41:28 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>

#include <stdio.h>

/*
**	return the nb of elems in b
*/

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

/*
**	put the first elem of b and put it on a
*/

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
	fill_buffer(buff, PA);
}

/*
**	get the elem of lis that the new pushed b elem have to get put
*/

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

/*
**	allocate the first elem of b
*/

static void init_b(t_all_data *all_data)
{
	if (!(all_data->piles->b = (t_llist_tmp*)malloc(sizeof(t_llist_tmp))))
		exit(1);
	all_data->piles->b->nb = all_data->piles->a->nb;
	all_data->piles->b->next = all_data->piles->b;
	all_data->piles->b->prev = all_data->piles->b;
	all_data->piles->b->dest = get_dest(all_data->piles->b->nb, all_data->lis);
}

/*
**	remove the first elem of a and put it on b
**	call get_dest and init_b if b is empty
*/

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
	fill_buffer(all_data->buff, PB);
}

/*
**	rotate a to get the first elem in the first position
*/

void		rot_a(t_llist **ptr_a, int len, t_data_buff *buff)
{
	int	r_count;

	r_count = 0;
	while ((*ptr_a)->nb > (*ptr_a)->prev->nb)
		++r_count;
	if (r_count > (len >> 1))
	{
		r_count = len - r_count;
		while (r_count--)
		{
			*ptr_a = (*ptr_a)->prev;
			fill_buffer(buff, RRA);
		}
	}
	else
	{
		while (r_count--)
		{
			*ptr_a = (*ptr_a)->next;
			fill_buffer(buff, RA);
		}
	}

}
