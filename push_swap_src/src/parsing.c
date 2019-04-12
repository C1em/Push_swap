/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:38:51 by coremart          #+#    #+#             */
/*   Updated: 2019/04/12 13:44:31 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

static int			ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == 'f'
																|| c == ' ')
		return (1);
	return (0);
}

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
			if (ft_isdigit(entry[nb_elem][i]))
				++tot_len;
			++i;
		}
		i = 0;
	}
	return (tot_len);
}

static void inline	add_nb(const char *const entry, int **arr, size_t size)
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
		if (tmp_i == i)
		{
			write(1, "Error\n", 6);
			exit(1);
		}
		*(--*arr) = ft_atoi(&entry[i + 1]);
		*(*(arr) + size) = **arr;
	}
}

t_arr				*pars(const char *const *const entry, int nb_elem)
{
	t_arr	*arr;
	int		nb_elem_tmp;
	ssize_t	len;

	if (!(arr = (t_arr*)malloc(sizeof(t_arr))))
		return (NULL);
	if (!(len = tot_len(entry, nb_elem)))
		return (NULL);
	if (!(arr->arr = (int*)malloc(sizeof(int) * (len << 1) - 1)))
		return (NULL);
	arr->size = (len << 1) - 1;
	nb_elem_tmp = nb_elem;
	arr->arr = &arr->arr[len];
	while (nb_elem_tmp--)
		add_nb(entry[nb_elem_tmp], &arr->arr, len);
	len = 0;
	while (len < arr->size)
	{
		printf("arr :%d\n", arr->arr[len]);
		++len;
	}
	printf("OK\n");
	return (arr);
}
