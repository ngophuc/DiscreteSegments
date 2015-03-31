#ifndef MYFUNCTIONS
#define MYFUNCTIONS

#include "DGtal/helpers/StdDefs.h"

using namespace DGtal;
using namespace Z2i;
using namespace std;

int max(int n, int m);
int min(int n, int m);

int pgcd(int a, int b);

double verticalDistance(Point p, Point aF, Point aL);
double verticalDistance(Point Uf, Point Ul, Point Lf, Point Ll);

PointVector<2,double> intersectionLines(double a, double b, double c, double d, double e, double f);

int findElement(vector<Point> vec, Point p);

double distance(Point p1, Point p2);

double angle(Point v1, Point v2);

#endif // MYFUNCTIONS

