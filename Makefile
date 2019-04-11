# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coremart <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 17:33:24 by coremart          #+#    #+#              #
#    Updated: 2019/04/11 18:17:21 by coremart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## DIRECTORIES ##
CHECKERDIR = checker_src
PUSHSWAPDIR = push_swap_src

## BINARIES ##
CHECKERBIN = checker
PUSHSWAPBIN = push_swap

all: $(CHECKERBIN) $(PUSHSWAPBIN)

$(CHECKERBIN):
	make -C $(CHECKERDIR)
	cp $(CHECKERDIR)/$(CHECKERBIN) .

$(PUSHSWAPBIN):
	make -C $(PUSHSWAPDIR)
	cp $(PUSHSWAPDIR)/$(PUSHSWAPBIN) .

.PHONY: all $(CHECKERBIN) $(PUSHSWAPBIN)
