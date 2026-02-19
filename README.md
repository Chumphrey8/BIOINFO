# BIOINFO
BIOINFO project 1 at OHIO University
Some issues that I ran into while programming this project:
Arrows to display direction made matrix unaligned:
Solution: Just used D,L,U in order to store direction instead and helped better with alignment
Another issue: for the bigger matrices, they looked confusing in the terminal and hard to understand
Solution:I could've either displayed the matrix to the output file or just included a message that stated that the matrix was too big to display(this is the one I did, Probably should've done the other one)
another issue was for the bigger sequences I wanted to copy and paste those into an input file instead of the terminal(easier in an input file in my opinion)
Solution: I made sure to check for input file in order to read from one and if there wasn't one, then I made sure to prompt the user for the sequences in the terminal
Another issue was that the input file would read an extra character because windows systems has an invisible character if the file was created in VS code.
Solution: I check for this character and made sure to not include it into the sequence
Another issue was the ANSI values, I tried to use hexdecimal color but it didnt work so I changed it to ANSI colors