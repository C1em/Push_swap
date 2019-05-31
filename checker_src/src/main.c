/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:47:33 by coremart          #+#    #+#             */
/*   Updated: 2019/05/31 16:22:37 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <unistd.h>

static int	get_option(char **av, int size)
{
	while (size--)
	{
		if (av[size][0] == '-' && av[size][1] == 'v' && !av[size][2])
			return (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_pile	*pile;
	t_pile	*op_pile;
	t_piles *piles;
	int		print_op;

	if (ac < 2)
	{
		write(1, "OK\n", 3);
		return (0);
	}
	if ((print_op = get_option(&av[1], ac - 1)))
		av = av + 1;
	pile = pars_pile(&av[1], ac - 1);
	op_pile = get_op();
	piles = apply_op_to_pile(pile, op_pile, print_op);
	check_if_order(piles);
	return (0);
}
