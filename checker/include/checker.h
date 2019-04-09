/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:48:02 by coremart          #+#    #+#             */
/*   Updated: 2019/04/09 09:45:13 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# define SA 0x1
# define SB 0x2
# define SS 0x4
# define PA 0x8
# define PB 0x10
# define RA 0x20
# define RB 0x40
# define RR 0x80
# define RRA 0x100
# define RRB 0x200
# define RRR 0x400

typedef struct	s_pile
{
	int				nb;
	struct s_pile	*next;
	struct s_pile	*prev;
}				t_pile;

typedef void (*fun)(t_pile *pile) t_fun_op;

/*
**	pars_pile.c
*/
t_pile					*pars_pile(char **arr, int size);
/*
**	pile_op.c
*/
t_pile	*pile_init(int nb);
t_pile	*add_elem(t_pile *pile, int nb);

#endif
