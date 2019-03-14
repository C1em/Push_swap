/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:38:51 by coremart          #+#    #+#             */
/*   Updated: 2019/03/14 06:06:44 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

t_arr	*pars(const char *const *const entry, const int nb_elem)
{
	t_arr	*arr;
	int		*arr_tmp;
	int		nb_elem_tmp;

	if (!(arr = (t_arr*)malloc(sizeof(t_arr))))
		return (NULL);
	if (!(arr->arr = (int*)malloc(sizeof(int) * nb_elem * 2 - 1)))
		return (NULL);
	arr->size = nb_elem;
	arr_tmp = arr->arr;
	nb_elem_tmp = nb_elem - 1;
	arr_tmp[nb_elem_tmp] = ft_atoi(entry[nb_elem_tmp]);
	while (nb_elem_tmp--)
    	{
		arr_tmp[nb_elem_tmp] = ft_atoi(entry[nb_elem_tmp]);
		arr_tmp[nb_elem_tmp + nb_elem] = arr_tmp[nb_elem_tmp];
	}
	return (arr);
}
