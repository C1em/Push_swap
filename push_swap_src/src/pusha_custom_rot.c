/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pusha_custom_rot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:33:13 by coremart          #+#    #+#             */
/*   Updated: 2019/05/23 15:35:03 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h>
#include <stdlib.h>

size_t		max_rot_bw_non_pusha(t_arr *arr)
{
	size_t rot_count;
	size_t	i;

	rot_count = 0;
	i = 0;
	while (arr->arr[i + 1] != -1)
	{
		if (arr->arr[i + 1] - arr->arr[i] > rot_count)
			rot_count = arr->arr[i] - arr->arr[i + 1];
		++i;
	}
	return (rot_count);
}

static ssize_t		rot_til_inverse_rot(t_llist *a, t_llist *lis, size_t size,
																		int rev)
{
	size_t	offset;
	size_t	rev_offset;
	ssize_t	rot_count;
	ssize_t	res;

	offset = (rev) ? sizeof(t_llist*) : 0;
	rev_offset = (rev) ? 0 :sizeof(t_llist*);
	rot_count = 0;
	res = 0;
	while ((rot_count << 1) < (ssize_t)size)
	{
		if (lis->nb == a->nb)
		{
			++rot_count;
			lis = *(t_llist**)((char*)lis + offset);
		}
		else
			rot_count = 0;
		a = *(t_llist**)((char*)a + offset);
		++res;
	}
	return (res - rot_count - 1);
}

static void		custom_ssp(t_all_data *data, size_t size, size_t rot_to_end_a,
																	int rev)
{
	size_t	rot_til_push;
	t_llist	*end_a;
	size_t	offset;

	rot_til_push = rot_count_til_push(data->piles->a, data->lis, size, rev);
	offset = (rev) ? sizeof(t_llist*) : 0;
	end_a = data->piles->a;
	while (rot_to_end_a--)
		end_a = *(t_llist**)((char*)end_a + offset);
	rot_to_end_a = rot_til_push;
	while (rot_to_end_a--)
	{
		data->piles->a = *(t_llist**)((char*)data->piles->a + offset);
		data->lis = *(t_llist**)((char*)data->lis + offset);
	}
	return (put_non_lis_on_b(data, end_a, rot_til_push, rev));
}

static void		rot_to_the_start(t_all_data *data, int tmp_top_lis, int rev)
{
	size_t	offset;
	int		op;

	offset = (rev) ? sizeof(t_llist*) : 0;
	op = (rev) ? RRA : RA;
	while (data->lis->nb != tmp_top_lis)
	{
		data->lis = *(t_llist**)((char*)data->lis + offset);
		data->piles->a = *(t_llist**)((char*)data->piles->a + offset);
		fill_buffer(data->buff, op);
	}
	if (rev)
	{
		data->lis = data->lis->prev;
		data->piles->a = data->piles->a->prev;
		fill_buffer(data->buff, RRA);
	}
}

static int	get_next_non_pusha(t_llist_tmp *b, t_arr *arr)
{
	int i;

	i = 0;
	while (arr->arr[i] == i)
	{
		b = b->next;
		++i;
	}
	return (b->nb);
}

int		pusha_custom_rot(t_all_data *data, t_arr *arr, t_llist *end_a, int rev)
{
	ssize_t	rot_to_last;
	ssize_t	rev_rot_to_last;
	int		top_b;

	//change to count on b
	rot_to_last = rot_til_inverse_rot(data->piles->a, data->lis, size, 0);
	rev_rot_to_last = rot_til_inverse_rot(data->piles->a->prev,
												data->lis->prev, size, 1);
	if (rev_rot_to_last + count_rot_to_next_pa(data, rot_to_last, end_a, rev << 1)
		< rot_to_last
		+ count_rot_to_next_pa(data, rev_rot_to_last, end_a, (rev << 1) + 1))
	{
		top_b = data->piles->b->nb;
		if (rev_rot_to_last != (ssize_t)-1)
		{
			data->piles->b = data->piles->b->prev;
			fill_buffer(data->buff, RRB);
			custom_pusha(data, size, rev_rot_to_last, 1);
			//change
			rot_to_the_start(data, top_b, 0);
		}
		if (rot_to_last != (ssize_t)-1)
			return (custom_pusha(data, size, rot_to_last, 0));
		return ;
	}
	top_b = get_next_non_pusha(data->piles->b, arr);
	if (rot_to_last != (ssize_t)-1)
		custom_pusha(data, size, rot_to_last, 0);
	//change
	rot_to_the_start(data, top_b, 1);
	if (rev_rot_to_last != (ssize_t)-1)
		custom_ssp(data, size, rev_rot_to_last, 1);
}
