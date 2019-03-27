/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:55:46 by coremart          #+#    #+#             */
/*   Updated: 2019/03/26 22:28:14 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

typedef struct	s_arr
{
	int		*arr;
	int		size;
}				t_arr;

typedef struct	s_list_head
{
	struct	s_list_head	*next;
	struct	s_list_head	*prev;
}				t_list_head;

typedef struct	s_llist
{
	t_list_head	head;
	int			nb;
}				t_llist;

typedef struct	s_lis_nb
{
	int	nb;
	int	lis;
}				t_lis_nb;


t_arr		*pars(const char *const *const tab, const int nb_elem);
int			*get_lis_index(int *const arr, int size);
extern void	rm_all(int nb, int *arr, int size);
t_list_head		*transform_to_llist(t_arr *arr, int *lis);
t_lis_nb	*transform_to_info_arr(t_arr *arr, int *lis);

#endif
