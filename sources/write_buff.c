/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:34:25 by coremart          #+#    #+#             */
/*   Updated: 2019/04/07 14:53:07 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_push_swap.h"
#include "libft.h"

static inline size_t	write_op(char *dest, int op)
{
	int		*op_arr;
	char	**str_op;
	int		i;

	op_arr = (int[11]){RA, RB, PB, PA, RR, SA, SB, SS, RRR, RRA, RRB};
	i = 0;
	str_op = (char[11][4]){"RA", "RB", "PB", "PA", "RR", "SA", "SB", "SS",
														"RRR", "RRA", "RRB"};
	while (op != op_arr[i])
		++i;
	while (*str_op)
	{
		*dest = *(str_op[i]);
		++str_op[i];
		++dest;
	}
	return ((i < 8) ? 2 : 3);
}

void					write_buff(t_data_buff *buff)
{
	char	chain[1536];
	size_t	i;
	size_t	j;
	size_t max;

	i = 0;
	j = 0;
	max = (buff->index > 512) ? 512 : buff->index;
	while (i < max)
	{
		j += write_op(&chain[j], buff->buff[i]);
		++i;
	}
	if (max == 512)
	{
		ft_memmove((void*)buff->buff, (void*)&buff->buff[512], (size_t)512);
		buff->index = 511;
	}
	write(1, chain, (size_t)j);
}
