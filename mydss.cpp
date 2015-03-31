#include "mydss.h"

myArithmeticalDSS::myArithmeticalDSS()
{

}

myArithmeticalDSS::~myArithmeticalDSS()
{

}

//constructor of DSS naive seg betwen two points
myArithmeticalDSS::myArithmeticalDSS(Point aF, Point aL)
{
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

    //Points of DSS from aF to aL
    mypVector = this->pointDSS(aF,aL);
}

myArithmeticalDSS::myArithmeticalDSS(int aA, int aB, Point aF, Point aL, Point aUf, Point aUl, Point aLf, Point aLl)
{
    this->myA = aA/pgcd(aA,aB);
    this->myB = aB/pgcd(aA,aB);
    this->myaF = aF;
    this->myaL = aL;
    this->myaUf = aUf;
    this->myaUl = aUl;
    this->myaLf = aLf;
    this->myaLl = aLl;

    // upper leaning point has reminder : ax - by = mu
    // lower leaning point has reminder : ax - by = mu + omega - 1
    this->myMu=aA*aUf[0] - aB*aUf[1];//=aA*aUl[0] - aB*aUl[1]
    this->myOmega=aA*aLf[0] - aB*aLf[1] - this->myMu + 1;

    //Points of DSS from aF to aL
    mypVector = this->pointDSS(aF,aL);
}

myArithmeticalDSS::myArithmeticalDSS(int aA, int aB, int aMu, int aOmega, Point aF, Point aL)
{
    this->myA = aA/pgcd(aA,aB);
    this->myB = aB/pgcd(aA,aB);
    this->myMu=aMu;
    this->myOmega=aOmega;
    this->myaF = aF;
    this->myaL = aL;

    ///////////////// To calculate
    this->myaUf = aF;
    this->myaUl = aL;
    this->myaLf = aF;
    this->myaLl = aL;

    //Points of DSS from aF to aL
    mypVector = this->pointDSS(aF,aL);
}

//Overload functions
myArithmeticalDSS& myArithmeticalDSS::operator=(const myArithmeticalDSS& s)
{
    if (this != &s)
    {
        this->myA = s.myA;
        this->myB = s.myB;
        this->myMu= s.myMu;
        this->myOmega=s.myOmega;
        this->myaF = s.myaF;
        this->myaL = s.myaL;
        this->myaUf = s.myaUf;
        this->myaUl = s.myaUl;
        this->myaLf = s.myaLf;
        this->myaLl = s.myaLl;
        this->mypVector = s.mypVector;
    }
    return *this;
}

bool myArithmeticalDSS::operator==(const myArithmeticalDSS& s)
{
    if (this == &s)
        return true;
    return ((this->myA == s.myA) &&
            (this->myB == s.myB) &&
            (this->myMu == s.myMu) &&
            (this->myOmega == s.myOmega) ); /* &&
            (this->myaF == s.myaF) &&
            (this->myaL == s.myaL) &&
            (this->myaUf == s.myaUf) &&
            (this->myaUl == s.myaUl) &&
            (this->myaLf == s.myaLf) &&
            (this->myaLl == s.myaLl) );
            */
}

bool myArithmeticalDSS::operator!=(const myArithmeticalDSS& s)
{
    return (*this != s);
}

std::ostream& DGtal::operator<<(std::ostream& out, const myArithmeticalDSS& s)
{
    return out<<"Arithmetic discrete segment is ( "
              <<s.a()<<" , "<<s.b()<<" , "<<s.mu()<<" , "<<s.omega()<<" )"<<endl;
}

//getters and settters
void myArithmeticalDSS::a(int aA)
{
    this->myA = aA;
}

void myArithmeticalDSS::b(int aB)
{
    this->myB = aB;
}

void myArithmeticalDSS::mu(int aMu)
{
    this->myMu = aMu;
}

void myArithmeticalDSS::omega(int aOmega)
{
    this->myOmega = aOmega;
}

void myArithmeticalDSS::pVector(Point p)
{
        (this->mypVector).push_back(p);
}

