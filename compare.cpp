#include "compare.h"

compare::compare(BI num)
{
	this->n = num;
	this->factoring = factor();
	timing();
	fileout();
}

void compare::emptyVecs()
{
	factoring.dixon_factors.clear();
	factoring.fermat_factors.clear();
	factoring.pollard_factors.clear();
	factoring.trial_factors.clear();
}

void compare::timing()
{
	
	clock_t t = clock();
	for (int i = 0; i < 3; i++)
	{
		emptyVecs();

		factoring.Trial(this->n);
		trial_t += double(clock() - t) / CLOCKS_PER_SEC;
		cout << "The trial division is done\n";

		t = clock();
		factoring.FermatHelper(this->n);
		fermat_t += double(clock() - t) / CLOCKS_PER_SEC;
		cout << "The Fermat method is done\n";

		t = clock();
		factoring.PollardRho(this->n);
		pollard_t += double(clock() - t) / CLOCKS_PER_SEC;
		cout << "The Pollard Rho method is done\n";

		t = clock();
		factoring.Dixon(this->n);
		dixon_t += double(clock() - t) / CLOCKS_PER_SEC;
		cout << "The Dixon method is done\n";
	}
	trial_t /= 3;
	fermat_t /= 3;
	pollard_t /= 3;
	dixon_t /= 3;
}

bool compare::compareResults()
{
	sort(begin(factoring.trial_factors), end(factoring.trial_factors));
	sort(begin(factoring.fermat_factors), end(factoring.fermat_factors));
	sort(begin(factoring.pollard_factors), end(factoring.pollard_factors));
	sort(begin(factoring.dixon_factors), end(factoring.dixon_factors));

	if (factoring.trial_factors == factoring.fermat_factors && factoring.trial_factors == factoring.pollard_factors && factoring.trial_factors == factoring.dixon_factors)
		return true;
	else return false;
}

void compare::fileout()
{
	//fstream f;
	//f.open("factor.txt");
	//if (!compareResults())
	//{
	//	f << "An error occured!";
	//	f.close();
	//	return;
	//}
	//f << "All the metods found the same divisors:\n";
	//for (long long i = 0; i < factoring.dixon_factors.size(); i++) f << factoring.dixon_factors[i] << " ";
	//f << "\n";
	//f << left << setw(25) << "Method name " << "Average time of execution\n";
	//f << left << setw(25) << "Trial division method " << trial_t << "\n";
	//f << left << setw(25) << "Fermat method " << fermat_t << "\n";
	//f << left << setw(25) << "Pollard Rho method " << pollard_t << "\n";
	//f << left << setw(25) << "Dixon method " << dixon_t << "\n";
	//f.close();
	//cout << "The results are in 'factor.txt' file";

	if (!compareResults())
	{
		cout << "An error occured!";
		return;
	}
	cout << "All the methods found the same divisors:\n";
	for (long long i = 0; i < factoring.dixon_factors.size(); i++) cout << factoring.dixon_factors[i] << " ";
	cout << "\n";
	cout << left << setw(25) << "Method name " << "Average time of execution\n";
	cout << left << setw(25) << "Trial division method " << trial_t << "\n";
	cout << left << setw(25) << "Fermat method " << fermat_t << "\n";
	cout << left << setw(25) << "Pollard Rho method " << pollard_t << "\n";
	cout << left << setw(25) << "Dixon method " << dixon_t << "\n";
}
