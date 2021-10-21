/**
Gabriel Henrique Linke - 2126630
Thiago de Mendonça Mildemberger - 1716980
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

using std::abs;
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

bool compareYCoordinate(Point a, Point b)
{
	return a.y < b.y;
}

bool compareXCoordinate(Point a, Point b)
{
	return a.x < b.x;
}

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
	vector<Point> remainingPoints;
	remainingPoints.reserve(end - start + 1);
	for (int i = start; i <= end; i++)
	{
		if (abs(points[i].x - points[m].x) < getEuclideanDistance(d))
			remainingPoints.push_back(points[i]);
	}
	sort(remainingPoints.begin(), remainingPoints.end(), compareYCoordinate);
	for (int i = 0; i < remainingPoints.size(); i++)
	{
		for (int j = i + 1; j < min((int)remainingPoints.size(), 15); j++)
			d = getEuclideanDistance(Pair(remainingPoints[i], remainingPoints[j])) < getEuclideanDistance(d) ? Pair(remainingPoints[i], remainingPoints[j]) : d;
	}
	return d;
}

// Algoritmo O(n²) para testes
Pair closestPairTest(vector<Point> points)
{
	Pair d = Pair(points[0], points[1]);
	for (int i = 0; i < points.size(); i++)
	{
		for (int j = 0; j < points.size(); j++)
		{
			if (i != j)
			{
				if (getEuclideanDistance(Pair(points[i], points[j])) < getEuclideanDistance(d))
					d = Pair(points[i], points[j]);
			}
		}
	}
	return d;
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

	// Pair closest2 = closestPairTest(points);

	// if (getEuclideanDistance(closest) != getEuclideanDistance(closest2))
	// {
	// 	cout << "Results should be the same"
	// 		 << " n: " << points.size() << endl;
	// }

	return 0;
}
