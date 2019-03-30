/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_pile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 20:56:44 by coremart          #+#    #+#             */
/*   Updated: 2019/03/30 23:41:52 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <string.h>

static int		puashb_if_destof(t_piles *piles, t_llist *lis, int max_elem)
{
	t_llist		*end_b;
	t_llist_tmp	*tmp_b;
	int			r_count;
	int			*tmp_tab;
	int			i;


	if (!(tmp_b = piles->b))
		return (0);
	if (!(tmp_tab = (int*)malloc(sizeof(int) * max_elem)))
		return (0);
	end_b = tmp_b->prev;
	r_count = 0;
	i = 0;
	while (tmp_b != end_b)// change to take account of the last elem
	{
		if (tmp_b->dest == piles->a->nb)
		{
			tmp_tab[i] = r_count;
			++i;
			tmp_tab[i] = -1;
		}
		tmp_b = tmp_b->next;
		++r_count;
	}
	//put all elem of tmp tab on a starting at the nearest
}

static void		go_through_pile(t_piles *piles, t_llist *lis, t_data_buff *buff)
{
	t_llist		*end_a;
	int			max_elem;

	end_a = piles->a->prev;
	max_elem = 0;
	while (piles->a != end_a) // change to take account of the last elem
	{
		max_elem = pushb_if_destof(piles, lis, max_elem); /* caution if is the dest of*/
		if (piles->a->nb == lis->nb)
			lis = lis->next;
		else
		{
			push_b(piles);
			++max_elem;
		}
		piles->a = piles->a->next;
		buff->buff[buff->index] = RA;
	}
}

static void		empty_b(t_piles *piles, t_llist *lis, t_data_buff *buff)
{
	int dest;

	while (piles->b)
	{
		dest = get_the_nearest_dest(piles->b, lis);
		put_to_dest(piles, dest);
	}
}

void			order_pile(t_piles *piles, t_llist *ll_lis)
{
	t_data_buff data_buff;

	data_buff.index = 0;
	go_through_pile(piles, ll_lis, &data_buff);
	empty_b(piles, ll_lis, &data_buff);
}
