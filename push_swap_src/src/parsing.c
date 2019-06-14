/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:38:51 by coremart          #+#    #+#             */
/*   Updated: 2019/06/14 02:24:24 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include <stdio.h>

static size_t		tot_len(const char *const *const entry, int nb_elem)
{
	size_t tot_len;
	size_t i;

	tot_len = 0;
	i = 0;
	while (nb_elem--)
	{
		while (entry[nb_elem][i])
		{
			if (ft_isdigit(entry[nb_elem][i])
				&& (ft_isspace(entry[nb_elem][i + 1])
				|| entry[nb_elem][i + 1] == '\0'))
				++tot_len;
			else if (!(ft_isdigit(entry[nb_elem][i])
					|| (ft_isspace(entry[nb_elem][i])
					|| entry[nb_elem][i] == '\0' || ((entry[nb_elem][i] == '-'
					|| entry[nb_elem][i] == '+') && (!i
					|| ft_isspace(entry[nb_elem][i - 1]))))))
				error();
			++i;
		}
		i = 0;
	}
	return (tot_len);
}

int					ft_custom_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 0;
	res = 0L;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = 1;
	while (str[i] >= '0' && str[i] <= '9' && !(res & (long)0x100000000))
		res = res * 10L + (long)(str[i++] - '0');
	if (sign)
	{
		if (res > (long)INT_MAX + 1L)
			error();
		return ((int)~res + 1);
	}
	if (res > INT_MAX)
		error();
	return ((int)res);
}

static void inline	add_nb(const char *const entry, int **arr,
							size_t size, int add_to_end)
{
	ssize_t	i;
	ssize_t	tmp_i;

	i = ft_strlen(entry) - 1;
	while ((tmp_i = i) != -1)
	{
		while (i + 1 && ft_isspace(entry[i]))
			--i;
		if (i == (ssize_t)-1)
			break ;
		while (i + 1 && ft_isdigit(entry[i]))
			--i;
		if (entry[i] == '-' || entry[i] == '+')
			--i;
		if (tmp_i == i)
			error();
		*(--*arr) = ft_custom_atoi(&entry[i + 1]);
		if (add_to_end)
			*(*arr + size) = **arr;
		else
			add_to_end = 1;
	}
}

static int			test_duplicate(t_arr *arr)
{
	int		*arr_tmp;
	size_t	i;

	i = (arr->size + 1) >> 1;
	if (!(arr_tmp = (int*)ft_memdup((void*)arr->arr, i * sizeof(int))))
		exit(1);
	ft_quicksort(arr_tmp, i);
	while (--i)
	{
		if (arr_tmp[i] == arr_tmp[i - 1])
		{
			free(arr_tmp);
			return (1);
		}
	}
	free(arr_tmp);
	return (0);
}

t_arr				*pars(const char *const *const entry, int nb_elem)
{
	t_arr	*arr;
	ssize_t	len;

	if (!(arr = (t_arr*)malloc(sizeof(t_arr))))
		exit(1);
	if (!(len = tot_len(entry, nb_elem)))
		return (NULL);
	arr->size = (len << 1) - 1;
	if (!(arr->arr = (int*)malloc(sizeof(int) * arr->size)))
		exit(1);
	arr->arr = &arr->arr[len];
	add_nb(entry[--nb_elem], &arr->arr, len, 0);
	while (nb_elem--)
		add_nb(entry[nb_elem], &arr->arr, len, 1);
	if (test_duplicate(arr))
		error();
	return (arr);
}
