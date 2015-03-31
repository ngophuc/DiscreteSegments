#include "mypch.h"
#include <iostream>

myPolylineConvexHull::myPolylineConvexHull()
{
    myBottom = 0;
    myTop = 0;
    mySize=0;
    myD.reserve(0);
}

myPolylineConvexHull::~myPolylineConvexHull()
{

}


myPolylineConvexHull::myPolylineConvexHull(int n)
{
    myBottom = 0;
    myTop = 0;
    mySize=n;
    myD.reserve(2*n+1);
    //cout<<"capacity of D is "<<myD.capacity()<<endl;
}

/*
myPolylineConvexHull::myPolylineConvexHull(myPolylineConvexHull h)
{
    myBottom = h.bottom();
    myTop = h.top();
    mySize=h.size();
    myD = h.myD();
    myH = h.myH();
}
*/

myPolylineConvexHull& myPolylineConvexHull::operator=(const myPolylineConvexHull& h)
{
    if (this != &h)
    {
        this->mySize = h.mySize;
        this->myTop = h.myTop;
        this->myBottom = h.myBottom;
        this->myD = h.myD;//vector<Point>
        this->myH = h.myH;//vector<Point>
    }
    return *this;
}

std::ostream& DGtal::operator<<(std::ostream& out, const myPolylineConvexHull& h)
{
    /*
    out <<"Convex hull info :"<<endl
            <<"size : "<<h.size()<<endl
            <<"top : "<<h.top()<<endl
            <<"bottom : "<<h.bottom()<<endl
            <<"convex hull : "<<endl;
    h.displayCovexHull();
    */
    out <<"Convex hull ( "<<h.bottom()<<" , "<<h.top()<<" )  : "<<endl;
    h.displayCovexHull();
    return out;
}

// isLeft(): test if a point is Left|On|Right of an infinite line.
//    Input:  three points P0, P1, and P2
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2 on the line
//            <0 for P2 right of the line
//    See: Algorithm 1 on Area of Triangles
int isLeft( Point P0, Point P1, Point P2 )
{
    return (P1[0] - P0[0])*(P2[1] - P0[1]) - (P2[0] - P0[0])*(P1[1] - P0[1]);
}

// simpleHull_2D(): Melkman's 2D simple polyline O(n) convex hull algorithm
//    Input:  P[] = array of 2D vertex points for a simple polyline
//    Output: H[] = output convex hull array of vertices (max is n)
//    Return: h   = the number of points in H[]
myPolylineConvexHull::myPolylineConvexHull(vector<Point> P)
{
    int n = mySize = P.size(); //n   = the number of points in P[]
    myD.reserve(2*n+1);

    // initial bottom and top deque indices
    myBottom = n-2;
    myTop = myBottom+3;

    // 3rd vertex is at both bottom and top
    myD[myBottom] = myD[myTop] = P[2];

    // initialize a deque D[] from bottom to top so that the
    // 1st three vertices of P[] are a ccw triangle
    if (isLeft(P[0], P[1], P[2]) > 0) {
        myD[myBottom+1] = P[0];
        myD[myBottom+2] = P[1];           // ccw vertices are: 2,0,1,2
    }
    else {
        myD[myBottom+1] = P[1];
        myD[myBottom+2] = P[0];           // ccw vertices are: 2,1,0,2
    }

    // compute the hull on the deque myD[]
    for (int i=3; i < n; i++) {   // process the rest of vertices
        // test if next vertex is inside the deque hull
        if ((isLeft(myD[myBottom], myD[myBottom+1], P[i]) > 0) &&
            (isLeft(myD[myTop-1], myD[myTop], P[i]) > 0) )
                 continue;         // skip an interior vertex

        // incrementally add an exterior vertex to the deque hull
        // get the rightmost tangent at the deque myBottom
        while (isLeft(myD[myBottom], myD[myBottom+1], P[i]) <= 0)
            ++myBottom;                 // remove myBottom of deque
        myD[--myBottom] = P[i];           // insert P[i] at bot of deque

        // get the leftmost tangent at the deque top
        while (isLeft(myD[myTop-1], myD[myTop], P[i]) <= 0)
            --myTop;                 // pop top of deque
        myD[++myTop] = P[i];           // push P[i] onto top of deque
    }

    // transcribe deque myD[] to the output hull array myH[]
    for (int h=0; h <= (myTop-myBottom); h++) // hull vertex counter
        myH.push_back(myD[myBottom + h]);
}

