/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_order.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 10:43:10 by coremart          #+#    #+#             */
/*   Updated: 2019/06/08 05:05:02 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <unistd.h>

void	check_if_order(t_piles *piles)
{
	t_pile *end_pile;

	if (piles->b)
		return ((void)write(1, "KO\n", 3));
	if (!piles->a)
		return ((void)write(1, "OK\n", 3));
	end_pile = piles->a->prev;
	while (piles->a != end_pile)
	{
		if (piles->a->nb > piles->a->next->nb)
			return ((void)write(1, "KO\n", 3));
		piles->a = piles->a->next;
	}
	write(1, "OK\n", 3);
}
