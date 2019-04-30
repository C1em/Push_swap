/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 09:38:43 by coremart          #+#    #+#             */
/*   Updated: 2019/04/29 19:50:20 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdlib.h>

/*
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
*/
void	push_a(t_piles *piles)
{
	if (!piles->b)
		return ;
	if (!piles->a)
		piles->a = pile_init(piles->b->nb);
	else
		piles->a = add_elem(piles->a, piles->b->nb);
	piles->b = rm_elem(piles->b);
}

void	push_b(t_piles *piles)
{
	if (!piles->a)
		return ;
	if (!piles->b)
		piles->b = pile_init(piles->a->nb);
	else
		piles->b = add_elem(piles->b, piles->a->nb);
	piles->a = rm_elem(piles->a);
}
