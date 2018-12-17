#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
  if (argc != 2)
    {
      cerr << "Invalid number of parameters entered.\nUsage: Bonus3 (number to catagorize)" << endl;
      exit(1);
    }
  
  int x = atoi(argv[1]);

  if (x <= 2)
    {
      cerr << "Invalid number entered. Must enter a number greater than 2" << endl;
      exit(1);
    }

  int sum = 0;

  for (int i = 1; i < x; i++)
    {
      if ((x % i) == 0)
	sum += i;
    }
  if (sum == x)
    cout << x << " is a perfect number" << endl;
  else if (sum < x)
    cout << x << " is a deficient number by " << (x - sum) << endl;
  else
    cout << x << " is an abundant number by " << (sum - x) << endl;
}
