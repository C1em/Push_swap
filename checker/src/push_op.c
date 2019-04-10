/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 09:38:43 by coremart          #+#    #+#             */
/*   Updated: 2019/04/10 10:05:20 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdlib.h>

void	push_a(t_piles *piles)
{
	if (!piles->b)
		return ;
	if (!piles->a)
		piles->a = pile_init(piles->b->nb);
	else
		piles->a = add_elem(piles->a, piles->b->nb);
	rm_elem(piles->b);
}

void	push_b(t_piles *piles)
{
	if (!piles->a)
		return ;
	if (!piles->b)
		piles->b = pile_init(piles->a->nb);
	else
		piles->b = add_elem(piles->b, piles->a->nb);
	rm_elem(piles->a);
}
