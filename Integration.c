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

	real = -2.66616;
	//printf("The real integration value is %lf\n", real);
	for (SLICENUMBER = 10; SLICENUMBER <= 200; SLICENUMBER+=10)
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
		printf("%d slices: The integration value is %lf  with error %.12lf\n", SLICENUMBER, value, error);
		//printf("%.12lf\n", log10(error));
		//printf("%lf\n", log10(SLICENUMBER));
	}
	

	return SUCCESS;
}

double OnePointGauss(double init, double end)
{
	double result, weight, position;

	weight = end - init;
	position = (pow(end, 2) - pow(init, 2)) / (2 * weight);

	result = weight*log(0.2*sin(position));

	return result;
}