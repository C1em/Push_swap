/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 08:19:51 by coremart          #+#    #+#             */
/*   Updated: 2019/03/14 11:18:58 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

extern inline void ft_tabcpy_and_rm_all(int nb,
									t_beol_n_index_arr *beol_n_index_arr_dst,
							t_beol_n_index_arr *beol_n_index_arr_src, int size)
{
	int *beol_dst;
	int *beol_src;
	int *index_arr_dst;
	int *index_arr_src;

	beol_dst = beol_n_index_arr_dst->beol;
	beol_src = beol_n_index_arr_src->beol;
	index_arr_dst = beol_n_index_arr_dst->index_arr;
	index_arr_src = beol_n_index_arr_src->index_arr;
	beol_dst[size] = beol_src[size];
	while (size--)
	{
		beol_dst[size] = beol_src[size];
		index_arr_dst[size] = index_arr_src[size];
		if (index_arr_src[size] == nb)
		{
			if (nb)
				index_arr_src[size] = -1;
			else
				index_arr_dst[size] = -1;
		}
	}
}

extern inline void rm_all(int nb, int *arr, int size)
{
	while (size--)
	{
		if (arr[size] == nb)
			arr[size] = -1;
	}
}

