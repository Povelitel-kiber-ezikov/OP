#define _CRT_SECURE_NO_WARNINGS

#include <locale.h>
#include <stdio.h>
#include <math.h>




int main()
{
	setlocale(LC_ALL, "Rus");


	
	double a, k, p, z;
	int i , b , c;
	
	//задаем натуральное число
	int x;
	printf("x = ");
	scanf("%d", &x);
	
	//задаем степень
	int n;
	printf("n = ");
	scanf("%d", &n);

	//задаем точность
	double E;
	printf("E = ");
	scanf("%lf", &E);

	
	//находим первое число
	for (i = 1; i < x; i++)
	{
		int k = pow(i, n);
		if (k < x )
		{
			b = i;
			
		}
	}

	//находим второе число
	for (i = 1; i <  x; i++)
	{
		int k = pow(i, n);
		if (k > x)
		{
			c = i;
			break;
		}
	}
	
	//вычисляем а0
	a = double(b + c) / 2;
	
	
	
	//вычисляем корень
	
	
	do {
		
		k = (((n - 1) * a + (x / pow(a, n - 1)))) / n;
		//printf("%.16lf \n", k);
		
		 p = a; // a i
		
		a = k; // a i+1

	} 
	while (fabs(a - p) > E);
	
	
	
	
	
	
	
	printf("k = %.16lf", k);
	return 0;
}
