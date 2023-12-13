// Lab 4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

double* Gauss(double** Array_A, double* Array_B, int n);

int main()
{
	setlocale(LC_ALL, "rus");
	const int N = 10;
	const int m = 2;
	double x[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	double y[11] = { 3, 87, 156, 210, 238, 252, 239, 211, 158, 90, -5 };
	double* POWERX = new double[2 * m];
	cout << "POWERX: ";
	for (int k = 0; k < 2 * m; k++)
	{
		POWERX[k] = 0;
		for (int i = 0; i < N; i++)
		{
			POWERX[k] += pow(x[i], k + 1);
		}
	}
	cout << POWERX << endl;

	double** SUMX = new double* [m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		SUMX[i] = new double[m + 1];
	}
	for (int l = 0; l < m + 1; l++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			if (j + l)
			{
				SUMX[l][j] = POWERX[l + j - 1];
			}
			else
			{
				SUMX[l][j] = N;
			}
		}
	}
	double* PRAW = new double[m + 1];
	for (int l = 0; l < m + 1; l++)
	{
		PRAW[l] = 0;
		for (int i = 0; i < N; i++)
		{
			PRAW[l] += y[i] * pow(x[i], l);
		}
	}
	double* a = Gauss(SUMX, PRAW, m + 1);
	double S2 = 0;
	for (int i = 0; i < N; i++)
	{
		double sum = y[i];
		for (int j = 0; j < m + 1; j++)
		{
			sum -= a[j] * pow(x[i], j);
		}
		S2 += pow(sum, 2);
	}
	S2 /= N - m - 1;
	double sigma = sqrt(S2);
	cout << "Коэфициенты a: " << endl;
	for (int i = 0; i < m + 1; i++)
	{
		cout << a[i] << " ";
	}
	cout << "\nCреднеквадратическое отклонение: " << sigma << endl;
	return 0;
}

double* Gauss(double** A, double* b, int n)
{
	double* X = new double[n];  //массив ответов
	for (int i = 0; i < n; i++) // прямой ход
	{
		for (int j = i + 1; j < n; j++)
		{
			if (abs(A[j][i]) > abs(A[i][i]))
			{
				swap(A[j], A[i]);  //меняются адреса т.к. двумерный массив
				swap(b[j], b[i]);   //меняются значени¤
			}
		}
		double A_Main = A[i][i];
		if (A_Main == 0)
		{
			cout << "error\n";
			system("pause");
			exit(0);
		}
		for (int j = i; j < n; j++)
		{
			A[i][j] /= A_Main;
		}
		b[i] /= A_Main;
		for (int j = i + 1; j < n; j++)
		{
			double s = A[j][i];
			for (int k = i; k < n; k++)
			{
				A[j][k] -= s * A[j][k];
			}
			b[j] -= s * b[i];
		}
	}
	for (int k = n - 1; k >= 0; k--)  //обратный ход
	{
		X[k] = b[k];
		for (int i = n - 1; i > k; i--)
		{
			X[k] -= A[k][i] * X[i];
		}
	}
	return X;
}