#include "mydbs.h"
#define HULL_MAX_SIZE 100

/*
 * myArithmeticalDBS class
 * myArithmeticalDBS class
 * myArithmeticalDBS class
 */
myArithmeticalDBS::myArithmeticalDBS()
{

}

myArithmeticalDBS::~myArithmeticalDBS()
{

}

myArithmeticalDBS::myArithmeticalDBS(Point aF, Point aL, int aOrder)
{
    this->myOrder = aOrder;

    int aA = aL[1]-aF[1];
    int aB = aL[0]-aF[0];

    this->myA = aA/pgcd(aA,aB);
    this->myB = aB/pgcd(aA,aB);
    this->myaF = aF;
    this->myaL = aL;
    this->myaUf = aF;
    this->myaUl = aL;
    this->myaLf = aF;
    this->myaLl = aL;

    this->myMu=aA*myaUf[0] - aB*myaUf[1];//=aA*aUl[0] - aB*aUl[1]
    this->myOmega=max(abs(myA),abs(myB));//=aA*aLf[0] - aB*aLf[1] - this->myMu + 1;

    //Points of DSS aF and aL
    this->mypVector.push_back(aF);
    this->mypVector.push_back(aL);
}

myArithmeticalDBS::myArithmeticalDBS(int aA, int aB, Point aF, Point aL, Point aUf, Point aUl, Point aLf, Point aLl, int aOrder)
{
    this->myA = aA/pgcd(aA,aB);
    this->myB = aB/pgcd(aA,aB);
    this->myaF = aF;
    this->myaL = aL;
    this->myaUf = aUf;
    this->myaUl = aUl;
    this->myaLf = aLf;
    this->myaLl = aLl;
    this->myOrder = aOrder;

    /// upper leaning point has reminder : ax - by = mu
    /// lower leaning point has reminder : ax - by = mu + omega - 1
    this->myMu=aA*aUf[0] - aB*aUf[1];//=aA*aUl[0] - aB*aUl[1]
    this->myOmega=aA*aLf[0] - aB*aLf[1] - this->myMu + 1;

    //Points of DSS aF and aL
    this->mypVector.push_back(aF);
    this->mypVector.push_back(aL);
}

myArithmeticalDBS::myArithmeticalDBS(int aA, int aB, int aMu, int aOmega, Point aF, Point aL, int aOrder)
{
    this->myA = aA/pgcd(aA,aB);
    this->myB = aB/pgcd(aA,aB);
    this->myMu=aMu;
    this->myOmega=aOmega;
    this->myaF = aF;
    this->myaL = aL;
    this->myOrder = aOrder;

    ///////////////// To calculate
    this->myaUf = aF;
    this->myaUl = aL;
    this->myaLf = aF;
    this->myaLl = aL;

    //Points of DSS aF and aL
    this->mypVector.push_back(aF);
    this->mypVector.push_back(aL);
}

//Overload functions
myArithmeticalDBS& myArithmeticalDBS::operator=(const myArithmeticalDBS& s)
{
    if (this != &s)
    {
        this->myA = s.myA;
        this->myB = s.myB;
        this->myMu= s.myMu;
        this->myOmega=s.myOmega;
        this->myaF = s.myaF;
        this->myaL = s.myaL;
        this->myOrder = s.myOrder;
        this->myaUf = s.myaUf;
        this->myaUl = s.myaUl;
        this->myaLf = s.myaLf;
        this->myaLl = s.myaLl;
        this->mypVector = s.mypVector;
    }
    return *this;
}

bool myArithmeticalDBS::operator==(const myArithmeticalDBS& s)
{
    if (this == &s)
        return true;
    return ((this->myA == s.myA) &&
            (this->myB == s.myB) &&
            (this->myMu == s.myMu) &&
            (this->myOmega ==s.myOmega) &&
            (this->myOrder == s.myOrder)); /* &&
            (this->myaF == s.myaF) &&
            (this->myaL == s.myaL) &&
            (this->myaUf == s.myaUf) &&
            (this->myaUl == s.myaUl) &&
            (this->myaLf == s.myaLf) &&
            (this->myaLl == s.myaLl) );
            */
}

bool myArithmeticalDBS::operator!=(const myArithmeticalDBS& s)
{
    return !(*this == s);
}

