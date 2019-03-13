/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:31:18 by coremart          #+#    #+#             */
/*   Updated: 2019/03/13 09:41:36 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

static inline int	binary_search_index(int len, int *arr, int index, int *biggest_elem_of_len)
{
	int lo;

	lo = 1;
	while (lo <= len)
	{
		if (arr[biggest_elem_of_len[ft_ceil((lo + len) / 2.0f)]] <= arr[index])
			lo = ft_ceil((lo + len) / 2.0f) + 1;
		else
			len = ft_ceil((lo + len) / 2.0f) - 1;
	}
	return (lo);
}

static int					*get_lis_result(int *arr, int *index_arr, int last_index, int len)
{
	int *res;

	printf("len :%d\n", len);
	if (!(res = (int*)malloc(sizeof(int) * len)))
		return (NULL);
	res[--len] = arr[last_index];
	while (len--)
	{
		res[len] = arr[index_arr[last_index]];
		last_index = index_arr[last_index];
	}
	return (res);
}

int					*get_lis(int *const arr, int size)
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
	biggest_elem_of_len[0] = -1;
	index_arr[0] = -1;
	i = 1;
	beol_last = 1;
	while (i < size)
	{
		new_beol_last = binary_search_index(beol_last, arr, i, biggest_elem_of_len);
		index_arr[i] = biggest_elem_of_len[new_beol_last - 1];
		biggest_elem_of_len[new_beol_last] = i;
		if (new_beol_last > beol_last)
			beol_last = new_beol_last;
		i++;
	}
	return (get_lis_result(arr, index_arr, biggest_elem_of_len[beol_last], beol_last));
}
