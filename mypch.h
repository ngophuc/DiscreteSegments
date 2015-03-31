#ifndef MYPCH_H
#define MYPCH_H

#include "DGtal/helpers/StdDefs.h"
#include "myfunctions.h"

using namespace DGtal;
using namespace Z2i;
using namespace std;

namespace DGtal
{
    // 2D simple polyline convex hull
    class myPolylineConvexHull
    {
        private:
            int mySize;
            int myTop;
            int myBottom;
            vector<Point> myD;//dequeue of convex hull
            vector<Point> myH;//convex hull points
            //vector<Point> P;//all points

            ////double myVDistance;

        public:
            myPolylineConvexHull();            
            ~myPolylineConvexHull();
            myPolylineConvexHull(int n);
            myPolylineConvexHull(vector<Point> P);
            //myPolylineConvexHull( myPolylineConvexHull h);

            //Overload functions
            myPolylineConvexHull& operator=(const myPolylineConvexHull& h);
            friend std::ostream& operator<<(std::ostream& out, const myPolylineConvexHull& h);

            //getters and setters
            void size(int n);
            void top(int n);
            void bottom(int n);
            void D(vector<Point> d);
            void H(vector<Point> h);
            ////void vDistance(double d);

            int size() const;
            int top() const;
            int bottom() const;
            vector<Point> D() const;
            vector<Point> H();
            ////double vDistance();

            int capacity() const;

            //services
            void displayCovexHull() const;
            void simpleHull_2D(Point P);//add to convex hull a point
            vector<Point> simpleHull_2D(vector<Point> P);//add to convex hull a set of points

            bool findPoint(Point P);//find a point in the convex hull

            //find a point after P in the hull such that
            //the slope of its with the neighbour is > a/b
            Point findLeaningPoint(Point P, int a, int b);

            //find a point after P in the hull such that
            //the slope of its with the neighbour is > a/b
            Point findLowerPoint(Point P, int a, int b);
            //find a point after P in the hull such that
            //the slope of its with the neighbour is < a/b
            Point findUpperPoint(Point P, int a, int b);

    };
}


#endif // MYPCH_H
