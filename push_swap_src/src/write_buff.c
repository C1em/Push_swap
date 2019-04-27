/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:34:25 by coremart          #+#    #+#             */
/*   Updated: 2019/04/27 23:51:03 by coremart         ###   ########.fr       */
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
	if (i & 0x18)
	{
		dest[0] = str_op[(i << 1) + i - 8];
		dest[1] = str_op[(i << 1) + i - 7];
		dest[2] = str_op[(i << 1) + i - 6];
		return (3);
	}
	dest[0] = str_op[i << 1];
	dest[1] = str_op[(i << 1) + 1];
	return (2);
}

void					write_buff(t_data_buff *buff)
{
	char	chain[2048];
	size_t	i;
	size_t	j;
	size_t max;

	i = 0;
	j = 0;
	max = (size_t)((buff->index > (ssize_t)511) ? 512 : buff->index + (ssize_t)1);
	while (i < max)
	{
		j += write_op(&chain[j], buff->buff[i]) + 1;
		chain[j - 1] = '\n';
		++i;
	}
	if (max == 512)
	{
		ft_memcpy((void*)buff->buff, (void*)&buff->buff[512], sizeof(int) * (size_t)512);
		buff->index -= (ssize_t)512;
	}
	else
		buff->index = (ssize_t)-1;
	write(1, chain, (size_t)j);
}
