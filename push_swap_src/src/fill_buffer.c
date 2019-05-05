/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:37:57 by coremart          #+#    #+#             */
/*   Updated: 2019/05/05 00:58:22 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include "libft.h"
#include <stdio.h>

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
	if (buff->index == (ssize_t)-1)
	{
		buff->index = (ssize_t)0;
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
