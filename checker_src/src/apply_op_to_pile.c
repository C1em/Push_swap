/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op_to_pile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 08:49:48 by coremart          #+#    #+#             */
/*   Updated: 2019/06/15 04:47:09 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

static void			custom_itoa(int nb, char *str_nb)
{
	int	len;

	if (nb < 0)
	{
		str_nb[0] = '-';
		str_nb = &str_nb[1];
		if (nb == INT_MIN)
		{
			str_nb[0] = '2';
			str_nb = &str_nb[1];
			nb = -147483648;
		}
		nb = ~nb + 1;
	}
	len = ft_count_digit(nb);
	str_nb[len] = '\0';
	while (len--)
	{
		str_nb[len] = (nb % 10) + '0';
		nb /= 10;
	}
}

static void			add_piles_to_str(t_piles *piles, int op, t_str *str)
{
	char	nb[12];
	t_pile	*end_a;
	t_pile	*end_b;

	end_a = piles->a;
	end_b = piles->b;
	add_header(str, op);
	nb[0] = '\0';
	if (piles->a)
		custom_itoa((piles->a = piles->a->next)->prev->nb, nb);
	add_nb_to_str(nb, str, 0);
	if (piles->b)
		custom_itoa((piles->b = piles->b->next)->prev->nb, nb);
	add_nb_to_str(nb, str, 1);
	while (piles->a != end_a || piles->b != end_b)
	{
		if (piles->a != end_a)
			custom_itoa((piles->a = piles->a->next)->prev->nb, nb);
		add_nb_to_str(nb, str, 0);
		if (piles->b != end_b)
			custom_itoa((piles->b = piles->b->next)->prev->nb, nb);
		add_nb_to_str(nb, str, 1);
	}
	add_string_to_str(str, "------------------\n");
}

static void inline	do_pile_op(t_piles *piles, int op)
{
	int			*op_arr;
	t_fun_op	*fun_op;
	size_t		i;

	op_arr = (int[11]){SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR};
	i = (op >= RA) ? 5 : 0;
	while (~op_arr[i] & op)
		++i;
	fun_op = (t_fun_op[11]){swap_a, swap_b, swap_ab, push_a, push_b, rot_a,
							rot_b, rot_ab, rev_rot_a, rev_rot_b, rev_rot_ab};
	return (fun_op[i](piles));
}

t_piles				*apply_op_to_pile(t_pile *a, t_pile *op_list, int print_op)
{
	t_pile	*end_op;
	t_piles	*piles;
	t_str	str;

	if (!(piles = (t_piles*)malloc(sizeof(t_piles))))
		exit(1);
	piles->b = NULL;
	if (!((piles->a = a) && op_list))
		return (piles);
	end_op = op_list->next;
	str.index = 0;
	if (print_op)
		add_piles_to_str(piles, 0, &str);
	while (op_list != end_op)
	{
		do_pile_op(piles, op_list->nb);
		if (print_op)
			add_piles_to_str(piles, op_list->nb, &str);
		op_list = op_list->prev;
	}
	do_pile_op(piles, op_list->nb);
	if (print_op)
		add_piles_to_str(piles, op_list->nb, &str);
	write_str(&str);
	return (piles);
}
