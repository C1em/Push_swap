/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:05:27 by coremart          #+#    #+#             */
/*   Updated: 2019/04/08 09:45:49 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

#include <stdio.h>

static int			is_destof(t_llist_tmp *b, int dest)
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

static void			push_all_rev(t_all_data *data, size_t rot_count)
{
	t_llist	*end_a;
	int		max_elem;

	max_elem = len_b(data->piles->b);
	end_a = data->piles->a;
	while (rot_count--)
		fill_buffer(data->buff, RRA);
	max_elem -= pusha_if_destof(data, max_elem);
	data->piles->a = data->piles->a->prev;
	while (data->piles->a != end_a)
	{
		max_elem -= pusha_if_destof(data, max_elem);
		data->piles->a = data->piles->a->prev;
	}
}

static void			push_all(t_all_data *data, size_t rot_count)
{
	t_llist	*end_a;
	int		max_elem;

	max_elem = len_b(data->piles->b);
	end_a = data->piles->a;
	while (rot_count--)
		fill_buffer(data->buff, RA);
	max_elem -= pusha_if_destof(data, max_elem);
	data->piles->a = data->piles->a->next;
	while (data->piles->a != end_a)
	{
		max_elem -= pusha_if_destof(data, max_elem);
		data->piles->a = data->piles->a->next;
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
			return (push_all_rev(data, rot_count));
		}
		tmp_a_rot = tmp_a_rot->next;
		tmp_a_rev_rot = tmp_a_rev_rot->prev;
		++rot_count;
	}
	data->piles->a = tmp_a_rot;
	return (push_all(data, rot_count));
}
