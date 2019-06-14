/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:13:58 by coremart          #+#    #+#             */
/*   Updated: 2019/06/14 05:37:35 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static inline int	rot_op_of(const char *str_op)
{
	if (str_op[2] == '\0')
	{
		if (str_op[1] == 'a')
			return (RA);
		if (str_op[1] == 'b')
			return (RB);
		if (str_op[1] == 'r')
			return (RR);
		error();
		return (0);
	}
	if (str_op[3] != '\0' || str_op[1] != 'r')
		return (0);
	if (str_op[2] == 'a')
		return (RRA);
	if (str_op[2] == 'b')
		return (RRB);
	if (str_op[2] == 'r')
		return (RRR);
	error();
	return (0);
}

static int			op_of(const char *str_op)
{
	if (!str_op || !str_op[0] || !str_op[1])
		error();
	if (str_op[0] == 'r')
		return (rot_op_of(str_op));
	if (str_op[2] != '\0')
		error();
	if (str_op[0] == 's')
	{
		if (str_op[1] == 'a')
			return (SA);
		if (str_op[1] == 'b')
			return (SB);
		if (str_op[1] == 's')
			return (SS);
	}
	else if (str_op[0] == 'p')
	{
		if (str_op[1] == 'a')
			return (PA);
		if (str_op[1] == 'b')
			return (PB);
	}
	error();
	return (0);
}

t_pile				*get_op(void)
{
	int		*all_op_arr;
	t_pile	*op_list;
	char	*line;

	all_op_arr = (int[11]){SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR};
	op_list = NULL;
	if (get_next_line(0, &line) != 1)
		return (NULL);
	op_list = pile_init(op_of(line));
	free(line);
	while (get_next_line(0, &line) == 1)
	{
		op_list = add_elem(op_list, op_of(line));
		free(line);
	}
	return (op_list->prev);
}
