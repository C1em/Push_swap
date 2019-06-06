/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:54:50 by coremart          #+#    #+#             */
/*   Updated: 2019/06/06 01:20:15 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include <stdio.h>

int						ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == 'f'
																|| c == ' ')
		return (1);
	return (0);
}

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

static int			test_duplicate(t_pile *pile)
{
	int		*arr;
	size_t	len;

	len = ft_pilelen(pile);
	if (!(arr = (int*)malloc(sizeof(int) * len)))
		exit(1);
	fill_arr(arr, pile, len);
	ft_quicksort(arr, len);
	while (--len)
	{
		if (arr[len] == arr[len - 1])
			return (1);
	}
	return (0);
}

int		ft_custom_atoi(const char *str)
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
		{
			write(2, "Error\n", 6);
			exit(1);
		}
		return ((int)~res + 1);
	}
	if (res > INT_MAX)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	return ((int)res);
}

t_pile					*pars_pile(char **arr, int size)
{
	t_pile *pile;
	ssize_t i;
	ssize_t tmp_i;

	pile = NULL;
	while (size--)
	{
		i = ft_strlen(arr[size]) - 1;
		while ((tmp_i = i) != -1)
		{
			while (i + 1 && ft_isspace(arr[size][i]))
				--i;
			if (i == (ssize_t)-1)
				break ;
			while (i + 1 && ft_isdigit(arr[size][i]))
				--i;
			if (arr[size][i] == '-' || arr[size][i] == '+')
			{
				if (i > 0 && !ft_isspace(arr[size][i - 1]))
					tmp_i = i;
				else
					--i;
			}
			if (tmp_i == i)
			{
				write(2, "Error\n", 6);
				exit(1);
			}
			pile = (pile) ? add_elem(pile, ft_custom_atoi(&arr[size][i + 1]))
						: pile_init(ft_custom_atoi(&arr[size][i + 1]));
		}
	}
	if(test_duplicate(pile))
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	return (pile);
}
