/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:31:18 by coremart          #+#    #+#             */
/*   Updated: 2019/03/09 07:19:36 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

int		*sort_array(t_arr *array)
{
	int *sorted;

	if (!(sorted = ft_memdup(array->arr, sizeof(int) * array->size)))
		return (NULL);
	ft_quicksort(sorted, 0, array->size - 1);
	return (sorted);
}

void	simplify_arr(int *arr, int *ref_arr, int size)
{
	int i;

	i = 0;
	if (size <= 0)
		return ;
	while (size--)
	{
		while (arr[i] != ref_arr[size])
			i++;
		arr[i] = size;
		i = 0;
	}
}