std::ostream& DGtal::operator<<(std::ostream& out, const myArithmeticalDBS& s)
{
    return out<<"Arithmetic blurred segment of order "
             <<s.order()<<" is ( "<<s.a()<<" , "<<s.b()<<" , "<<s.mu()<<" , "<<s.omega()<<" )"<<endl;
}

//getters and settters
void myArithmeticalDBS::a(int aA)
{
    this->myA = aA;
}

void myArithmeticalDBS::b(int aB)
{
    this->myB = aB;
}

void myArithmeticalDBS::mu(int aMu)
{
    this->myMu = aMu;
}

void myArithmeticalDBS::omega(int aOmega)
{
    this->myOmega = aOmega;
}

void myArithmeticalDBS::order(int aOmega)
{
    this->myOmega = aOmega;
}

void myArithmeticalDBS::pVector(Point p)
{
        (this->mypVector).push_back(p);
}

void myArithmeticalDBS::pVector(vector<Point> p)
{
    for(vector<Point>::iterator it = p.begin(); it != p.end(); it++)
        (this->mypVector).push_back(*it);
}

int myArithmeticalDBS::a() const
{
    return this->myA;
}

int myArithmeticalDBS::b() const
{
    return this->myB;
}

int myArithmeticalDBS::mu() const
{
    return this->myMu;
}

int myArithmeticalDBS::omega() const
{
    return this->myOmega;
}

Point myArithmeticalDBS::aF() const
{
    return this->myaF;
}

Point myArithmeticalDBS::aL() const
{
    return this->myaL;
}

Point myArithmeticalDBS::aUf() const
{
    return this->myaUf;
}

Point myArithmeticalDBS::aUl() const
{
    return this->myaUl;
}

Point myArithmeticalDBS::aLf() const
{
    return this->myaLf;
}

Point myArithmeticalDBS::aLl() const
{
    return this->myaLl;
}

vector<Point> myArithmeticalDBS::pVector() const
{
    return this->mypVector;
}

int myArithmeticalDBS::order() const
{
    return this->myOrder;
}

bool myArithmeticalDBS::isInDSL(Point p)
{
    return ((this->a()*p[0]-this->b()*p[1]) >= this->mu()) &&
           ((this->a()*p[0]-this->b()*p[1]) < this->mu()+this->omega());
}

bool myArithmeticalDBS::isInDBS(Point p)
{
    return ((p[0]>=myaF[0] && p[0]<=myaL[0] && p[1]>=myaF[1] && p[1]<=myaL[1]) &&
           (reminder(p) >= this->mu()) &&
           (reminder(p) < this->mu()+this->omega()));
}

bool myArithmeticalDBS::isValid()
{
    //verify upper and lower leaning points belongs to segments ????
    return isInDSL(myaLf) && isInDSL(myaLl) && isInDSL(myaUf) && isInDSL(myaUl);
}

bool myArithmeticalDBS::isLeaningPoint(Point p)
{
    //return ((this->a()*p[0]-this->b()*p[1]) == this->mu()) ||
    //       ((this->a()*p[0]-this->b()*p[1]) < this->mu()+this->omega());
    return (reminder(p) == this->mu()) || (reminder(p) < this->mu()+this->omega());

}

