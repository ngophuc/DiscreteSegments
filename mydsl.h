#ifndef MYDSL
#define MYDSL

#include "DGtal/helpers/StdDefs.h"
#include "myfunctions.h"

using namespace DGtal;
using namespace Z2i;
using namespace std;

namespace DGtal
{
    //class myArithmeticalDSS;
    //class myIterator;
    class myArithmeticalDSL
    {
        private:
            int myA;
            int myB;
            int myMu;
            int myOmega;
            //a DSL : mu <= ax - by < mu + omega
            //lower leaning line : ax - by = mu
            //upper leaning line : ax - by = mu + omega

        public:
            //constructor
            myArithmeticalDSL();
            ~myArithmeticalDSL();
            myArithmeticalDSL(int aA, int aB, int aMu, int aOmega);

            //Overload functions
            myArithmeticalDSL& operator=(const myArithmeticalDSL& s);
            bool operator==(const myArithmeticalDSL& s);
            bool operator!=(const myArithmeticalDSL& s);
            friend std::ostream& operator<<(std::ostream& out, const myArithmeticalDSL& s);

            //getters and settters
            void a(int aA);
            void b(int aB);
            void mu(int aMu);
            void omega(int aOmega);

            int a() const;
            int b() const;
            int mu() const;
            int omega() const;

            //services
            //Point pointDSL(Point p);
            vector<Point> pointDSL(Point p);
            vector<Point> pointDSL(Point begin, Point end);
            bool isInDSL(Point p);
            bool isLeaningPoint(Point p);
            int reminder(Point p);

            //CDrawableWithBoard2D
            string className();
            //DrawableWithBoard2D defaultStyle(std::string m);

            //Iterator
            //vector<Point>::iterator begin(Point p);
            //vector<Point>::iterator end(Point p);
            //vector<Point> pointDSL(Point begin, Point end);
    };
}

#endif // MYDSL

