//
// Created by pszwed on 27.03.2021.
//

#include <iostream>
using namespace std;


#define LSP 0
#if LSP==0

class Ellipse{
protected:
    double width;
    double height;
    double cx;
    double cy;
public:
    Ellipse(double _cx, double _cy,
            double w, double h)
    :cx(_cx),cy(_cy),
    width(w),height(h){}
    virtual void setWidth(double w){
        width=w;}
    virtual void setHeight(double h){
        height=h;}
    virtual double getArea(){
        return 3.14*width/2*height/2;}
};

class Circle:public Ellipse{
public:
    Circle(double _cx, double _cy,
            double radius)
    :Ellipse(_cx,_cy,radius,radius){}
    virtual void setWidth(double w){
        Ellipse::setWidth(w);
        Ellipse::setHeight(w);
    }
    virtual void setHeight(double h){
        Ellipse::setWidth(h);
        Ellipse::setHeight(h);
    }
    void setRadius(double r){
        setWidth(r);
    }
};


void test_substitution(){
    Ellipse*tab[]{new Ellipse(0,0,1,2),new Circle(0,0.,2)};
    cout<<tab[0]->getArea()<<endl;
    cout<<tab[1]->getArea()<<endl;
    cout<<endl;
    tab[0]->setHeight(2);
    tab[0]->setWidth(4);
    tab[1]->setHeight(2);
    tab[1]->setWidth(4);
    cout<<tab[0]->getArea()<<endl;
    cout<<tab[1]->getArea()<<endl;
    cout<<endl;
    delete tab[0];
    delete tab[1];
}

#else // LSP==1

class Circle{
protected:
    double radius;
    double cx;
    double cy;
public:
    Circle(double _cx, double _cy,
            double _r)
           :cx(_cx),cy(_cy),
           radius(_r){}
    virtual void setRadius(double r){
        radius=r;}
    virtual double getArea(){
        return 3.14*radius*radius;}
};

class Ellipse:public Circle{
    double radiusAux;
public:
    Ellipse(double _cx, double _cy,
            double w, double h)
            :Circle(_cx,_cy,w/2),
             radiusAux(h/2){}
    void setRadius(double r){
        radius=r;
        radiusAux=r;
    }
    virtual void setWidth(double w){
        Circle::setRadius(w/2);
    }
    virtual void setHeight(double h){
        radiusAux=h/2;
    }
    double getArea(){
        return 3.14*radius*radiusAux;}
};


void test_substitution(){
    Circle*tab[]{new Ellipse(0,0,1,2),new Circle(0,0.,2)};
    cout<<tab[0]->getArea()<<endl;
    cout<<tab[1]->getArea()<<endl;
    cout<<endl;
    tab[0]->setRadius(2);
    tab[1]->setRadius(2);
    cout<<tab[0]->getArea()<<endl;
    cout<<tab[1]->getArea()<<endl;
    cout<<endl;
    delete tab[0];
    delete tab[1];
}
#endif

int main(){
    test_substitution();
}