#include "VectorFromRectangle.cpp"

//@author Шульга Алексей
double** getTransposeMatrix(double **transpMatrix, double **a, int row, int column)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			transpMatrix[j][i] = a[i][j];

	return transpMatrix;
}

//@author Шульга Алексей
double** makeMatrixFromVector(vector<double> vector)
{
	double **matrix = new double *[1];
	for (int i = 0; i < 1; i++)
	{
		matrix[i] = new double[vector.size()];
	}

	for (int i = 0; i < 1; i++)
		for (int j = 0; j < vector.size(); j++)
			matrix[i][j] = vector[j];

	return matrix;
}

//@author Шульга Алексей
double** multiplyMatrics(double **result, double **matrix1, double **matrix2, int row1, int column1, int column2)
{
	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < column2; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < column1; k++)
				result[i][j] += matrix1[i][k] * matrix2[k][j];
		}
	}
	return result;
}

//@author Шульга Алексей
double** multiplyNumToMatrix(double **matrix, double number, int row, int column)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			matrix[i][j] = number * matrix[i][j];
	return matrix;
}

//@author Шульга Алексей
double** differenceMatrix(double **matrix1, double **matrix2, int row, int column)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			matrix1[i][j] = matrix1[i][j] - matrix2[i][j];

	return matrix1;
}

//@author Шульга Алексей
void clearMemory(double **matrix, int row)
{
	for (int i = 0; i < row; i++)
		delete matrix[i];

	delete[] matrix;
}

//@author Шульга Алексей
double ** createMatrix(int row, int column)
{
	double **matrix = new double *[row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new double[column];
	}

	return matrix;
}


