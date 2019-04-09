/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:47:33 by coremart          #+#    #+#             */
/*   Updated: 2019/04/08 13:25:37 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		main(int ac, char **av)
{
	t_pile	*pile;
	int	*op_arr;

	pile = pars_pile(&av[1], ac - 1);
	op_arr = get_op();
	apply_op_to_pile();
	check_if_order();
}