void myArithmeticalDSS::pVector(vector<Point> p)
{
    for(vector<Point>::iterator it = p.begin(); it != p.end(); it++)
        (this->mypVector).push_back(*it);
}

int myArithmeticalDSS::a() const
{
    return this->myA;
}

int myArithmeticalDSS::b() const
{
    return this->myB;
}

int myArithmeticalDSS::mu() const
{
    return this->myMu;
}

int myArithmeticalDSS::omega() const
{
    return this->myOmega;
}

Point myArithmeticalDSS::aF() const
{
    return this->myaF;
}

Point myArithmeticalDSS::aL() const
{
    return this->myaL;
}

Point myArithmeticalDSS::aUf() const
{
    return this->myaUf;
}

Point myArithmeticalDSS::aUl() const
{
    return this->myaUl;
}

Point myArithmeticalDSS::aLf() const
{
    return this->myaLf;
}

Point myArithmeticalDSS::aLl() const
{
    return this->myaLl;
}

vector<Point> myArithmeticalDSS::pVector() const
{
    return this->mypVector;
}

bool myArithmeticalDSS::isInDSL(Point p)
{
    return ((this->a()*p[0]-this->b()*p[1]) >= this->mu()) &&
           ((this->a()*p[0]-this->b()*p[1]) < this->mu()+this->omega());
}

bool myArithmeticalDSS::isInDSS(Point p)
{
    return ((p[0]>=myaF[0] && p[0]<=myaL[0] && p[1]>=myaF[1] && p[1]<=myaL[1]) &&
           (reminder(p) >= this->mu()) &&
           (reminder(p) < this->mu()+this->omega()));
}

bool myArithmeticalDSS::isValid()
{
    //verify upper and lower leaning points belongs to segments ????
    return isInDSL(myaLf) && isInDSL(myaLl) && isInDSL(myaUf) && isInDSL(myaUl);
}

bool myArithmeticalDSS::isLeaningPoint(Point p)
{
    //return ((this->a()*p[0]-this->b()*p[1]) == this->mu()) ||
    //       ((this->a()*p[0]-this->b()*p[1]) < this->mu()+this->omega());
    return (reminder(p) == this->mu()) || (reminder(p) < this->mu()+this->omega());

}

int myArithmeticalDSS::reminder(Point p)
{
    return (this->a()*p[0]-this->b()*p[1]);
}

vector<Point> myArithmeticalDSS::pointDSS(Point p)
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

vector<Point> myArithmeticalDSS::pointDSS(Point begin, Point end)
{
    vector<Point> pVector, tmp;
    vector<Point>::iterator pVectorIterator;
    Point aP;
    for (int i=begin[0]; i<=end[0]; i++)
    {
        aP[0]=i;
        tmp = this->pointDSS(aP);
        for(pVectorIterator = tmp.begin(); pVectorIterator != tmp.end(); pVectorIterator++)
            pVector.push_back(*pVectorIterator);
    }
    return pVector;
}

bool myArithmeticalDSS::extendFront(Point p)
{
    //return reminder(p)>=myMu && reminder(p)<myMu+myOmega;
    if (reminder(p)>myMu && reminder(p)<myMu+myOmega-1){//p belongs to Segment
        cout<<"ok ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return true;
    }
    else if(reminder(p)==myMu){
        cout<<"(1) : reminder mu ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        myaUf = myaUl;
        myaUl = p;
        cout<<"(2) : reminder mu ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return true;
    }
    else if(reminder(p)==myMu+myOmega-1){
        cout<<"(1) : reminder mu+omega-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        myaLf = myaLl;
        myaLl = p;
        cout<<"(2) : reminder mu+omega-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return true;
    }
    else if(reminder(p)==myMu-1){//p is weakly exterior point, Segment has slope (pLf)
        cout<<"(1) : reminder mu-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        int aA = p[1]-myaUf[1];
        int aB = p[0]-myaUf[0];
        myA = aA/pgcd(aA,aB);//p[1]-myaUf[1];
        myB = aB/pgcd(aA,aB);//p[0]-myaUf[0];
        myaUl = p;
        this->myMu=myA*myaUl[0] - myB*myaUl[1];//=myA*myaUf[0] - myB*myaUf[1]
        this->myOmega=myA*myaLl[0] - myB*myaLl[1] - this->myMu + 1;//myA*myaLf[0] - myB*myaLf[1] - this->myMu + 1
        cout<<"(2) : reminder mu-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return true;
    }
    else if(reminder(p)==myMu+myOmega){//p is weakly exterior point, Segment has slope (pUf)
        cout<<"(1) : reminder mu+omega ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        cout<<"(1) : reminder mu+omega ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        //if(reminder(myaLf)==reminder(p)-1)
        int aA = p[1]-myaLf[1];
        int aB = p[0]-myaLf[0];
        myA = aA/pgcd(aA,aB);//p[1]-myaLf[1];
        myB = aB/pgcd(aA,aB);//p[0]-myaLf[0];
        myaLl = p;
        this->myMu=myA*myaUl[0] - myB*myaUl[1];//=myA*myaUf[0] - myB*myaUf[1];
        this->myOmega=myA*myaLl[0] - myB*myaLl[1] - this->myMu + 1;//myA*myaLf[0] - myB*myaLf[1] - this->myMu + 1
        cout<<"(2) : reminder mu+omega ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return true;
    }
    else
        return false;
}

