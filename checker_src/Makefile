# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coremart <coremart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/20 18:29:57 by aljacque          #+#    #+#              #
#    Updated: 2019/04/11 17:11:56 by coremart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
NAME = checker
CFLAGS = -Werror -Wall -Wextra
DFLAGS = -MT $@ -MMD -MP -MF $(DDIR)/$*.d

### INCLUDES ###
LIB = ../libft
LIBH = $(LIB)/include
HDIR = include
LIBA = $(LIB)/libft.a

### SOURCES ###
SDIR = src
_SRCS = apply_op_to_pile.c check_if_order.c get_op.c main.c pars_pile.c \
		pile_op.c push_op.c rev_rot_op.c rot_op.c swap_op.c
SRC = $(patsubst %,$(SDIR)/%,$(_SRCS))

### OBJECTS ####
ODIR = obj
_OBJ = $(_SRCS:.c=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

## DEPENDENCIES ##
DDIR = deps
_DEPS = $(_OBJ:.o=.d)
DEPS = $(patsubst %,$(DDIR)/%,$(_DEPS)) 

### RULES ###
all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB)
	gcc -g -o $(NAME) $(LIBA) $(OBJ) $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c
	gcc $(CFLAGS) -g $(DFLAGS) -o $@ -c $< -I $(HDIR) -I $(LIBH)

-include $(DEPS)

asan :
	make -C $(LIB)
	gcc -g -fsanitize=address -o $(NAME) $(LIBA) $(SDIR)/*.c $(CFLAGS) -I $(HDIR) -I $(LIBH)
	$(MAKE) clean

clean:
	@make -C $(LIB) clean
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIB) fclean
	@rm -f $(NAME)

re: fclean all

.PRECIOUS: $(DDIR)/%.d
.PHONY: all clean fclean re