//getters and setters
void myPolylineConvexHull::size(int n)
{
    //this->mySize = n;
    this->mySize=n;
    //cout<<"myD capacity issssssss "<<myD.capacity()<<endl;
    //this->myD.clear();
    this->myD.reserve(2*n+1);
    //cout<<"myD capacity issssssss "<<myD.capacity()<<endl;
}

void myPolylineConvexHull::top(int n)
{
    this->myTop = n;
}

void myPolylineConvexHull::bottom(int n)
{
    this->myBottom = n;
}

void myPolylineConvexHull::D(vector<Point> d)
{
    this->myD = d;
}

void myPolylineConvexHull::H(vector<Point> h)
{
    this->myH = h;
}
/*
void myPolylineConvexHull::vDistance(double d)
{
    this->myVDistance = d;
}
*/
int myPolylineConvexHull::size() const
{
    return this->mySize;
}

int myPolylineConvexHull::top() const
{
    return this->myTop;
}

int myPolylineConvexHull::bottom() const
{
    return this->myBottom;
}

int myPolylineConvexHull::capacity() const
{
    return this->myD.capacity();
}

vector<Point> myPolylineConvexHull::D() const
{
    return this->myD;
}

vector<Point> myPolylineConvexHull::H()
{
    int size = myTop-myBottom+1;
    vector<Point> v(size);
    myH = v;
    // transcribe deque myD[] to the output hull array myH[]
    for (int h=0; h < size; h++) // hull vertex counter
        //myH.push_back(myD[myBottom + h]);
        myH[h]=myD[myBottom + h];
    /*
    cout<<"convex hull :"<<endl;
    for (int h=0; h < size; h++) // hull vertex counter
        cout<<myD[myTop - h]<<endl;
    cout<<"end convex hull :"<<endl;
    */
    return this->myH;
}
/*
double myPolylineConvexHull::vDistance()
{
    return this->myVDistance;
}
*/
//services
void myPolylineConvexHull::displayCovexHull() const
{
    if(myTop!=0 & myBottom!=0)
    {
        int size = myTop-myBottom+1;
        for (int h=0; h < size; h++) // hull vertex counter
            cout<<myD[myBottom + h]<<" ";
    }
}

