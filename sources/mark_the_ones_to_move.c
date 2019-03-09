/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_the_ones_to_move.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 07:19:06 by coremart          #+#    #+#             */
/*   Updated: 2019/03/09 10:41:14 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_push_swap.h"
#include <stdlib.h>

static inline int	count_from_to(int start, int end, int *arr)
{
	int count_greater;
	int i;

	count_greater = 0;
	i = start + 1;
	while (i <= end)
	{
		if (arr[start] < arr[i])
			count_greater++;
		i++;
	}
	return (count_greater);
}

static void			count_first_part(t_arr *arr, int end, int *mask_tab)
{
	int i;

	i = end;
	while (i--)
		mask_tab[i] = count_from(i, end, arr->arr);
}

static void			count_last_part(t_arr *arr, int start, int end, int *mask_tab)
{
	int i;
	int count_greater;

	i = arr->size;
	while (--i > start)
	{
		count_greater = 0;
		count_greater += count_from(i, arr->size - 1, arr->arr);
		if (!start)
			continue;
		if (arr->arr[arr->size - 1] < arr->arr[0])
			count_greater++;
		count_greater += count_from(0, end, arr->arr);
		mask_tab[end] = count_greater;
	}
}

static int			*number_of_next_greater(t_arr *arr, int start, int end)
{
	int *mask_tab;

	if (!(mask_tab = (int*)malloc(sizeof(int) * arr->size)))
		return (NULL);
	if (start)
		count_first_part(arr, end, mask_tab);
	count_last_part(arr, start, end, mask_tab);
}

static void			search_the_best_sequence(int* arr, int start)
{
	arr[start] = 1;
}

void				mark_the_ones_to_move(t_arr *arr)
{
	int *mask_tab;
	int start;

	start = 0;
	while (arr->arr[start] != 0)
		start++;
	mask_tab = number_of_next_greater(arr, start,
							((!start) ? arr->size - 1 : start - 1));
	search_the_best_sequence(mask_tab, start);
}
