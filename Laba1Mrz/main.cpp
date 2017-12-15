//@author стандартные библиотеки с++
#include<iostream>
#include <cmath>
#include<vector>
//@author http://cimg.eu
#include "CImg-2.1.5/CImg.h"
//@author Шульга Алексей, гр. 521701, 30.11.2017
#include "VectorFromRectangle.cpp"
#include"matrixAndVector.h"

using namespace std;
using namespace cimg_library;

int RGB = 3;
vector<VectorFromRectangle> listVectorsFromRectangle;

double **list;

double **matrixWeight1;
double **matrixWeight2;
double **MatrixY;
double **MatrixX;
double **MatrixX_;
double **MatrixDeltaX;

//@author Шульга Алексей
double calculateLearningFactor(double **matrix, int column)
{
	double sum = 0;
	for (int i = 0; i < column; i++)
	{
		sum += pow((matrix[0][i]),2);
	}

	if (sum == 0)
		return 0.01;

	return 1/sum;
}

//@author Шульга Алексей
double recoveryColorPixel(double number)
{
	double newPixel = (number + 1)/2 * 255 ;

	if (newPixel > 255)
		newPixel = 255;
	else if (newPixel < 0)
		newPixel =  0;
	return newPixel;
}

//@author Шульга Алексей
void imageRecovery(int n, int m, int p, int width, int height)
{
	CImg<double> im(width, height, 1, 3);
	int N = n*m*RGB;
	double **m_1_p = createMatrix(1, p);
	double **m_1_N = createMatrix(1, n*m*RGB);
	int index = 0;

		for (int x = 0; x < width; x += n)
		{
			for (int y = 0; y < height; y += m)
			{
				MatrixX = makeMatrixFromVector(listVectorsFromRectangle[index].getVectorForRect());
				MatrixY = multiplyMatrics(m_1_p, MatrixX, matrixWeight1, 1, N, p);
				MatrixX_ = multiplyMatrics(m_1_N, MatrixY, matrixWeight2, 1, p, N);
				index++;
				int q = 0;

				for (int i = x; i < x + n; i++)
				{
					for (int j = y; j < y + m; j++)
					{
						im(i, j, 0, 0) = recoveryColorPixel(MatrixX_[0][q++]);
						im(i, j, 0, 1) = recoveryColorPixel(MatrixX_[0][q++]);
						im(i, j, 0, 2) = recoveryColorPixel(MatrixX_[0][q++]);
					}
				}
			}
		clearMemory(MatrixX, 1);
	}

	clearMemory(m_1_p, 1);
	clearMemory(m_1_N, 1);

	im.display();
	im.save("new_image.bmp");
}

