![Alt text](/static/getnextline.drawio.png?raw=true "Diagram for get next line")

One of the biggest difficulty I encountered with this project is the mental shift between conditional programming to invariant programming. It caused me pain. Additionaly, all the memory bugs, segfaults and other C monsters traumatized me a little but it was for the best !

I will explain in detail what is invariant programming, how it leads to cleaner and easier logic implementation. 


Thanks to Wissem Boussah *wboussah* for reviewing my logic and discussing edge cases and Ronan Gouachet *rgouachet* for the last and most vicious memory leak.


Compile with 
cc -Wall -Wextra -Werror ./get_next_line.c ./get_next_line.h ./get_next_line_utils.c -g -D BUFFER_SIZE=1000
Note that you can change the value of the buffer_size value.


A hard limit has been set to prevent that the count_bytes transfered by the function read()
man 2 read gives : 
    On  Linux,  read()  (and similar system calls) will transfer at most 0x7ffff000 (2,147,479,552) bytes, returning the number of bytes
    actually transferred. 


Examine memory leak with 
valgrind --tool=memcheck --leak-check=full --track-origins=yes ./a.out


Learned to read valgrind output
https://bytes.usc.edu/cs104/wiki/valgrind/#conditional-jump-or-move-depends-on-uninitialized-values

Learned gdb :
https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf