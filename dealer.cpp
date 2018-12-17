// Final-Problem2
// dealer.cpp
// Jackson Steele

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char ** argv)
 {
   bool verbose = false;
   int percent;
   int numtrials;
   int result;

   pid_t pid;

   int numsuccesses = 0;
   int numfailures = 0;

   float successes, failures;

   int index;
   int c;

   ofstream outputfile;
   string outfilename;

  opterr = 0;

  if (argc == 1)
    {
      cerr << "Invalid number of parameters entered.\nUsage: dealer -p (0-100) [-v] (number of trials desired)" << endl;
      return 1;
    }

  while ((c = getopt(argc, argv, "p:vo:")) != -1)
    switch (c)
      {
      case 'p':
        percent = atoi(optarg);
	if (percent > 100 || percent < 0)
	  {
	    cerr << "Invalid percentage entered (valid: 0-100)." << endl;
	    return 1;
	  }
	else if (percent == 0 && optarg[0] != '0')
	  {
	    cerr << "Non-digit entered for percentage (valid: 0-100)." << endl;
	    return 1;
	  }
        break;
      case 'v':
        verbose = true;
        break;
      case 'o':
	outfilename = optarg;
	break;
      case '?':
        if (optopt == 'p')
          cerr << "Option " << char(optopt) << " requires an argument." << endl;
        else
          cerr << "Unknown option " << char(optopt) << endl;
	return 1;
      default:
        abort ();
      }

  if (optind < argc)
      numtrials = atoi(argv[optind]);
  else
    {
      cerr << "The last parameter should be the number of desired iterations." << endl;
      return 1;
    }

  for (int i = 0; i < numtrials; i++)
   {
     if ((pid = fork()) == 0)
       execvp("./hand", argv);
     else
     {
       waitpid(pid, &result, 0);
       if (WEXITSTATUS(result) == 1)
	 {
	   numsuccesses++;
	   if (verbose)
	     cout << "PID " << pid << " returned Success" << endl;
	 }
       else
	 {
	   numfailures++;
	   if (verbose)
	     cout << "PID " << pid << " returned Failure" << endl;
	 }
     }
   }
   cout << endl << endl << "Created " << numtrials << " processes." << endl;
   successes = (float)numsuccesses*100/(float)numtrials;
   failures = (float)numfailures*100/(float)numtrials;
   cout << "Success - " << fixed << setprecision(1) << successes << "%" << endl;
   cout << "Failure - " << fixed << setprecision(1) << failures << "%" << endl;
   cout << endl << "Results were written to " << outfilename << endl << endl;

   outputfile.open(outfilename, ios::out | ios::app | ios::binary);
   if (!outputfile.is_open())
     {
       cerr << "Error: File did not open." << endl;
       return 1;
     }
   outputfile.write((char*)&percent, sizeof(percent));
   outputfile.write((char*)&numtrials, sizeof(numtrials));
   outputfile.write((char*)&successes, sizeof(successes));
   outputfile.write((char*)&failures, sizeof(failures));
   outputfile.close();
}
