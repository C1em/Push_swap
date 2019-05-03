#!/bin/bash

RES="1"
while [ "$RES" != "13" ]
do
	RES=$(ARG=$(ruby -e "puts (0..4).to_a.shuffle.join(' ')"); echo $ARG > trace && ./push_swap $ARG | wc -l | cut -b 7,8)
done
echo $RES