//@author Шульга Алексей
void study(int p, int N, int e)
{
	double alpha;
	double alpha_;
	double E;
	int s = 1;

	double **m_N_p = createMatrix(N, p);
	double **m_p_N = createMatrix(p, N);
	double **m_p_1 = createMatrix(p, 1);
	double **m_1_p = createMatrix(1, p);
	double **m_N_1 = createMatrix(N, 1);
	double **m_1_N = createMatrix(1, N);
	
	do{
		E = 0;

		for (int i = 0; i < listVectorsFromRectangle.size(); i++)
		{
			MatrixX = makeMatrixFromVector(listVectorsFromRectangle[i].getVectorForRect());
			MatrixY = multiplyMatrics(m_1_p, MatrixX, matrixWeight1, 1, N, p);
			MatrixX_ = multiplyMatrics(m_1_N, MatrixY, matrixWeight2, 1, p, N);
			MatrixDeltaX = differenceMatrix(MatrixX_, MatrixX, 1, N);

			alpha_ = calculateLearningFactor(MatrixY, p);
			
			double **operation1W_ = getTransposeMatrix(m_p_1, MatrixY, 1, p);
			double **operation2W_ = multiplyMatrics(m_p_N, operation1W_, MatrixDeltaX, p, 1, N);
			double **operation3W_ = multiplyNumToMatrix(operation2W_, alpha_, p, N);

			matrixWeight2 = differenceMatrix(matrixWeight2, operation3W_, p, N);

			alpha = calculateLearningFactor(MatrixX, N);

			double **operation1W = getTransposeMatrix(m_N_p, matrixWeight2, p, N);
			double **operation2W = multiplyMatrics(m_1_p, MatrixDeltaX, operation1W, 1, N, p);
			double **operation3W = getTransposeMatrix(m_N_1, MatrixX, 1, N);
			double **operation4W = multiplyNumToMatrix(operation3W, alpha, N, 1);
			double **operation5W = multiplyMatrics(m_N_p, operation4W, operation2W, N, 1, p);

			matrixWeight1 = differenceMatrix(matrixWeight1, operation5W, N, p);

			clearMemory(MatrixX,1);
		}

		for (int i = 0; i < listVectorsFromRectangle.size(); i++)
		{
			MatrixX = makeMatrixFromVector(listVectorsFromRectangle[i].getVectorForRect());
			MatrixY = multiplyMatrics(m_1_p, MatrixX, matrixWeight1, 1, N, p);
			MatrixX_ = multiplyMatrics(m_1_N, MatrixY, matrixWeight2, 1, p, N);
			MatrixDeltaX = differenceMatrix(MatrixX_, MatrixX, 1, N);

			for (int j = 0; j < N; j++)
			{
				E += pow(MatrixDeltaX[0][j], 2);
			}

			clearMemory(MatrixX,1);
		}

		cout << " Iteration: " << s << "; Error: " << E << endl;
		s++;
	} while (E > e);

	clearMemory(m_p_1, p);
	clearMemory(m_N_p, N);
	clearMemory(m_N_1, N);
	clearMemory(m_1_p, 1);
	clearMemory(m_1_N, 1);
	clearMemory(m_p_N, p);

	double z = (N*listVectorsFromRectangle.size()*1.0) / ((N + listVectorsFromRectangle.size())*p + 2);
	cout << "Z = " << z << endl;
}

//@author Шульга Алексей
void createMatrixWeights(int n, int m, int p)
{
	int N = n*m*RGB;
	matrixWeight1 = new double*[N];
	for (int i = 0; i < N; i++)
		matrixWeight1[i] = new double[p];

	for (int i = 0; i<N; i++)
		for (int j = 0; j < p; j++){
		double t = (double)(rand()) / RAND_MAX * 2 - 1;
		matrixWeight1[i][j] = t*0.01;
		}

	double **m_p_N = createMatrix(p, N);

	matrixWeight2 = getTransposeMatrix(m_p_N, matrixWeight1, N, p);
}

//@author Шульга Алексей
double conversionColorPixel(double number)
{
	return 2*number/255-1;
}

//@author Шульга Алексей
VectorFromRectangle createVectorFromRectangle(CImg<double> image, int x, int y, int n, int m)
{
	VectorFromRectangle vectorFromRectangle = VectorFromRectangle();

	for (int i = x; i < x+n; i++)
	{
		for (int j = y; j < y+m; j++)
		{
			double pixvalRED = image(i, j, 0, 0);

			vectorFromRectangle.addElementToVector(conversionColorPixel(pixvalRED));

			double pixvalGREEN = image(i, j, 0, 1);
			vectorFromRectangle.addElementToVector(conversionColorPixel(pixvalGREEN));

			double pixvalBLUE = image(i, j, 0, 2);
			vectorFromRectangle.addElementToVector(conversionColorPixel(pixvalBLUE));
		}
	}
	return vectorFromRectangle;
}

//@author Шульга Алексей
int main()
{
	CImg<double> image("tiger.bmp");
	int image_width = image.width();
	int image_height = image.height();
	int n, m, p, e;

	cout << "width: " << image_width << " height " << image_height  << endl;

	cout << "Enter height of rectangle(n):" << endl;
	cin >> n;

	cout << "Enter wight of rectangle(m):" << endl;
	cin >> m;

	cout << "Enter number of neuron(p):" << endl;
	cin >> p;

	cout << "Enter error (e):" << endl;
	cin >> e;

	for (int x = 0; x < image_width; x += n)
	{
		for (int y = 0; y < image_height; y += m)
		{
			listVectorsFromRectangle.push_back(createVectorFromRectangle(image, x, y, n, m));
		}
	}

	createMatrixWeights(n, m, p);
	study(p, n*m*RGB, e);
	imageRecovery(n, m, p, image_width, image_height);

	getchar();
	return 0;
}