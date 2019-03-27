/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:37:54 by coremart          #+#    #+#             */
/*   Updated: 2019/03/26 21:49:13 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>

t_list_head		*transform_to_llist(t_arr *arr, int *lis)
{
	int			i;
	t_llist*	head;

	i = lis[-1] - 1;
	if (!(head = (t_llist*)malloc(sizeof(t_llist) * ((arr->size + 1) >> 1))))
		return (NULL);
	head[i].head.next = &head->head;
	head->head.prev = &head[i].head;
	head[i].nb = arr->arr[lis[i]];
	while (i--)
	{
		head[i].nb = arr->arr[lis[i]];
		head[i].head.next = &head[i + 1].head;
		head[i + 1].head.prev = &head[i].head;
	}
	return (&head->head);
}
