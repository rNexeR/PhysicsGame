#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <Python.h>
using namespace std;

static const int WIDTH = 1000, HEIGHT = 450;
static double PI = M_PI;//3.1416;
static const float FPS = 60;
static const double GRAVITY = 9.8;

class Point
{
public:
    int x;
    int y;
    Point()
    {
        this->x=0;
        this->y=0;
    }
    Point(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
};

class Line
{
public:
    Point p1;
    Point p2;
    Line()
    {
    }
    Line(Point p1,Point p2)
    {
        this->p1=p1;
        this->p2=p2;
    }
};

static Point* lineIntersection(Line l1,Line l2) {
    Point p1=l1.p1;
    Point p2=l1.p2;
    Point p3=l2.p1;
    Point p4=l2.p2;

    // Store the values for fast access and easy
    // equations-to-code conversion
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return NULL;

    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

    // Check if the x and y coordinates are within both lines
//    if ( x < min(x1, x2) || x > max(x1, x2) ||
//    x < min(x3, x4) || x > max(x3, x4) ) return NULL;
//    if ( y < min(y1, y2) || y > max(y1, y2) ||
//    y < min(y3, y4) || y > max(y3, y4) ) return NULL;

    // Return the point of intersection
    Point* ret = new Point();
    ret->x = x;
    ret->y = y;
    return ret;
}

static bool segmentIntersection(Line l1,Line l2)
{
    Point* p=lineIntersection(l1,l2);
    if(p!=NULL)
    {
        if((p->x<l1.p1.x && p->x<l1.p2.x)
           ||(p->x>l1.p1.x && p->x>l1.p2.x))
           {
               delete p;
               return false;
           }

        if((p->x<l2.p1.x && p->x<l2.p2.x)
           ||(p->x>l2.p1.x && p->x>l2.p2.x))
           {
               delete p;
               return false;
           }

        if((p->y<l1.p1.y && p->y<l1.p2.y)
           ||(p->y>l1.p1.y && p->y>l1.p2.y))
           {
               delete p;
               return false;
           }

        if((p->y<l2.p1.y && p->y<l2.p2.y)
           ||(p->y>l2.p1.y && p->y>l2.p2.y))
           {
               delete p;
               return false;
           }
        delete p;
        return true;
    }
    delete p;
    return false;
}

static Point rotateAroundPoint(Point point,Point pivot,float angle)
{
    //Move the universe (the point b)
    float s = sin(angle*PI/180);
    float c = cos(angle*PI/180);

    // translate point back to origin:
    int res_x = point.x;
    int res_y = point.y;

    // rotate point
    float xnew = res_x * c + res_y * s;
    float ynew = -res_x * s + res_y * c;

    // translate point back:
    res_x = xnew + pivot.x;
    res_y = ynew + pivot.y;

    return Point(res_x,res_y);
}

static bool hitboxCollision(int a_x,int a_y,int a_width,int a_height,float a_angle,
              int b_x,int b_y,int b_width,int b_height,float b_angle)
{
    Point pa1(a_x,
              a_y);

    Point pa2(a_x + cos (a_angle*PI/180) * a_width
             ,a_y - sin (a_angle*PI/180) * a_width);

    Point pa3(a_x + cos (a_angle*PI/180) * a_width + sin (a_angle*PI/180) * a_height,
              a_y - sin (a_angle*PI/180) * a_width + cos (a_angle*PI/180) * a_height);

    Point pa4(a_x + sin (a_angle*PI/180) * a_height,
              a_y + cos (a_angle*PI/180) * a_height);


    Point pb1(b_x,
              b_y);

    Point pb2(b_x + cos (b_angle*PI/180) * b_width
             ,b_y - sin (b_angle*PI/180) * b_width);

    Point pb3(b_x + cos (b_angle*PI/180) * b_width + sin (b_angle*PI/180) * b_height,
              b_y - sin (b_angle*PI/180) * b_width + cos (b_angle*PI/180) * b_height);

    Point pb4(b_x + sin (b_angle*PI/180) * b_height,
              b_y + cos (b_angle*PI/180) * b_height);

    Line la1(pa1,pa2);
    Line la2(pa2,pa3);
    Line la3(pa3,pa4);
    Line la4(pa4,pa1);

    Line lb1(pb1,pb2);
    Line lb2(pb2,pb3);
    Line lb3(pb3,pb4);
    Line lb4(pb4,pb1);

    if(segmentIntersection(la1,lb1))
        return true;
    if(segmentIntersection(la1,lb2))
        return true;
    if(segmentIntersection(la1,lb3))
        return true;
    if(segmentIntersection(la1,lb4))
        return true;

    if(segmentIntersection(la2,lb1))
        return true;
    if(segmentIntersection(la2,lb2))
        return true;
    if(segmentIntersection(la2,lb3))
        return true;
    if(segmentIntersection(la2,lb4))
        return true;

    if(segmentIntersection(la3,lb1))
        return true;
    if(segmentIntersection(la3,lb2))
        return true;
    if(segmentIntersection(la3,lb3))
        return true;
    if(segmentIntersection(la3,lb4))
        return true;

    if(segmentIntersection(la4,lb1))
        return true;
    if(segmentIntersection(la4,lb2))
        return true;
    if(segmentIntersection(la4,lb3))
        return true;
    if(segmentIntersection(la4,lb4))
        return true;






    vector<Point*>intersections;
    intersections.push_back(lineIntersection(la1,lb1));
    intersections.push_back(lineIntersection(la1,lb2));
    intersections.push_back(lineIntersection(la1,lb3));
    intersections.push_back(lineIntersection(la1,lb4));

    intersections.push_back(lineIntersection(la2,lb1));
    intersections.push_back(lineIntersection(la2,lb2));
    intersections.push_back(lineIntersection(la2,lb3));
    intersections.push_back(lineIntersection(la2,lb4));

    intersections.push_back(lineIntersection(la3,lb1));
    intersections.push_back(lineIntersection(la3,lb2));
    intersections.push_back(lineIntersection(la3,lb3));
    intersections.push_back(lineIntersection(la3,lb4));

    intersections.push_back(lineIntersection(la4,lb1));
    intersections.push_back(lineIntersection(la4,lb2));
    intersections.push_back(lineIntersection(la4,lb3));
    intersections.push_back(lineIntersection(la4,lb4));


    int x_min=0;int x_max=0;
    int y_max=0;int y_min=0;

    if(a_width*a_height>b_width*b_height)
    {
        x_min = pa1.x;
        x_min=min(x_min,pa2.x);
        x_min=min(x_min,pa3.x);
        x_min=min(x_min,pa4.x);
        x_max = pa1.x;
        x_max=max(x_max,pa2.x);
        x_max=max(x_max,pa3.x);
        x_max=max(x_max,pa4.x);

        y_min = pa1.y;
        y_min=min(y_min,pa2.y);
        y_min=min(y_min,pa3.y);
        y_min=min(y_min,pa4.y);
        y_max = pa1.y;
        y_max=max(y_max,pa2.y);
        y_max=max(y_max,pa3.y);
        y_max=max(y_max,pa4.y);
    }else
    {
        x_min = pb1.x;
        x_min=min(x_min,pb2.x);
        x_min=min(x_min,pb3.x);
        x_min=min(x_min,pb4.x);
        x_max = pb1.x;
        x_max=max(x_max,pb2.x);
        x_max=max(x_max,pb3.x);
        x_max=max(x_max,pb4.x);

        y_min = pb1.y;
        y_min=min(y_min,pb2.y);
        y_min=min(y_min,pb3.y);
        y_min=min(y_min,pb4.y);
        y_max = pb1.y;
        y_max=max(y_max,pb2.y);
        y_max=max(y_max,pb3.y);
        y_max=max(y_max,pb4.y);
    }

    int cont=0;

    for(int i=0;i<(int)intersections.size();i++)
    {
        Point* point=intersections[i];
        if(point!=NULL)
        {
            if(point->x > x_min
               && point->x < x_max
               && point->y > y_min
               && point->y < y_max)
            {
                cont++;
            }
        }
    }

    vector<Point*>::iterator i;
    for ( i = intersections.begin() ; i < intersections.end(); i++ )
    {
        delete * i;
    }


    if(cont>=8)
        return true;

    return false;
}

static bool hitboxCollision(Box *b1,float a1,Box *b2,float a2)
{
    return hitboxCollision(b1->x,b1->y,b1->width,b1->height,a1,b2->x,b2->y,b2->width,b2->height,a2);
}

static string intToString(int number)
{
    if (number == 0)
        return "0";
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0; i<(int)temp.length(); i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

static void write(float xo, float yo, float vo, float angle)
{
    ofstream out("pyGraph.py",ios::out);
    string t = string("from math import sin, cos\n")+
string("from numpy import array, arange\n")+
string("from pylab import plot,xlabel,show, ylabel, title, grid\n")+

"PI = 3.1416\n"+
"GRAVITY = 9.8\n"+
"Xo = " + intToString(xo) + "\n"+
"Yo = " + intToString(yo) +"\n"+
"Vo = " + intToString(vo) +"\n"+
"Angle = " + intToString(angle) + "\n"+
"Angle = Angle*PI/180\n"+
"print Angle\n"+
"Vox = Vo*cos(Angle)\n"+
"Voy = Vo*sin(Angle)\n"+

"x = []\n"+
"y = []\n"+

"tiempo = arange(0,100,0.3)\n"+

"for t in tiempo:\n"+
"	xtemp = Xo + (Vox*t)\n"+
"	ytemp = Yo + (Voy*t) - (0.5*GRAVITY*t*t)\n"+
"	if (ytemp < 0):\n"+
"		break\n"+
"	x.append(xtemp)\n"+
"	y.append(ytemp)\n"+

"plot(x,y)\n"+
"xlabel('x')\n"+
"ylabel('y')\n"+
"title('Lanzamiento de Proyectil')\n"+
"grid(True)\n"+
"show()";

    out.write((char*)t.c_str(),t.size());
    out.close();

//    system( "python pyGraph.py" );
}
