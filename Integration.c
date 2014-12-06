#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define		SUCCESS		0
#define		FAILURE		-1
#define		INITIALPOINT	0
#define		LENGTH	1
const double EULER_NUMBER = 2.7182818285;

double OnePointGauss(double init, double end);
double retrieveX(double y);
double totalHeight();

int main()
{
	int loop, SLICENUMBER;
	double real, error, init, end, slice, value, height;

	real = -1;
	
	//printf("The real integration value is %lf\n", real);
	for (SLICENUMBER = 10; SLICENUMBER <= 10; SLICENUMBER+=10)
	{
		value = 0;
		height = log(sin(0.001));
		end = INITIALPOINT;
		slice = totalHeight() / SLICENUMBER;;
		for (loop = 0; loop < SLICENUMBER; loop++)
		{
			init = end;
			height += slice;
			end = retrieveX(height);
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

	result = weight*log(sin(position));

	return result;
}

double totalHeight(){
	double result = 0;

	/*Since all equations we are using is increasing*/
	result = log(sin(LENGTH)) - log(sin(0.001));
	return result;
}

double retrieveX(double y)
{
	double result = asin(pow(EULER_NUMBER, y));

	return result;
}