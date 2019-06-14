# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    script.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coremart <coremart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 15:37:02 by coremart          #+#    #+#              #
#    Updated: 2019/06/14 04:18:07 by coremart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

RES="OK"
while [ "$RES" = "OK" ]
do
	RES=$(timeout 3s bash -c 'ARG=$(ruby -e "puts (-19..19).to_a.shuffle.join('\'' '\'')"); echo $ARG > trace && ./push_swap $ARG | ./checker $ARG')
	if [ $? = 124 ]
	then
		echo "timout"
	fi
#	RES=$(ARG=$(ruby -e "puts (0..9).to_a.shuffle.join(' ')"); echo $ARG > trace && ./push_swap $ARG | wc -l | cut -b 6,7,8)
done
echo $RES
