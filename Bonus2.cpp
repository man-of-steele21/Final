#include <iostream>

using namespace std;

bool IsPrime(int number)
  {
    if(number < 2) return false;
    if(number == 2) return true;
    if(number % 2 == 0) return false;

    for(int i=3; (i*i)<=number; i+=2)
        if(number % i == 0 ) return false;

    return true;
  }

int main()
{
  cout << "1, 2, 3, 4, 5";

  bool NotUgly;

  for (int i = 6; i < 10000; i++)
    {
      NotUgly = false;
      if (!IsPrime(i))
	{
	  if ((i % 2) || (i % 3) || (i % 5))
	    for (int j = 6; j < i; j++)
		if (IsPrime(j))
		    if ((i % j) == 0)
		      NotUgly = true;
	}

      else
	NotUgly = true;

      if (!NotUgly)
	  cout << ", " << i;
    }

  cout << endl;

  return 0;
}
