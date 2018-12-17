#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char ** argv)
{
  int fd[2];
  int pid, bytesread;

  char c;
  char buffer[20];

  string infilename, outfilename;

  ofstream outputfile;

  if (argc != 3)
    {
      cerr << "Usage: mighty (name of input file) (name of outputfile)" << endl;
      return 1;
    }

  pipe(fd);

  pid = fork();

  if (pid == 0) // In child process
    {
      dup2(fd[1], 1);

      close(fd[0]);

      execl("/bin/cat", "cat", "-b", argv[1], (char*)0);

      close(fd[1]);
    }
  else // In parent process
    {
      dup2(fd[0], 0);

      close(fd[1]);
      
      outputfile.open(argv[2]);

      while ((bytesread = read(fd[0], buffer, 1)) > 0)
	{
	  cout << buffer;
	  outputfile << buffer;
	}
      close(fd[0]);
    }
}
