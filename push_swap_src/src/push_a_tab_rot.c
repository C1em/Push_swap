/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a_tab_rot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 03:09:40 by coremart          #+#    #+#             */
/*   Updated: 2019/06/15 04:29:41 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	rotate to get the good number a the top of a before the push a
**	especially when we have already pushed on a at this position,
**	we need to rotate in consequence
*/

static void	rot_a_to_match_the_push(t_all_data *all_data)
{
	while (all_data->piles->a->nb != all_data->piles->b->dest)
		rot_a(all_data, 0);
	while (all_data->piles->b->nb < all_data->piles->a->prev->nb
			|| all_data->piles->b->nb > all_data->piles->a->nb)
	{
		if (all_data->piles->a->prev->nb > all_data->piles->a->nb
				&& (all_data->piles->b->nb > all_data->piles->a->prev->nb
				|| all_data->piles->b->nb < all_data->piles->a->nb))
			break ;
		rot_a(all_data, 1);
	}
}

/*
**	collect all elems that have to be push on a int the "reverse" order
**				and call rot_a_to_match_the_push then call push_a and add_to_lis
*/

void		push_a_tab_reverse_rot(size_t len_arr, t_arr *arr,
									t_all_data *all_data)
{
	size_t rot_count;

	while (len_arr--)
	{
		rot_count = arr->size - arr->arr[len_arr];
		while (rot_count--)
			rot_b(all_data, 1);
		rot_a_to_match_the_push(all_data);
		push_a(all_data->piles, all_data->buff);
		add_to_lis(all_data->lis, all_data->piles->a->nb);
		arr->size = arr->arr[len_arr];
	}
}

/*
**	collect all elems that have to be push on a int the "normal" order
**				and call rot_a_to_match_the_push then call push_a and add_to_lis
*/

void		push_a_tab_rot(size_t len_arr, int *arr, t_all_data *all_data)
{
	int		rot_count;
	int		next;
	size_t	i;

	i = 0;
	next = 0;
	while (i < len_arr)
	{
		rot_count = arr[i] - next;
		while (rot_count--)
			rot_a(all_data, 0);
		rot_a_to_match_the_push(all_data);
		push_a(all_data->piles, all_data->buff);
		add_to_lis(all_data->lis, all_data->piles->a->nb);
		next = arr[i] + 1;
		++i;
	}
}
