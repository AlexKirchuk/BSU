# Lab 1 — Real Numbers (Variant 7)

Develop a **console application in Java** to compute the approximate value of a function using its **Taylor series expansion**.  
The calculation should stop when the absolute value of the next term becomes less than a given threshold **ε**, defined as:

epsilon = 10^(-k), k in N

Compare the obtained result with the value computed using standard library functions.  
The program should read `x` and `k` from the keyboard and display the result with **three decimal places**.  

## Function for this variant: `cos(x)`