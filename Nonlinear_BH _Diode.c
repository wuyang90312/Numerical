#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define		SUCCESS		0
#define		FAILURE		-1

int totalOffset(double offset1, double offset2);
double calcualteConstant(double derivative);
double DerivativeValue(double flux);
double calculateOffset(double* voltage, int decision);

const double EULER = 2.71828182845904523536;
const double COEFFICIENT[2] = { 0.0004096, 0.0005632 };
const double COEFFICIENT1[2] = { 0.016384, 0.022528 };

int main()
{
	int threshold = 1;
	double *voltage, derivative1, derivative2, offset1, offset2, c1, c2, oldV1, oldV2;

	voltage = calloc(2, sizeof(double));

	double V1 = 0.094946, V2 = 0.087194;
	while (threshold)
	{
		oldV1 = V1 - voltage[0];
		oldV2 = V2 - voltage[1];
		offset1 = calculateOffset(voltage, 0);
		derivative1 = DerivativeValue(voltage[0], 0);
		offset2 = calculateOffset(voltage, 1);
		derivative2 = DerivativeValue(voltage[1], 1);

		voltage[0] -= offset1 / derivative1;
		voltage[1] -= offset2 / derivative2;
		threshold = totalOffset(offset1, offset2, voltage);
		c1 = calcualteConstant(derivative1);
		c2 = calcualteConstant(derivative2);
		V1 = sqrt(pow(V1 - voltage[0], 2) + pow(V2 - voltage[1], 2));
		oldV1 = sqrt(pow(c1*oldV1*oldV1, 2) + pow(c2*oldV2*oldV2, 2));
		//printf("e(k+1) : [%.12lf]; c*e^2  < [%.12lf] = %s\n", V1, oldV1, (V1 < oldV1) ? "TRUE" : "FALSE");
		printf("The voltageA is %lf, B is %lf; OffsetA is %lf, B is %lf\n", voltage[0], voltage[1], offset1, offset2);
	}

	return SUCCESS;
}

double calcualteConstant(double derivative)
{
	double result, secDeriv = (derivative - 1) * 40;

	result = (1.000001)*pow(secDeriv / derivative, 2) / 2;
	return result;
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

int totalOffset(double offset1, double offset2)
{
	int threshold = 0;
	double result = pow(offset1, 2) + pow(offset2, 2);
	result = sqrt(result);

	if (result > 0.000001)
		threshold = 1;

	return threshold;
}