#include<vector>
using namespace std;

//@author Шульга Алексей
class VectorFromRectangle
{
	vector<double> vectorRectangle;

public:
	VectorFromRectangle()
	{
	}

	void addElementToVector(double valuePixel)
	{
		vectorRectangle.push_back(valuePixel);
	}

	vector<double> getVectorForRect()
	{
		return vectorRectangle;
	}
};