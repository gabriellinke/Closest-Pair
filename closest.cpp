/**
Gabriel Henrique Linke - 2126630
Thiago de Mendonça Mildemberger - 
**/

#include <iostream>
#include <vector>
#include <string>

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
	int size = 0;
	fileReader >> size;
	vector<Point> points;
	points.reserve(size);
	Point point;
	while (fileReader >> point.x >> point.y)
	{
		points.push_back(point);
	}
	return points;
}

Point closestPair(vector<Point> points)
{
	return points[0];
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;

	vector<Point> points = readPoints(argv[1]);

	Point closest = closestPair(points);
	cout << "Closest " << setprecision(6) << fixed << closest.x << " " << closest.y << endl;
	return 0;
}
