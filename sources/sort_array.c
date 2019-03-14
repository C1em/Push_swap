/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:31:18 by coremart          #+#    #+#             */
/*   Updated: 2019/03/14 15:25:56 by coremart         ###   ########.fr       */
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
//	printf("len :%d\n", len);
	while (lo <= len)
	{
/*		printf("beol :%d, index :%d, mid :%d\n",
			biggest_elem_of_len[ft_ceil((lo + len) / 2.0f)], index,
												ft_ceil((lo + len) / 2.0f));
*/		if (arr[biggest_elem_of_len[ft_ceil((lo + len) / 2.0f)]] <= arr[index])
			lo = ft_ceil((lo + len) / 2.0f) + 1;
		else
			len = ft_ceil((lo + len) / 2.0f) - 1;
	}
	return (lo);
}

static int			*get_lis_result(int *arr, int *index_arr,
												int last_index, int len)
{
	int *res;

	if (!(res = (int*)malloc(sizeof(int) * len)))
		return (NULL);
	res[--len] = arr[last_index];
	while (!(last_index & (1 << 31)) && len--)
	{
		res[len] = arr[index_arr[last_index]];
		last_index = index_arr[last_index];
	}
	return (res);
}

static inline int	get_new_lis(t_beol_n_index_arr *beol_n_index_arr,
											int *arr, int index, int beol_last)
{
	int new_beol_last;

/*	printf("beol_tmp :%d, %d, %d, %d, %d index_arr_tmp :%d, %d, %d, %d, %d, %d, %d, %d, %d\n",
	beol_n_index_arr->beol[0], beol_n_index_arr->beol[1],
	beol_n_index_arr->beol[2], beol_n_index_arr->beol[3], beol_n_index_arr->beol[4],
	beol_n_index_arr->index_arr[0], beol_n_index_arr->index_arr[1],
	beol_n_index_arr->index_arr[2], beol_n_index_arr->index_arr[3], beol_n_index_arr->index_arr[4],
	beol_n_index_arr->index_arr[5], beol_n_index_arr->index_arr[6], beol_n_index_arr->index_arr[7],
	beol_n_index_arr->index_arr[8]);
*/	new_beol_last = binary_search_index(beol_last, arr, index,
														beol_n_index_arr->beol);
	beol_n_index_arr->index_arr[index] =
									beol_n_index_arr->beol[new_beol_last - 1];
	beol_n_index_arr->beol[new_beol_last] = index;
/*	printf("beol_tmp :%d, %d, %d, %d, %d index_arr_tmp :%d, %d, %d, %d, %d, %d, %d, %d, %d\n\n",
	beol_n_index_arr->beol[0], beol_n_index_arr->beol[1],
	beol_n_index_arr->beol[2], beol_n_index_arr->beol[3], beol_n_index_arr->beol[4],
	beol_n_index_arr->index_arr[0], beol_n_index_arr->index_arr[1],
	beol_n_index_arr->index_arr[2], beol_n_index_arr->index_arr[3], beol_n_index_arr->index_arr[4],
	beol_n_index_arr->index_arr[5], beol_n_index_arr->index_arr[6], beol_n_index_arr->index_arr[7],
	beol_n_index_arr->index_arr[8]);
*/	return (new_beol_last);
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
	tot_size = size * 2 - 1;
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
			printf("OK\n");
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
			beol_n_index_arr_tmp.beol = &beol_n_index_arr_tmp.beol[1];
			beol_n_index_arr_tmp.beol[0] = -1;
			beol_last_tmp--;
		}
	}
	printf("beoll :%d\n", beol_last);
	return (get_lis_result(arr, beol_n_index_arr->index_arr,
			beol_n_index_arr->beol[beol_last], beol_last));
}

int					*get_lis(int *const arr, int size)
{
	int					i;
	int					beol_last;
	int					new_beol_last;
	int					*biggest_elem_of_len;
	int					*index_arr;
	t_beol_n_index_arr	beol_n_index_arr;

	if (!(index_arr = (int*)malloc(sizeof(int) * size * 2 - 1)))
		return (NULL);
	if (!(biggest_elem_of_len = (int*)malloc(sizeof(int) * size * 2)))
		return (NULL);
	i = 1;
	beol_last = 1;
	biggest_elem_of_len[1] = 0;
	biggest_elem_of_len[0] = -1;
	index_arr[0] = -1;
	while (i < size)
	{
		new_beol_last = binary_search_index(beol_last, arr, i,
														biggest_elem_of_len);
		index_arr[i] = biggest_elem_of_len[new_beol_last - 1];
		biggest_elem_of_len[new_beol_last] = i;
		if (new_beol_last > beol_last)
			beol_last = new_beol_last;
		i++;
	}
	beol_n_index_arr.beol = biggest_elem_of_len;
	beol_n_index_arr.index_arr = index_arr;
	return (continue_lis(&beol_n_index_arr, arr, size, beol_last));
}
