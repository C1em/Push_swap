/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_to_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:02:21 by coremart          #+#    #+#             */
/*   Updated: 2019/03/25 21:47:30 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include "libft.h"
#include <stdlib.h>

t_lis_nb	*transform_to_info_arr(t_arr *arr, int *lis)
{
	t_lis_nb *info_arr;
	int i;

	if (!(info_arr = (t_lis_nb*)malloc(sizeof(t_lis_nb) * ((arr->size + 1) >> 1))))
		return (NULL);
	i = (arr->size + 1) >> 1;
	while (i--)
	{
		info_arr[i].nb = arr->arr[i];
		info_arr[i].lis = 0;
	}
	i = lis[-1];
	while (i--)
		info_arr[lis[i] % ((arr->size + 1) >> 1)].nb = 1;
	return (info_arr);
}
