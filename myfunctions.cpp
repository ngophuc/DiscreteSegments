#include "myfunctions.h"

int max(int n, int m)
{
    return n>m ? n:m;
}

int min(int n, int m)
{
    return n<m ? n:m;
}

int pgcd(int a, int b)
{
    a = abs(a);
    b = abs(b);
    int r;
    while (b != 0)
    {
        r = a%b;
        a = b;
        b = r;
    }
    return a;
}

//vertical distance of p to the line (aF,aL)
double verticalDistance(Point p, Point aF, Point aL)
{
    //line (aF,aL) y = a x + b
    cout<<"p = "<<p<<endl<<"aF = "<<aF<<endl<<"aL = "<<aL<<endl;
    double a = (double)(aL[1]-aF[1])/(aL[0]-aF[0]);
    double b = aF[1]-a*aF[0];
    return fabs(p[1] - a*p[0]-b);//vertical distance of p to the line
}

//max vertical distance between (Uf,Ul), (aF,aL)
double verticalDistance(Point Uf, Point Ul, Point Lf, Point Ll)
{
    //upper line y = a1 x + b1
    double a1 = (double)(Ul[1]-Uf[1])/(Ul[0]-Uf[0]);
    double b1 = Uf[1]-a1*Uf[0];
    double d11 = a1*Lf[0]+b1;//vertical distance of Lf to upper line
    double d12 = a1*Ll[0]+b1;//vertical distance of Ll to upper line

    //lower line y = a2 x + b2
    double a2 = (double)(Ll[1]-Lf[1])/(Ll[0]-Lf[0]);
    double b2 = Lf[1]-a2*Lf[0];
    double d21 = a2*Uf[0]+b2;//vertical distance of Uf to lower line
    double d22 = a2*Ul[0]+b2;//vertical distance of Ul to lower line

    return max(d11,max(d12,max(d21,d22)));
}

PointVector<2,double> intersectionLines(double a, double b, double c, double d, double e, double f)
{
    //l1 : a x - b y = c
    //l1 : d x - e y = f
    PointVector<2,double> p(0,0);
    if(b*d-a*e!=0)
    {
        p[0] = (b*f - c*e)/(b*d-a*e);
        p[1] = (a*p[0] - c)/b;
    }
    //cout<<"lines ("<<a<<","<<b<<","<<c<<") and ("<<d<<","<<e<<","<<f<<") ==> intersection point : "<<p<<endl;
    return p;
}

int findElement(vector<Point> vec, Point p)
{
    vector<Point>::iterator it = find(vec.begin(),vec.end(),p);
    if(it != vec.end())
        return (it-vec.begin());
    else
        return -1;
}


double distance(Point p1, Point p2)
{
    return sqrt((p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]));
}

double angle(Point v1, Point v2)
{
    //normalize the vector
    PointVector<2,double> n_v1, n_v2;
    n_v1[0] = v1[0]/(sqrt(v1[0]*v1[0] + v1[1]*v1[1]));
    n_v1[1] = v1[1]/(sqrt(v1[0]*v1[0] + v1[1]*v1[1]));

    n_v2[0] = v2[0]/(sqrt(v2[0]*v2[0] + v2[1]*v2[1]));
    n_v2[1] = v2[1]/(sqrt(v2[0]*v2[0] + v2[1]*v2[1]));

    return acos(n_v1[0]*n_v2[0]+n_v1[1]*n_v2[1]);
}
