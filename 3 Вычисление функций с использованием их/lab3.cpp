#include <iostream>
#include <cmath>

//SN- значение суммы для заданного n
double sn(double x, int n)
{
	double sum = x;

	for (int i = 1; i <= n; i++)
	{
		int val = 4 * i + 1;
		sum += pow(x, val) / val;
	}

	return sum;
}

//SE - значение суммы для заданной точности
double se(double x, double e)
{
	double s = x;
	int n = 1;
	double x_calc;
	do
	{
		int val = 4 * n + 1;
		x_calc = pow(x, val) / val;
		s += x_calc;
		n++;
		
	} while (x_calc > e);

	return s;
}

//Y-точное значение функции
double y(double x)
{
	double logX = (x + 1.0) / (x - 1.0);
	if (logX < 0)
	{
		// у отричательного ln найти нельзя
		return NULL;
	}

	return (0.25 * log(logX) + 0.5 * atan(x));
}


int main() {
	//Функция уснавливает локаль(русские буквы) консоли
	setlocale(0, "");
	int n = 3;
	const int i_max = 11;
	double x_all[i_max] = { 0.1, 0.17, 0.24, 0.31, 0.38, 0.45, 0.52, 0.59, 0.66, 0.73, 0.8 };
	double e = 0.0001;


	for (int i = 0; i < i_max; i++)
	{
		double yy = y(x_all[i]);
		std::cout << "X=" << x_all[i] << "	SN=" << sn(x_all[i], n) << "	SE=" << se(x_all[i], e) <<	"	Y=";
		if (yy == NULL) {
			std::cout << "нельзя посчитать";
		}
		else
		{
			std::cout << yy;
		}
		std::cout << "\n";
	}

	return 0;
}