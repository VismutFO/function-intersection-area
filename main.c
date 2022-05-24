#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

#define _GNU_SOURCE


typedef float afunc(float);

float f1(float x);
float f2(float x);
float f3(float x);

float f1d(float x);
float f2d(float x);
float f3d(float x);

int I; // for counting iterations

float root(afunc *f, afunc *g, afunc* fd, afunc* gd, float a, float b, float eps1)
{
	I++;
	float fa = f(a);// метод хорд
	fa -= g(a);
	float fb = f(b);
	fb -= g(b);
	float c = (a * fb - b * fa) / (fb - fa);// [a, c]
	float c2 = a - (f(a) - g(a)) / (fd(a) - gd(a));
	if (c2 < c)
	{
		float temp = c2;
		c2 = c;
		c = temp;
	}
	if (c2 - c < eps1)
	{
		return c;
	}
	else
	{
		return root(f, g, fd, gd, c, c2, eps1);
	}
}

float integral(afunc* f, float a, float b, float eps1)
{
	int N = 16384;
	float res = 0., temp = 0.;
	while (1)
	{
		float h = (b - a) / (float)N;
		temp = 0.;
		for (int i = 0; i <= N; i++)
		{
			temp += h / 3. * f(a + h * i) * ((i == 0 || i == N) ? 1. : ((i % 2) == 0) ? 2. : 4.);
		}
		float z = temp - res;
		if ((z > 0 ? z : -z) < eps1 * 15.)
		{
			return temp > 0 ? temp : -temp;
		}
		res = temp;
		N *= 2;
	}
}

int main(int argc, char* argv[])
{
	float point12, point13, point23;
	afunc* arr[3];
	arr[0] = f1;
	arr[1] = f2;
	arr[2] = f3;
	afunc* arrd[3];
	arrd[0] = f1d;
	arrd[1] = f2d;
	arrd[2] = f3d;
	if (argc > 1)
	{
		const char* short_options = "hriR:I:";

		const struct option long_options[] = {
			{ "help", no_argument, NULL, 'h'},
			{ "root", no_argument, NULL, 'r'},
			{ "iterations", no_argument, NULL, 'i' },
			{ "test-root", required_argument, NULL, 'R' },
			{ "test-integral", required_argument, NULL, 'I' },
			{ NULL, 0, NULL, 0}
		};
		int res;

		int i, j;
		float a, b, e, r;

		while ((res = getopt_long(argc, argv, short_options,
			long_options, &i)) != -1)
		{
			switch (res)
			{
			case 'h':
				printf("-h or --help for flags\n");
				printf("-r or --root to count points\n");
				printf("-i or --iterations to count iterations in func root\n");
				printf("-R or --test-root to test func root(F1:F2:A:B:E:R)\n");
				printf("-I or --test-integral to test func integral(F:A:B:E:R)\n");
				break;
			case 'r':
				point12 = root(f1, f2, f1d, f2d, 4, 6, 0.00001);
				printf("%f\n", point12);
				point13 = root(f1, f3, f1d, f3d, 1, 2, 0.00001);
				printf("%f\n", point13);
				point23 = root(f2, f3, f2d, f3d, 4, 5, 0.00001);
				printf("%f\n", point23);
				break;
			case 'i':
				I = 0;
				root(f1, f2, f1d, f2d, 4, 6, 0.00001);
				printf("%d\n", I);
				I = 0;
				root(f1, f3, f1d, f3d, 1, 2, 0.00001);
				printf("%d\n", I);
				I = 0;
				root(f2, f3, f2d, f3d, 4, 5, 0.00001);
				printf("%d\n", I);
				break;
			case 'R':
				sscanf(optarg, "%d:%d:%f:%f:%f:%f", &i, &j, &a, &b, &e, &r);
				if (i > j)
				{
					int temp = i;
					i = j;
					j = temp;
				}
				float resR = root(arr[i], arr[j], arrd[i], arrd[j], a, b, e);
				float erR = (resR - r > 0 ? resR - r : r - resR);
				printf("%f %f %f\n", resR, erR, erR / r);
				break;
			case 'I':
				sscanf(optarg, "%d:%f:%f:%f:%f", &i, &a, &b, &e, &r);
				float resI = integral(arr[i], a, b, e);
				float erI = (resI - r > 0 ? resI - r : r - resI);
				printf("%f %f %f\n", resI, erI, erI / r);
				break;
			case '?':
			default:
				printf("found unknown option %d %d\n", i, res);
				break;
			}
		}
		return 0;
	}
	point12 = root(f1, f2, f1d, f2d, 4, 6, 0.00001);
	point13 = root(f1, f3, f1d, f3d, 1, 2, 0.00001);
	point23 = root(f2, f3, f2d, f3d, 4, 5, 0.00001);
	float res = integral(f1, point13, point12, 0.00001);
	res -= integral(f2, point23, point12, 0.00001);
	res -= integral(f3, point13, point23, 0.00001);
	printf("%.10f\n", res);
	return 0;
}
