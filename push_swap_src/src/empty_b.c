/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:05:27 by coremart          #+#    #+#             */
/*   Updated: 2019/05/03 03:25:48 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include "libft.h"

static int			is_destof(t_llist_tmp *b, int dest)
{
	t_llist_tmp *end_b;

	end_b = b;
	if (b->dest == dest)
		return (1);
	b = b->next;
	while (b != end_b)
	{
		if (b->dest == dest)
			return (1);
		b = b->next;
	}
	return (0);
}

static size_t		count_rot_til_dest_of(t_piles *piles, size_t size, int rev)
{
	size_t	rot_count;
	int		offset;
	t_llist	*tmp_a;

	tmp_a = piles->a;
	rot_count = 0;
	offset = (rev) ? sizeof(t_llist*) : 0;
	while (!is_destof(piles->b, tmp_a->nb))
	{
		tmp_a = *(t_llist**)((char*)tmp_a + offset);
		if (++rot_count == size)
			break ;
	}
	return (rot_count);
}

static size_t		rot_count_after_empty(t_llist *a, size_t rot_count, size_t size,
																			int rev)
{
	int offset;

	offset = (rev) ? sizeof(t_llist*) : 0;
	while (rot_count--)
		a = *(t_llist**)((char*)a + offset);
	rot_count = 0;
	while (a->nb > a->prev->nb)
	{
		a = a->next;
		++rot_count;
	}
	if (rot_count > (size >> 1))
		return (size - rot_count);
	return (rot_count);
}

static void			push_all(t_all_data *data, const t_llist *end_a,
													size_t rot_count, int rev)
{
	int		max_elem;
	int		op;
	size_t	offset;

	op = (rev) ? RRA : RA;
	offset = (rev) ? sizeof(t_llist*) : 0;
	while (rot_count--)
		fill_buffer(data->buff, op);
	max_elem = len_b(data->piles->b);
	max_elem -= pusha_if_destof(data, max_elem);
	while (data->piles->a != end_a)
	{
		if (!end_a)
			end_a = data->piles->a;
		data->piles->a = *(t_llist**)((char*)data->piles->a + offset);
		fill_buffer(data->buff, op);
		max_elem -= pusha_if_destof(data, max_elem);
	}
	rm_useless_rot(data, 0, rev);
}

void				empty_b(t_all_data *data, size_t size)
{
	size_t	rot_til_push;
	size_t	rev_rot_til_push;
	size_t	rot_to_smallest;
	size_t	rev_rot_to_smallest;
	t_llist	*end_a;

	if (!data->piles->b
		|| (rot_til_push = count_rot_til_dest_of(data->piles, size, 0)) == size)
		return ;
	rev_rot_til_push = count_rot_til_dest_of(data->piles, size, 1);
	rot_to_smallest = rot_count_after_empty(data->piles->a, rot_til_push, size, 0);
	rev_rot_to_smallest = rot_count_after_empty(data->piles->a, rev_rot_til_push,
																		size, 1);
	if (rot_til_push + rev_rot_to_smallest >= rev_rot_til_push + rot_to_smallest
		|| ((rev_rot_til_push + rot_to_smallest - rot_til_push - rev_rot_to_smallest)
		+ ((rev_rot_til_push + rot_to_smallest - rot_til_push - rev_rot_to_smallest) >> 1))
		<= (size_t)len_b(data->piles->b))
	{
		end_a = (rot_til_push) ? data->piles->a : NULL;
		rot_til_push = rev_rot_til_push;
		while (rot_til_push--)
			data->piles->a = data->piles->a->prev;
		return (push_all(data, end_a, rev_rot_til_push, 1));
	}
	end_a = (rot_til_push) ? data->piles->a : NULL;
	rev_rot_til_push = rot_til_push;
	while (rev_rot_til_push--)
		data->piles->a = data->piles->a->next;
	return (push_all(data, end_a, rot_til_push, 0));
}
