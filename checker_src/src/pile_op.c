/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 08:25:21 by coremart          #+#    #+#             */
/*   Updated: 2019/04/11 12:56:01 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdlib.h>

#include <stdio.h>

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
	pile->prev->next = elem;
	pile->prev = elem;
	return (elem);
}

t_pile	*rm_elem(t_pile *elem)
{
	if (elem->next == elem)
	{
		free(elem);
		return (NULL);
	}
	elem = elem->next;
	elem->prev= elem->prev->prev;
	free(elem->prev->next);
	elem->prev->next = elem;
	return (elem);
}
