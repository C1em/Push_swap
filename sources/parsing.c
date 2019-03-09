/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:38:51 by coremart          #+#    #+#             */
/*   Updated: 2019/03/08 04:20:04 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdlib.h>

#include <stdio.h>

t_arr	*pars(const char *const *const tab, const int nb_elem)
{
	t_arr *arr;

	if (!(arr = (t_arr*)malloc(sizeof(t_arr))))
		return (NULL);
	if (!(arr->arr = (int*)malloc(sizeof(int) * 10)))
		return (NULL);
	(void)tab;
	(void)nb_elem;
	return (arr);
}
