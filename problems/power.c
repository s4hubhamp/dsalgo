#include <stdio.h>
#include <math.h>

long long power(int, int);

int main()
{
    int a, n;
    printf("Enter A(base): ");
    scanf("%d", &a);
    printf("Enter n(exponent):");
    scanf("%d", &n);

    printf("Result of %d raised to %d is: %lld\n", n, a, power(a, n));
}

long long power(int a, int n)
{
    if (n == 0)
    {
        return 1;
    }

    long long x = power(a, floor(n / 2));
    if (n % 2)
    {
        return x * x * a;
    }
    else
    {
        return x * x;
    }
}
