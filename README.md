# Push_swap

This project is introduction to the differents sortings algorithms.
The goal is to order a pile a of element given as parameter by using another pileb and these operations :
  - ra  (rotate a)
  - rb  (rotate b)
  - rra (reverse rotate a)
  - rrb (reverse rotate b)
  - pa  (push on a)
  - pb  (push on b)
  - sa  (swap the 2 first elements on a)
  - sb  (swap the 2 first elements on b)
  
 You can try it by doing make and ./push_swap 4 10 2 5 for example.
 There is also a checker program that check if the operations sort the pile.
 You can try it by doing : ARG="4 10 2 5"; ./push_swap $ARG | ./checker $ARG
