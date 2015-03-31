#include <iostream>
#include <exception>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"
#include "mydsl.h"
#include "mydss.h"
#include "mydbs.h"
#include "mypch.h"

//#include "AlphaThickSegmentComputer.h"

#include "fraction.h"

//! [ArithmeticalDSSHeader]
#include "DGtal/geometry/curves/ArithmeticalDSS.h"
//! [ArithmeticalDSSHeader]

using namespace std;
using namespace DGtal;
using namespace Z2i;

typedef PointVector<2,int> Point;
typedef PointVector<2,double> dPoint;
typedef std::vector<Point> Range;
typedef std::vector<Point>::const_iterator ConstIterator;
typedef ArithmeticalDSS<ConstIterator,int,4> DSS4;

/**
 * Example of a test. To be completed.
 *
 */
void testFuzzySegmentOnePoint()
{
    Board2D aBoard;
    Point bottomLeft( -20, -20 );
    Point topRight( 20, 20 );
    Domain domain( bottomLeft, topRight );
    // Draw the grid
    aBoard << SetMode(domain.className(), "Grid") << domain;

    std::vector<Z2i::Point> aContour;
    aContour.push_back(Point(-15,10));
    aContour.push_back(Point(-14,11));
    aContour.push_back(Point(-14,9));
    aContour.push_back(Point(-13,9));
    aContour.push_back(Point(-13,7));
    aContour.push_back(Point(-12,7));
    aContour.push_back(Point(-12,5));
    aContour.push_back(Point(-11,4));
    aContour.push_back(Point(-9,3));
    aContour.push_back(Point(-8,3));
    //
    aContour.push_back(Point(-7,4));
    aContour.push_back(Point(-5,2));
    aContour.push_back(Point(-3,1));
    aContour.push_back(Point(-3,0));
    aContour.push_back(Point(-2,0));
    aContour.push_back(Point(0,0));
    aContour.push_back(Point(2,0));
    aContour.push_back(Point(2,1));
    aContour.push_back(Point(3,2));
    aContour.push_back(Point(5,2));
    aContour.push_back(Point(6,4));
    aContour.push_back(Point(7,3));
    aContour.push_back(Point(9,4));
    //
    aContour.push_back(Point(10,4));
    aContour.push_back(Point(10,8));
    aContour.push_back(Point(11,6));
    aContour.push_back(Point(11,7));
    aContour.push_back(Point(11,9));
    aContour.push_back(Point(12,12));
    aContour.push_back(Point(13,10));
    aContour.push_back(Point(13,11));

    /* display de boundary */
    aBoard << SetMode((*aContour.begin()).className(), "Both");
    for (std::vector<Z2i::Point>::const_iterator it = aContour.begin();
         it != aContour.end(); it++){
      aBoard << *it;
    }

    /* display de boundary */
    typedef  AlphaThickSegmentComputer< Z2i::Point > AlphaThickSegmentComputer2D;
    trace.beginBlock ( "Testing alphaThick segment" );
    AlphaThickSegmentComputer2D anAlphaThickSegmentComputer;
    anAlphaThickSegmentComputer.init(aContour.begin(),5);
    AlphaThickSegmentComputer2D anAlphaThickSegmentComputer2;
    anAlphaThickSegmentComputer2.init(aContour.begin(), 10);
    AlphaThickSegmentComputer2D anAlphaThickSegmentComputer3;
    anAlphaThickSegmentComputer3.init(aContour.begin(), 2);
    AlphaThickSegmentComputer2D anAlphaThickSegmentComputer4;
    anAlphaThickSegmentComputer4.init(aContour.begin(), 1);

  /* travel over the contour points and add to the seg */
  while (anAlphaThickSegmentComputer.end() != aContour.end() &&
         anAlphaThickSegmentComputer.extendFront()){}
  while (anAlphaThickSegmentComputer2.end() != aContour.end() &&
         anAlphaThickSegmentComputer2.extendFront() ){}
  while (anAlphaThickSegmentComputer3.end() != aContour.end() &&
         anAlphaThickSegmentComputer3.extendFront()){}
  while (anAlphaThickSegmentComputer4.end() != aContour.end() &&
         anAlphaThickSegmentComputer4.extendFront()){}
  /* travel over the contour points and add to the seg */

  /* Display convexhull */
  std::vector<Z2i::Point> aVect = anAlphaThickSegmentComputer.getConvexHull();
  aBoard.setLineWidth(5);
  aBoard.setPenColor(DGtal::Color::Purple);
  for (unsigned int i = 0; i < aVect.size(); i++){
    aBoard.drawLine(aVect.at(i)[0], aVect.at(i)[1],
                    aVect.at((i+1)%aVect.size())[0],
                    aVect.at((i+1)%aVect.size())[1]);
  }
  /* Display convexhull */
  /* Display boundingbox */
  aBoard << SetMode((*anAlphaThickSegmentComputer.begin()).className(), "Grid");
  aBoard << CustomStyle( anAlphaThickSegmentComputer2.className(),
                         new CustomColors( DGtal::Color::Green, DGtal::Color::None ) );
  aBoard << anAlphaThickSegmentComputer2;
  aBoard << CustomStyle( anAlphaThickSegmentComputer.className(),
                         new CustomColors( DGtal::Color::Blue, DGtal::Color::None ) );
  aBoard << anAlphaThickSegmentComputer;
  aBoard << CustomStyle( anAlphaThickSegmentComputer3.className(),
                         new CustomColors( DGtal::Color::Yellow, DGtal::Color::None ) );
  aBoard << anAlphaThickSegmentComputer3;
  aBoard << CustomStyle( anAlphaThickSegmentComputer4.className(),
                         new CustomColors( DGtal::Color::Magenta, DGtal::Color::None ) );
  aBoard << anAlphaThickSegmentComputer4;
  /* Display boundingbox */

  /* Display the input curve *
  aBoard << SetMode((*aContour.begin()).className(), "Grid");
  for (std::vector<Z2i::Point>::const_iterator it = aContour.begin();
       it != aContour.end(); it++){
    aBoard << *it;
    if (it+1 != aContour.end()){
      Z2i::Point next = *(it+1);
      aBoard.setPenColor(DGtal::Color::Gray);
      aBoard.drawLine((*it)[0], (*it)[1], next[0], next[1]);
    }
  }
  /* Display the input curve */

  aBoard.saveSVG("fuzzySegment.svg");
}

