/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:47:33 by coremart          #+#    #+#             */
/*   Updated: 2019/04/28 17:15:14 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <unistd.h>

int		main(int ac, char **av)
{
	t_pile	*pile;
	t_pile	*op_pile;
	t_piles *piles;

	if (ac < 2)
	{
		write(1, "OK\n", 3);
		return (0);
	}
	pile = pars_pile(&av[1], ac - 1);
	op_pile = get_op();
	piles = apply_op_to_pile(pile, op_pile);
	check_if_order(piles);
	return (0);
}
