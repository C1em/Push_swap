/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:55:46 by coremart          #+#    #+#             */
/*   Updated: 2019/04/06 13:09:08 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include <string.h>

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

typedef struct	s_arr
{
	int		*arr;
	int		size;
}				t_arr;

typedef struct	s_llist
{
	struct s_llist	*next;
	struct s_llist	*prev;
	int				nb;
}				t_llist;

typedef struct	s_llist_tmp
{
	struct s_llist_tmp	*next;
	struct s_llist_tmp	*prev;
	int				nb;
	int				dest;
}				t_llist_tmp;

typedef struct	s_piles
{
	t_llist		*a;
	t_llist_tmp	*b;
}				t_piles;

typedef struct	s_data_buff
{
	char		buff[1024];
	size_t		index;
	size_t		nb_same_rot;
	size_t		tot_size;
	int			rot;
}				t_data_buff;

typedef struct	s_all_data
{
	t_data_buff *buff;
	t_piles		*piles;
	t_llist		*lis;
}				t_all_data;

/*
**	parsing.c
*/
t_arr		*pars(const char *const *const tab, const int nb_elem);
/*
**	get_lis.c
*/
int			*get_lis_index(int *const arr, int size);
/*
**	list_op.c
*/
t_llist		*transform_to_ll_lis(t_arr *arr, int *lis);
t_piles		*transform_to_pile(t_arr *arr);
void		add_to_lis(t_llist *lis, int nb);
/*
**	pile_op.c
*/
void		push_a(t_piles *piles, t_data_buff *buff);
void		push_b(t_all_data *all_data);
void		rot_a(t_llist **ptr_a, int len, t_data_buff *buff);
int			len_b(t_llist_tmp *b);
/*
**	order_pile.c
*/
void		order_pile(t_all_data *all_data);
/*
**	fill_buffer.c
*/
void		fill_buffer(t_data_buff *buff, char op);
/*
**	write_buff.c
*/
void		write_buff(t_data_buff *buff);

void		print_list(void *list);


#endif
