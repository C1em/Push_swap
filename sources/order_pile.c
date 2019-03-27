/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_pile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 20:56:44 by coremart          #+#    #+#             */
/*   Updated: 2019/03/26 23:01:05 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	search_first_mv(t_lis_nb *arr, int size)
{
	int i;
	int j;

	i = 0;
	j = size - 1;
	while (i < j)
	{
		if (!arr[i].lis)
			return (i);
		if (!arr[j].lis)
			return (j);
		--j;
		++i;
	}
}

static int	search_dest(t_list_head *head, int nb)
{
	if (nb < ((t_llist*)head)->nb)
		while (nb < ((t_llist*)head)->nb)
			head = head->next;
	else
	{
		while (nb > ((t_llist*)head)->nb)
			head = head->prev;
		head = head->next;
	}
	return (((t_llist*)head)->nb);
}

void		order_pile(t_lis_nb *arr, int size,  t_list_head *head)
{
	int		index_mv;
	int		dest;


	index_mv = search_first_mv(arr, size);
	dest = search_dest(head, arr[index_mv].nb);

}
