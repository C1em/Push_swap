/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 08:25:21 by coremart          #+#    #+#             */
/*   Updated: 2019/04/10 10:04:27 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdlib.h>

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

void	rm_elem(t_pile *elem)
{
	if (elem->next == elem)
	{
		free(elem);
		elem = NULL;
		return ;
	}
	elem = elem->next;
	elem->prev= elem->prev->prev;
	free(elem->prev->next);
	elem->prev->next = elem;
}
