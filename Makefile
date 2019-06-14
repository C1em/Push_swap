# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coremart <coremart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 17:33:24 by coremart          #+#    #+#              #
#    Updated: 2019/06/14 00:55:50 by coremart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
NAME1 = push_swap
NAME2 = checker
CFLAGS = -Werror -Wall -Wextra
DFLAGS = -MT $@ -MMD -MP -MF $(DDIR)/$*.d

### INCLUDES ###
LIB = libft
LIBH = $(LIB)/include
HDIR_PUSH_SWAP = push_swap_src/include
HDIR_CHECKER = checker_src/include
LIBA = $(LIB)/libft.a

### SOURCES PUSH SWAP ###
PDIR_PUSH_SWAP = push_swap_src
SDIR_PUSH_SWAP = $(PDIR_PUSH_SWAP)/src
_SRCS_PUSH_SWAP = main.c get_lis.c parsing.c list_op.c pile_op.c put_non_lis_on_b.c \
		write_buff.c empty_b.c fill_buffer.c fun_fill_rot.c fun_fill_push.c \
		rot_count.c ssp_custom_rot.c pusha_custom_rot.c pile_utils.c error.c \
		get_lis_utils.c push_a_tab.c push_a_tab_rot.c rot_op.c
SRC_PUSH_SWAP = $(patsubst %,$(SDIR_PUSH_SWAP)/%,$(_SRCS_PUSH_SWAP))

### SOURCES CHECKER ###
PDIR_CHECKER = checker_src
SDIR_CHECKER = $(PDIR_CHECKER)/src
_SRCS_CHECKER = apply_op_to_pile.c check_if_order.c get_op.c main.c pars_pile.c \
		pile_op.c push_op.c rev_rot_op.c rot_op.c swap_op.c
SRC_CHECKER = $(patsubst %,$(SDIR_CHECKER)/%,$(_SRCS_CHECKER))

### OBJECTS PUSH SWAP ####
ODIR_PUSH_SWAP = $(PDIR_PUSH_SWAP)/obj
_OBJ_PUSH_SWAP = $(_SRCS_PUSH_SWAP:.c=.o)
OBJ_PUSH_SWAP = $(patsubst %,$(ODIR_PUSH_SWAP)/%,$(_OBJ_PUSH_SWAP))

### OBJECTS CHECKER ####
ODIR_CHECKER = $(PDIR_CHECKER)/obj
_OBJ_CHECKER = $(_SRCS_CHECKER:.c=.o)
OBJ_CHECKER = $(patsubst %,$(ODIR_CHECKER)/%,$(_OBJ_CHECKER))

## DEPENDENCIES ##
DDIR = deps
_DEPS = $(_OBJ_CHECKER:.o=.d) $(_OBJ_PUSH_SWAP:.o=.d)
DEPS = $(patsubst %,$(DDIR)/%,$(_DEPS))

### RULES ###

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJ_PUSH_SWAP)
	make -C $(LIB)
	gcc -g -o $(NAME1) $(LIBA) $(OBJ_PUSH_SWAP) $(CFLAGS)

$(NAME2): $(OBJ_CHECKER)
	make -C $(LIB)
	gcc -g -o $(NAME2) $(LIBA) $(OBJ_CHECKER) $(CFLAGS)

$(ODIR_PUSH_SWAP)/%.o: $(SDIR_PUSH_SWAP)/%.c
	gcc $(CFLAGS) -g $(DFLAGS) -o $@ -c $< -I $(HDIR_PUSH_SWAP) -I $(LIBH)

$(ODIR_CHECKER)/%.o: $(SDIR_CHECKER)/%.c
	gcc $(CFLAGS) -g $(DFLAGS) -o $@ -c $< -I $(HDIR_CHECKER) -I $(LIBH)

-include $(DEPS)

clean:
	@make -C $(LIB) clean
	@rm -f $(OBJ_CHECKER) $(OBJ_PUSH_SWAP)

fclean: clean
	@make -C $(LIB) fclean
	@rm -f $(NAME1) $(NAME2)

re: fclean all

.PRECIOUS: $(DDIR)/%.d
.PHONY: all clean fclean re $(NAME1) $(NAME2)
