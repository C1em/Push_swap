/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:31:18 by coremart          #+#    #+#             */
/*   Updated: 2019/04/11 14:32:13 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

static int			ft_max(int a, int b)
{
	return ((a > b) ? a : b);
}

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

static void			shift_right(int *index_arr, int start, int *arr, int size_a)
{
	int index_tmp;
	int end;
	int end_tmp;
	int prev_nb;
	int next_nb;

	end = (index_arr[start] >= size_a) ? size_a : 0;
	end_tmp = (index_arr[start] >= size_a) ? ft_min((size_a >> 1) + size_a,
									*index_arr + size_a - 1) : (size_a >> 1);
	next_nb = (start + 1 < index_arr[-1])
									? arr[index_arr[start + 1]] : 0x7FFFFFFF;
	if (start + 1 >= index_arr[-1] || index_arr[start + 1] != end_tmp)
		++end_tmp;
	while (start + 1 && index_arr[start] >= end)
	{
		prev_nb = (start) ? arr[index_arr[start - 1]] : -0x7FFFFFFF - 1;
		index_tmp = index_arr[start];
		while (++index_tmp < end_tmp)
			if (arr[index_tmp] >= prev_nb && arr[index_tmp] <= next_nb)
				index_arr[start] = index_tmp;
		end_tmp = index_arr[start];
		next_nb = arr[end_tmp];
		--start;
	}
}

static void			shift_left(int *index_arr, int start, int *arr, int size_a)
{
	int index_tmp;
	int end;
	int end_tmp;
	int next_nb;
	int prev_nb;

	end = (index_arr[start] >= size_a) ? (size_a << 1) - 1 : size_a;
	end_tmp = (index_arr[start] >= size_a) ? (size_a >> 1) + size_a
		: ft_max(size_a >> 1, index_arr[index_arr[-1] - 1] - size_a + 1);
	prev_nb = (start) ? arr[index_arr[start - 1]] : -0x7FFFFFFF - 1;
	if (!start || index_arr[start - 1] != end_tmp)
		--end_tmp;
	while (start < index_arr[-1] && index_arr[start] < end)
	{
		next_nb = (start + 1 < index_arr[-1])
									? arr[index_arr[start + 1]] : 0x7FFFFFFF;
		index_tmp = index_arr[start];
		while (--index_tmp > end_tmp)
			if (arr[index_tmp] >= prev_nb && arr[index_tmp] <= next_nb)
				index_arr[start] = index_tmp;
		end_tmp = index_arr[start];
		prev_nb = arr[end_tmp];
		++start;
	}
}

static void			squeeze_lis(int *arr, int size, int *index_arr)
{
	int left_index;
	int right_index;
	int mid;
	int size_ia;

	size_ia = *index_arr;
	++index_arr;
	mid = size >> 1;
	right_index = size_ia - 1;
	while (index_arr[right_index] > mid + size)
		--right_index;
	left_index = right_index;
	while (left_index + 1 && index_arr[left_index] > mid)
		--left_index;
	if (left_index > -1)
		shift_right(index_arr, left_index, arr, size);
	if (left_index  + 1 < size_ia && index_arr[left_index + 1] < size)
		shift_left(index_arr, left_index + 1, arr, size);
	if (index_arr[right_index] >= size)
		shift_right(index_arr, right_index, arr, size);
	if (right_index + 1 != size_ia
						&& index_arr[right_index + 1] > (size >> 1) + size)
		shift_left(index_arr, right_index + 1, arr, size);
}

static int			*get_lis(int *index_arr, int last_elem, int size)
{
	int		*lis_endex;

	if (!(lis_endex = (int*)malloc(sizeof(int) * size)))
		return (NULL);
	size--;
	lis_endex[size] = last_elem;
	while (size--)
	{
		lis_endex[size] = index_arr[last_elem];
		last_elem = index_arr[last_elem];
	}
	return (lis_endex);
}

static inline void			ft_tabcpy_n_add(int *const dst, const int *const src,
													int size, const int add)
{
	while (size--)
		dst[size] = src[size] + add;
}

static inline int	*get_part_lis(int *const arr, int size, int *actual_max_len)
{
	int		i;
	int		beol_last;
	int		new_beol_last;
	int		*biggest_elem_of_len;
	int		*index_arr;

	if (!(index_arr = (int*)malloc(sizeof(int) * size)))
		return (NULL);
	if (!(biggest_elem_of_len = (int*)malloc(sizeof(int) * (size + 1))))
		return (NULL);
	beol_last = 1;
	i = 0;
	biggest_elem_of_len[1] = 0;
	biggest_elem_of_len[0] = -1;
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
	if (beol_last > *actual_max_len)
	{
		*actual_max_len = beol_last;
		return (get_lis(index_arr, biggest_elem_of_len[beol_last],
																	beol_last));
	}
	return (NULL);
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
		return (NULL);
	*actual_lis_len = 1;
	actual_lis = &actual_lis_len[1];
	while (i < size)
	{
		if ((tmp_lis = get_part_lis(&arr[i], size, actual_lis_len)))
			ft_tabcpy_n_add(actual_lis, tmp_lis, *actual_lis_len, i);
		i++;
	}
	squeeze_lis(arr, size, actual_lis_len);
	return (actual_lis);
}
