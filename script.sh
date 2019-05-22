#!/bin/bash

RES="OK"
while [ "$RES" = "OK" ]
do
	RES=$(ARG=$(ruby -e "puts (0..19).to_a.shuffle.join(' ')"); echo $ARG > trace && ./push_swap $ARG | ./checker $ARG)
#	RES=$(ARG=$(ruby -e "puts (0..9).to_a.shuffle.join(' ')"); echo $ARG > trace && ./push_swap $ARG | wc -l | cut -b 6,7,8)
done
echo $RES
