/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:52:30 by coremart          #+#    #+#             */
/*   Updated: 2019/06/08 01:04:06 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>

void	print_list(void *list)
{
	void *end;

	end = list;
	printf("%d\n", ((t_llist*)list)->nb);
	list = (void*)((t_llist*)list)->next;
	while (list != end)
	{
		printf("%d\n", ((t_llist*)list)->nb);
		list = (void*)((t_llist*)list)->next;
	}
}

void	free_lst(t_llist *lst)
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

int		main(int ac, char **av)
{
	t_arr		*arr;
	int			*lis;
	t_llist		*ll_lis;
	t_piles		*piles;
	t_data_buff data_buff;
	t_all_data	all_data;

	if (ac < 2)
		return (0);
	arr = pars((const char**)&av[1], ac - 1);
	if (arr->size < 2)
		return (0);
	lis = get_lis_index(arr->arr, (arr->size + 1) >> 1);
	ll_lis = transform_to_ll_lis(arr, lis);
	free(&lis[-1]);
	piles = transform_to_pile(arr);
	data_buff.index = -1;
	all_data.buff = &data_buff;
	all_data.piles = piles;
	all_data.lis = ll_lis;
	start_sort_pile(&all_data, (arr->size + 1) >> 1);
	empty_b(&all_data, (arr->size + 1) >> 1);
	free_lst(all_data.lis);
	free_lst(all_data.piles->b);
	rot_a_til_order(&piles->a, (arr->size + 1) >> 1, &data_buff);
	free_lst(all_data.piles->a);
	free(all_data.piles);
	free(arr->arr);
	free(arr);
	write_buff(&data_buff);
	write_buff(&data_buff);
	return (0);
}