//add a point to the convex hull
void myPolylineConvexHull::simpleHull_2D(Point P)
{
    int s = (myTop-myBottom)> 0 ? myTop-myBottom : myH.size();
    // update the hull H[] with point P
    if(s<2)//myH.size()
    {
        myH.push_back(P);
        ////myVDistance=0;
        myTop=myBottom=0;
    }
    else
    {
        if(s==2)//myH.size()
        {
            int n = mySize;
            // initial bottom and top deque indices
            myBottom = n-2;
            myTop = myBottom+3;

            // 3rd vertex is at both bottom and top
            myD[myBottom] = myD[myTop] = P;

            // initialize a deque D[] from bottom to top so that the
            // 1st three vertices of P[] are a ccw triangle
            if (isLeft(myH[0], myH[1], P) > 0) {
                myD[myBottom+1] = myH[0];
                myD[myBottom+2] = myH[1];           // ccw vertices are: 2,0,1,2
            }
            else {
                myD[myBottom+1] = myH[1];
                myD[myBottom+2] = myH[0];           // ccw vertices are: 2,1,0,2
            }
            //cout<<"3 hull points : "<<endl<<myD[myBottom]<<endl<<myD[myBottom+1]<<endl<<myD[myBottom+2]<<endl;

            // calculate the distance
            //myVDistance=max(verticalDistance(myD[myTop-1],myD[myBottom-1],myD[myBottom]),
            //                verticalDistance(myD[myBottom+1],myD[myTop-1],myD[myTop]));
            ////myVDistance=verticalDistance(myD[myBottom+1],myD[myTop-1],myD[myTop]);
            /*
            // myH = H();
            // transcribe deque myD[] to the output hull array myH[]
            for (int h=0; h <= (myTop-myBottom); h++) // hull vertex counter
                myH.push_back(myD[myBottom + h]);
                //myH[h]=myD[myBottom + h];
            */
            myH.pop_back();
            myH.pop_back();
        }
        else // process others vertices
        {
            // compute the hull on the deque myD[]
            // test if the vertex is not inside the deque hull
            if (not ((isLeft(myD[myBottom], myD[myBottom+1], P) > 0) &&
                     (isLeft(myD[myTop-1], myD[myTop], P) > 0)))
            {
                // incrementally add an exterior vertex to the deque hull
                // get the rightmost tangent at the deque myBottom
                while (myBottom<myTop && isLeft(myD[myBottom], myD[myBottom+1], P) <= 0)
                    ++myBottom;                 // remove myBottom of deque
                if(myBottom == myTop)
                    myBottom = myTop-2;
                myD[--myBottom] = P;           // insert P at bot of deque

                // get the leftmost tangent at the deque top
                while (myTop>myBottom && isLeft(myD[myTop-1], myD[myTop], P) <= 0)
                    --myTop;                 // pop top of deque
                if(myBottom == myTop)
                    myTop = myBottom+2;
                myD[++myTop] = P;           // push P onto top of deque

                /*
                // myH = H();
                // transcribe deque myD[] to the output hull array myH[]
                for (int h=0; h <= (myTop-myBottom); h++) // hull vertex counter
                    //myH.push_back(myD[myBottom + h]);
                    myH[h]=myD[myBottom + h];
                */
                // calculate the distance
                //myVDistance=verticalDistance(myD[myBottom+1],myD[myBottom],myD[myBottom+2]);
                /*
                cout<<"Point myD[myBottom+1] : "<<myD[myBottom+1]<<endl;
                cout<<"Point myD[myBottom+2] : "<<myD[myBottom+2]<<endl;
                cout<<"Point myD[myTop-1]    : "<<myD[myTop-1]<<endl;
                cout<<"Point myD[myTop-2]    : "<<myD[myTop-2]<<endl;
                */
                //myVDistance=max(verticalDistance(P,myD[myBottom],myD[myBottom+2]),verticalDistance(P,myD[myBottom],myD[myBottom+2]));
                //myVDistance=max(verticalDistance(myD[myTop-1],myD[myBottom-1],myD[myBottom]),
                //                verticalDistance(myD[myBottom+1],myD[myTop-1],myD[myTop]));
                /**** Hull *****
                cout<<"convex hull :"<<endl;
                for (int h=0; h < myTop-myBottom+1; h++) // hull vertex counter
                    cout<<myD[myBottom + h]<<endl;
                cout<<"end convex hull :"<<endl;
                /**** Hull *****/

                /*
                cout<<"myD[myTop-1] = "<<myD[myTop-1]<<endl
                   <<"myD[myBottom-1] = "<<myD[myBottom-1]<<endl
                   <<"myD[myBottom] = "<<myD[myBottom]<<endl;
                myVDistance=verticalDistance(myD[myTop-1],myD[myBottom-1],myD[myBottom]);
                */
                /*
                cout<<"myD[myBottom+1] = "<<myD[myBottom+1]<<endl
                   <<"myD[myTop-1] = "<<myD[myTop-1]<<endl
                   <<"myD[myTop] = "<<myD[myTop]<<endl;
                */
                ////myVDistance=verticalDistance(myD[myBottom+1],myD[myTop-1],myD[myTop]);
            }
        }
    }
}

//vector<Point> myPolylineConvexHull::simpleHull_2D(vector<Point> P);//add to convex hull a set of points

