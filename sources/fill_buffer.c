/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:37:57 by coremart          #+#    #+#             */
/*   Updated: 2019/04/08 09:05:43 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static inline void		dispatch_rot(t_data_buff *buff, int op)
{
	t_fun_match_op	*fun_match_op;
	size_t			i;

	fun_match_op = (t_fun_match_op[4]){{.p = fill_rot_a, .op = RA},
										{.p = fill_rot_b, .op = RB},
										{.p = fill_rev_rot_a, .op = RRA},
										{.p = fill_rev_rot_b, .op = RRB}};
	i = 0;
	while (~op & fun_match_op[i].op)
		++i;
	return (fun_match_op[i].p(buff));
}

void				fill_buffer(t_data_buff *buff, int op)
{
	if (buff->index & (0x1 << 31))
	{
		buff->index = 0UL;
		buff->buff[0] = op;
		return ;
	}
	if (op & ROT)
		return (dispatch_rot(buff, op));
	if (op & PA)
		return (fill_push_a(buff));
	if (op & PB)
		return (fill_push_b(buff));
}
