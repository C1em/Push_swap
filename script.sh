#!/bin/bash

RES="OK"
while [ "$RES" = "OK" ]
do
	RES=$(timeout 10s bash -c 'ARG=$(ruby -e "puts (0..100).to_a.shuffle.join('\'' '\'')"); echo $ARG > trace && ./push_swap $ARG | ./checker $ARG')
	if [ $? = 124 ]
	then
		echo "timout"
	fi
#	RES=$(ARG=$(ruby -e "puts (0..9).to_a.shuffle.join(' ')"); echo $ARG > trace && ./push_swap $ARG | wc -l | cut -b 6,7,8)
done
echo $RES
