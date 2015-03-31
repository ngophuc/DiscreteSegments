#include "mydsl.h"

myArithmeticalDSL::myArithmeticalDSL()
{

}

myArithmeticalDSL::~myArithmeticalDSL()
{

}

myArithmeticalDSL::myArithmeticalDSL(int aA, int aB, int aMu, int aOmega)
{
    this->myA = aA/pgcd(aA,aB);
    this->myB = aB/pgcd(aA,aB);
    this->myMu = aMu;
    this->myOmega = aOmega;
}

//Overload functions
myArithmeticalDSL& myArithmeticalDSL::operator=(const myArithmeticalDSL& s)
{
    if (this != &s)
    {
        this->myA = s.myA;
        this->myB = s.myB;
        this->myMu= s.myMu;
        this->myOmega=s.myOmega;
    }
    return *this;
}

bool myArithmeticalDSL::operator==(const myArithmeticalDSL& s)
{
    if (this == &s)
        return true;
    return ((this->myA == s.myA) &&
            (this->myB == s.myB) &&
            (this->myMu == s.myMu) &&
            (this->myOmega == s.myOmega));
}

bool myArithmeticalDSL::operator!=(const myArithmeticalDSL& s)
{
    return (*this != s);
}

std::ostream& DGtal::operator<<(std::ostream& out, const myArithmeticalDSL& s)
{
    return out<<"Arithmetic discrete line is ( "
             <<s.a()<<" , "<<s.b()<<" , "<<s.mu()<<" , "<<s.omega()<<" )"<<endl;
}

//getters and settters
void myArithmeticalDSL::a(int aA)
{
    this->myA = aA;
}

void myArithmeticalDSL::b(int aB)
{
    this->myB = aB;
}

void myArithmeticalDSL::mu(int aMu)
{
    this->myMu = aMu;
}

void myArithmeticalDSL::omega(int aOmega)
{
    this->myOmega = aOmega;
}

int myArithmeticalDSL::a() const
{
    return this->myA;
}

int myArithmeticalDSL::b() const
{
    return this->myB;
}

int myArithmeticalDSL::mu() const
{
    return this->myMu;
}

int myArithmeticalDSL::omega() const
{
    return this->myOmega;
}

//services
/*
Point myArithmeticalDSL::pointDSL(Point p)
{
    return Point(p[0], (this->a()*p[0]/this->b())+this->mu());

}
*/
bool myArithmeticalDSL::isInDSL(Point p)
{
    return ((this->a()*p[0]-this->b()*p[1]) >= this->mu()) &&
           ((this->a()*p[0]-this->b()*p[1]) < this->mu()+this->omega());
}

bool myArithmeticalDSL::isLeaningPoint(Point p)
{
    return ((this->a()*p[0]-this->b()*p[1]) == this->mu()) ||
           ((this->a()*p[0]-this->b()*p[1]) < this->mu()+this->omega());
}

int myArithmeticalDSL::reminder(Point p)
{
    return (this->a()*p[0]-this->b()*p[1]);
}

vector<Point> myArithmeticalDSL::pointDSL(Point p)
{
    vector<Point> pVector;
    int lower = ceil((this->a()*p[0]-this->mu()-this->omega())/(double)this->b());
    int upper = floor(this->a()*p[0]-this->mu())/(double)this->b();
    //cout<<"(lower,upper) = "<<lower<<" , "<<upper<<endl;
    for (int i=lower; i<=upper; i++)
    {
        //cout<<"(x,y) = "<<p[0]<<" , "<<i<<" and ins SDL "<<isInDSL(p)<<endl;
        if(p[0]>=0 && i>=0 && isInDSL(Point(p[0],i)))
            pVector.push_back(Point(p[0],i));
    }
    return pVector;
}

vector<Point> myArithmeticalDSL::pointDSL(Point begin, Point end)
{
    vector<Point> pVector, tmp;
    vector<Point>::iterator pVectorIterator;
    Point aP;
    for (int i=begin[0]; i<=end[0]; i++)
    {
        aP[0]=i;
        tmp = this->pointDSL(aP);
        for(pVectorIterator = tmp.begin(); pVectorIterator != tmp.end(); pVectorIterator++)
            pVector.push_back(*pVectorIterator);
    }
    return pVector;
}

//CDrawableWithBoard2D
string myArithmeticalDSL::className()
{
    return "mydsl";
}

//Iterator
/*
vector<Point>::iterator myArithmeticalDSL::begin(Point p)
{
    vector<Point> tmp = this->pointDSL(p);
    vector<Point>::iterator it = tmp.begin();
    //for(it = tmp.begin(); it != tmp.end(); it++);
    return it;
}

vector<Point>::iterator myArithmeticalDSL::end(Point p)
{
    vector<Point> tmp = this->pointDSL(p);
    vector<Point>::iterator it = tmp.begin();
    for( ; it != tmp.end(); it++);
    return it;
}
*/




