#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <csignal>
#include <time.h>
#include <rng/gsl_rng.h>

using namespace std;

int pid;

void signalhandler(int signumber)
{
  if (pid == 0)
    {
      cout << "Signal received by child: " << signumber << endl;
      if (signumber == SIGKILL)
	exit(0);
    }
  else
    {
      cout << "Signal received by parent: " << signumber << endl;
      kill(pid, SIGKILL);
      wait();
      cout << "Parent will exit now" << endl;
      exit(0);
    }
}

int main(int argc, char ** argv)
{
  struct timespec halfsecond = {0, 500000000L};
  struct timespec wholesecond = {0, 1000000000L};

  gsl_rng * myrng;
  const gsl_rng_type * rngtype;

  int result;

  pid = fork();

  for (int i = 1; i <= 31; i++)
    {
      signal(i, signalhandler);
    }

  if (pid == 0) // In child process
    {
      while (true)
	{
	  cout << "Child waiting" << endl;
	  nanosleep(&halfsecond, NULL);
	}
    }
  else // In parent process
    {
      gsl_rng_env_setup();

      rngtype = gsl_rng_default;
      myrng = gsl_rng_alloc (rngtype);

      gsl_rng_set(myrng, (getpid() * 1000)); // seeding with PID*1000 for better accuracy

      nanosleep(&wholesecond, NULL);
      while (true)
	{
	  result = (gsl_rng_uniform_int (myrng, 30) + 1);
	  cout << "Parent sending signal " << result << endl;
	  kill(pid, result);
	  nanosleep(&halfsecond, NULL);
	}

      gsl_rng_free (myrng);

    }
  return 0;
}
