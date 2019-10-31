/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pusha_custom_rot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:33:13 by coremart          #+#    #+#             */
/*   Updated: 2019/10/31 23:54:15 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static ssize_t		rot_til_inverse_rot(t_arr *arr, int rev)
{
	size_t	i;

	i = 0;
	while (arr->arr[i + 1] - arr->arr[i] <= (arr->size >> 1))
		++i;
	if (rev)
		return ((ssize_t)(arr->size - arr->arr[i + 1]));
	return ((ssize_t)arr->arr[i]);
}

static void			custom_pusha(t_all_data *data, t_arr *arr,
							ssize_t rot_count_to_end, int rev)
{
	size_t	len;
	size_t	i;
	t_arr	tmp_arr;

	i = 0;
	len = 0;
	if (rev)
		while (arr->arr[i] != arr->size - rot_count_to_end)
			++i;
	tmp_arr.arr = &arr->arr[i];
	tmp_arr.size = arr->size;
	if (rev)
		while (tmp_arr.arr[len] != -1)
			++len;
	else
		while (tmp_arr.arr[len++] != rot_count_to_end)
			;
	if (rev)
		push_a_tab_reverse_rot(len, &tmp_arr, data);
	else
		push_a_tab_rot(len, tmp_arr.arr, data);
}

static void			rot_to_the_start(t_all_data *data, t_llist_tmp *top_b,
										int rev)
{
	size_t	offset;
	int		op;

	offset = (rev) ? sizeof(t_llist_tmp*) : 0;
	op = (rev) ? RRB : RB;
	while (data->piles->b != top_b)
		rot_b(data, rev);
}

static t_llist_tmp	*get_next_non_pusha(t_llist_tmp *b, t_arr *arr)
{
	int i;

	i = 0;
	while (arr->arr[i] == i)
	{
		b = b->next;
		++i;
	}
	return (b);
}

void				pusha_custom_rot(t_all_data *data, t_arr *arr,
										int rev)
{
	ssize_t		rot_to_last;
	ssize_t		rev_rot_to_last;
	t_llist_tmp	*top_b;

	rot_to_last = rot_til_inverse_rot(arr, 0);
	rev_rot_to_last = rot_til_inverse_rot(arr, 1);
	if (rev_rot_to_last + count_rot_to_end_of_pa(arr->arr, rot_to_last,
		data->piles->b, rev) < rot_to_last
		+ count_rot_to_end_of_pa(arr->arr,
		rev_rot_to_last, data->piles->b, rev))
	{
		top_b = data->piles->b;
		if (rev_rot_to_last != (ssize_t)-1)
			custom_pusha(data, arr, rev_rot_to_last, 1);
		rot_to_the_start(data, top_b, 0);
		if (rot_to_last != (ssize_t)-1)
			custom_pusha(data, arr, rot_to_last, 0);
		return ;
	}
	top_b = get_next_non_pusha(data->piles->b, arr);
	if (rot_to_last != (ssize_t)-1)
		custom_pusha(data, arr, rot_to_last, 0);
	rot_to_the_start(data, top_b, 1);
	if (rev_rot_to_last != (ssize_t)-1)
		custom_pusha(data, arr, rev_rot_to_last, 1);
}
