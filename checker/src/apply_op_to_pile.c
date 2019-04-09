/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op_to_pile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 08:49:48 by coremart          #+#    #+#             */
/*   Updated: 2019/04/09 09:35:42 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

#include "string.h"

static inline	do_pile_op(t_pile *pile, int op)
{
	int		*op_arr;
	size_t	i;

	op_arr = (int[11]){SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR};
	i = (op >= RA) ? 5 : 0;
	while (~op_arr[i] & op)
		++i;
	// chose fun
}

void			apply_to_pile(t_pile *pile, t_pile *op_list)
{
	t_pile *end_op;

	if (!pile || !op_list)
		return ;
	end_op = op_list->next;
	while (op_list != end_op)
	{
		do_pile_op(pile, op_list->nb);
		op_list = op_list->prev;
	}
}
