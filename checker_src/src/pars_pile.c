/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:54:50 by coremart          #+#    #+#             */
/*   Updated: 2019/04/12 11:13:31 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

int						ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == 'f'
																|| c == ' ')
		return (1);
	return (0);
}

t_pile					*pars_pile(char **arr, int size)
{
	t_pile *pile;
	ssize_t i;
	ssize_t tmp_i;

	pile = NULL;
	while (size--)
	{
		i = ft_strlen(arr[size]) - 1;
		while ((tmp_i = i) != -1)
		{
			while (i + 1 && ft_isspace(arr[size][i]))
				--i;
			if (i == (ssize_t)-1)
				break ;
			while (i + 1 && ft_isdigit(arr[size][i]))
				--i;
			if (tmp_i == i)
			{
				write(1, "Error\n", 6);
				exit(1);
			}
			pile = (pile) ? add_elem(pile, ft_atoi(&arr[size][i + 1]))
										: pile_init(ft_atoi(&arr[size][i + 1]));
		}
	}
	return (pile);
}
