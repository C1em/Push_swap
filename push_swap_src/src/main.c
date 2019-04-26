/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:52:30 by coremart          #+#    #+#             */
/*   Updated: 2019/04/26 18:21:07 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

void		print_arr(t_arr *arr)
{
	int size;
	int i;

	size = (arr->size + 1) >> 1;
	i = 0;
	while (i < size)
		printf("%d\n", arr->arr[i++]);
}

static int	usage(void)
{
	return (0);
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
		return (usage());
	arr = pars((const char**)&av[1], ac - 1);
	if (arr->size < 2)
		return (0);
	print_arr(arr);
	printf("size :%d\n", (arr->size + 1) >> 1);
	lis = get_lis_index(arr->arr, (arr->size + 1) >> 1);
	ll_lis = transform_to_ll_lis(arr, lis);
	piles = transform_to_pile(arr);
	data_buff.index = -1;
	all_data.buff = &data_buff;
	all_data.piles = piles;
	all_data.lis = ll_lis;
/*
	t_llist *end_lis = all_data.lis;
	do
	{
		printf("lis :%d\n", all_data.lis->nb);
		all_data.lis = all_data.lis->next;
	}
	while (all_data.lis != end_lis);
	exit(0);
*/
	start_sort_pile(&all_data, (arr->size + 1) >> 1);
//	printf("before empty_b :\n");
//	write_buff(&data_buff);
	empty_b(&all_data);
//	printf("before rot_a :\n");
//	write_buff(&data_buff);
	rot_a_til_order(&piles->a, (arr->size + 1) >> 1, &data_buff);
	printf("\nres :\n");
	write_buff(&data_buff);
	printf("\n");

	printf("a :\n");
	t_llist *end_a = piles->a;
	do
	{
		printf("%d\n", piles->a->nb);
		piles->a = piles->a->next;
	}
	while (piles->a != end_a);
	if (!piles->b)
		printf("b's empty !!!!!!!");
	else
		printf("NOOOOOOOOOOOOO\n");

	return (0);
}
