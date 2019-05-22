/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 00:40:09 by coremart          #+#    #+#             */
/*   Updated: 2019/05/22 15:19:22 by coremart         ###   ########.fr       */
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

size_t		rot_count_til_push(t_llist *a, t_llist *lis, size_t size, int rev)
{
	size_t	rot_count;
	int		offset;

	rot_count = 0;
	offset = (rev) ? sizeof(t_llist*) : 0;
	while (a->nb == lis->nb)
	{
		lis = *(t_llist**)((char*)lis + offset);
		a = *(t_llist**)((char*)a + offset);
		if (++rot_count == size)
			break ;
	}
	return (rot_count);
}

size_t		count_rot_to_next_pa(t_all_data *all_data, size_t rot_count,
											t_llist *end_a, int rev_ab)
{
	t_llist		*tmp_a;
	t_llist_tmp	*tmp_b;
	size_t		offset_a;
	size_t		offset_b;

	tmp_a = all_data->piles->a;
	tmp_b = all_data->piles->b;
	offset_a = (rev_ab & 2) ? sizeof(t_llist*) : 0;
	offset_b = (rev_ab & 1) ? sizeof(t_llist_tmp*) : 0;
	while (rot_count--)
		tmp_b = *(t_llist_tmp**)((char*)tmp_b + offset_b);
	while (!is_destof(tmp_b, tmp_a->nb))
		if ((tmp_a = *(t_llist**)((char*)tmp_a + offset_a)) == end_a)
			return (0);
	return (count_rot_to_the_nearest_pa(tmp_b, tmp_a->nb));
}
