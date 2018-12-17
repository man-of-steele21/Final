#include <iostream>
#include <math.h>
#include <iomanip>
#include <gsl_sf_gamma.h>
#include <gsl_sf_log.h>

using namespace std;

long double factorial(int a)
{
  long double fact = 1.0;

  for (int i = 1; i <= a; i++)
    {
      fact = fact*(long double)i;
    }
  return fact;
}

int main()
{
  long double LN, Stirling, Error, ErrorPercent, e;
  int FirstN = -1;
  
  cout << "N\tln(Factorial)\t\tStirling's Formula\tError\t\tError Percent" << endl;

  e = exp(1.0);

  // cout << "e = " << e << endl;

  for (int i = 1; i <= 100; i++)
    {
      // Natural Log Factorial
      LN = (gsl_sf_log(gsl_sf_fact(i))/gsl_sf_log(e));
      cout << i << "\t" << scientific << setprecision(6) << LN;

      // Stirling
      Stirling = (i*gsl_sf_log(i)/gsl_sf_log(e) - i);
      cout << "\t\t" << Stirling; 

      Error = fabs(LN - Stirling);
      ErrorPercent = fabs(Error/Stirling);
      cout << "\t\t" << Error << "\t" << ErrorPercent << endl;

      if ((ErrorPercent < 0.001) && (FirstN == -1))
	  FirstN = i;
    }

  
  // Used math.h to compute the value of N at which Stirling's approximation is within 0.1% of the exact result
  for (int i = 1; i <= 1000; i++)
    {
      // Natural Log Factorial
      LN = (logl(factorial(i))/logl(e));

      // Stirling
      Stirling = (i*logl(i)/logl(e) - i); 

      Error = fabsl(LN - Stirling);
      ErrorPercent = fabsl(Error/Stirling);

      if ((ErrorPercent < 0.001) && (FirstN == -1))
	  FirstN = i;
    }

  cout << "Value of N at which Stirling's approximation is within 0.1%: " << FirstN << endl;

  return 0;
}
