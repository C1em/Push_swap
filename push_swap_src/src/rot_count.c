/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 00:40:09 by coremart          #+#    #+#             */
/*   Updated: 2019/05/01 01:25:59 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t		lst_len(t_llist *lst)
{
	t_llist	*end_lst;
	size_t	i;

	if (!lst)
		return (0);
	end_lst = lst;
	lst = lst->next;
	i = 1;
	while (lst != end_lst)
	{
		++i;
		lst = lst->next;
	}
	return (i);
}

size_t		rot_count_til_push(t_all_data *data, size_t size, int rev)
{
	size_t	rot_count;
	int		offset;
	t_llist	*tmp_a;
	t_llist	*tmp_lis;

	tmp_a = data->piles->a;
	tmp_lis = data->lis;
	rot_count = 0;
	offset = (rev) ? sizeof(t_llist*) : 0;
	while (tmp_a->nb == tmp_lis->nb)
	{
		tmp_lis = *(t_llist**)((char*)tmp_lis + offset);
		tmp_a = *(t_llist**)((char*)tmp_a + offset);
		if (++rot_count == size)
			break ;
	}
	return (rot_count);
}
