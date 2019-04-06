/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 06:06:56 by coremart          #+#    #+#             */
/*   Updated: 2019/04/06 13:08:20 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include "libft.h"

#include <stdio.h>

static inline int	reverse_op(int op)
{
	if (op & RA)
		return (RRA);
	if (op & RRA)
		return (RA);
	if (op & RB)
		return (RRB);
	if (op & RRB)
		return (RB);
}

static inline int	check_special_case(t_data_buff *buff, int op)
{
	size_t i;

	i = buff->index;
	if (op & RRA)
	{
		while (i && (buff->buff[i] & (RB | RRB | SB)))
			--i;
		if (((buff->buff[i] & PB) << 1) & buff->buff[i - 1] & RA)
		{
			buff->buff[i - 1] = SA;
			buff->buff[i] = PB;
			buff->nb_same_rot = 0UL;
			return (1);
		}
		return (0);
	}
	while (i && (buff->buff[i] & (RA | RRA | SA)))
		--i;
	if (((buff->buff[i] & PA) << 3) & buff->buff[i - 1] & RB)
	{
		buff->buff[i - 1] = SB;
		buff->buff[i] = PA;
		buff->nb_same_rot = 0UL;
		return (1);
	}
	return (0);
}

static inline void	reverse_rot(t_data_buff *buff)
{
	printf("WAW\n");

	while ((buff->nb_same_rot)--)
		--buff->index;	//check rr or rrr
	++buff->index;
	buff->buff[buff->index] = reverse_op(buff->rot);
	buff->rot = reverse_op(buff->rot);
	buff->nb_same_rot = 1UL;
}

static inline void	fill_buff_rot(t_data_buff *buff, int op)
{
	if (op & RA)
	{
		if (buff->buff[buff->index] & RRA)
		{
			--buff->index;
			--buff->nb_same_rot;
		}
		else if (buff->buff[buff->index] & RB)
		{
			buff->buff[buff->index] = RR;
			if (buff->rot & (RA | RB | RR))
				++buff->nb_same_rot;
			else
			{
				buff->rot = RR;
				buff->nb_same_rot = 1UL;
			}
		}
		else
		{
			++buff->index;
			buff->buff[buff->index] = RA;
			if (buff->rot & RA)
				++buff->nb_same_rot;
			else
			{
				buff->nb_same_rot = 1UL;
				buff->rot = RA;
			}
		}
	}
	else if (op & RB)
	{
		if (buff->buff[buff->index] & RRB)
		{
			--buff->index;
			--buff->nb_same_rot;
		}
		else if (buff->buff[buff->index] & RA)
		{
			buff->buff[buff->index] = RR;
			if (buff->rot & (RA | RB | RR))
				++buff->nb_same_rot;
			else
			{
				buff->rot = RR;
				buff->nb_same_rot = 1UL;
			}
		}
		else
		{
			++buff->index;
			buff->buff[buff->index] = RB;
			if (buff->rot & RB)
				++buff->nb_same_rot;
			else
			{
				buff->nb_same_rot = 1UL;
				buff->rot = RB;
			}
		}
	}
	else if (op & RRA)
	{
		if (check_special_case(buff, RRA))
			return ;
		if (buff->buff[buff->index] & RA)
		{
			--buff->index;
			--buff->nb_same_rot;
		}
		else if (buff->buff[buff->index] & RRB)
		{
			buff->buff[buff->index] = RRR;
			if (buff->rot & (RRA | RRB | RRR))
				++buff->nb_same_rot;
			else
			{
				buff->rot = RRR;
				buff->nb_same_rot = 1UL;
			}
		}
		else
		{
			++buff->index;
			buff->buff[buff->index] = RRA;
			if (buff->rot & RRA)
				++buff->nb_same_rot;
			else
			{
				buff->nb_same_rot = 1UL;
				buff->rot = RRA;
			}
		}
	}
	else if (op & RRB)
	{
		if (check_special_case(buff, RRB))
			return ;
		if (buff->buff[buff->index] & RB)
		{
			--buff->index;
			--buff->nb_same_rot;
		}
		else if (buff->buff[buff->index] & RRA)
		{
			buff->buff[buff->index] = RRR;
			if (buff->rot & (RRA | RRB | RRR))
				++buff->nb_same_rot;
			else
			{
				buff->rot = RRR;
				buff->nb_same_rot = 1UL;
			}
		}
		else
		{
			++buff->index;
			buff->buff[buff->index] = RRB;
			if (buff->rot & RRB)
				++buff->nb_same_rot;
			else
			{
				buff->nb_same_rot = 1UL;
				buff->rot = RRB;
			}
		}
	}
}

static inline void	fill_buff_push(t_data_buff *buff, int op)
{
	if (op & PA)
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
				buff->nb_same_rot = 1UL;
			}
			else if (buff->buff[buff->index] & RRA)
			{
				buff->buff[buff->index - 1] = RRA;
				buff->buff[buff->index] = SA;
				buff->nb_same_rot = 0UL;
			}
		}
		else
		{
			if (buff->index == 1023UL)
				return (write_buff());
			++buff->index;
			buff->buff[buff->index] = PA;
		}
	}
	else if (op & PB)
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
				buff->nb_same_rot = 1UL;
			}
			else if (buff->buff[buff->index] & RRB)
			{
				buff->buff[buff->index - 1] = RRB;
				buff->buff[buff->index] = SB;
				buff->nb_same_rot = 0UL;
			}
		}
		else
		{
			if (buff->index == 1023UL)
				return (write_buff());
			++buff->index;
			buff->buff[buff->index] = PB;
		}
	}
}

void				fill_buffer(t_data_buff *buff, int op)
{
	if (buff->index == -1UL)
	{
		buff->index = 0UL;
		buff->buff[0] = op;
		if (op = buff->rot)
			++buff->rot;
		else if (op & ( RA | RB | RRA | RRB))
		{
			buff->rot = op;
			buff->nb_same_rot = 1UL;
		}
		return ;
	}
	if (buff->nb_same_rot + 1 > (buff->tot_size >> 1) && op == buff->rot)
		return (reverse_rot(buff));
	if (op & ( RA | RB | RRA | RRB))
		return (fill_buff_rot(buff, op));
	if (op & (PA |PB))
		return (fill_buff_push(buff, op));
}
