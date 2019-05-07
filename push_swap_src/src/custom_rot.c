/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 23:57:49 by coremart          #+#    #+#             */
/*   Updated: 2019/05/07 02:08:43 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t		max_rot_bw_non_lis(t_llist *a, t_llist *lis)
{
	t_llist	*end_a;
	size_t	max_rot_count;
	size_t	rot_count;

	end_a = NULL;
	rot_count = 0;
	max_rot_count = 0;
	while (a != end_a)
	{
		if (lis->nb == a->nb)
		{
			++rot_count;
			lis = lis->next;
		}
		else
		{
			if (!end_a)
				end_a = a;
			if (rot_count > max_rot_count)
				max_rot_count = rot_count;
			rot_count = 0;
		}
		a = a->next;
	}
	if (rot_count > max_rot_count)
		return (rot_count + 1);
	return (max_rot_count + 1);
}

size_t		rot_til_inverse_rot(t_llist *a, t_llist *lis, size_t size, int rev)
{
	size_t	offset;
	size_t	rev_offset;
	size_t	rot_count;
	size_t	res;

	offset = (rev) ? sizeof(t_llist*) : 0;
	rev_offset = (rev) ? 0 :sizeof(t_llist*);
	rot_count = 1;
	res = 0;
	while ((rot_count << 1) < size)
	{
		if (lis->nb == a->nb)
		{
			++rot_count;
			lis = *(t_llist**)((char*)lis + offset);
		}
		else
			rot_count = 1;
		a = *(t_llist**)((char*)a + offset);
		++res;
	}
	return (res - rot_count);
}

void		ssp_custom_rot(t_all_data *data)
{
	if (rot_to_last > rev_rot_to_last)
	{
		rev_rot;
		rot;
	}
	else
	{
		rot;
		rev_rot;
	}
}
