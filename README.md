This was a project for the UIC Youth Scholars Program 2021.
# Register Machines
A [register machine](https://en.wikipedia.org/wiki/Register_machine) is an abstract machine composed of an infinite number of registers $R_i, i \in \mathbb W$ which can each store a number.
Four operations are permitted:
* $Z(n):$ Set $R_n$ to 0
* $S(n):$ increment $ by 1
* $T(m, n):$ copy contents of $R_m$ to $R_n$
* $J(m, n, i):$ if contents of $R_m$ and $R_n$ are the same, go to instruction $i$. Otherwise, go to next instruction.
# Usage
To simulate a register machine with this program, type your program in registerprogram.txt. Then run RegMachine.exe. Arguments for the program are passed through command line input, and stored in registers 0 and 1.

Syntax for programming: type the letter of the command, then the arguments as integers, separated with spaces, eg. `J 1 3 6`. The command `H` indicates to halt. Examples of programs below.

Limitations/notes:
* Register numbers start at 0, not 1 like in the packet. Also, they're finite here.
* Can't really handle negative numbers, unless they are encoded as positive integers.

# Simple program examples

### $n-1$ (packet example)  
input: n; output:n-1;
```
Z 1
J 0 1 9
Z 2
S 1
J 0 1 8
S 2
J 0 0 4
T 2 0
H
```
### Addition
input: $n, m$; output: $n + m$
```
Z 2
Z 3
J 0 2 7
S 2
S 3
J 0 0 3
Z 2
J 1 2 12
S 2
S 3
J 0 0 8
T 3 0
H
```
### Subtraction
input: $n, m$ with $n>m$; output: $n - m$
```
Z 2
J 0 1 6
S 1
S 2
J 0 0 2
T 2 0
H
```
### Multiplication  
input: $n, m$; output: $n \cdot m$
```
Z 3
Z 4
J 1 3 11
Z 2
J 0 2 9
S 2
S 4
J 0 0 5
S 3
J 0 0 3
T 4 0
H
```
### Square
input: $n$; output: $n^2$
```
T 0 1
Z 3
Z 4
J 1 3 12
Z 2
J 0 2 10
S 2
S 4
J 0 0 6
S 3
J 0 0 4
T 4 0
H
```