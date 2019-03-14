/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:55:46 by coremart          #+#    #+#             */
/*   Updated: 2019/03/14 10:57:09 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

typedef struct	s_arr
{
	int		*arr;
	int		size;
	char	padding[4];
}				t_arr;

typedef struct	s_beol_n_index_arr
{
	int		*beol;
	int		*index_arr;
}				t_beol_n_index_arr;

t_arr		*pars(const char *const *const tab, const int nb_elem);
int			*get_lis(int *arr, int size);
extern void	ft_tabcpy_and_rm_all(int nb,
									t_beol_n_index_arr *beol_n_index_arr_dst,
							t_beol_n_index_arr *beol_n_index_arr_src, int size);
extern void	rm_all(int nb, int *arr, int size);

#endif
