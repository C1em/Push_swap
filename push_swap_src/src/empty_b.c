/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:05:27 by coremart          #+#    #+#             */
/*   Updated: 2019/04/12 17:25:11 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h>

int				is_destof(t_llist_tmp *b, int dest)
{
	t_llist_tmp *end_b;

	end_b = b->prev;
	while (b != end_b)
	{
		if (b->dest == dest)
			return (1);
		b = b->next;
	}
	if (b->dest == dest)
		return (1);
	return (0);
}

static void			push_all(t_all_data *data, size_t rot_count, int rev)
{
	t_llist	*end_a;
	int		max_elem;
	int		op;
	size_t	offset;

	op = (rev) ? RRA : RA;
	offset = (rev) ? sizeof(t_llist*) : 0;
	max_elem = len_b(data->piles->b);
	end_a = data->piles->a;
	while (rot_count--)
		fill_buffer(data->buff, op);
	max_elem -= pusha_if_destof(data, max_elem);
	data->piles->a = *(t_llist**)((char*)data->piles->a + offset);
	while (data->piles->a != end_a)
	{
		max_elem -= pusha_if_destof(data, max_elem);
		data->piles->a = *(t_llist**)((char*)data->piles->a + offset);
	}
}

void				empty_b(t_all_data *data)
{
	size_t	rot_count;
	t_llist	*tmp_a_rot;
	t_llist	*tmp_a_rev_rot;

	if (!data->piles->b)
		return ;
	rot_count = 0;
	tmp_a_rev_rot = data->piles->a;
	tmp_a_rot = data->piles->a;
	while (!is_destof(data->piles->b, tmp_a_rot->nb))
	{
		if (is_destof(data->piles->b, tmp_a_rev_rot->nb))
		{
			data->piles->a = tmp_a_rev_rot;
			return (push_all(data, rot_count, 1));
		}
		tmp_a_rot = tmp_a_rot->next;
		tmp_a_rev_rot = tmp_a_rev_rot->prev;
		++rot_count;
	}
	data->piles->a = tmp_a_rot;
	return (push_all(data, rot_count, 0));
}
