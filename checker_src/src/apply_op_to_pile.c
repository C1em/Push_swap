/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op_to_pile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 08:49:48 by coremart          #+#    #+#             */
/*   Updated: 2019/06/14 07:02:51 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "libft.h"

#include <stdio.h>

static void			write_str(t_str *str)
{
	write(1, str->str, str->index);
	str->index = 0;
}

static void			add_string_to_str(t_str *str, char *string)
{
	while (*string)
	{
		str->str[str->index] = *string;
		++string;
		if (++str->index == 2048)
			write_str(str);
	}
}

static void			custom_itoa(int nb, char *str_nb)
{
	int	len;
	int	tmp_nb;

	len = 0;
	if (!nb)
	{
		str_nb[0] = '0';
		str_nb[1] = '\0';
		return ;
	}
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
	tmp_nb = nb;
	while (tmp_nb)
	{
		tmp_nb /= 10;
		++len;
	}
	str_nb[len] = '\0';
	while (len--)
	{
		str_nb[len] = (nb % 10) + '0';
		nb /= 10;
	}
}

static void			add_nb_to_str(char *nb, t_str *str, int eol)
{
	int i;

	i = ft_strlen(nb);
	add_string_to_str(str, nb);
	if (eol)
		add_string_to_str(str, "\n");
	else
	{
		while (i < 12)
		{
			add_string_to_str(str, " ");
			++i;
		}
	}
	nb[0] = '\0';
}

static inline int	log2(int nb)
{
	int res;

	res = 0;
	while (nb > 1)
	{
		nb >>= 1;
		++res;
	}
	return (res);
}

static void			add_header(t_str *str, int op)
{
	int index;

	add_string_to_str(str, "\n");
	if (!op)
		return (add_string_to_str(str, "Pile a:     Pile b:\n"));
	index = (log2(op) << 1) + (op >= 512) + (op == 1024);
	str->str[str->index] = "sasbsspapbrarbrrrrarrbrrr"[index];
	if (++str->index == 2048)
		write_str(str);
	str->str[str->index] = "sasbsspapbrarbrrrrarrbrrr"[index + 1];
	if (++str->index == 2048)
		write_str(str);
	if (op >= 256)
	{
		str->str[str->index] = "sasbsspapbrarbrrrrarrbrrr"[index + 2];
		if (++str->index == 2048)
			write_str(str);
	}
	add_string_to_str(str, "\nPile a:     Pile b:\n");
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
