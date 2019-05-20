#!/bin/bash

RES="OK"
while [ "$RES" = "OK" ]
do
	RES=$(ARG=$(ruby -e "puts (0..6).to_a.shuffle.join(' ')"); echo $ARG > trace && ./push_swap $ARG | ./checker $ARG)
done
echo $RES
