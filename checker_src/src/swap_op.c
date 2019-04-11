/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 09:38:57 by coremart          #+#    #+#             */
/*   Updated: 2019/04/10 10:32:57 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap_a(t_piles *piles)
{
	int tmp;

	if (!piles->a || piles->a->next == piles->a)
		return ;
	tmp = piles->a->nb;
	piles->a->nb = piles->a->next->nb;
	piles->a->next->nb = tmp;
}

void	swap_b(t_piles *piles)
{
	int tmp;

	if (!piles->b || piles->b->next == piles->b)
		return ;
	tmp = piles->b->nb;
	piles->b->nb = piles->b->next->nb;
	piles->b->next->nb = tmp;
}

void	swap_ab(t_piles *piles)
{
	swap_a(piles);
	swap_b(piles);
}
