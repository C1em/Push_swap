/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_fill_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:22:17 by coremart          #+#    #+#             */
/*   Updated: 2019/06/15 04:44:19 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void inline	put_in_buff(t_data_buff *buff, int op)
{
	if (buff->index == 1023)
		write_buff(buff);
	++buff->index;
	buff->buff[buff->index] = op;
}

void				fill_push_a(t_data_buff *buff)
{
	if (buff->buff[buff->index] & PB)
		--buff->index;
	else if (buff->index && buff->buff[buff->index - 1] & PB)
	{
		if (buff->buff[buff->index] & RA)
		{
			if (buff->index > 1 && buff->buff[buff->index - 2] & SB)
			{
				--buff->index;
				buff->buff[buff->index - 1] = SS;
				buff->buff[buff->index] = RA;
			}
			else
				buff->buff[buff->index - 1] = SA;
		}
		else if (buff->buff[buff->index] & RRA)
		{
			buff->buff[buff->index - 1] = RRA;
			buff->buff[buff->index] = SA;
		}
		else
			put_in_buff(buff, PA);
	}
	else
		put_in_buff(buff, PA);
}

void				fill_push_b(t_data_buff *buff)
{
	if (buff->buff[buff->index] & PA)
		--buff->index;
	else if (buff->index && buff->buff[buff->index - 1] & PA)
	{
		if (buff->buff[buff->index] & RB)
		{
			if (buff->index > 1 && buff->buff[buff->index - 2] & SA)
			{
				buff->buff[buff->index - 2] = SS;
				buff->buff[buff->index - 1] = RB;
				--buff->index;
			}
			else
				buff->buff[buff->index - 1] = SB;
		}
		else if (buff->buff[buff->index] & RRB)
		{
			buff->buff[buff->index - 1] = RRB;
			buff->buff[buff->index] = SB;
		}
		else
			put_in_buff(buff, PB);
	}
	else
		put_in_buff(buff, PB);
}
