/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:31:18 by coremart          #+#    #+#             */
/*   Updated: 2019/06/14 02:26:11 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

static inline int	binary_search_index(int len, int *arr, int index,
													int *biggest_elem_of_len)
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

static int			*get_lis(int *index_arr, int last_elem, int size)
{
	int		*lis_index;

	if (!(lis_index = (int*)malloc(sizeof(int) * size)))
		exit(1);
	--size;
	lis_index[size] = last_elem;
	while (size--)
	{
		lis_index[size] = index_arr[last_elem];
		last_elem = index_arr[last_elem];
	}
	free(index_arr);
	return (lis_index);
}

static int			*is_less_than_prev(int beol_last, int *actual_max_len,
								int *biggest_elem_of_len, int *index_arr)
{
	int	tmp;

	if (beol_last > *actual_max_len)
	{
		*actual_max_len = beol_last;
		tmp = biggest_elem_of_len[beol_last];
		free(biggest_elem_of_len);
		return (get_lis(index_arr, tmp, beol_last));
	}
	free(biggest_elem_of_len);
	free(index_arr);
	return (NULL);
}

static inline int	*get_part_lis(int *const arr, int size, int *actual_max_len)
{
	int		i;
	int		beol_last;
	int		new_beol_last;
	int		*biggest_elem_of_len;
	int		*index_arr;

	if (!(index_arr = (int*)malloc(sizeof(int) * size)))
		exit(1);
	if (!(biggest_elem_of_len = (int*)malloc(sizeof(int) * (size + 1))))
		exit(1);
	beol_last = 1;
	i = 0;
	*(void**)biggest_elem_of_len = (void*)0xFFFFFFFF;
	index_arr[0] = -1;
	while (++i < size)
	{
		new_beol_last = binary_search_index(beol_last, arr, i,
											biggest_elem_of_len);
		index_arr[i] = biggest_elem_of_len[new_beol_last - 1];
		biggest_elem_of_len[new_beol_last] = i;
		if (new_beol_last > beol_last)
			beol_last = new_beol_last;
	}
	return (is_less_than_prev(beol_last, actual_max_len,
								biggest_elem_of_len, index_arr));
}

/*
**	longest increasing sequence algorithm adapted to get it from an array
**	consedered as a loop (56123 has for lis : 12356) then squeeze the lis
**	to get the one with the max. of elem at the middle of the array
**	when they are multiple lis
*/

int					*get_lis_index(int *const arr, int size)
{
	int *actual_lis;
	int *actual_lis_len;
	int *tmp_lis;
	int i;

	i = 0;
	if (!(actual_lis_len = (int*)malloc(sizeof(int) * (size + 1))))
		exit(1);
	*actual_lis_len = 1;
	actual_lis = &actual_lis_len[1];
	while (i < size)
	{
		if ((tmp_lis = get_part_lis(&arr[i], size, actual_lis_len)))
		{
			ft_tabcpy_n_add(actual_lis, tmp_lis, *actual_lis_len, i);
			free(tmp_lis);
		}
		i++;
	}
	squeeze_lis(arr, size, actual_lis_len);
	return (actual_lis);
}
