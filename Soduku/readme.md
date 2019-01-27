Introduction to Computing
=========================
Assignment 1 Autumn 2017
=========================

For this assignment we will write a program which checks whether
a certain input is a valid nxn sudoku or not. 

For our purposes, an nxn sudoku is a collection of numbers
organised in rows, columns and subsquares. We consider each of the rows,
columns, and subsquares to have n elements, with n being a square number
greater than 1: 4, 9, 16 and so on. It follows that a 4x4 sudoku 
will contain 16 elements, a 9x9 one 81 elements, and so on. 

For instance the following is a 4x4 sudoku that we could expect 
in input for our program:

1 2 3 4
4 1 2 76
4 4 4 1
9 4 1 -7

The rows are:

1 2 3 4; 4 1 2 76; 4 4 4 1; 9 4 1 -7

The columns are:

1 4 4 9; 2 1 4 4; 3 2 4 1; 4 76 1 -7

The subsquares are:

1 2 4 1; 3 4 2 76; 4 4 9 4; 4 1 1 -7

We say that an nxn sudoku is _valid_ if each of the rows, columns
and subsquares contains all the numbers from 1 to n.

The sudoku above is clearly not a valid one. 

The following 9x9 sudoku is a valid one:

8 4 2 5 7 1 9 3 6 
3 5 1 8 6 9 7 4 2
7 6 9 2 4 3 1 8 5
5 9 7 6 2 8 3 1 4
6 2 3 1 9 4 5 7 8
4 1 8 3 5 7 2 6 9
9 8 6 7 3 2 4 5 1
1 7 4 9 8 5 6 2 3
2 3 5 4 1 6 8 9 7 

File scd.cpp contains an initial draft for the program and
additional instructions. Complete the program and submit
the source file.

The program reads the input and prints it on the screen. It
determines whether the sudoku is a valid one or not and prints
the outcome on the screen. 

As you can see, the sudoku is read from a text file: the program
asks the user to enter the name of the file containing the input.

For this to work, the executable and the input text file need to
be in the same directory but this may not work as expected if
you use an IDE to launch the program. 

So if this aspect doesn't work as expected please execute the
program from a Terminal.

In order to test the program you will have to create some text
files containing sudokus. When our program requires the name of
the file in input, this needs to be entered including any
extensions (for instance .txt) that are part of the name of the
file. 

Some guidelines for this assignment:

- None of the functions, except for the main, should contain user
or file input or output (std::ifstream, std::cin, std::cout,
etc) in their implementation: std::ifstream, std::cin,
std::cout, etc are only allowed in the main. 

- All the variables should be declared in the scope of a function
(either the main or some other one): global variables are not
allowed.

- All the loops should be controlled either by the loop condition
or by return. Statements such as switch, break, continue, goto
are not allowed anywhere in the program.

- Compile and test your program on Linux on the lab computers before 
submitting in order to make sure you are not using any non-standard features. 

- If you use features introduced in the C++11 (or later) version of the standard 
you need to specify this in a comment on top of your source file. 