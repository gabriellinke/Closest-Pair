/**
Gabriel Henrique Linke - 2126630
Thiago de Mendonça Mildemberger - 
**/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

#include <iomanip>
#include <fstream>

using std::cerr;
using std::cout;
using std::endl;

using std::fixed;
using std::ifstream;
using std::min;
using std::setprecision;
using std::string;
using std::vector;

struct Point
{
	double x;
	double y;
};

using Pair = std::pair<Point, Point>;

vector<Point> readPoints(const string inputFile)
{
	ifstream fileReader(inputFile);
	if (!fileReader)
	{
		cerr << "Arquivo não pode ser aberto" << endl;
		fflush(stdin);
		getchar();
		// return;
	}
	vector<Point> points;
	int size = 0;
	Point point;
	fileReader >> size;
	points.reserve(size);

	while (fileReader >> point.x >> point.y)
	{
		points.push_back(point);
	}
	return points;
}

double getEuclideanDistance(Pair pair)
{
	return sqrt((pair.first.x - pair.second.x) * (pair.first.x - pair.second.x) + (pair.first.y - pair.second.y) * (pair.first.y - pair.second.y));
}

// Daria pra chamar recursivamente passando subvetores, porém criar um subvetor é uma operação O(n), e só passar
// start e end vai ser O(1)
Pair closestPairRecursive(vector<Point> points, int start, int end)
{
	// Base case
	int size = end - start;
	if (size <= 3)
	{
		if (size == 3)
		{
			return min({
						   Pair(points[start], points[start + 1]),
						   Pair(points[start], points[start + 2]),
						   Pair(points[start + 1], points[start + 2]),
					   },
					   [](Pair p1, Pair p2)
					   {
						   return getEuclideanDistance(p1) < getEuclideanDistance(p2);
					   });
		}
		else if (size == 2)
			return Pair(points[start], points[start + 1]);
		else
			cout << "O conjunto tem apenas um ponto" << endl;
	}
}

Pair closestPair(vector<Point> points)
{
	// Construct Px and Py in O(nlogn) time
	return closestPairRecursive(points, 0, points.size());
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;

	time_t start, end;
	start = clock();

	vector<Point> points = readPoints(argv[1]);
	Pair closest = closestPair(points);

	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

	cout << setprecision(6) << fixed << time_taken << " " << getEuclideanDistance(closest) << " " << closest.first.x << " " << closest.first.y << " " << closest.second.x << " " << closest.second.y << endl;
	return 0;
}
