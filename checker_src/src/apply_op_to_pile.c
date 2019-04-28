/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op_to_pile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 08:49:48 by coremart          #+#    #+#             */
/*   Updated: 2019/04/28 18:39:04 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdlib.h>

#include <stdio.h>

static void				print_list(t_pile *pile)
{
	t_pile *end_pile;

	if (!pile)
		return ;
	end_pile = pile->prev;
	while (pile != end_pile)
	{
		printf("%d\n", pile->nb);
		pile = pile->next;
	}
	printf("%d\n", pile->nb);
}

static void inline	do_pile_op(t_piles *piles, int op)
{
	int			*op_arr;
	t_fun_op	*fun_op;
	size_t		i;

	op_arr = (int[11]){SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR};
	i = (op >= RA) ? 5 : 0;
	while (~op_arr[i] & op)
		++i;
	fun_op = (t_fun_op[11]){swap_a, swap_b, swap_ab, push_a, push_b, rot_a,
							rot_b, rot_ab, rev_rot_a, rev_rot_b, rev_rot_ab};
	printf("op : %d\n", op_arr[i]);
	return(fun_op[i](piles));
}

t_piles			*apply_op_to_pile(t_pile *a, t_pile *op_list)
{
	t_pile	*end_op;
	t_piles	*piles;

	if (!(piles = (t_piles*)malloc(sizeof(t_piles))))
		exit(1);
	piles->a = a;
	piles->b = NULL;
	if (!a || !op_list)
		return (piles);
	end_op = op_list->next;
	while (op_list != end_op)
	{
		print_list(piles->a);
		printf("_______________________________\n");
		do_pile_op(piles, op_list->nb);
		op_list = op_list->prev;
	}
	do_pile_op(piles, op_list->nb);
	return (piles);
}
