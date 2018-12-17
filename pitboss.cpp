// Final-Problem2
// pitboss.cpp
// Jackson Steele

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char ** argv)
 {
   bool foundpercent = false;
   
   int percent;
   int numtrials;
   int result;

   float successes, failures;

   char c;
   
   ifstream inputfile;
   string infilename;

   opterr = 0;

    if (argc == 1)
    {
      cerr << "Invalid number of parameters entered.\nUsage: pitboss -p (0-100) (name of output file)" << endl;
      return 1;
    }

  while ((c = getopt(argc, argv, "p:")) != -1)
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
      infilename = argv[optind];
  else
    {
      cerr << "The last parameter should be the name of the desired input file." << endl;
      return 1;
    }

  int inpercent;

  inputfile.open(infilename, ios::in | ios::binary);

  if (!inputfile.is_open())
    {
      cerr << "Error: File did not open." << endl;
      return 1;
    }

  cout << endl << "Reading results from " << infilename << " ..." << endl << endl;

  cout << "Checking results for -p = " << percent << " ..." << endl << endl;

  while (!inputfile.eof() && !foundpercent)
    {
      inputfile.read((char*)&inpercent, sizeof(inpercent));
      inputfile.read((char*)&numtrials, sizeof(numtrials));
      inputfile.read((char*)&successes, sizeof(successes));
      inputfile.read((char*)&failures, sizeof(failures));

      if (inpercent == percent)
	{
	  cout << "Found " << numtrials << " trials." << endl << endl;
	  cout << "Success - " << (int) successes << "%" << endl;
	  cout << "Failure - " << (int) failures << "%" << endl << endl;
	  foundpercent = true;
	}
    }
  if (!foundpercent)
    {
      cerr << "Error: Selected percent not found" << endl;
      return 1;
    }

  inputfile.close();
  
 }
