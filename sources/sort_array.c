/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:31:18 by coremart          #+#    #+#             */
/*   Updated: 2019/03/15 23:27:51 by coremart         ###   ########.fr       */
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
	if (arr[index] == arr[biggest_elem_of_len[lo - 1]])
		return (lo - 1);
	return (lo);
}
/*
static int			*get_lis_result(int *arr, int *index_arr,
												int last_index, int len)
{
	int *res;

	if (!(res = (int*)malloc(sizeof(int) * len)))
		return (NULL);
	res[--len] = arr[last_index];
	while (!(index_arr[last_index] & (1 << 31)) && len--)
	{
		res[len] = arr[index_arr[last_index]];
		last_index = index_arr[last_index];
	}
	res = &res[len];
	return (res);
}*/
/*
static inline int	get_new_lis(t_beol_n_index_arr *beol_n_index_arr,
											int *arr, int index, int beol_last)
{
	int new_beol_last;

	if (beol_n_index_arr->beol[1] > arr[index])
		return (0);
	new_beol_last = binary_search_index(beol_last, arr, index,
														beol_n_index_arr->beol);
	beol_n_index_arr->index_arr[index] =
									beol_n_index_arr->beol[new_beol_last - 1];
	beol_n_index_arr->beol[new_beol_last] = index;
	return (new_beol_last);
}

static int			*continue_lis(t_beol_n_index_arr *beol_n_index_arr,
											int *arr, int size, int beol_last)
{
	t_beol_n_index_arr beol_n_index_arr_tmp;
	int *index_arr_tmp;
	int tot_size;
	int i;
	int beol_last_tmp;
	int new_beol_last;

	i = 0;
	tot_size = (size << 1) - 1;
	if (!(beol_n_index_arr_tmp.beol = (int*)malloc(sizeof(int) * tot_size + 1)))
		return (NULL);
	if (!(index_arr_tmp = (int*)malloc(sizeof(int) * tot_size)))
		return (NULL);
	beol_n_index_arr_tmp.index_arr = index_arr_tmp;
	ft_tabcpy_and_rm_all(0, &beol_n_index_arr_tmp, beol_n_index_arr, size);
	beol_last_tmp = beol_last;
	if (beol_n_index_arr_tmp.beol[1] == 0)
	{
		beol_n_index_arr_tmp.beol = &beol_n_index_arr_tmp.beol[1];
		beol_n_index_arr_tmp.beol[0] = -1;
		beol_last_tmp--;
	}
	while (size + i++ < tot_size)
	{
		if ((new_beol_last = get_new_lis(&beol_n_index_arr_tmp, arr,
									size + i - 1, beol_last_tmp)) > beol_last)
		{
			beol_last = new_beol_last;
			ft_tabcpy_and_rm_all(i, beol_n_index_arr, &beol_n_index_arr_tmp,
																	size + i);
		}
		else
			rm_all(i, index_arr_tmp, size + i);
		if (new_beol_last > beol_last_tmp)
			beol_last_tmp = new_beol_last;
		if (beol_n_index_arr_tmp.beol[1] == i)
		{
			beol_n_index_arr_tmp.beol = &beol_n_index_arr_tmp.beol[i];
			beol_n_index_arr_tmp.beol[0] = -1;
			beol_last_tmp--;
		}
	}
	printf("end :%d\n", beol_last);
	return (get_lis_result(arr, beol_n_index_arr->index_arr,
			beol_n_index_arr->beol[beol_last], beol_last));
}
*/

static void			squeeze_lis(int *lis_index, int *arr, int size_li)
{
	int i;
	int index_tmp;
	int next_nb;
	int previous_index;

	if (size_li == 1)
		return ;
	i = 1;
	index_tmp = lis_index[0];
	next_nb = arr[lis_index[1]];
	while (--index_tmp >= 0)
	{
		if (arr[index_tmp] < next_nb)
			lis_index[0] = index_tmp;
	}
	while (i + 1 < size_li)
	{
		previous_index = lis_index[i - 1];
		next_nb = arr[lis_index[i + 1]];
		index_tmp = lis_index[i];
		while (--index_tmp > previous_index)
		{
			printf("lis_index :%d, %d, %d, %d, %d\n", lis_index[0], lis_index[1], lis_index[2], lis_index[3], lis_index[4]);
			if (arr[index_tmp] < next_nb && arr[index_tmp] > arr[previous_index])
				lis_index[i] = index_tmp;
		}
		i++;
	}
}

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

int					*get_lis(int *const arr, int size)
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
	index_arr = get_lis_index(index_arr, biggest_elem_of_len[beol_last],
																	beol_last);
	squeeze_lis(index_arr, arr, beol_last);
	return (index_arr);
}
