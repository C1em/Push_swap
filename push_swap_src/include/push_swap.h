/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:55:46 by coremart          #+#    #+#             */
/*   Updated: 2019/05/05 04:25:15 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <string.h>

# define SA 0x1		// 1
# define SB 0x2		// 2
# define SS 0x4		// 4
# define PA 0x8		// 8
# define PB 0x10	// 16
# define RA 0x20	// 32
# define RB 0x40	// 64
# define RR 0x80	// 128
# define RRA 0x100	// 256
# define RRB 0x200	// 512
# define RRR 0x400	// 1024
# define ROT 0x360	// 2048

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
	int			buff[1024];
	ssize_t		index;
}				t_data_buff;

typedef struct	s_all_data
{
	t_data_buff *buff;
	t_piles		*piles;
	t_llist		*lis;
}				t_all_data;

typedef struct	s_fun_match_op
{
	void		(*p)(t_data_buff *buff);
	int			op;
}				t_fun_match_op;


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
void		rot_a_til_order(t_llist **ptr_a, int len, t_data_buff *buff);
int			len_b(t_llist_tmp *b);

/*
**	put_non_lis_on_b.c
*/
void		start_sort_pile(t_all_data *data, size_t size);
int			pusha_if_destof(t_all_data *all_data, int max_elem, t_llist *end_a,
																		int rev);
/*
**	fill_buffer.c
*/
void		fill_buffer(t_data_buff *buff, int op);
/*
**	write_buff.c
*/
void		write_buff(t_data_buff *buff);
/*
**	fun_fill_rot.c
*/
void	fill_rot_a(t_data_buff *buff);
void	fill_rot_b(t_data_buff *buff);
void	fill_rev_rot_a(t_data_buff *buff);
void	fill_rev_rot_b(t_data_buff *buff);
/*
**	fun_fill_push.c
*/
void	fill_push_a(t_data_buff *buff);
void	fill_push_b(t_data_buff *buff);
/*
**	empty_b.c
*/
void		empty_b(t_all_data *data, size_t size);
int			is_destof(t_llist_tmp *b, int dest);

/*
**	rot_count.c
*/
size_t		rot_count_til_push(t_llist *a, t_llist *lis, size_t size, int rev);
size_t		lst_len(t_llist *lst);
size_t		count_rot_to_next_pa(t_all_data *all_data, size_t rot_count,
											t_llist *end_a, int rev_ab);

void		print_list(void *list);


#endif
