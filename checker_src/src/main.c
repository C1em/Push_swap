/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:47:33 by coremart          #+#    #+#             */
/*   Updated: 2019/06/08 05:05:43 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

static int	get_option(char ***av, int *size)
{
	if ((*av)[*size - 1][0] == '-' && (*av)[*size - 1][1] == 'v'
		&& !(*av)[*size - 1][2])
	{
		--*size;
		return (1);
	}
	if ((*av)[1][0] == '-' && (*av)[1][1] == 'v' && !(*av)[1][2])
	{
		++*av;
		return (1);
	}
	return (0);
}

void		free_pile(t_pile *pile)
{
	if (!pile)
		return ;
	pile->prev->next = NULL;
	while (pile->next)
	{
		pile = pile->next;
		free(pile->prev);
	}
	free(pile);
}

int			main(int ac, char **av)
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
	print_op = get_option(&av, &ac);
	pile = pars_pile(&av[1], ac - 1);
	op_pile = get_op();
	piles = apply_op_to_pile(pile, op_pile, print_op);
	check_if_order(piles);
	free_pile(piles->a);
	free_pile(piles->b);
	free_pile(op_pile);
	free(piles);
	return (0);
}
