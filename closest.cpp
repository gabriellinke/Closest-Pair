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
using std::sort;
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

// Daria pra chamar recursivamente passando subvetores, porém criar um subvetor é uma operação O(n),
// e só passar start e end vai ser O(1)
Pair closestPairRecursive(vector<Point> points, int start, int end)
{
	// Caso base
	int size = end - start + 1;
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
		{
			throw std::runtime_error("O conjunto tem apenas um ponto");
		}
	}

	// Divisão
	int m = (end + start) / 2;
	Pair d1 = closestPairRecursive(points, start, m);
	Pair d2 = closestPairRecursive(points, m + 1, end);
	Pair d = getEuclideanDistance(d1) < getEuclideanDistance(d2) ? d1 : d2;

	//Conquista

	return d;
}

bool compareXCoordinate(Point a, Point b)
{
	return a.x < b.x;
}

Pair closestPair(vector<Point> points)
{
	// Construct Px in O(nlogn) time
	sort(points.begin(), points.end(), compareXCoordinate);
	return closestPairRecursive(points, 0, points.size() - 1);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;

	time_t start = clock();

	vector<Point> points = readPoints(argv[1]);
	Pair closest = closestPair(points);

	time_t end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

	cout << setprecision(6) << fixed << time_taken << " " << getEuclideanDistance(closest) << " " << closest.first.x << " " << closest.first.y << " " << closest.second.x << " " << closest.second.y << endl;
	return 0;
}