int myArithmeticalDBS::reminder(Point p)
{
    return (this->a()*p[0]-this->b()*p[1]);
}
/*
vector<Point> myArithmeticalDBS::pointDBS(Point p)
{
    vector<Point> pVector;
    int lower = ceil((this->a()*p[0]-this->mu()-this->omega())/(double)this->b());
    int upper = floor(this->a()*p[0]-this->mu())/(double)this->b();
    //cout<<"(lower,upper) = "<<lower<<" , "<<upper<<endl;
    for (int i=lower; i<=upper; i++)
    {
        //cout<<"(x,y) = "<<p[0]<<" , "<<i<<" and in SDL is "<<isInDSL(p)<<endl;
        if(p[0]>=0 && i>=0 && isInDSL(Point(p[0],i)))
            pVector.push_back(Point(p[0],i));
    }
    return pVector;
}
*/
bool myArithmeticalDBS::extendFront(Point p)
{
    if (reminder(p)>myMu && reminder(p)<myMu+myOmega-1){//p belongs to Segment
        cout<<"ok ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        myaL = p;
        return true;
    }
    else if(reminder(p)==myMu){
        cout<<"(1) : reminder mu ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        myaUf = myaUl;
        myaUl = p;
        myaL = p;
        cout<<"(2) : reminder mu ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return true;
    }
    else if(reminder(p)==myMu+myOmega-1){
        cout<<"(1) : reminder mu+omega-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        myaLf = myaLl;
        myaLl = p;
        myaL = p;
        cout<<"(2) : reminder mu+omega-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return true;
    }
    else if(reminder(p)<=myMu-1){//p is exterior point, Segment has slope (pLf)
        cout<<"(1) : reminder <= mu-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        //find new lower point P of reminder r(p)+1
        bool find = false;
        int x = myaF[0], y;
        while(find==false && x <= myaL[0])
        {
            //ax - by = r(M)+1
            y = (myA*x - reminder(p) - 1);
            find = (y % myB == 0);
            x++;
        }
        if(find==true)
        {
            myaUf = Point(x-1, y/myB);
            int aA = p[1]-myaUf[1];
            int aB = p[0]-myaUf[0];
            myA = aA/pgcd(aA,aB);//p[1]-myaUf[1];//(y/myB);
            myB = aB/pgcd(aA,aB);//p[0]-myaUf[0];//(x-1);
            myaUl = p;
            myaLf = myaLl;
            this->myMu=myA*myaUl[0] - myB*myaUl[1];//=myA*myaUf[0] - myB*myaUf[1]
            this->myOmega=myA*myaLl[0] - myB*myaLl[1] - this->myMu + 1;//myA*myaLf[0] - myB*myaLf[1] - this->myMu + 1
            cout<<"(2) : reminder <= mu-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
            cout<<"reminder : "<<reminder(myaUf)<<" , "<<reminder(myaUl)<<" , "<<reminder(myaLf)<<" , "<<reminder(myaLl)<<endl;
            if(myOrder>0 && (double)myOmega/max(abs(myA),abs(myB))>myOrder)
                return false;
            return true;
        }
        return false;

    }
    else if(reminder(p)>=myMu+myOmega){//p is exterior point, Segment has slope (pUf)
        cout<<"(1) : reminder >= mu+omega ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        //find new lower point P of reminder r(p)-1
        bool find = false;
        int x = myaF[0], y;
        while(find==false && x <= myaL[0])
        {
            //ax - by = r(M)-1
            y = (myA*x - reminder(p) + 1);
            find = (y % myB == 0);
            x++;
        }
        if(find==true)
        {
            //if(reminder(myaLf)==reminder(p)-1)
            myaLf = Point(x-1, y/myB);
            int aA = p[1]-myaLf[1];
            int aB = p[0]-myaLf[0];
            myA = aA/pgcd(aA,aB);//p[1]-myaLf[1];//(y/myB);
            myB = aB/pgcd(aA,aB);//p[0]-myaLf[0];//(x-1);
            myaLl = p;
            myaUf = myaUl;
            this->myMu=myA*myaUl[0] - myB*myaUl[1];//=myA*myaUf[0] - myB*myaUf[1];
            this->myOmega=myA*myaLl[0] - myB*myaLl[1] - this->myMu + 1;//myA*myaLf[0] - myB*myaLf[1] - this->myMu + 1
            cout<<"(2) : reminder >= mu+omega ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
            cout<<"reminder : "<<reminder(myaUf)<<" , "<<reminder(myaUl)<<" , "<<reminder(myaLf)<<" , "<<reminder(myaLl)<<endl;
            if(myOrder>0 && (double)myOmega/max(abs(myA),abs(myB))>myOrder)
                return false;
            return true;
        }
        else
            return false;
    }
    return false;
}








/*
 * myGeometricalDBS class
 * myGeometricalDBS class
 * myGeometricalDBS class
 */
myGeometricalDBS::myGeometricalDBS()
{

}

myGeometricalDBS::~myGeometricalDBS()
{

}

