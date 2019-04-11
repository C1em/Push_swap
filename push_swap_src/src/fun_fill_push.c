/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_fill_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:22:17 by coremart          #+#    #+#             */
/*   Updated: 2019/04/11 14:34:09 by coremart         ###   ########.fr       */
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

void	fill_push_a(t_data_buff *buff)
{
	if (buff->buff[buff->index] & PB)
		--buff->index;
	else if (buff->index && buff->buff[buff->index - 1] & PB)
	{
		if (buff->buff[buff->index] & RA)
		{
			buff->buff[buff->index - 1] = (buff->index > 1UL
						&& buff->buff[buff->index - 2UL] & SB) ? SS : SA;
			buff->buff[buff->index] = RA;
		}
		else if (buff->buff[buff->index] & RRA)
		{
			buff->buff[buff->index - 1] = RRA;
			buff->buff[buff->index] = SA;
		}
	}
	else
		put_in_buff(buff, PA);
}

void	fill_push_b(t_data_buff *buff)
{
	if (buff->buff[buff->index] & PA)
		--buff->index;
	else if (buff->index && buff->buff[buff->index - 1UL] & PA)
	{
		if (buff->buff[buff->index] & RB)
		{
			buff->buff[buff->index - 1] = (buff->index > 1UL
						&& buff->buff[buff->index - 2UL] & SA) ? SS : SB;
			buff->buff[buff->index] = RB;
		}
		else if (buff->buff[buff->index] & RRB)
		{
			buff->buff[buff->index - 1] = RRB;
			buff->buff[buff->index] = SB;
		}
	}
	else
		put_in_buff(buff, PB);
}