bool myPolylineConvexHull::findPoint(Point P)//find a point in the convex hull
{
    int size = myTop-myBottom+1;
    Point tmp;
    for (int h=0; h < size; h++){ // hull vertex counter
        tmp = myD[myBottom + h];
        if(tmp==P)
            return true;
    }
    return false;
}

//find a point after P in the hull such that
//the slope of its with the neighbour is > a/b
Point myPolylineConvexHull::findLeaningPoint(Point P, int a, int b)
{
    int size = myTop-myBottom+1;
    Point tmp, tmp_next;
    double slope;

    /**** Hull *****/
    if(size<3)
    {
        cout<<"top = "<<myTop<<" and bottom = "<<myBottom;
        cout<<" => convex hull ("<<mySize<<")"<<endl;
        for (int h=0; h < size; h++) // hull vertex counter
            cout<<myD[myBottom + h]<<endl;
        cout<<"end convex hull."<<endl;
    }
    /**** Hull *****/

    int h=0;
    while(myD[myBottom + h] != P && h < size) h++;
    if(h<size)//if(myD[myBottom + h] == P)
    {
        for (int i = h; i < size - 1; i++){ // hull vertex counter
            tmp = myD[myBottom + i];
            tmp_next = myD[myBottom + i + 1];
            slope = (double)(tmp_next[1]-tmp[1])/(tmp_next[0]-tmp[0]);
            //cout<<"tmp ="<<tmp<<endl<<"tmp_next ="<<tmp_next<<" slope = "<<slope<<" a/b = "<<(double)a/b<<endl;
            if(slope > (double(a)/b))
                return tmp;
        }
    }
    return P;
}

//find a point after P in the hull such that
//the slope of its with the neighbour is > a/b
Point myPolylineConvexHull::findLowerPoint(Point P, int a, int b)
{

    int size = myTop-myBottom+1;
    Point tmp, tmp_next;
    double slope;

    /**** Hull *****
    cout<<"convex hull :"<<endl;
    for (int h=0; h < size; h++) // hull vertex counter
        cout<<myD[myBottom + h]<<endl;
    cout<<"end convex hull :"<<endl;
    /**** Hull *****/

    int h=0;
    while(myD[myBottom + h] != P && h < size) h++;
    if(h<size)//if(myD[myBottom + h] == P)
    {
        for (int i = h; i < size - 1; i++){ // hull vertex counter
            tmp = myD[myBottom + i];
            tmp_next = myD[myBottom + i + 1];
            //cout<<"tmp ="<<tmp<<endl<<"tmp_next ="<<tmp_next<<endl;
            slope = (double)(tmp[1]-tmp_next[1])/(tmp[0]-tmp_next[0]);
            if(slope > (double(a)/b))
                return tmp;
        }
    }
    return P;
}

//find a point after P in the hull such that
//the slope of its with the neighbour is < a/b
Point myPolylineConvexHull::findUpperPoint(Point P, int a, int b)
{
    int size = myTop-myBottom+1;
    Point tmp, tmp_next;
    double slope;

    /**** Hull *****
    cout<<"convex hull :"<<endl;
    for (int h=0; h < size; h++) // hull vertex counter
        cout<<myD[myTop - h]<<endl;
    cout<<"end convex hull :"<<endl;
    /**** Hull *****/

    int h=size-1;
    while(myD[myTop - h] != P && h >= 0) h--;
    if(h>=0)//if(myD[myTop - h] == P)
    {
        for (int i = h; i < size -1; i++){ // hull vertex counter
            tmp = myD[myTop - i];
            tmp_next = myD[myTop - i - 1];
            slope = (double)(tmp[1]-tmp_next[1])/(tmp[0]-tmp_next[0]);
            //cout<<"h = "<<h<<" my top = "<<myTop<<" tmp = "<<tmp<<" tmp_next = "
            //    <<tmp_next<<"slope = "<<slope<<" a = "<<a<<" b = "<<b<<endl;
            if(slope < (double(a)/b))
                return tmp_next;
        }
    }
    return P;
}

