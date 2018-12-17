1.
Problem1.sh and Problem1.cpp are the respective Bash script and C++ files for Problem 1.
I also included Problem1-1.sh and Problem1-1.cpp that I used to run each of the codes for 100 seconds for question 1.1.
The answers for questions 1.1-1.3 are in a file called Final.pdf.

2.
For Problem 2, I created a script that runs dealer 9 times (percentages from 10 to 90) and stores the result in a file called output.bin. The script is called Problem2.sh
Run pitboss after the script is run to access the selected record.
I included dealer.cpp in the tarball.

3.
mighty.cpp is for problem 3. I also included a foo.txt to be tee'd into another file. Use mighty like: ./mighty foo.txt (destination file name).

4.
Problem4.cpp is for problem 4. Ctrl-c will kill the running program before it kills itself automatically.

Bonus:
I completed all three bonus problems, they are labeled Bonus1.cpp, Bonus2.cpp, and Bonus3.cpp

ALL problems:
My included Makefile is set up to compile all of the .cpp files listed above to run all problems, including the bonus problems.
My GSL library is installed under ~/local/gsl-2.5/ and I had to set my library path variable by using the command: export LD_LIBRARY_PATH=~/local/gsl-2.5/.libs
