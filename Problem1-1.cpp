#include <iostream>
#include <math.h>
#include <iomanip>
#include <unistd.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <ctime>

#define _USE_MATH_DEFINES

using namespace std;

int main(int argc, char **argv)
{

  long count = 0;
  float x, y, z, dev, err, res;
  gsl_rng * myrng;

  long trials = 0;

  const gsl_rng_type * rngtype;

  time_t beg = time(0);
  time_t end = (beg + 100);
  time_t curr;

  gsl_rng_env_setup();

  rngtype = gsl_rng_default;
  myrng = gsl_rng_alloc (rngtype);

  gsl_rng_set(myrng, (getpid() * 1000)); // seeding with PID*1000 for better accuracy

  for (trials = 0; time(0) < end; trials++)
    {
      x = gsl_rng_uniform (myrng);
      y = gsl_rng_uniform (myrng);
      z = sqrt(pow(x, 2) + pow(y, 2));
      if (z < 1)
	count++;
    }

  gsl_rng_free (myrng);

  res = 4*(float)count/(float)trials;

  dev = fabs(res-M_PI);

  err = dev/M_PI*100;
 
  cout << "Number of points ran: " << trials << endl;
  cout << "Result: " << fixed << setprecision(5) << res << endl;
  cout << "Deviation: " << fixed << setprecision(5) << dev << endl;
  cout << "Percent error: " << fixed << setprecision(5) << err << endl;

  return 0;
}
