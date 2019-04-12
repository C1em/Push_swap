/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_fill_rot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:22:20 by coremart          #+#    #+#             */
/*   Updated: 2019/04/12 14:39:36 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void inline	put_in_buff(t_data_buff *buff, int op)
{
	if (buff->index == 1023)
		return (write_buff(buff));
	++buff->index;
	buff->buff[buff->index] = op;
}

void				fill_rot_a(t_data_buff *buff)
{
	if (buff->buff[buff->index] & RRA)
		--buff->index;
	else if (buff->buff[buff->index] & RB)
		buff->buff[buff->index] = RR;
	else
		put_in_buff(buff, RA);
}

void				fill_rot_b(t_data_buff *buff)
{
	if (buff->buff[buff->index] & RRB)
		--buff->index;
	else if (buff->buff[buff->index] & RA)
		buff->buff[buff->index] = RR;
	else
		put_in_buff(buff, RB);
}

void				fill_rev_rot_a(t_data_buff *buff)
{
	size_t i;

	i = buff->index;
	while (i && (buff->buff[i] & (RB | RRB | SB)))
		--i;
	if (((buff->buff[i] & PB) << 1) & buff->buff[i - 1] & RA)
	{
		buff->buff[i - 1] = SA;
		return ;
	}
	if (buff->buff[buff->index] & RA)
		--buff->index;
	else if (buff->buff[buff->index] & RRB)
		buff->buff[buff->index] = RRR;
	else
		put_in_buff(buff, RRA);
}

void				fill_rev_rot_b(t_data_buff *buff)
{
	size_t i;

	i = buff->index;
	while (i && (buff->buff[i] & (RA | RRA | SA)))
		--i;
	if (((buff->buff[i] & PA) << 3) & buff->buff[i - 1] & RB)
	{
		buff->buff[i - 1] = SB;
		return ;
	}
	if (buff->buff[buff->index] & RB)
		--buff->index;
	else if (buff->buff[buff->index] & RRA)
		buff->buff[buff->index] = RRR;
	else
		put_in_buff(buff, RRB);
}