myGeometricalDBS::myGeometricalDBS(Point aF, Point aL, int aWidth)
{
    this->myWidth = aWidth;

    int aA = aL[1]-aF[1];
    int aB = aL[0]-aF[0];

    this->myA = aA/pgcd(aA,aB);
    this->myB = aB/pgcd(aA,aB);
    this->myaF = aF;
    this->myaL = aL;
    this->myaUf = aF;
    this->myaUl = aL;
    this->myaLf = aF;
    this->myaLl = aL;

    this->myMu=aA*myaUf[0] - aB*myaUf[1];//=aA*aUl[0] - aB*aUl[1]
    this->myOmega=max(abs(myA),abs(myB));//=aA*aLf[0] - aB*aLf[1] - this->myMu + 1;

    //Points of DSS aF and aL
    this->mypVector.push_back(aF);
    this->mypVector.push_back(aL);

    //myPolylineConvexHull h(HULL_MAX_SIZE);
    this->myHull.size(HULL_MAX_SIZE);
    this->myHull.simpleHull_2D(aF);
    this->myHull.simpleHull_2D(aL);
    //cout<<"constructor : "<<myHull<<endl;
}

myGeometricalDBS::myGeometricalDBS(int aA, int aB, Point aF, Point aL, Point aUf, Point aUl, Point aLf, Point aLl, int aWidth)
{
    this->myA = aA/pgcd(aA,aB);
    this->myB = aB/pgcd(aA,aB);
    this->myaF = aF;
    this->myaL = aL;
    this->myaUf = aUf;
    this->myaUl = aUl;
    this->myaLf = aLf;
    this->myaLl = aLl;
    this->myWidth = aWidth;

    /// upper leaning point has reminder : ax - by = mu
    /// lower leaning point has reminder : ax - by = mu + omega - 1
    this->myMu=aA*aUf[0] - aB*aUf[1];//=aA*aUl[0] - aB*aUl[1]
    this->myOmega=aA*aLf[0] - aB*aLf[1] - this->myMu + 1;

    //Points of DSS aF and aL
    this->mypVector.push_back(aF);
    this->mypVector.push_back(aL);

    //myPolylineConvexHull h(HULL_MAX_SIZE);
    this->myHull.size(HULL_MAX_SIZE);
    this->myHull.simpleHull_2D(aF);
    this->myHull.simpleHull_2D(aL);
}

myGeometricalDBS::myGeometricalDBS(int aA, int aB, int aMu, int aOmega, Point aF, Point aL, int aWidth)
{
    this->myA = aA/pgcd(aA,aB);
    this->myB = aB/pgcd(aA,aB);
    this->myMu=aMu;
    this->myOmega=aOmega;
    this->myaF = aF;
    this->myaL = aL;
    this->myWidth = aWidth;

    ///////////////// To calculate
    this->myaUf = aF;
    this->myaUl = aL;
    this->myaLf = aF;
    this->myaLl = aL;

    //Points of DSS aF and aL
    this->mypVector.push_back(aF);
    this->mypVector.push_back(aL);

    //myPolylineConvexHull h(HULL_MAX_SIZE);
    this->myHull.size(HULL_MAX_SIZE);
    this->myHull.simpleHull_2D(aF);
    this->myHull.simpleHull_2D(aL);
}

//Overload functions
myGeometricalDBS& myGeometricalDBS::operator=(const myGeometricalDBS& s)
{
    if (this != &s)
    {
        this->myA = s.myA;
        this->myB = s.myB;
        this->myMu= s.myMu;
        this->myOmega=s.myOmega;
        this->myaF = s.myaF;
        this->myaL = s.myaL;
        this->myWidth = s.myWidth;
        this->myaUf = s.myaUf;
        this->myaUl = s.myaUl;
        this->myaLf = s.myaLf;
        this->myaLl = s.myaLl;
        this->mypVector = s.mypVector;
        this->myHull = s.myHull;
    }
    return *this;
}

bool myGeometricalDBS::operator==(const myGeometricalDBS& s)
{
    if (this == &s)
        return true;
    return ((this->myA == s.myA) &&
            (this->myB == s.myB) &&
            (this->myMu == s.myMu) &&
            (this->myOmega == s.myOmega) &&
            (this->myWidth == s.myWidth)); /* &&
            (this->myaF == s.myaF) &&
            (this->myaL == s.myaL) &&
            (this->myaUf == s.myaUf) &&
            (this->myaUl == s.myaUl) &&
            (this->myaLf == s.myaLf) &&
            (this->myaLl == s.myaLl) );
            */
}

