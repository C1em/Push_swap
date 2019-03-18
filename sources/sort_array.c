/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:31:18 by coremart          #+#    #+#             */
/*   Updated: 2019/03/18 13:46:06 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
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
/*
static void			squeeze_lis(int *lis_index, int *arr, int size_li,
																int arr_size)
{
	int i;
	int index_tmp;
	int next_nb;
	int previous_index;

	printf("lis_index :%d, %d, %d, %d, %d\n", lis_index[0], lis_index[1], lis_index[2], lis_index[3], lis_index[4]);
	i = 1;
	index_tmp = lis_index[0];
	next_nb = arr[lis_index[1]];
	while (--index_tmp >= lis_index[size_li - 1] - arr_size)
		if (arr[index_tmp] < next_nb)
			lis_index[0] = index_tmp;
	while (i + 1 < size_li)
	{
		previous_index = lis_index[i - 1];
		next_nb = arr[lis_index[i + 1]];
		index_tmp = lis_index[i];
		while (--index_tmp > previous_index && index_tmp != arr_size - 1)
			if (arr[index_tmp] < next_nb && arr[index_tmp]
														> arr[previous_index])
				lis_index[i] = index_tmp;
		i++;
	}
	previous_index = lis_index[i - 1];
	index_tmp = lis_index[i];
	while (--index_tmp > previous_index)
		if (arr[index_tmp] > arr[previous_index])
			lis_index[i] = index_tmp;
}
*/


static void			shift_right(int *index_arr, int index, int size_a, int *arr)
{
	int next_nb;
	int prev_nb;
	int index_tmp;
	int end;
	int start;

	index_arr = &index_arr[1];
	end = (index_arr[index] >= size_a) ? (size_a >> 1) + size_a : size_a >> 1;
	start = (index_arr[index] >= size_a) ? size_a : 0;
	while (index_arr[index] >= start)
	{
		index_tmp = index_arr[index];
		next_nb = (index + 1 < index_arr[-1]) ? arr[index_arr[index + 1]]
																: 0x01111111;
		prev_nb = (index > 0) ? arr[index_arr[index - 1]] : 0x10000000;
		while (index_tmp < end)
		{
			if (arr[index_tmp] <= next_nb && arr[index_tmp] >= prev_nb)
				index_arr[index] = index_tmp;
			index_tmp++;
		}
		end = index_arr[index];
		index--;
	}
}

static void			shift_left(int *index_arr, int index, int size_a, int *arr)
{
	int next_nb;
	int prev_nb;
	int index_tmp;
	int end;
	int start;

	index_arr = &index_arr[1];
	start = (index_arr[index] >= size_a) ? (size_a >> 1) + size_a : size_a >> 1;
	end = (index_arr[index] >= size_a) ? (size_a + 1) << 1: size_a;
	while (index_arr[index] < end)
	{
		index_tmp = index_arr[index];
		next_nb = (index + 1 < index_arr[-1]) ? arr[index_arr[index + 1]]
																: 0x01111111;
		prev_nb = (index > 0) ? arr[index_arr[index - 1]] : 0x10000000;
		while (index_tmp > start)
		{
			if (arr[index_tmp] <= next_nb && arr[index_tmp] >= prev_nb)
				index_arr[index] = index_tmp;
			index_tmp--;
		}
		start = index_arr[index];
		index++;
	}
}

static void			squeeze_lis(int *arr, int size, int *index_arr)
{
	int left_index;
	int right_index;
	int mid;
	int size_ia;

	size_ia = *index_arr;
	index_arr = &index_arr[1];
	mid = size >> 1;
	left_index = size_ia - 1;
	right_index = size_ia - 1;
	while (left_index && index_arr[left_index] > mid)
		--left_index;
	while (index_arr[right_index] > mid + size)
		--right_index;
/*	int i = -1;
	while(++i < 20)
		printf("%d : %d\n", index_arr[i], arr[index_arr[i]]);
*/	shift_right(&index_arr[-1], left_index, size, arr);
/*	i = -1;
	while(++i < 20)
		printf("%d : %d\n", index_arr[i], arr[index_arr[i]]);
*/	shift_right(&index_arr[-1], right_index, size, arr);
/*	i = -1;
	while(++i < 20)
		printf("%d : %d\n", index_arr[i], arr[index_arr[i]]);
*/	shift_left(&index_arr[-1], left_index + 1, size, arr);
/*	i = -1;
	while(++i < 20)
		printf("%d : %d\n", index_arr[i], arr[index_arr[i]]);
*/	shift_left(&index_arr[-1], right_index + 1, size, arr);
/*	i = -1;
	while(++i < 20)
		printf("%d : %d\n", index_arr[i], arr[index_arr[i]]);
*/}

static int			*get_lis_index(int *index_arr, int last_elem, int size)
{
	int		*lis_endex;

	printf("size :%d\n", size);
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
	if (!(biggest_elem_of_len = (int*)malloc(sizeof(int) * size + 1)))
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
		return (get_lis_index(index_arr, biggest_elem_of_len[beol_last],
																	beol_last));
	}
	return (NULL);
}

int					*get_lis(int *const arr, int size)
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