void testFuzzySegmentOnCurve()
{
    Board2D aBoard;
    Point bottomLeft( -20, -20 );
    Point topRight( 20, 20 );
    Domain domain( bottomLeft, topRight );
    // Draw the grid
    aBoard << SetMode(domain.className(), "Grid") << domain;

    std::vector<Z2i::Point> aContour;
    aContour.push_back(Point(-15,10));
    aContour.push_back(Point(-14,11));
    aContour.push_back(Point(-14,9));
    aContour.push_back(Point(-13,9));
    aContour.push_back(Point(-13,7));
    aContour.push_back(Point(-12,7));
    aContour.push_back(Point(-12,5));
    aContour.push_back(Point(-11,4));
    aContour.push_back(Point(-9,3));
    aContour.push_back(Point(-8,3));
    //
    aContour.push_back(Point(-7,4));
    aContour.push_back(Point(-5,2));
    aContour.push_back(Point(-3,1));
    aContour.push_back(Point(-3,0));
    aContour.push_back(Point(-2,0));
    aContour.push_back(Point(0,0));
    aContour.push_back(Point(2,0));
    aContour.push_back(Point(2,1));
    aContour.push_back(Point(3,2));
    aContour.push_back(Point(5,2));
    aContour.push_back(Point(6,4));
    aContour.push_back(Point(7,3));
    aContour.push_back(Point(9,4));
    //
    aContour.push_back(Point(10,4));
    aContour.push_back(Point(10,8));
    aContour.push_back(Point(11,6));
    aContour.push_back(Point(11,7));
    aContour.push_back(Point(11,9));
    aContour.push_back(Point(12,12));
    aContour.push_back(Point(13,10));
    aContour.push_back(Point(13,11));

    /* display de boundary */
    //aBoard << SetMode((*aContour.begin()).className(), "Paving");
    aBoard << SetMode("PointVector", "Both");
    for (vector<Point>::iterator it = aContour.begin();
         it != aContour.end(); it++){
      aBoard << *it;
    }
    /* display de boundary */

    typedef  AlphaThickSegmentComputer< Z2i::Point > AlphaThickSegmentComputer2D;
    int thickness = 3;

    vector<AlphaThickSegmentComputer2D> fuzzSegmentSet;

    //run over the points on the contours
    for (vector<Point>::iterator it = aContour.begin();it != aContour.end();it++)
    {
        AlphaThickSegmentComputer2D anAlphaThickSegmentComputer;
        anAlphaThickSegmentComputer.init(it,thickness);

        /* travel over the contour points and add to the seg */
        while (anAlphaThickSegmentComputer.end() != aContour.end() &&
               anAlphaThickSegmentComputer.extendFront()){}
        /* pb anAlphaThickSegmentComputer.end() == aContour.end() */
        fuzzSegmentSet.push_back(anAlphaThickSegmentComputer);
        /*
        if(anAlphaThickSegmentComputer.end() == aContour.end())
            break;
        */
    }
    fuzzSegmentSet.pop_back();

    /* Display boundingbox */
    for (vector<AlphaThickSegmentComputer2D>::iterator it = fuzzSegmentSet.begin();it != fuzzSegmentSet.end();it++)
    {
        /*
        AlphaThickSegmentComputer2D anAlphaThickSegmentComputer = *it;
        aBoard << SetMode(anAlphaThickSegmentComputer.className(), "BoundingBox");
        aBoard << anAlphaThickSegmentComputer;
        */
        aBoard << SetMode((*it).className(), "BoundingBox");
        aBoard << *it;
    }
    /* Display boundingbox */
    aBoard.saveSVG("fuzzySegments.svg");
}

