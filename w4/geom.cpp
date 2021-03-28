//
// Created by pszwed on 15.10.2019.
//
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Coord {
public:
    double x;
    double y;

    Coord(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    string asText() const {
        char buf[256];
        sprintf(buf, "%f %f", x, y);
        return string(buf);
    }
};

class GeoObject{
public:
    virtual ~GeoObject(){}
    virtual string asWKT(bool printHeader = true)const{
        return "";
    }
};


class Point:public GeoObject{
    Coord p;
public:
    Point (double x=0,double y=0):p(x,y){}
    string asWKT(bool printHeader)const{
        string r;
        if(printHeader)r="POINT ";
        r.append("( ");
        r.append(p.asText());
        r.append(" )");
        return r;
    }
};

class Linestring:public GeoObject{
public:
    vector<Coord> line;
    Linestring(const vector<double>&v){

    }
    string asWKT(bool printHeader)const{
        string r;
        if(printHeader)r="LINESTRING ";
        r.append("( ");
        for(int i=0;i<line.size();i++){
            if(i!=0)r.append(", ");
            r.append(line[i].asText());
        }
        r.append(" )");
        return r;
    }
};

class Polygon:public GeoObject{

};


class MultiLineString:public GeoObject{

};

class MultiPolygon:public GeoObject{

};


class Geometry{
public:
    vector<GeoObject*> elements;
    ~Geometry();
    string asWKT();
};

Geometry::~Geometry(){
    for(int i=0;i<elements.size();i++){
        delete elements[i];
    }
}

string Geometry::asWKT(){
    string r;
    for(int i=0;i<elements.size();i++){
        r.append(elements[i]->asWKT());
    }
    r.append(" ");
    return r;
}

//int main(){
//
//}