#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define		SUCCESS		0
#define		FAILURE		-1
#define		CROSS_SECTION_AREA	0.0001
#define		INITIAL_OFFSET		8000

static const double B_COORD[15] = { 0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9 };
static const double H_COORD[15] = { 0, 14.7, 36.5, 71.7, 121.4, 197.4, 256.2, 348.7, 540.6, 1062.8, 2318, 4781, 8687.4, 13924.3, 22650.2 };
static const double DERIVATIVE[14] = { 73.5, 109, 176, 248.5, 380, 588, 925, 1919, 5222, 12552, 24630, 39064, 52369, 87259};

double DerivativeValue(double flux);
double calculateRatio(double input);
double calculateField(double flux);

int main()
{
	int loop;
	double ratio, derivative, field = 0, flux = 0, offset;
	
	offset = -INITIAL_OFFSET;
	ratio = calculateRatio(offset);

	while (ratio >= 0.000001)
	{
		derivative = DerivativeValue(flux);
		if ( derivative == -1)
		{
			printf("ERROR: OUT OF RANGE OF BH TABLE\n");
			return FAILURE;
		}
		flux -= offset / (2.8373*pow(10, 9) + 50 * derivative);
		field = calculateField(flux);
		offset = 2.3873* pow(10, 9) *flux + 5 * pow(10, -3) * field - 8000;
		ratio = calculateRatio(offset);
		printf("The ratio is %lf, offset is %lf,The flux is %.8lf, the field is %lf, the derivative is %lf\n", ratio, offset, flux, field, derivative);
	}

	printf("The ratio is %12lf, The flux is %.8lf", ratio, flux);
	return SUCCESS;
}

double DerivativeValue(double flux)
{
	int index;
	double result, density = flux / CROSS_SECTION_AREA;

	if (density < 0)
		density = -density;

	if (density >= 0 && density < 1)
	{
		index = floor(density / 0.2);
		result = 1 / DERIVATIVE[index];
	}
	else if (density >= 1 && density < 1.9)
	{
		index = 5 + floor((density - 1) / 0.1);
		result = 1/DERIVATIVE[index];
	}
	else
		result = -1;
	return result;
}

double calculateField(double flux)
{
	int index;
	double field = 0, density = flux / CROSS_SECTION_AREA;

	if (density < 0)
		density = -density;

	if (density >= 0 && density < 1)
	{
		index = floor(density / 0.2);
		field = H_COORD[index] + (density - B_COORD[index])*DERIVATIVE[index];
	}
	else if (density >= 1 && density <= 1.9)
	{
		index = 5 + floor((density - 1) / 0.1);
		field = H_COORD[index] + (density - B_COORD[index])*DERIVATIVE[index];
	}
	else
		field = -1;

	return field;
}

double calculateRatio(double input)
{
	double result = input / INITIAL_OFFSET;
	if (result < 0)
		result = -result;
	return result;
}