int myArithmeticalDSS::extendFrontStandard(Point p)
{
    if (reminder(p)>myMu && reminder(p)<myMu+myOmega-1){//p belongs to Segment
        cout<<"ok ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return 1;
    }
    else if(reminder(p)==myMu){
        cout<<"(1) : reminder mu ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        myaUf = myaUl;
        myaUl = p;
        cout<<"(2) : reminder mu ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return 2;
    }
    else if(reminder(p)==myMu+myOmega-1){
        cout<<"(1) : reminder mu+omega-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        myaLf = myaLl;
        myaLl = p;
        cout<<"(2) : reminder mu+omega-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return 3;
    }
    else if(reminder(p)==myMu-1){//p is weakly exterior point, Segment has slope (pLf)
        cout<<"(1) : reminder mu-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        int aA = p[1]-myaUf[1];
        int aB = p[0]-myaUf[0];
        myA = aA/pgcd(aA,aB);//p[1]-myaUf[1];
        myB = aB/pgcd(aA,aB);//p[0]-myaUf[0];
        myaUl = p;
        this->myMu=myA*myaUl[0] - myB*myaUl[1];//=myA*myaUf[0] - myB*myaUf[1]
        //this->myOmega=myA*myaLl[0] - myB*myaLl[1] - this->myMu + 1;//myA*myaLf[0] - myB*myaLf[1] - this->myMu + 1
        this->myOmega=max(abs(myA),abs(myB));
        cout<<"(2) : reminder mu-1 ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return 4;
    }
    else if(reminder(p)==myMu+myOmega){//p is weakly exterior point, Segment has slope (pUf)
        cout<<"(1) : reminder mu+omega ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        int aA = p[1]-myaLf[1];
        int aB = p[0]-myaLf[0];
        myA = aA/pgcd(aA,aB);//p[1]-myaLf[1];
        myB = aB/pgcd(aA,aB);//p[0]-myaLf[0];
        myaLl = p;
        this->myMu=myA*myaUl[0] - myB*myaUl[1];//=myA*myaUf[0] - myB*myaUf[1];
        //cout<<"(2) : reminder mu+omega ==> "<<myaLl<<myA<<" "<<myB<<" "<<myMu<<endl;
        //this->myOmega=myA*myaLl[0] - myB*myaLl[1] - this->myMu + 1;//myA*myaLf[0] - myB*myaLf[1] - this->myMu + 1
        this->myOmega=max(abs(myA),abs(myB));
        cout<<"(2) : reminder mu+omega ==> "<<myaUf<<myaUl<<myaLf<<myaLl<<endl;
        return 5;
    }
    else
        return -1;
}

//Iterator ????
/*
myIterator myArithmeticalDSS::begin(Point p)
{
    myIterator it(this,p);
    return it;
}

vector<Point>::iterator myArithmeticalDSS::end(Point p)
{
    myIterator it(this,p);
    return it;
}
*/






