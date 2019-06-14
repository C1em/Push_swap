/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 04:11:12 by coremart          #+#    #+#             */
/*   Updated: 2019/06/15 04:30:02 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static inline int	is_better_in_rev(t_all_data *all_data, t_arr *arr,
										size_t len, int rev)
{
	return (arr->arr[len - 1] + count_rot_to_end_of_pa(arr->arr,
			arr->arr[len - 1], all_data->piles->b, rev)
			- transformed_r_to_rr(arr->arr[0], all_data->buff, 0)
			> arr->size - arr->arr[0]
			+ count_rot_to_end_of_pa(arr->arr, arr->arr[0],
			all_data->piles->b, rev) - transformed_r_to_rr(arr->size
			- arr->arr[len - 1], all_data->buff, 1) + len - 1);
}

static inline int	destof_b_after_rot(t_llist_tmp *b, size_t rot)
{
	while (rot--)
		b = b->next;
	return (b->dest);
}

/*
**	orient in push_a_tab_rot or push_a_tab_reverse_rot according to
**	array elements aiming to the least rotations to push all ements
**	return array's lenghth
*/

int					push_a_tab(t_arr *arr, t_all_data *all_data, int rev)
{
	size_t		len;
	int			tmp_dest;

	len = 0;
	while (arr->arr[len] != -1)
		++len;
	if (!len)
		return (0);
	tmp_dest = destof_b_after_rot(all_data->piles->b, arr->arr[0]);
	if (max_rot_bw_non_pusha(arr->arr) > (size_t)(arr->size >> 1))
		pusha_custom_rot(all_data, arr, rev);
	else if (is_better_in_rev(all_data, arr, len, rev))
		push_a_tab_reverse_rot(len, arr, all_data);
	else
		push_a_tab_rot(len, arr->arr, all_data);
	while (all_data->piles->a->nb != tmp_dest)
		rot_a(all_data, 0);
	return (len);
}
