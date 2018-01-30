unsigned int factorial (unsigned int n)
{
	unsigned int final = 1;

	for(unsigned int i = n; i > 0; i--)
	{
		final *= i;
	}

	return final;
}

double power (double base, unsigned int n)
{
	double final = 1;
	
	if(n > 0)
	{
		for(unsigned int i = 0; i < n; i++)
		{
		final *= base;
		}	
	}

	return final;
}

unsigned int fibonacci (unsigned int n)
{
	if(n == 0 || n == 1)
	{
	return n;
	}
	else
	{
	unsigned int f0 = 0;

	unsigned int f1 = 1;

	unsigned int next;

	for(int i = 1; i < n ; i++)
	{
	next = f0 + f1;

	f0 = f1;

	f1 = next;
	}

	return next;
	}	
}