bool myGeometricalDBS::operator!=(const myGeometricalDBS& s)
{
    return !(*this == s);
}

std::ostream& DGtal::operator<<(std::ostream& out, const myGeometricalDBS& s)
{
    return out<<"Geometric blurred segment of width "<<s.width()<<" is ("<<s.a()<<" , "<<s.b()<<" , "<<s.mu()<<" , "<<s.omega()<<" )"<<endl;
}

//getters and settters
void myGeometricalDBS::a(int aA)
{
    this->myA = aA;
}

void myGeometricalDBS::b(int aB)
{
    this->myB = aB;
}

void myGeometricalDBS::mu(int aMu)
{
    this->myMu = aMu;
}

void myGeometricalDBS::omega(int aOmega)
{
    this->myOmega = aOmega;
}

void myGeometricalDBS::width(double aOmega)
{
    this->myOmega = aOmega;
}

void myGeometricalDBS::pVector(Point p)
{
        (this->mypVector).push_back(p);
}

void myGeometricalDBS::pVector(vector<Point> p)
{
    for(vector<Point>::iterator it = p.begin(); it != p.end(); it++)
        (this->mypVector).push_back(*it);
}

int myGeometricalDBS::a() const
{
    return this->myA;
}

int myGeometricalDBS::b() const
{
    return this->myB;
}

int myGeometricalDBS::mu() const
{
    return this->myMu;
}

int myGeometricalDBS::omega() const
{
    return this->myOmega;
}

Point myGeometricalDBS::aF() const
{
    return this->myaF;
}

Point myGeometricalDBS::aL() const
{
    return this->myaL;
}

Point myGeometricalDBS::aUf() const
{
    return this->myaUf;
}

Point myGeometricalDBS::aUl() const
{
    return this->myaUl;
}

Point myGeometricalDBS::aLf() const
{
    return this->myaLf;
}

Point myGeometricalDBS::aLl() const
{
    return this->myaLl;
}

vector<Point> myGeometricalDBS::pVector() const
{
    return this->mypVector;
}

double myGeometricalDBS::width() const
{
    return this->myWidth;
}

bool myGeometricalDBS::isInDSL(Point p)
{
    return ((this->a()*p[0]-this->b()*p[1]) >= this->mu()) &&
           ((this->a()*p[0]-this->b()*p[1]) < this->mu()+this->omega());
}

bool myGeometricalDBS::isInDBS(Point p)
{
    return ((p[0]>=myaF[0] && p[0]<=myaL[0] && p[1]>=myaF[1] && p[1]<=myaL[1]) &&
           (reminder(p) >= this->mu()) &&
           (reminder(p) < this->mu()+this->omega()));
}

bool myGeometricalDBS::isValid()
{
    //verify upper and lower leaning points belongs to segments ????
    return isInDSL(myaLf) && isInDSL(myaLl) && isInDSL(myaUf) && isInDSL(myaUl);
}

bool myGeometricalDBS::isLeaningPoint(Point p)
{
    //return ((this->a()*p[0]-this->b()*p[1]) == this->mu()) ||
    //       ((this->a()*p[0]-this->b()*p[1]) < this->mu()+this->omega());
    return (reminder(p) == this->mu()) || (reminder(p) < this->mu()+this->omega());

}

int myGeometricalDBS::reminder(Point p)
{
    return (this->a()*p[0]-this->b()*p[1]);
}

