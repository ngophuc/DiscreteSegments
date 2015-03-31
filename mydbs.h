#ifndef MYDBS
#define MYDBS

#include "DGtal/helpers/StdDefs.h"
#include "mypch.h"

using namespace DGtal;
using namespace Z2i;
using namespace std;

namespace DGtal
{
    class myArithmeticalDBS
    {
        private:
            int myA;//slope (a,b)
            int myB;
            int myMu;
            int myOmega;
            //a DSL : mu <= ax - by < mu + omega
            //lower leaning line : ax - by = mu
            //upper leaning line : ax - by = mu + omega
            Point myaF; // the first (ending) point
            Point myaL;// the last (ending) point

            Point myaUf;// the first upper (leaning) point
            Point myaUl;// the last upper (leaning) point
            Point myaLf;// the first lower (leaning) point
            Point myaLl;// the last lower (leaning) point

            vector<Point> mypVector; //points of my DBS

            int myOrder; //order of the blurred segment

        public:
            //Constructor
            myArithmeticalDBS();
            ~myArithmeticalDBS();
            myArithmeticalDBS(Point aF, Point aL, int aOrder);
            myArithmeticalDBS(int aA, int aB, Point aF, Point aL, Point aUf, Point aUl, Point aLf, Point aLl, int aOrder);
            myArithmeticalDBS(int aA, int aB, int aMu, int aOmega, Point aF, Point aL, int aOrder);

            //Overload functions
            myArithmeticalDBS& operator=(const myArithmeticalDBS& s);
            bool operator==(const myArithmeticalDBS& s);
            bool operator!=(const myArithmeticalDBS& s);
            friend std::ostream& operator<<(std::ostream& out, const myArithmeticalDBS& s);
            //friend Board2D& operator<<(Board2D& out, const myArithmeticalDBS& s);

            //getters and setters
            void a(int aA);
            void b(int aB);
            void mu(int aMu);
            void omega(int aOmega);
            void aF(Point p);
            void aL(Point p);
            void aUf(Point p);
            void aUl(Point p);
            void aLf(Point p);
            void aLl(Point p);
            void pVector(Point p);
            void pVector(vector<Point> p);
            void order(int d);

            int a() const;
            int b() const;
            int mu() const;
            int omega() const;
            Point aF() const;
            Point aL() const;
            Point aUf() const;
            Point aUl() const;
            Point aLf() const;
            Point aLl() const;
            vector<Point> pVector() const;
            int order() const;

            //services
            bool isValid();
            //vector<Point> pointDBS(Point p);
            bool isInDSL(Point p);
            bool isInDBS(Point p);
            bool isLeaningPoint(Point p);
            int reminder(Point p);
            bool extendFront(Point p);            
    };

    class myGeometricalDBS
    {
        private:
            int myA;//slope (a,b)
            int myB;
            int myMu;
            int myOmega;
            //a DSL : mu <= ax - by < mu + omega
            //lower leaning line : ax - by = mu
            //upper leaning line : ax - by = mu + omega
            Point myaF; // the first (ending) point
            Point myaL;// the last (ending) point

            Point myaUf;// the first upper (leaning) point
            Point myaUl;// the last upper (leaning) point
            Point myaLf;// the first lower (leaning) point
            Point myaLl;// the last lower (leaning) point

            myPolylineConvexHull myHull;//convex hull of points

            vector<Point> mypVector; //points of my DBS

            double myWidth; //vertical distance of the convex set of DBS


        public:
            //Constructor
            myGeometricalDBS();
            ~myGeometricalDBS();
            //myGeometricalDBS(myGeometricalDBS s);
            myGeometricalDBS(Point aF, Point aL, int aWidth);
            myGeometricalDBS(int aA, int aB, Point aF, Point aL, Point aUf, Point aUl, Point aLf, Point aLl, int aWidth);
            myGeometricalDBS(int aA, int aB, int aMu, int aOmega, Point aF, Point aL, int aWidth);

            //Overload functions
            myGeometricalDBS& operator=(const myGeometricalDBS& s);
            bool operator==(const myGeometricalDBS& s);
            bool operator!=(const myGeometricalDBS& s);
            friend std::ostream& operator<<(std::ostream& out, const myGeometricalDBS& s);
            //friend Board2D& operator<<(Board2D& out, const myGeometricalDBS& s);

            //getters and setters
            void a(int aA);
            void b(int aB);
            void mu(int aMu);
            void omega(int aOmega);
            void aF(Point p);
            void aL(Point p);
            void aUf(Point p);
            void aUl(Point p);
            void aLf(Point p);
            void aLl(Point p);
            void pVector(Point p);
            void pVector(vector<Point> p);
            void width(double d);

            int a() const;
            int b() const;
            int mu() const;
            int omega() const;
            Point aF() const;
            Point aL() const;
            Point aUf() const;
            Point aUl() const;
            Point aLf() const;
            Point aLl() const;
            vector<Point> pVector() const;
            double width() const;

            //services
            bool isValid();
            vector<Point> pointDSS(Point p);
            bool isInDSL(Point p);
            bool isInDBS(Point p);
            bool isLeaningPoint(Point p);
            int reminder(Point p);
            bool extendFront(Point p);
            int extendFrontOptimal(Point p);

            //draw function
            void drawDBS(Board2D& out);
    };
}
#endif // myArithmeticalDBS_H