int main()
{
    cout << "Hello World!" << endl;
    //testFuzzySegmentOnCurve();

    /*
    Fraction f1(3,8), f2(1,2), f3(10,2);
    cout<<f1;
    cout << f1 << '*' << f2 << '=' << f1*f2 << '\n'
              << f2 << '*' << f3 << '=' << f2*f3 << '\n'
              << 2  << '*' << f1 << '=' << 2 *f1 << '\n';
    */
    /////////////////////////// simpleHull_2D ///////////////////////////////////////
    /*
    {
        //cout<<endl<<endl<<endl;
        vector<Point> contour;
        contour.push_back(Point(-15,10));
        contour.push_back(Point(-14,11));
        contour.push_back(Point(-14,9));
        contour.push_back(Point(-13,9));
        contour.push_back(Point(-13,7));
        contour.push_back(Point(-12,7));
        contour.push_back(Point(-12,5));
        contour.push_back(Point(-11,4));
        contour.push_back(Point(-9,3));
        contour.push_back(Point(-8,3));
        contour.push_back(Point(-7,4));
        contour.push_back(Point(-5,2));
        contour.push_back(Point(-3,1));
        contour.push_back(Point(-3,0));
        contour.push_back(Point(-2,0));
        contour.push_back(Point(-1,0));
        contour.push_back(Point(0,0));
        contour.push_back(Point(1,0));
        contour.push_back(Point(2,0));
        contour.push_back(Point(2,1));
        contour.push_back(Point(3,2));
        contour.push_back(Point(5,2));
        contour.push_back(Point(6,4));
        contour.push_back(Point(7,3));
        contour.push_back(Point(9,4));
        contour.push_back(Point(10,4));
        contour.push_back(Point(10,8));
        contour.push_back(Point(11,6));
        contour.push_back(Point(11,7));
        contour.push_back(Point(11,9));
        contour.push_back(Point(12,12));
        contour.push_back(Point(13,10));
        contour.push_back(Point(13,11));

        myPolylineConvexHull hull(contour.size());
        cout<<hull;

        for (vector<Point>::iterator it = contour.begin();it != contour.end();it++)
        {
            hull.simpleHull_2D(*it);
            //cout<<"top = "<<hull.top()<<" and bottom = "<<hull.bottom()<<endl;
        }

        //vector<Point> convexHull = simpleHull_2D(contour);
        vector<Point> convexHull = hull.H();

        Board2D board;
        // Draw points
        for (vector<Point>::iterator it = contour.begin();it != contour.end();it++)
        {
            board << *it;
        }

        //Draw convex hull
        for(vector<Point>::iterator it = convexHull.begin(); it != convexHull.end(); it++)
        {
            board << SetMode((*it).className(), "Both")
                     << CustomStyle((*it).className(), new CustomColors( Color(255,0,0), Color(192, 0, 0)))
                     << *it;
            //cout<<*it<<" ";
        }

        // Draw the grid
        Point bottomLeft(-16, 0 );
        Point topRight( 14, 12 );
        Domain domain( bottomLeft, topRight );
        board << SetMode(domain.className(), "Grid") << domain;

        // Draw the orthonormal base
        board.drawArrow(0.0, 0.0, 1.0, 0.0);
        board.drawArrow(0.0, 0.0, 0.0, 1.0);

        // Save
        board.drawLine(0,0,5,5,2);
        board.saveSVG("convexhull.svg");
        cout<<endl;
    }
    */
    /////////////////////////// simpleHull_2D ///////////////////////////////////////

    /////////////////////////// Circle recongization ///////////////////////////////////////
    vector<Point> contour;
    contour.push_back(Point(-15,10));
    contour.push_back(Point(-14,11));
    contour.push_back(Point(-14,9));
    contour.push_back(Point(-13,9));
    contour.push_back(Point(-13,7));
    contour.push_back(Point(-12,7));
    contour.push_back(Point(-12,5));
    contour.push_back(Point(-11,4));
    contour.push_back(Point(-9,3));
    contour.push_back(Point(-8,3));
    //
    contour.push_back(Point(-7,4));
    contour.push_back(Point(-5,2));
    contour.push_back(Point(-3,1));
    contour.push_back(Point(-3,0));
    contour.push_back(Point(-2,0));
    contour.push_back(Point(0,0));
    contour.push_back(Point(2,0));
    contour.push_back(Point(2,1));
    contour.push_back(Point(3,2));
    contour.push_back(Point(5,2));
    contour.push_back(Point(6,4));
    contour.push_back(Point(7,3));
    contour.push_back(Point(9,4));
    //
    contour.push_back(Point(10,4));
    contour.push_back(Point(10,8));
    contour.push_back(Point(11,6));
    contour.push_back(Point(11,7));
    contour.push_back(Point(11,9));
    contour.push_back(Point(12,12));
    contour.push_back(Point(13,10));
    contour.push_back(Point(13,11));

    double d = 2; //width of the blurred segment
    vector<myGeometricalDBS> setDBS;//set of all dbs decomposed from contour
    for (int it = 0; it < contour.size(); it++)
    {
        Point b1 = contour[it];
        Point b2 = contour[it+1];
        cout<<endl<<"=========> b1 = "<<b1<<" and b2 = "<<b2<<endl;
        myGeometricalDBS seg(b1, b2, d); //ending points
        cout<<"(1)"<<seg;

        bool isSeg = true;
        int sub_it = it+2;
        for(; isSeg==true && sub_it < contour.size(); sub_it++)
        {
            cout<<sub_it<<" - current point = "<<contour[sub_it]<<endl;
            myGeometricalDBS seg_copie = seg;
            isSeg = seg.extendFront(contour[sub_it]);
            if (isSeg == true)
                seg.pVector(contour[sub_it]);
            else
            {
                seg = seg_copie;
                //cout<<"---------------- decom it "<<it<<" and sub it "<<sub_it<<endl;
                it = sub_it-2;
            }
        }
        cout<<"(2)"<<seg;
        setDBS.push_back(seg);
        if(sub_it == contour.size()) break;//stop when the last seg is found
    }

    //print out all seg of the decomposition
    cout<<endl<<"The decomposition is "<<setDBS.size()<<endl;
    for(vector<myGeometricalDBS>::iterator it = setDBS.begin(); it != setDBS.end(); it++)
    {
        cout<<"("<<(*it).a()<<" , "<<(*it).b()<<" , "<<(*it).mu()<<" , "<<(*it).omega()<<" )";
        //cout<<" first "<<(*it).aF()<<" and last "<<(*it).aL()<<endl;
        //int pos =findElement(contour,(*it).aF());
        cout<<" => "<<findElement(contour,(*it).aF())<<":"<<(*it).aF()
           <<" and "<<findElement(contour,(*it).aL())<<":"<<(*it).aL()<<endl;
    }

    Board2D boardDBSeg;
    // Draw the grid
    Point bottomLeft(-16, 0 );
    //Point topRight( 14, 12 );
    Point topRight( 60, 30 );
    Domain domain( bottomLeft, topRight );
    boardDBSeg << SetMode(domain.className(), "Grid") << domain;

    // Draw the orthonormal base
    boardDBSeg.drawArrow(0.0, 0.0, 1.0, 0.0);
    boardDBSeg.drawArrow(0.0, 0.0, 0.0, 1.0);
    for(vector<myGeometricalDBS>::iterator it = setDBS.begin(); it != setDBS.end(); it++)
    {
        // Draw each seg in the set
        vector<Point> myDBSeg = (*it).pVector();
        // Draw the DSL points between firstPoint and lastPoint
        for (vector<Point>::iterator sub_it = myDBSeg.begin(); sub_it != myDBSeg.end(); sub_it++)
            boardDBSeg << *sub_it; //Draw the point
    }

    for(vector<myGeometricalDBS>::iterator it = setDBS.begin(); it != setDBS.end(); it++)
    {
        //draw the lining lines
        boardDBSeg.setPenColor(Color( 255, 0, 0 ));
        PointVector<2,double> p7 = intersectionLines((*it).a(),(*it).b(),(*it).mu(),
                                       (*it).b(),-(*it).a(),(*it).b()*(*it).aF()[0] + (*it).a()*(*it).aF()[1]);
        PointVector<2,double> p8 = intersectionLines((*it).a(),(*it).b(),(*it).mu() + (*it).omega()-1,
                                       (*it).b(),-(*it).a(),(*it).b()*(*it).aF()[0] + (*it).a()*(*it).aF()[1]);

        PointVector<2,double> p9 = intersectionLines((*it).a(),(*it).b(),(*it).mu(),
                                       (*it).b(),-(*it).a(),(*it).b()*(*it).aL()[0] + (*it).a()*(*it).aL()[1]);
        PointVector<2,double> p10 = intersectionLines((*it).a(),(*it).b(),(*it).mu() + (*it).omega()-1,
                                       (*it).b(),-(*it).a(),(*it).b()*(*it).aL()[0] + (*it).a()*(*it).aL()[1]);
        boardDBSeg.drawLine(p7[0],p7[1],p9[0],p9[1],1);
        boardDBSeg.drawLine(p8[0],p8[1],p10[0],p10[1],1);
        boardDBSeg.drawLine(p7[0],p7[1],p8[0],p8[1],1);
        boardDBSeg.drawLine(p9[0],p9[1],p10[0],p10[1],1);
    }

    //Conversion into tangent space
    vector<double> alpha;
    vector<double> length;
    //scan the poly decompostion
    for(vector<myGeometricalDBS>::iterator it = setDBS.begin(); it+1 != setDBS.end(); it++)
    {
        //for each segment, store the angle and leng of segments
        double l = 0, a = 0;
        int begin = findElement(contour,(*it).aF());
        int end = findElement(contour,(*it).aL());
        for (int i = begin; i<end; i++)
            l += distance(contour[i],contour[i+1]);
        length.push_back(l);

        if(it == setDBS.begin())
            alpha.push_back(0.0);
        else
        {
                Point p1 = Point((*it).aL()[0]-(*it).aF()[0], (*it).aL()[1]-(*it).aF()[1]); //v1 = (*it)[aL - aF]
                Point p2 = Point((*(it+1)).aL()[0]-(*(it+1)).aF()[0], (*(it+1)).aL()[1]-(*(it+1)).aF()[1]); //v1 = (*it+1)[aL - aF]
                a = angle(p1,p2);
                alpha.push_back(a);
        }
        cout<<"angle = "<<a<<" and length "<<l<<endl;
    }

    //draw the tangent space (x,y) = (length,alpha)
    //for(vector<double>::iterator it = alpha.begin(); it+1 != alpha.end(); it++)
    vector<dPoint> Ti1,Ti2,Ti;
    dPoint p(0.0,0.0);
    Ti.push_back(p);
    p[0] = length[0];
    p[1] = 0.0;
    Ti1.push_back(p);
    Ti.push_back(p);
    p[0] = Ti1.back()[0] ;
    p[1] = Ti1.back()[1]+alpha[0];
    Ti2.push_back(p);
    Ti.push_back(p);
    for(int it = 1; it < alpha.size(); it++)
    {
        p[0] = Ti2.back()[0] +length[it-1];
        p[1] = Ti2.back()[1];
        Ti1.push_back(p);
        Ti.push_back(p);
        p[0] = Ti1.back()[0];
        p[1] = Ti1.back()[1]+alpha[it];
        Ti2.push_back(p);
        Ti.push_back(p);
        printf("Point : %f %f %f %f \n",Ti2.back()[0],Ti2.back()[1],Ti1.back()[0],Ti1.back()[1]);
        //boardDBSeg.drawLine(Ti2.back()[0],Ti2.back()[1],Ti1.back()[0],Ti1.back()[1],1);
        //boardDBSeg.drawLine(Ti2.back()[0],Ti2.back()[1],Ti1.back()[0],Ti1.back()[1],1);
    }

    for(int it = 0; it < Ti.size()-1; it++)
    {
        boardDBSeg.setPenColor(Color( 0, 0, 255 ));
        boardDBSeg.drawLine(Ti[it][0],Ti[it][1],Ti[it+1][0],Ti[it+1][1],1);
    }

    // Save
    boardDBSeg.saveSVG("myDBSegGeoDecom.svg");
    /////////////////////////// Circle recongization ///////////////////////////////////////

    return 0;
}


