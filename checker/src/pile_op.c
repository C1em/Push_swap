/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 08:25:21 by coremart          #+#    #+#             */
/*   Updated: 2019/04/09 08:29:11 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_pile	*pile_init(int nb)
{
	t_pile *elem;

	if (!(elem = (t_pile*)malloc(sizeof(t_pile))))
		exit(1);
	elem->nb = nb;
	elem->next = elem;
	elem->prev = elem;
	return (elem);
}

t_pile	*add_elem(t_pile *pile, int nb)
{
	t_pile *elem;

	if (!(elem = (t_pile*)malloc(sizeof(t_pile))))
		exit(1);
	elem->nb = nb;
	elem->next = pile;
	elem->prev = pile->prev;
	pile->prev = elem;
	return (elem);
}
