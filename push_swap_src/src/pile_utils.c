/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 04:12:56 by coremart          #+#    #+#             */
/*   Updated: 2019/06/09 04:19:09 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_llist	*rot_pile(size_t rot_count, t_llist *pile, int rev)
{
	size_t	offset;

	offset = (rev) ? sizeof(t_llist*) : 0;
	while (rot_count--)
		pile = *(t_llist**)((char*)pile + offset);
	return (pile);
}

int		len_b(t_llist_tmp *b)
{
	t_llist_tmp	*end_b;
	int			i;

	if (!b)
		return (0);
	end_b = b->prev;
	i = 0;
	while (end_b != b)
	{
		++i;
		b = b->next;
	}
	return (i + 1);
}

int		is_destof(t_llist_tmp *b, int dest)
{
	t_llist_tmp *end_b;

	end_b = b;
	if (b->dest == dest)
		return (1);
	b = b->next;
	while (b != end_b)
	{
		if (b->dest == dest)
			return (1);
		b = b->next;
	}
	return (0);
}
