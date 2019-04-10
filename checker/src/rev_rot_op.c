/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rot_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 09:38:54 by coremart          #+#    #+#             */
/*   Updated: 2019/04/10 10:12:04 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	rev_rot_a(t_piles *piles)
{
	if (piles->a)
		piles->a = piles->a->prev;
}

void	rev_rot_b(t_piles *piles)
{
	if (piles->b)
		piles->b = piles->b->prev;
}

void	rev_rot_ab(t_piles *piles)
{
	if (piles->a)
		piles->a = piles->a->prev;
	if (piles->b)
		piles->b = piles->b->prev;
}
