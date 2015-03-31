#ifndef MYDSS
#define MYDSS

#include "DGtal/helpers/StdDefs.h"
#include "myfunctions.h"

using namespace DGtal;
using namespace Z2i;
using namespace std;

namespace DGtal
{
    //class myArithmeticalDSS;
    //class myIterator;
    class myArithmeticalDSS// : public myDSL
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

            vector<Point> mypVector; //points of my DSS

        public:
            //Constructor
            myArithmeticalDSS();
            ~myArithmeticalDSS();
            myArithmeticalDSS(Point aF, Point aL);
            myArithmeticalDSS(int aA, int aB, Point aF, Point aL, Point aUf, Point aUl, Point aLf, Point aLl);
            myArithmeticalDSS(int aA, int aB, int aMu, int aOmega, Point aF, Point aL);

            //Overload functions
            myArithmeticalDSS& operator=(const myArithmeticalDSS& s);
            bool operator==(const myArithmeticalDSS& s);
            bool operator!=(const myArithmeticalDSS& s);
            friend std::ostream& operator<<(std::ostream& out, const myArithmeticalDSS& s);

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

            //services
            bool isValid();
            vector<Point> pointDSS(Point p);
            vector<Point> pointDSS(Point begin, Point end);
            bool isInDSL(Point p);
            bool isInDSS(Point p);
            bool isLeaningPoint(Point p);
            int reminder(Point p);
            bool extendFront(Point p);
            int extendFrontStandard(Point p);

            //Iterator ????
            //myIterator begin(Point p);
            //myIterator end(Point p);
    };
}
#endif // MYDSS

