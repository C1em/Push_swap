/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 09:38:51 by coremart          #+#    #+#             */
/*   Updated: 2019/04/10 10:10:38 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	rot_a(t_piles *piles)
{
	if (piles->a)
		piles->a = piles->a->next;
}

void	rot_b(t_piles *piles)
{
	if (piles->b)
		piles->b = piles->b->next;
}

void	rot_ab(t_piles *piles)
{
	if (piles->a)
		piles->a = piles->a->next;
	if (piles->b)
		piles->b = piles->b->next;
}
