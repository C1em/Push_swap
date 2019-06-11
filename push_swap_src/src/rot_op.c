/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 03:49:55 by coremart          #+#    #+#             */
/*   Updated: 2019/06/11 03:51:00 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		rot_a(t_all_data *data, int rev)
{
	data->piles->a = *(t_llist**)((char*)data->piles->a
					+ (rev) ? sizeof(t_llist*) : 0);
	fill_buffer(data->buff, (rev) ? RRA : RA);
}

void		rot_b(t_all_data *data, int rev)
{
	data->piles->b = *(t_llist_tmp**)((char*)data->piles->b
					+ (rev) ? sizeof(t_llist_tmp*) : 0);
	fill_buffer(data->buff, (rev) ? RRB : RB);
}
