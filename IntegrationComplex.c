#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define		SUCCESS		0
#define		FAILURE		-1
#define		INITIALPOINT	0
#define		LENGTH	1

double ComplexGauss(double init, double end);

int main()
{
	int loop, SLICENUMBER;
	double real, error, init, end, slice, value;

	real = -2.66616;
	printf("The real integration value is %lf\n", real);
	for (SLICENUMBER = 10; SLICENUMBER <= 10; SLICENUMBER+=10)
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

/* Make n as 3 */
double ComplexGauss(double init, double end)
{
	double result, weight, weight1, offset, offset1, position;

	offset = end - init;
	weight = 4*(end - init)/9;
	weight1 = 2.5*(end-init)/9;
	position = init+offset/2;
	offset1 = 0.774597*offset / 2;

	result = weight*log(0.2*sin(position)) + weight1*log(0.2*sin(position - offset1)) + weight1*log(0.2*sin(position + offset1));

	return result;
}