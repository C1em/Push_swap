/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:52:30 by coremart          #+#    #+#             */
/*   Updated: 2019/06/15 04:45:11 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static void	free_lst(t_llist *lst)
{
	if (!lst)
		return ;
	lst->prev->next = NULL;
	while (lst->next)
	{
		lst = lst->next;
		free(lst->prev);
	}
	free(lst);
}

static void	free_lst_tmp(t_llist_tmp *lst)
{
	if (!lst)
		return ;
	lst->prev->next = NULL;
	while (lst->next)
	{
		lst = lst->next;
		free(lst->prev);
	}
	free(lst);
}

static void	free_all(t_all_data *data, t_arr *arr)
{
	free_lst(data->lis);
	free_lst_tmp(data->piles->b);
	free_lst(data->piles->a);
	free(data->piles);
	free(arr->arr);
	free(arr);
}

int			main(int ac, char **av)
{
	t_arr		*arr;
	int			*lis;
	t_data_buff data_buff;
	t_all_data	all_data;

	if (ac < 2)
		return (0);
	arr = pars((const char**)&av[1], ac - 1);
	if (arr->size < 2)
		return (0);
	lis = get_lis_index(arr->arr, (arr->size + 1) >> 1);
	data_buff.index = -1;
	all_data.buff = &data_buff;
	all_data.piles = transform_to_pile(arr);
	all_data.lis = transform_to_ll_lis(arr, lis);
	free(&lis[-1]);
	start_sort_pile(&all_data, (arr->size + 1) >> 1);
	empty_b(&all_data, (arr->size + 1) >> 1);
	rot_a_til_order(&all_data.piles->a, (arr->size + 1) >> 1, &data_buff);
	free_all(&all_data, arr);
	write_buff(&data_buff);
	write_buff(&data_buff);
	return (0);
}
