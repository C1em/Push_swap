/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_pile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 20:56:44 by coremart          #+#    #+#             */
/*   Updated: 2019/04/04 04:57:58 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
/*
static void		print_buff(t_data_buff *buff)
{
	size_t i;

	i = 0;
	while (i <= buff->index)
	{
		printf("buff :%d\n", buff->buff[i++]);
	}
}

static void		print_list(void *list)
{
	void *end_list;

	if (!list)
		return ;
	end_list = list;;
	do
	{
		printf("%d\n", ((t_llist*)list)->nb);
		list = (void*)(((t_llist*)list)->next);
	}
	while (end_list != list);
}
*/
static void		rot_a_to_match_the_push(t_all_data *all_data,
															int max_greater_nb)
{
	t_llist	*tmp_dest;
	size_t	offset_from_dest;
	t_piles	*tmp_piles;

	tmp_piles = all_data->piles;
	if (tmp_piles->a->nb < tmp_piles->b->nb)
	{
		while (tmp_piles->a->nb < tmp_piles->b->nb)
		{
			tmp_piles->a = tmp_piles->a->next;
			++all_data->buff->index;
			all_data->buff->buff[all_data->buff->index] = RA;
		}
		return ;
	}
	tmp_dest = tmp_piles->a;
	offset_from_dest = 0;
	while (tmp_dest->nb != tmp_piles->b->dest)
	{
		tmp_dest = tmp_dest->next;
		++offset_from_dest;
	}
	while (tmp_piles->a->nb > tmp_piles->b->nb
										&& max_greater_nb - offset_from_dest + 1)
	{
		tmp_piles->a = tmp_piles->a->prev;
		++offset_from_dest;
		++all_data->buff->index;
		all_data->buff->buff[all_data->buff->index] = RRA;
	}
	--all_data->buff->index;
}

static void		push_a_tab_reverse_rot(size_t len_arr, int *arr, size_t len_b,
															t_all_data *all_data)
{
	size_t rot_count;
	size_t i;

	i = len_arr;
	while (i--)
	{
		rot_count = len_b - arr[i];
		while (rot_count--)
		{
			all_data->piles->b = all_data->piles->b->prev;
			all_data->buff->buff[++all_data->buff->index] = RRB;
		}
		rot_a_to_match_the_push(all_data, len_arr - i);
		push_a(all_data->piles, all_data->buff);
		add_to_lis(all_data->lis, all_data->piles->a->nb);
		len_b = arr[i];
	}
}

static void		push_a_tab_rot(size_t len_arr, int *arr, t_all_data *all_data)
{
	int rot_count;
	size_t i;
	int next;

	i = 0;
	next = 0;
	while (i < len_arr)
	{
		rot_count = arr[i] - next;
		while (rot_count--)
		{
			all_data->piles->b = all_data->piles->b->next;
			all_data->buff->buff[all_data->buff->index] = RB;
		}
		rot_a_to_match_the_push(all_data, i);
		push_a(all_data->piles, all_data->buff);
		add_to_lis(all_data->lis, all_data->piles->a->nb);
		next = arr[i];
		++i;
	}
}

static int		push_a_tab(int *arr, int size_b, t_all_data *all_data)
{
	size_t len;
	int tmp_dest;

	len = 0;
	while (arr[len] != -1)
		++len;
	if (!len)
		return (0);
	tmp_dest = all_data->piles->b->dest;
	if (arr[0] > size_b - arr[len - 1])
		push_a_tab_reverse_rot(len, arr, size_b, all_data);
	else
		push_a_tab_rot(len, arr, all_data);
	while (all_data->piles->a->nb != tmp_dest)
	{
		all_data->piles->a = all_data->piles->a->next;
		++all_data->buff->index;
		all_data->buff->buff[all_data->buff->index] = RA;
	}
	return (len);
}

static int		pusha_if_destof(t_all_data *all_data, int max_elem)
{
	t_llist_tmp	*end_b;
	t_llist_tmp	*tmp_b;
	int			r_count;
	int			*tmp_arr;
	int			i;

	if (!max_elem)
		return (0);
	if (!(tmp_b = all_data->piles->b))
		return (0);
	if (!(tmp_arr = (int*)malloc(sizeof(int) * max_elem)))
		exit(1);
	tmp_arr[0] = -1;
	end_b = tmp_b->prev;
	r_count = 0;
	i = 0;
	while (tmp_b != end_b)
	{
		if (tmp_b->dest == all_data->piles->a->nb)
		{
			tmp_arr[i] = r_count;
			++i;
			tmp_arr[i] = -1;
		}
		tmp_b = tmp_b->next;
		++r_count;
	}
	if (tmp_b->dest == all_data->piles->a->nb)
	{
		tmp_arr[i] = r_count;
		++i;
		tmp_arr[i] = -1;
	}
	tmp_b = tmp_b->next;
	++r_count;
	r_count = push_a_tab(tmp_arr, r_count, all_data);
	free(tmp_arr);
	return (r_count);
}

static void		go_through_pile(t_all_data *all_data)
{
	t_llist		*end_a;
	int			max_elem;

	end_a = all_data->piles->a->prev;
	max_elem = len_b(all_data->piles->b);
	while (all_data->piles->a != end_a)
	{
/*		printf("\nlis :\n");
		print_list((void*)all_data->lis);
		printf("\na :\n");
		print_list((void*)all_data->piles->a);
		printf("\nb :\n");
		print_list((void*)all_data->piles->b);
		printf("______________________________\n");
		printf("max_elem :%d\n", max_elem);
*/		max_elem -= pusha_if_destof(all_data, max_elem);
//		printf("max_elem :%d\n", max_elem);
		if (all_data->piles->a->nb == all_data->lis->nb)
			all_data->lis = all_data->lis->next;
		else
		{
			push_b(all_data);
			++max_elem;
		}
		all_data->piles->a = all_data->piles->a->next;
		all_data->buff->buff[all_data->buff->index] = RA;
	}
/*	printf("\nlis :\n");
	print_list((void*)all_data->lis);
	printf("\na :\n");
	print_list((void*)all_data->piles->a);
	printf("\nb :\n");
	print_list((void*)all_data->piles->b);
	printf("______________________________\n");
		printf("max_elem :%d\n", max_elem);
*/	max_elem -= pusha_if_destof(all_data, max_elem);
//		printf("max_elem :%d\n", max_elem);
	if (all_data->piles->a->nb == all_data->lis->nb)
		all_data->lis = all_data->lis->next;
	else
	{
		push_b(all_data);
		++max_elem;
	}
//	printf("max_elem :%d\n", max_elem);
	all_data->piles->a = all_data->piles->a->next;
	all_data->buff->buff[all_data->buff->index] = RA;
/*	printf("\nlis :\n");
	print_list((void*)all_data->lis);
	printf("\na :\n");
	print_list((void*)all_data->piles->a);
	printf("\nb :\n");
	print_list((void*)all_data->piles->b);
	printf("______________________________\n");
*/}

void			order_pile(t_all_data *all_data)
{
	go_through_pile(all_data);
//	printf("\nsecond part :\n\n");
//	print_buff(all_data->buff);
	go_through_pile(all_data);
}
