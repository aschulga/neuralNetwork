#ifndef __MYMATRIX
#define __MYMATRIX

double** getTransposeMatrix(double **matrix, double **a, int row, int column);
double** makeMatrixFromVector(vector<double> vector);
double** multiplyMatrics(double **resultMatrix, double **matrix1, double **matrix2, int row1, int column1, int column2);
double** differenceMatrix(double **matrix1, double **matrix2, int row, int column);
double** multiplyNumToMatrix(double **matrix, double number, int row, int column);
void clearMemory(double **matrix, int row);
double** createMatrix(int row, int column);

#endif