#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define		SUCCESS					0
#define		FAILURE					-1
#define		POLYNOMIAL_DEPTH		3

static const double X_COORD[6] = { 0, 1.3, 1.4, 1.7, 1.8, 1.9 };
static const double Y_COORD[6] = { 0, 540.6, 1062.8, 8687.4, 13924.3, 22650.2 };

void differentaition(double* derivative);
void fillItem(double a, double b, double c, double* target);
double	combinationCalculation(int depth, int location, double* input);
void polynomialGeneration(double* item, double* constant, double coefficient);
void cleanUp(int length, double* target);
double realizePolynomial(double variable, double* equation);

int main()
{
	int		loop, iteration = 0;
	double *derivative, a1, b1, a2, b2,x1,x2, coefficient, *equation, delta;
	double item[6] = { 0, 0, 0, 0, 0, 0 }, constant[3] = {0, 0, 0};

	derivative = malloc(6*sizeof(double)); /* Declare the memory location for the derviative value of each point*/
	equation = calloc(4, sizeof(double)); /* Declare the memory location for the polynomial */
	differentaition(derivative); /* Put all derivatives into the array */
	
	for (iteration = 0; iteration < 5; iteration++)
	{
		/* Obtain the coefficient from Y and derivative */
		a1 = Y_COORD[iteration];
		a2 = Y_COORD[iteration + 1];
		b1 = derivative[iteration];
		b2 = derivative[iteration + 1];
		x1 = X_COORD[iteration];
		x2 = X_COORD[iteration + 1];

		/* Get the value of the constant */
		coefficient = 1 / pow(x1 - x2, 2);
		/* Get the coefficient of V_1 */
		fillItem(x1, x2, x2, constant);
		polynomialGeneration(equation, constant, b1*coefficient);
		/* Get the coefficient of V_2 */
		fillItem(x1, x1, x2, constant);
		polynomialGeneration(equation, constant, b2*coefficient);
		/* Get the coefficient of U_1 */
		fillItem((3 * x1 - x2) / 2, x2, x2, constant);
		coefficient = -2.0 / pow(x1 - x2, 3);
		polynomialGeneration(equation, constant, a1*coefficient);
		/* Get the coefficient of U_2 */
		fillItem((3 * x2 - x1) / 2, x1, x1, constant);
		coefficient = -2.0 / pow(x2 - x1, 3);
		polynomialGeneration(equation, constant, a2*coefficient);
		printf("Polynomial in subdomain [%lf, %lf] is:\n%fX^3 + %fX^2 + %fX +%f\n", 
		x1, x2, equation[0], equation[1], equation[2], equation[3]);
		printf("The starting point is %lf, the end point is %lf\n",
		realizePolynomial(x1, equation),realizePolynomial(x2, equation));
		printf("The derivative is %fX^2 + %fX +%f\n", 3*equation[0], 2*equation[1], equation[2]);
		delta = pow(2 * equation[1], 2) - 4 * (3 * equation[0])*equation[2];
		printf("The delta is %lf\n", delta);
		if (delta > 0)
		{
			printf("Two solution points: %lf, %lf\n", 
			(-2 * equation[1] - sqrt(delta) )/ (6 * equation[0]), 
			(-2 * equation[1] + sqrt(delta)) / (6 * equation[0]));
		}
		printf("\n");
		cleanUp(3, equation);
	}

	return SUCCESS;
}

double realizePolynomial(double variable, double* equation)
{
	int loop;
	double result = 0;

	for (loop = POLYNOMIAL_DEPTH; loop >= 0; loop--)
		result += equation[POLYNOMIAL_DEPTH-loop] * pow(variable, loop);
	return result;
}

/* Give the derivative values of 6 points */
void differentaition(double* target)
{
	int loop;

	for (loop = 0; loop < 6; loop++)
	{
		if (loop == 0) /* If the point locates at either end, calculate the derivative based on a adjacent point and itself */
			target[loop] = (Y_COORD[1]-Y_COORD[0]) / (X_COORD[1] - X_COORD[0]);
		else if (loop == 5)
			target[loop] = (Y_COORD[5] - Y_COORD[4]) / (X_COORD[5] - X_COORD[4]);
		else /* otherwise, calculate the derivative based on both adjacent points */
			target[loop] = (Y_COORD[loop + 1] - Y_COORD[loop - 1]) / (X_COORD[loop + 1] - X_COORD[loop - 1]);
	}
}

/* Clean up all of the cells */
void cleanUp(int length, double* target)
{
	for (; length >= 0; length--)
		target[length] = 0;
}

void fillItem(double a, double b, double c, double* target)
{
	target[0] = -a;
	target[1] = -b;
	target[2] = -c;

}

double	combinationCalculation(int depth, int location, double* input)
{
	int loop;
	double result, sum = 0;

	if (depth == 0)
		return 1;

	if (input[location] == 0)
		return 0;
	
	result = input[location];
	depth--;
	if (depth == 0)
		return result;		
	else
	{
		for (loop = location + 1; loop < POLYNOMIAL_DEPTH; loop++)
		{
			if (depth + loop <= POLYNOMIAL_DEPTH)
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

void polynomialGeneration(double* item, double* constant, double coefficient)
{
	int loop, depth, loop1;
	double sum;

	/* Add coefficient of each order to the array */
	for (loop = 0; loop <= POLYNOMIAL_DEPTH; loop++)
	{
		sum = 0;

		if (loop == 0)
			depth = 0;
		else
			depth = POLYNOMIAL_DEPTH - loop;

		for (loop1 = 0; loop1 <= depth; loop1++)
		{
			sum += combinationCalculation(loop, loop1, constant);
		}
		item[loop] += sum*coefficient;
	}
}
