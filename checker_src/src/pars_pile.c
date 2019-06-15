/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:54:50 by coremart          #+#    #+#             */
/*   Updated: 2019/06/15 05:15:58 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "libft.h"
#include <stdlib.h>
#include <limits.h>

static size_t		ft_pilelen(t_pile *pile)
{
	size_t	i;
	t_pile	*end_pile;

	if (!pile)
		return (0);
	i = 1;
	end_pile = pile;
	pile = pile->next;
	while (pile != end_pile)
	{
		pile = pile->next;
		++i;
	}
	return (i);
}

static void			fill_arr(int *arr, t_pile *pile, size_t len)
{
	while (len--)
	{
		arr[len] = pile->nb;
		pile = pile->prev;
	}
}

static void			test_duplicate(t_pile *pile)
{
	int		*arr;
	size_t	len;

	if (!(len = ft_pilelen(pile)))
		return ;
	if (!(arr = (int*)malloc(sizeof(int) * len)))
		exit(1);
	fill_arr(arr, pile, len);
	ft_quicksort(arr, len);
	while (--len)
	{
		if (arr[len] == arr[len - 1])
		{
			free(arr);
			error();
		}
	}
	free(arr);
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

t_pile				*pars_pile(char **arr, int size)
{
	t_pile	*pile;
	ssize_t	i;
	ssize_t	tmp_i;

	pile = NULL;
	while (size--)
	{
		i = ft_strlen(arr[size]) - 1;
		while ((tmp_i = i) != -1)
		{
			while (i + 1 && ft_isspace(arr[size][i]))
				--i;
			while (i + 1 && ft_isdigit(arr[size][i]))
				--i;
			if (i + 1 && (arr[size][i] == '-' || arr[size][i] == '+'))
				if ((i-- && !ft_isspace(arr[size][i])))
					error();
			if (tmp_i == i)
				error();
			pile = (pile) ? add_elem(pile, ft_custom_atoi(&arr[size][i + 1]))
						: pile_init(ft_custom_atoi(&arr[size][i + 1]));
		}
	}
	test_duplicate(pile);
	return (pile);
}
