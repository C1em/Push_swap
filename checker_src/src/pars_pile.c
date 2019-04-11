/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:54:50 by coremart          #+#    #+#             */
/*   Updated: 2019/04/09 08:26:25 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "libft.h"
#include <stdlib.h>

t_pile					*pars_pile(char **arr, int size)
{
	t_pile *pile;

	if (!size)
		return (NULL);
	--size;
	pile = pile_init(ft_atoi(arr[size]));
	while (size--)
		pile = add_elem(pile, ft_atoi(arr[size]));
	return (pile);
}
