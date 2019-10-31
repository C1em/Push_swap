/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssp_custom_rot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 23:57:49 by coremart          #+#    #+#             */
/*   Updated: 2019/10/31 23:53:11 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t			max_rot_bw_non_lis(t_llist *a, t_llist *lis)
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
		if (lis->nb == a->nb && ++rot_count)
			lis = lis->next;
		else
			rot_count = 0;
		if (rot_count > max_rot_count)
			max_rot_count = rot_count;
		a = a->next;
	}
	return (max_rot_count);
}

static ssize_t	rot_til_rev(t_llist *a, t_llist *lis, size_t size, int rev)
{
	size_t	offset;
	size_t	rev_offset;
	ssize_t	rot_count;
	ssize_t	res;

	offset = (rev) ? sizeof(t_llist*) : 0;
	rev_offset = (rev) ? 0 : sizeof(t_llist*);
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
	put_non_lis_on_b(data, end_a, rot_til_push, rev);
}

static void		rot_to_the_start(t_all_data *data, int tmp_top_lis, int rev)
{
	size_t	offset;

	offset = (rev) ? sizeof(t_llist*) : 0;
	while (data->lis->nb != tmp_top_lis)
	{
		data->lis = *(t_llist**)((char*)data->lis + offset);
		rot_a(data, rev);
	}
	if (rev)
	{
		data->lis = data->lis->prev;
		rot_a(data, 1);
	}
}

void			ssp_custom_rot(t_all_data *data, size_t size)
{
	ssize_t	to_last;
	ssize_t	rev_to_last;
	int		tmp_top_lis;

	to_last = rot_til_rev(data->piles->a, data->lis, size, 0);
	rev_to_last = rot_til_rev(data->piles->a->prev, data->lis->prev, size, 1);
	tmp_top_lis = data->lis->nb;
	if (to_last > rev_to_last + 1)
	{
		if (rev_to_last != (ssize_t)-1)
		{
			data->lis = data->lis->prev;
			rot_a(data, 1);
			custom_ssp(data, size, rev_to_last, 1);
			data->lis = data->lis->next;
			rot_to_the_start(data, tmp_top_lis, 0);
		}
		custom_ssp(data, size, to_last, 0);
		return ;
	}
	if (to_last != (ssize_t)-1)
		custom_ssp(data, size, to_last, 0);
	rot_to_the_start(data, tmp_top_lis, 1);
	if (rev_to_last != (ssize_t)-1)
		custom_ssp(data, size, rev_to_last, 1);
}
