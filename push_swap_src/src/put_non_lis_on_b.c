/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_non_lis_on_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 20:56:44 by coremart          #+#    #+#             */
/*   Updated: 2019/06/11 04:11:24 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

/*
**	go through b:	put the nb of rotation of the elems that
**							have to be pushed on a in a array
**					call push_a_tab with the array
**					return the nb of of elems pushed on a
*/

int					pusha_if_destof(t_all_data *all_data, int max_elem, int rev)
{
	t_llist_tmp	*end_b;
	t_llist_tmp	*tmp_b;
	t_arr		tmp_arr;
	int			i;

	if (!max_elem || !(tmp_b = all_data->piles->b))
		return (0);
	if (!(tmp_arr.arr = (int*)malloc(sizeof(int) * (max_elem + 1))))
		exit(1);
	end_b = tmp_b->prev;
	tmp_arr.size = 0;
	i = 0;
	while (tmp_b != end_b && ++tmp_arr.size)
	{
		if (tmp_b->dest == all_data->piles->a->nb && ++i)
			tmp_arr.arr[i - 1] = tmp_arr.size - 1;
		tmp_b = tmp_b->next;
	}
	if (tmp_b->dest == all_data->piles->a->nb && ++i)
		tmp_arr.arr[i - 1] = tmp_arr.size;
	++tmp_arr.size;
	tmp_arr.arr[i] = -1;
	tmp_arr.size = push_a_tab(&tmp_arr, all_data, rev);
	free(tmp_arr.arr);
	return (tmp_arr.size);
}

/*
**	go through a:	push b the one that aren't in lis
**					call pusha_if_destof at each iteration
*/

void				put_non_lis_on_b(t_all_data *all_data, t_llist *end_a,
									size_t rot_count, int rev)
{
	int		max_elem;
	size_t	offset;

	offset = (rev) ? sizeof(t_llist*) : 0;
	while (rot_count--)
		fill_buffer(all_data->buff, ((rev) ? RRA : RA));
	max_elem = len_b(all_data->piles->b) + 1;
	while (all_data->piles->a != end_a)
	{
		max_elem -= pusha_if_destof(all_data, max_elem, rev);
		if (all_data->piles->a->nb == all_data->lis->nb)
		{
			all_data->lis = *(t_llist**)((char*)all_data->lis + offset);
			rot_a(all_data, rev);
		}
		else
		{
			push_b(all_data);
			++max_elem;
			if (rev)
				rot_a(all_data, 1);
		}
	}
	push_b(all_data);
}

/*
**	find the first elem of a that is not in lis and call put_non_lis_on_b
**	with rev = 1 if the first elem is in the "reverse" order or rev = 0 if
**	the first elem is in the "normal" order
*/

void				start_sort_pile(t_all_data *data, size_t size)
{
	size_t	rot_til_push;
	size_t	rev_rot_til_push;
	t_llist	*end_a;

	if ((rot_til_push = rot_count_til_push(data->piles->a, data->lis, size, 0))
						== size)
		return ;
	if ((max_rot_bw_non_lis(data->piles->a, data->lis) << 1) > size)
		return (ssp_custom_rot(data, size));
	rev_rot_til_push = rot_count_til_push(data->piles->a->prev, data->lis->prev,
											size, 1) + 1;
	if (rev_rot_til_push >= rot_til_push
		|| ((rot_til_push - rev_rot_til_push) << 1)
		< size - lst_len(data->lis))
	{
		end_a = rot_pile(rev_rot_til_push, data->piles->a, 1);
		data->piles->a = rot_pile(rot_til_push, data->piles->a, 0);
		data->lis = rot_pile(rot_til_push, data->lis, 0);
		return (put_non_lis_on_b(data, end_a, rot_til_push, 0));
	}
	end_a = rot_pile(rot_til_push, data->piles->a, 0);
	data->piles->a = rot_pile(rev_rot_til_push, data->piles->a, 1);
	data->lis = rot_pile(rev_rot_til_push, data->lis, 1);
	put_non_lis_on_b(data, end_a, rev_rot_til_push, 1);
}
