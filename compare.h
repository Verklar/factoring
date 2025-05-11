#pragma once
#include<ctime>
#include<fstream>
#include "factor.h"
class compare
{
	BI n = 1;
	factor factoring;
	double trial_t = 0, fermat_t = 0, pollard_t = 0, dixon_t = 0;
public:
	void emptyVecs();
	compare(BI num);
	void timing();
	bool compareResults();
	bool check();
	void fileout();
};

