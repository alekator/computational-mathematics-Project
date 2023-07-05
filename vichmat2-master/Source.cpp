#include <iostream>
#include <fstream>
using namespace std;
const int N = 4;
//нахождение детерминанта
float Det(int G, double M[4][4])
{
	if (G == 1)
		return M[0][0];
	else
	{
		double M1[4][4];
		int i, x, X, Y;
		float Res = 0;
		for (i = 0; i < G; i++)
		{
			for (Y = 1; Y < G; Y++)
			{
				x = 0;
				for (X = 0; X < G; X++)
					if (X != i)
						M1[Y - 1][x++] = M[Y][X];
			}
			if (i % 2 == 0)
				Res += M[0][i] * Det(G - 1, M1);
			else
				Res -= M[0][i] * Det(G - 1, M1);
		}
		return Res;
	}
}
//создание матрицы и нахождение  детерминанта 
int podstanovka(int k, double M[4][4], double A[4][4], double B[4])
{
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			M[i][j] = A[i][j];
		}
	for (i = 0; i < N; i++)             //подстановка
	{                       //
						//
		M[i][k] = B[i];             //
	}                       //
	float Opr = Det(4, M);
	return Opr;
}
void vyvod(double V[4][4])
{
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			if (j == 0) printf("\n");
			else printf("\t");
			printf("%7.0f", V[i][j]);
		}
	printf("\n");
}
int f1()
{
	double A[4][4] = {
			{3,12,-1,0},
			{-5,2,0,32},
			{2,0,16,-3},
			{12,3,0,0} };

	double B[4] = { 18,-15,0,21 };

	//Вывод на экран исходной матрицы
	printf("\nOutput of the original matrix");
	vyvod(A);

	//------Нахождение определителя исходной матрицы--------------------------- 
	printf("\nDerivation of the determinant of the original matrix\n");
	float Op = Det(4, A);
	printf("Determinant = %7.0f\n", Op);
	//------------------------------------------------------------------------- 

	//***********************************
		//действия над новыми матрицами
	double M1[N][N];
	float Op1 = podstanovka(0, M1, A, B);
	printf("Determinant 1 = %7.0f\n", Op1);

	double M2[N][N];
	float Op2 = podstanovka(1, M2, A, B);
	printf("Determinant 2 = %7.0f\n", Op2);

	double M3[N][N];
	float Op3 = podstanovka(2, M3, A, B);
	printf("Determinant 3 = %7.0f\n", Op3);

	double M4[N][N];
	float Op4 = podstanovka(3, M4, A, B);
	printf("Determinant 4 = %7.0f\n", Op4);


	// Вывод решения
	printf("\nconclusion of the solution\n");
	float x1 = Op1 / Op;
	printf("X1 = %7.5f\n", x1);
	float x2 = Op2 / Op;
	printf("X2 = %7.5f\n", x2);
	float x3 = Op3 / Op;
	printf("X3 = %7.5f\n", x3);
	float x4 = Op4 / Op;
	printf("X4 = %7.5f\n", x4);
	return 0;
}



//Решение СЛАУ методом итераций
double* iter(double** a, double* y, int n)
{
	double* res = new double[n];
	int i, j;


	for (i = 0; i < n; i++)
	{
		res[i] = y[i] / a[i][i];
	}

	double eps = 0.001;
	double* Xn = new double[n];

	do {
		for (i = 0; i < n; i++) {
			Xn[i] = y[i] / a[i][i];
			for (j = 0; j < n; j++) {
				if (i == j)
					continue;
				else {
					Xn[i] -= a[i][j] / a[i][i] * res[j];
				}
			}
		}

		bool flag = true;
		for (i = 0; i < n - 1; i++) {
			if (abs(Xn[i] - res[i]) > eps) {
				flag = false;
				break;
			}
		}

		for (i = 0; i < n; i++) {
			res[i] = Xn[i];
		}

		if (flag)
			break;
	} while (1);

	return res;
}



int f3()
{
	double** a;
	double* y;
	double* x;
	ifstream Infile;
	int n, i, j;
	printf ("Enter the number of equations: ");
	cin >> n;
	if (n == 4)
	{
		Infile.open("inArray4.txt");
	}
	else {
		Infile.open("inArray5.txt");
	}

	y = new double[n];
	a = new double* [n];
	for (i = 0; i < n; i++)
	{
		a[i] = new double[n];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j <= n; j++)
		{
			if (j != n)
			{
				Infile >> a[i][j];
			}
			else
			{
				Infile >> y[i];
			}
		}
	}
	Infile.close();

	for (i = 0; i < n; i++)
	{
		for (j = 0; j <= n; j++)
		{
			if (j != n)
			{
				printf("%f\t", a[i][j]);
			}
			else
			{
				printf ("%f \t", y[i]);
			}
		}
		printf("\n");
	}

	x = iter(a, y, n);

	for (i = 0; i < n; i++)
	{
		printf("%f \t", x[i]);
	}
	printf("\n");

	return 0;
}

void sysout(double** a, double* y, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%f", a[i][j]);
				printf("%d *x", j);
				if (j < n - 1)
					printf(" + ");
		}
		printf(" = ");
		printf("%f", y[i]);
		printf("\n");
	}
	return;
}
double* gauss(double** a, double* y, int n)
{
	double* x, max;
	int k, index;
	const double eps = 0.00001;  // точность
	x = new double[n];
	k = 0;
	while (k < n)
	{
		// Поиск строки с максимальным a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max < eps)
		{
			// нет ненулевых диагональных элементов
			printf("The solution cannot be obtained because of the null column ");
			printf("%d", index);
			printf(" matrices A ");
			printf("\n");
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		// Нормализация уравнений
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	// обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}
int f2()
{
	double** a, * y, * x;
	int n;
	system("chcp 1251");
	system("cls");
	printf("Enter the number of equations: ");
	cin >> n;
	a = new double* [n];
	y = new double[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			printf("a[ %d", i);
			printf("][%d", j); 
			printf("]= ");
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		printf("y[%d", i);
		printf("]= ");
		cin >> y[i];
	}
	sysout(a, y, n);
	x = gauss(a, y, n);
	for (int i = 0; i < n; i++)
		cout << "x[" << i << "]=" << x[i] << endl;
	cin.get(); cin.get();
	return 0;
}
int main()
{
	int i;
	while (true)
	{
		cout << "Choose:" << endl <<
			"1) by the Kramer method." << endl <<

			"2) by the Gauss method." << endl <<

			"3) by Iteration method." << endl;
			cin >> i;
		switch (i)
		{
		case 1: f1(); break;
		case 2: f2(); break;
		case 3: f3(); break;
		default: return 0;
		}
	}
}