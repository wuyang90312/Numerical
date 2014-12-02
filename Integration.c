#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define		SUCCESS		0
#define		FAILURE		-1
#define		INITIALPOINT	0
#define		LENGTH	1

double OnePointGauss(double init, double end);

int main()
{
	int loop, SLICENUMBER;
	double real, error, init, end, slice, value;

	real = cos(0) - cos(1);
	//printf("The real integration value is %lf\n", real);
	for (SLICENUMBER = 1; SLICENUMBER <= 20; SLICENUMBER++)
	{
		value = 0;
		slice = (double)LENGTH / SLICENUMBER;
		for (loop = 0; loop < SLICENUMBER; loop++)
		{
			init = INITIALPOINT + slice*loop;
			end = init + slice;
			value += OnePointGauss(init, end);
		}
		error = value - real;
		if (error < 0)
			error = -error;
		//printf("%d slices: The integration value is %lf  with error %.12lf\n", SLICENUMBER, value, error);
		//printf("%.12lf\n", log10(error));
		printf("%lf\n", log10(SLICENUMBER));
	}
	

	return SUCCESS;
}

double OnePointGauss(double init, double end)
{
	double result, weight, position;

	weight = end - init;
	position = (pow(end, 2) - pow(init, 2)) / (2 * weight);

	result = weight*sin(position);

	return result;
}