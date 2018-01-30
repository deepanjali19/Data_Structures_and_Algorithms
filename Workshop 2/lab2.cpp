unsigned int factorial (unsigned int n)
        {
        unsigned int final;

        if(n == 0 || n == 1)
        {
        final = 1;
        }
        else
        {
        final = n * (factorial(n-1));
        } 

        return final;
        }

double power (double base, unsigned int n)
        {
        double final;

        if(n == 1)
        {
        final = base;
        }
        else if(n == 0)
        {
        final = 1;
        }
        else
        {
        final = base * power(base,n-1);
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
        unsigned final = fibonacci(n-1) + fibonacci(n-2);

        return final;
        }
}

