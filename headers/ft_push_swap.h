/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:55:46 by coremart          #+#    #+#             */
/*   Updated: 2019/03/12 14:58:50 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

typedef struct	s_arr
{
	int	*arr;
	int	size;
}				t_arr;


t_arr	*pars(const char *const *const tab, const int nb_elem);
void	mark_the_ones_to_move(t_arr *arr);

#endif
