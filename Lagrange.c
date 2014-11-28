#include <stdio.h>
#include <stdlib.h>

#define		SUCCESS		0
#define		FAILURE		-1

static const double X_COORD[6] = { 0, 0.2, 0.4, 0.6, 0.8, 1.0 };
static const double Y_COORD[6] = { 0, 14.7, 36.5, 71.7, 121.4, 197.4 };

//static const double X_COORD[6] = { 0, 1.3, 1.4, 1.7, 1.8, 1.9 };
//static const double Y_COORD[6] = { 0, 540.6, 1062.8, 8687.4, 13924.3, 22650.2 };

double CoefficientCalculation(int index);
void fillItem(int index, double* target);
double	combinationCalculation(int depth, int location, double* input);

int main()
{
	int empty,loop, loop1, depth;
	double sum, tmp, coefficient, *constant;
	double item[6] = {0,0,0,0,0,0};

	constant = malloc(5 * sizeof(double));

	for (empty = 0; empty < 6; empty++)
	{
		coefficient = CoefficientCalculation(empty);
		fillItem(empty, constant); /* Withdraw a cell out of the array */

		/* Add coefficient of each order to the array */
		for (loop = 0; loop < 6; loop++)
		{
			sum = 0;

			if (loop == 0)
				depth = 0;
			else
				depth = 5 - loop;

			for (loop1 = 0; loop1 <= depth; loop1++)
			{
				sum += combinationCalculation(loop, loop1, constant);
			}
			item[loop] += sum*coefficient;
		//	printf("\n");
		}
	}

	printf("Polynomial is:\n%fX^5 + %fX^4 + %fX^3 + %fX^2 + %fX +%f", item[0], item[1], item[2], item[3], item[4], item[5]);
	return SUCCESS;
}

/* calculate the result of  Y_j/((X_j - X_1)(X_j - X_2)...(X_j - X_n)) */
double CoefficientCalculation(int index)
{
	int loop = 5;
	double result = 1;

	for (; loop >= 0; loop--)
	{
		if (loop == index)
			result *= Y_COORD[loop];
		else
			result /= (X_COORD[index] - X_COORD[loop]);
	}
	return result;
}

void fillItem(int index, double* target)
{
	int loop, count = 0;

	for (loop = 0; loop < 6; loop++)
	{
		if (loop == index)
			continue;
		else
		{
			target[count] = -X_COORD[loop];
			count++;
		}
	}
}
double	combinationCalculation(int depth, int location, double* input)
{
	int loop;
	double result, sum = 0;

	if (depth == 0)
		return 1;

	if (input[location] == 0)
	{
		return 0;
	}
	
	result = input[location];
	depth--;
	if (depth == 0)
	{
		return result;
	}		
	else
	{
		for (loop = location + 1; loop < 5; loop++)
		{
			if (depth + loop <= 5)
			{
				sum += combinationCalculation(depth, loop, input);
			}
			else
				break;
		}
	}		
	result *= sum;

	return result;
}