bool myGeometricalDBS::extendFront(Point p)
{
    //cout<<"before : "<<myHull<<endl;
    myHull.simpleHull_2D(p);
    //cout<<"after : "<<myHull<<endl;

    if (reminder(p)>myMu && reminder(p)<myMu+myOmega-1){//p belongs to Segment
        //cout<<"ok ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        myaL = p;
        return true;
    }
    else if(reminder(p)==myMu){
        //cout<<"(1) : reminder mu ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        ////myaUf = myaUl;
        myaUl = p;
        myaL = p;
        //cout<<"(2) : reminder mu ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return true;
    }
    else if(reminder(p)==myMu+myOmega-1){
        //cout<<"(1) : reminder mu+omega-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        ////myaLf = myaLl;
        myaLl = p;
        myaL = p;
        //cout<<"(2) : reminder mu+omega-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return true;
    }
    else if(reminder(p)<=myMu-1){//p is exterior point, Segment has slope (pLf)
        //cout<<"(1) : reminder <= mu-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        myaUl = p;
        myaUf = myHull.H()[1]; //point before p in the upper convex hull
        int aA = p[1]-myaUf[1];
        int aB = p[0]-myaUf[0];
        myA = aA/pgcd(aA,aB);//p[1]-myaUf[1];
        myB = aB/pgcd(aA,aB);//p[0]-myaUf[0];
        ////myaUl = p;
        ////myaLf = myaLl;
        ////myaLf = myaLl = myHull.findLowerPoint(myaLf,myA,myB);
        //myaLf = myaLl = myHull.findLowerPoint(myaLl,myA,myB);
        myaLf = myaLl = myHull.findLeaningPoint(myaLl,myA,myB);
        this->myMu=myA*myaUl[0] - myB*myaUl[1];//=myA*myaUf[0] - myB*myaUf[1]
        this->myOmega=myA*myaLl[0] - myB*myaLl[1] - this->myMu + 1;//myA*myaLf[0] - myB*myaLf[1] - this->myMu + 1
        //cout<<"(2) : reminder <= mu-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        //cout<<"reminder : "<<reminder(myaUf)<<" , "<<reminder(myaUl)<<" , "<<reminder(myaLf)<<" , "<<reminder(myaLl)<<endl;
        //cout<<"myWith = "<<myWidth<<" and thickness of the line = "<<(double)(myOmega-1)/max(abs(myA),abs(myB))<<endl;
        if(myWidth>0 && (double)(myOmega-1)/max(abs(myA),abs(myB))>myWidth)
        //if(myWidth>0 && (double)(myOmega-1)/abs(myB)>myWidth)
                return false;
        myaL = p;
        return true;
    }
    else if(reminder(p)>=myMu+myOmega){//p is exterior point, Segment has slope (pUf)
        //cout<<"(1) : reminder >= mu+omega ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        myaLl = p;
        myaLf = myHull.H()[myHull.H().size()-2]; //point before p in the lower convex hull
        int aA = p[1]-myaLf[1];
        int aB = p[0]-myaLf[0];
        myA = aA/pgcd(aA,aB);//p[1]-myaLf[1];
        myB = aB/pgcd(aA,aB);//p[0]-myaLf[0];
        ////cout<<"P = "<<p<<endl<<"Lf = "<<myaLf<<endl<<"a = "<<myA<<" b = "<<myB<<endl;
        ////myaUl = p;
        ////myaLf = myaLl;
        ////myaUf = myaUl = myHull.findUpperPoint(myaUf,myA,myB);
        myaUf = myaUl = myHull.findLeaningPoint(myaUl,myA,myB);
        this->myMu=myA*myaUl[0] - myB*myaUl[1];//=myA*myaUf[0] - myB*myaUf[1]
        this->myOmega=myA*myaLl[0] - myB*myaLl[1] - this->myMu + 1;//myA*myaLf[0] - myB*myaLf[1] - this->myMu + 1
        //cout<<"(2) : reminder >= mu+omega ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        //cout<<"reminder : "<<reminder(myaUf)<<" , "<<reminder(myaUl)<<" , "<<reminder(myaLf)<<" , "<<reminder(myaLl)<<endl;
        //cout<<"myWith = "<<myWidth<<" and thickness of the line = "<<(double)(myOmega-1)/max(abs(myA),abs(myB))<<endl;
        if(myWidth>0 && (double)(myOmega-1)/max(abs(myA),abs(myB))>myWidth)
        //if(myWidth>0 && (double)(myOmega-1)/abs(myB)>myWidth)
                return false;
        myaL = p;
        return true;
    }
    return false;
}

//Iterator ????
/*
myIterator myGeometricalDBS::begin(Point p)
{
    myIterator it(this,p);
    return it;
}

vector<Point>::iterator myGeometricalDBS::end(Point p)
{
    myIterator it(this,p);
    return it;
}
*/
