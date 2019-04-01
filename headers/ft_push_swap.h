/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:55:46 by coremart          #+#    #+#             */
/*   Updated: 2019/04/01 02:50:45 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

enum
{
	SA = 1,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
};

typedef struct	s_arr
{
	int		*arr;
	int		size;
}				t_arr;

typedef struct	s_llist
{
	int			nb;
	t_llist		*next;
	t_llist		*prev;
}				t_llist;

typedef struct	s_llist_tmp
{
	int			nb;
	int			dest;
	t_llist		*next;
	t_llist		*prev;
}				t_llist_tmp;


typedef struct	s_piles
{
	t_llist		*a;
	t_llist_tmp	*b;
}				t_piles;

typedef struct	s_data_buff
{
	char		buff[2048];
	size_t		index;
}				t_data_buff;

typedef struct	s_all_data
{
	t_data_buff *buff;
	t_piles		*piles;
	t_llist		*lis;
}				t_all_data;


t_arr		*pars(const char *const *const tab, const int nb_elem);
int			*get_lis_index(int *const arr, int size);
extern void	rm_all(int nb, int *arr, int size);
t_llist		*transform_to_ll_lis(t_arr *arr, int *lis);
t_llist		*transform_to_pile(t_arr *arr);

#endif
