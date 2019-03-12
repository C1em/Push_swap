/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:31:18 by coremart          #+#    #+#             */
/*   Updated: 2019/03/12 15:03:43 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

static inline void	ft_array_set(int *const arr, int size, const int nb)
{
	while (size--)
		arr[size] = nb;
}

static inline int	binary_search_index(int len, int *arr, int index)
{
	int lo;

	lo = 1;
	while (lo <= len)
	{
		if (arr[ft_ceil((lo + len) / 2.0f)] <= arr[index])
			lo = ft_ceil((lo + len) / 2.0f) + 1;
		else
			len = ft_ceil((lo + len) / 2.0f) - 1;
	}
	return (lo);
}

int					*get_lis(int *arr, int size)
{
	int i;
	int beol_last;
	int new_beol_last;
	int *biggest_elem_of_len;
	int *index_arr;

	if (!(biggest_elem_of_len = (int*)malloc(sizeof(int) * size + 1)))
		return (NULL);
	if (!(index_arr = (int*)malloc(sizeof(int) * size)))
		return (NULL);
	biggest_elem_of_len[1] = 0;
	ft_arr_set(index_arr, size, -1);
	i = 1;
	beol_last = 1;
	while (i < size)
	{
		new_beol_last = binary_search_index(beol_last, arr, i);
		index_arr[i] = biggest_elem_of_len[new_beol_last - 1];
		biggest_elem_of_len[new_beol_last] = i;
		if (new_beol_last > beol_last)
			beol_last = new_beol_last;
		i++;
	}
}
