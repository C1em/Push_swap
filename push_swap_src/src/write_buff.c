/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:34:25 by coremart          #+#    #+#             */
/*   Updated: 2019/04/12 16:35:00 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "push_swap.h"
#include "libft.h"

#include <stdio.h>

static inline size_t	write_op(char *dest, int op)
{
	int		*op_arr;
	char	*str_op;
	int		i;

	op_arr = (int[11]){RA, RB, PB, PA, RR, SA, SB, SS, RRR, RRA, RRB};
	i = 0;
	str_op = (char[26]){"rarbpbparrsasbssrrrrrarrb"};
	while (op != op_arr[i])
		++i;
	if (i < 8)
	{
		dest[0] = str_op[i << 1];
		dest[1] = str_op[(i << 1) + 1];
		return (2);
	}
	dest[0] = str_op[16 + ((i - 8) << 1) + (i - 8)];
	dest[1] = str_op[17 + ((i - 8) << 1) + (i - 8)];
	dest[2] = str_op[18 + ((i - 8) << 1) + (i - 8)];
	return (3);
}

void					write_buff(t_data_buff *buff)
{
	char	chain[2048];
	size_t	i;
	size_t	j;
	size_t max;

	i = 0;
	j = 0;
	max = (buff->index > 511) ? 512 : buff->index + 1;
	while (i < max)
	{
		j += write_op(&chain[j], buff->buff[i]) + 1;
		chain[j - 1] = '\n';
		++i;
	}
	if (max == 512)
	{
		ft_memmove((void*)buff->buff, (void*)&buff->buff[512], (size_t)512);
		buff->index -= 512;
		if (buff->index < 511)
		{
			write(1, chain, (size_t)j);
			return (write_buff(buff));
		}
	}
	write(1, chain, (size_t)j);
}
