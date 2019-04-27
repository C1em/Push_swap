#!/bin/bash

count="-"
while [ "$count" != "b" ]
do
	./push_swap `ruby -e "puts (1..80).to_a.shuffle.join(' ')"` > trace
	count=$(cat trace | tail -c 2)
done
echo $count
