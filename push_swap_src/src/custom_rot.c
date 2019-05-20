/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 23:57:49 by coremart          #+#    #+#             */
/*   Updated: 2019/05/14 04:20:25 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h>
#include <stdlib.h>

size_t		max_rot_bw_non_lis(t_llist *a, t_llist *lis)
{
	t_llist	*end_a;
	size_t	max_rot_count;
	size_t	rot_count;

	end_a = a;
	rot_count = 0;
	max_rot_count = 0;
	if (lis->nb == a->nb)
	{
		++rot_count;
		lis = lis->next;
	}
	a = a->next;
	while (a != end_a)
	{
		if (lis->nb == a->nb)
		{
			++rot_count;
			lis = lis->next;
		}
		else
		{
			if (rot_count > max_rot_count)
				max_rot_count = rot_count;
			rot_count = 0;
		}
		a = a->next;
	}
	printf("max count :%lu, %lu\n", max_rot_count, rot_count);
	if (rot_count > max_rot_count)
		return (rot_count);
	return (max_rot_count);
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
	size_t	rot_til_push_tmp;
	t_llist	*end_a;
	size_t	offset;

	rot_til_push = rot_count_til_push(data->piles->a, data->lis, size, rev);
	offset = (rev) ? sizeof(t_llist*) : 0;
	end_a = data->piles->a;
	while (rot_to_end_a--)
		end_a = *(t_llist**)((char*)end_a + offset);
	rot_til_push_tmp = rot_til_push;
	while (rot_til_push_tmp--)
	{
		data->piles->a = *(t_llist**)((char*)data->piles->a + offset);
		data->lis = *(t_llist**)((char*)data->lis + offset);
	}
	printf("end_a :%d\n", end_a->nb);
//	if (rev)
//		exit(0);
	return (put_non_lis_on_b(data, end_a, rot_til_push, rev));
}

void		rot_to_the_start(t_all_data *data, int tmp_top_lis, int rev);
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

void		ssp_custom_rot(t_all_data *data, size_t size)
{
	ssize_t	rot_to_last;
	ssize_t	rev_rot_to_last;
	int		tmp_top_lis;

	rot_to_last = rot_til_inverse_rot(data->piles->a, data->lis, size, 0);
	rev_rot_to_last = rot_til_inverse_rot(data->piles->a->prev,
												data->lis->prev, size, 1) + 1;
	tmp_top_lis = data->lis->nb;
	printf("rot_to_last :%lu, rev_rot_to_last :%lu\n", rot_to_last, rev_rot_to_last);
	if (rot_to_last > rev_rot_to_last)
	{
		if (rev_rot_to_last)
			custom_ssp(data, size, rev_rot_to_last, 1);
		// rot while not at the start (/!\ if the start is pushed)
		rot_to_the_start(data, tmp_top_lis, 0);
		if (rot_to_last != (ssize_t)-1)
			return (custom_ssp(data, size, rot_to_last, 0));
		return ;
	}
	if (rot_to_last != (ssize_t)-1)
		custom_ssp(data, size, rot_to_last, 0);
	// rot while not at the start (/!\ if the start is pushed)
	rot_to_the_start(data, tmp_top_lis, 1);
	if (rev_rot_to_last)
		custom_ssp(data, size, rev_rot_to_last - 1, 1);
}
