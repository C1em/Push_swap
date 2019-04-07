/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_non_lis_on_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 20:56:44 by coremart          #+#    #+#             */
/*   Updated: 2019/04/07 13:39:38 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <string.h>
#include <stdlib.h>

/*
**	rotate to get the good number a the top of a before the push a
**	especially when we have already pushed on a at this position,
**	we need to rotate in consequence
*/

static void		rot_a_to_match_the_push(t_all_data *all_data)
{
	while (all_data->piles->a->nb != all_data->piles->b->dest)
	{
		all_data->piles->a = all_data->piles->a->next;
		fill_buffer(all_data->buff, RA);
	}
	while (all_data->piles->b->nb < all_data->piles->a->prev->nb
			|| all_data->piles->b->nb > all_data->piles->a->nb)
	{
		if (all_data->piles->a->prev->nb > all_data->piles->a->nb
				&& (all_data->piles->b->nb > all_data->piles->a->prev->nb
				|| all_data->piles->b->nb < all_data->piles->a->nb))
			break;
		all_data->piles->a = all_data->piles->a->prev;
		fill_buffer(all_data->buff, RRA);
	}
}

/*
**	collect all elems that have to be push on a int the "reverse" order
**				and call rot_a_to_match_the_push then call push_a and add_to_lis
*/

static void		push_a_tab_reverse_rot(size_t len_arr, int *arr, size_t len_b,
															t_all_data *all_data)
{
	size_t rot_count;
	size_t i;

	i = len_arr;
	while (i--)
	{
		rot_count = len_b - arr[i];
		while (rot_count--)
		{
			all_data->piles->b = all_data->piles->b->prev;
			fill_buffer(all_data->buff, RRB);
		}
		rot_a_to_match_the_push(all_data);
		push_a(all_data->piles, all_data->buff);
		add_to_lis(all_data->lis, all_data->piles->a->nb);
		len_b = arr[i];
	}
}

/*
**	collect all elems that have to be push on a int the "normal" order
**				and call rot_a_to_match_the_push then call push_a and add_to_lis
*/

static void		push_a_tab_rot(size_t len_arr, int *arr, t_all_data *all_data)
{
	int rot_count;
	size_t i;
	int next;

	i = 0;
	next = 0;
	while (i < len_arr)
	{
		rot_count = arr[i] - next;
		while (rot_count--)
		{
			all_data->piles->b = all_data->piles->b->next;
			fill_buffer(all_data->buff, RB);
		}
		rot_a_to_match_the_push(all_data);
		push_a(all_data->piles, all_data->buff);
		add_to_lis(all_data->lis, all_data->piles->a->nb);
		next = arr[i] + 1;
		++i;
	}
}

/*
**	orient in push_a_tab_rot or push_a_tab_reverse_rot according to
**	array elements aiming to the least rotations to push all ements
**	return array's lenghth
*/

static int		push_a_tab(int *arr, int size_b, t_all_data *all_data)
{
	size_t len;
	t_llist_tmp *tmp_b;
	int tmp_dest;

	len = 0;
	while (arr[len] != -1)
		++len;
	if (!len)
		return (0);
	tmp_b = all_data->piles->b;
	tmp_dest = arr[0];
	while (tmp_dest--)
		tmp_b = tmp_b->next;
	tmp_dest = tmp_b->dest;
	if (arr[0] > size_b - arr[len - 1])
		push_a_tab_reverse_rot(len, arr, size_b, all_data);
	else
		push_a_tab_rot(len, arr, all_data);
	while (all_data->piles->a->nb != tmp_dest)
	{
		all_data->piles->a = all_data->piles->a->next;
		fill_buffer(all_data->buff, RA);
	}
	return (len);
}

/*
**	go through b:	put the nb of rotation of the elems that
**							have to be pushed on a in a array
**					call push_a_tab with the array
**					return the nb of of elems pushed on a
*/

int			pusha_if_destof(t_all_data *all_data, int max_elem)
{
	t_llist_tmp	*end_b;
	t_llist_tmp	*tmp_b;
	int			r_count;
	int			*tmp_arr;
	int			i;

	if (!max_elem)
		return (0);
	if (!(tmp_b = all_data->piles->b))
		return (0);
	if (!(tmp_arr = (int*)malloc(sizeof(int) * (max_elem + 1))))
		exit(1);
	end_b = tmp_b->prev;
	r_count = 0;
	i = 0;
	while (tmp_b != end_b)
	{
		if (tmp_b->dest == all_data->piles->a->nb)
		{
			tmp_arr[i] = r_count;
			++i;
		}
		tmp_b = tmp_b->next;
		++r_count;
	}
	tmp_arr[i] = -1;
	if (tmp_b->dest == all_data->piles->a->nb)
	{
		tmp_arr[i] = r_count;
		++i;
	}
	tmp_arr[i] = -1;
	r_count = push_a_tab(tmp_arr, r_count + 1, all_data);
	free(tmp_arr);
	return (r_count);
}

/*
**	go through a:	push b the one that aren't in lis
**					call pusha_if_destof at each iteration
*/

void		put_non_lis_on_b(t_all_data *all_data)
{
	t_llist		*end_a;
	int			max_elem;

	end_a = all_data->piles->a->prev;
	max_elem = 0;
	while (all_data->piles->a != end_a)
	{
		max_elem -= pusha_if_destof(all_data, max_elem);
		if (all_data->piles->a->nb == all_data->lis->nb)
			all_data->lis = all_data->lis->next;
		else
		{
			push_b(all_data);
			++max_elem;
		}
		all_data->piles->a = all_data->piles->a->next;
		fill_buffer(all_data->buff, RA);
	}
	max_elem -= pusha_if_destof(all_data, max_elem);
	if (all_data->piles->a->nb == all_data->lis->nb)
		all_data->lis = all_data->lis->next;
	else
	{
		push_b(all_data);
		++max_elem;
	}
	all_data->piles->a = all_data->piles->a->next;
	fill_buffer(all_data->buff, RA);
}
