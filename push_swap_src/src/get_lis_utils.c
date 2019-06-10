/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lis_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 01:32:11 by coremart          #+#    #+#             */
/*   Updated: 2019/06/10 02:56:44 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_max(int a, int b)
{
	return ((a > b) ? a : b);
}

void		ft_tabcpy_n_add(int *const dst, const int *const src,
										int size, const int add)
{
	while (size--)
		dst[size] = src[size] + add;
}

static void	shift_left(int *index_arr, int start, int *arr, int size_a)
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

static void	shift_right(int *index_arr, int start, int *arr, int size_a)
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

void		squeeze_lis(int *arr, int size, int *index_arr)
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
	if (left_index + 1 < size_ia && index_arr[left_index + 1] < size)
		shift_left(index_arr, left_index + 1, arr, size);
	if (index_arr[right_index] >= size)
		shift_right(index_arr, right_index, arr, size);
	if (right_index + 1 != size_ia
						&& index_arr[right_index + 1] > (size >> 1) + size)
		shift_left(index_arr, right_index + 1, arr, size);
}
