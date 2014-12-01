#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define		SUCCESS		0
#define		FAILURE		-1

int totalOffset(double offset1, double offset2, double* voltage);
double DerivativeValue(double flux);
double calculateOffset(double* voltage, int decision);

const double EULER = 2.71828182845904523536;
const double COEFFICIENT[2] = { 0.0004096, 0.0005632 };
const double COEFFICIENT1[2] = { 0.016384, 0.022528 };

int main()
{
	int threshold = 1;
	double *voltage, derivative1, derivative2, offset1, offset2;

	voltage = calloc(2,sizeof(double));
	
	while (threshold)
	{
		offset1 = calculateOffset(voltage, 0);
		derivative1 = DerivativeValue(voltage[0], 0);
		offset2 = calculateOffset(voltage, 1);
		derivative2 = DerivativeValue(voltage[1], 1);

		voltage[0] -= offset1 / derivative1;
		voltage[1] -= offset2 / derivative2;
		threshold = totalOffset(offset1, offset2, voltage);
		printf("The voltageA is %lf, B is %lf; OffsetA is %lf, B is %lf\n", voltage[0], voltage[1], offset1, offset2);
	}
	
	return SUCCESS;
}

double DerivativeValue(double voltage, int decision)
{
	double result = 1 + COEFFICIENT1[decision] * pow(EULER, 40 * voltage);
	return result;
}

double calculateOffset(double* voltage, int decision)
{
	double result = voltage[0] + voltage[1] - 0.2 - COEFFICIENT[decision] + COEFFICIENT[decision] * pow(EULER, 40 * voltage[decision]);
	return result;
}

double SecondOrderDerivativeValue(double voltage, int decision)
{
	double result = 40*COEFFICIENT1[decision] * pow(EULER, 40 * voltage);
	return result;
}

int totalOffset(double offset1, double offset2, double* voltage)
{
	int threshold = 0;
	offset1 /= (2 * SecondOrderDerivativeValue(voltage[0], 0));
	offset2 /= (2 * SecondOrderDerivativeValue(voltage[1], 1));
	double result = pow(offset1, 2) + pow(offset2, 2);
	result = sqrt(result);

	if (result > 0.000001)
		threshold = 1;

	return threshold;
}