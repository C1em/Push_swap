/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:13:58 by coremart          #+#    #+#             */
/*   Updated: 2019/04/11 12:46:34 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

static int inline	get_index_of(char *haystack, char *needle)
{
	size_t index_hay;
	size_t index_needle;

	if (!needle[0])
		return (-1);
	index_hay = (needle[0] == 'r') ? 10 : 0;
	index_needle = 0;
	while (haystack[index_hay])
	{
		if (!needle[index_needle])
			return (index_hay - index_needle);
		if (haystack[index_hay] == needle[index_needle])
		{
			++index_needle;
			++index_hay;
		}
		else
		{
			index_needle = 0;
			if (index_hay < 16)
				index_hay += (index_hay & 1) ? 1 : 2;
			else
			{	if (index_hay == 16)
					continue ;
				if (index_hay <= 19)
					index_hay = 19;
				else if (index_hay <= 22)
					index_hay = 22;
				else
					index_hay = 25;
			}
		}
	}
	return (-1);
}

t_pile					*get_op(void)
{
	int		*all_op_arr;
	t_pile	*op_list;
	char	*line;
	size_t	index;

	all_op_arr = (int[11]){SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR};
	op_list = NULL;
	if (get_next_line(0, &line) != 1)
		return (NULL);
	if ((index = get_index_of("sasbsspapbrarbrrrrarrbrrr", line)) == -1)
		return (NULL);
	op_list = pile_init(all_op_arr[(index <= 16) ? index >> 1
												: (8 + (index - 16) % 3)]);
	while (get_next_line(0, &line) == 1)
	{
		if ((index = get_index_of("sasbsspapbrarbrrrrarrbrrr", line)) == -1)
			return (NULL);
		op_list = add_elem(op_list, all_op_arr[(index <= 16) ? index >> 1
												: (8 + (index - 16) % 3)]);
		free(line);
	}
	return (op_list->prev);
}
