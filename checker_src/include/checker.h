/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:48:02 by coremart          #+#    #+#             */
/*   Updated: 2019/05/31 16:53:56 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# define SA 0x1//1
# define SB 0x2//2
# define SS 0x4//4
# define PA 0x8//8
# define PB 0x10//16
# define RA 0x20//32
# define RB 0x40//64
# define RR 0x80//128
# define RRA 0x100//256
# define RRB 0x200//512
# define RRR 0x400//1024

typedef struct	s_pile
{
	int				nb;
	struct s_pile	*next;
	struct s_pile	*prev;
}				t_pile;

typedef struct	s_piles
{
	t_pile	*a;
	t_pile	*b;
}				t_piles;

typedef struct	s_str
{
	char	str[2048];
	int		index;
}				t_str;



typedef void (*t_fun_op)(t_piles *piles);

/*
**	pars_pile.c
*/
t_pile		*pars_pile(char **arr, int size);

/*
**	get_op.c
*/
t_pile			*get_op(void);

/*
**	apply_to_pile.c
*/
t_piles			*apply_op_to_pile(t_pile *a, t_pile *op_list, int print_op);

/*
**	pile_op.c
*/
t_pile	*pile_init(int nb);
t_pile	*add_elem(t_pile *pile, int nb);
t_pile	*rm_elem(t_pile *elem);

/*
**	rot_op.c
*/
void	rot_ab(t_piles *piles);
void	rot_b(t_piles *piles);
void	rot_a(t_piles *piles);

/*
**	rev_rot_op.c
*/
void	rev_rot_ab(t_piles *piles);
void	rev_rot_b(t_piles *piles);
void	rev_rot_a(t_piles *piles);

/*
**	swap_op.c
*/
void	swap_a(t_piles *piles);
void	swap_b(t_piles *piles);
void	swap_ab(t_piles *piles);

/*
**	push_op.c
*/
void	push_b(t_piles *piles);
void	push_a(t_piles *piles);
/*
**	check_if_order.c
*/
void	check_if_order(t_piles *piles);

#endif
