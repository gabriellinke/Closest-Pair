/**
Gabriel Henrique Linke - 2126630
Thiago de Mendonça Mildemberger - 
**/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <iomanip>
#include <fstream>

using std::cerr;
using std::cout;
using std::endl;

using std::fixed;
using std::ifstream;
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

Pair closestPair(vector<Point> points)
{
	Pair teste;
	teste.first = points[0];
	teste.second = points[1];
	return teste;
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
