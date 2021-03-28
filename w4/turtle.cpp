//
// Created by pszwed on 20.03.2020.
//
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
using namespace std;
#include <stdio.h>
#include <fstream>
#include <vector>


class Command;
class Turtle{
public:
    double x,y;
    double angle;
    bool isPenDown;

    Turtle(){
        x=y=0;
        angle=0;
        isPenDown=true;
    }
    void forward(double distance);
    void rotate(double angle);
    void changePenState(bool putDown);
    void execute(const Command&c);

};


void Turtle::forward(double distance){
    if(isPenDown){
        cout<<"<line x1=\""<<x<<"\" y1=\""<<y<<"\" ";
    }
    x+=distance*cos(angle*M_PI/180);
    y+=distance*sin(angle*M_PI/180);
    if(isPenDown) {
        cout<<"x2=\""<<x<<"\" y2=\""<<y<<"\" "
              "style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n";
    }

}
void Turtle::rotate(double angle){
    this->angle+=angle;
}
void Turtle::changePenState(bool putDown){
    isPenDown = putDown;
}


void test(){
    cout<<"<!DOCTYPE html>\n<html>\n<body>\n";
    cout<<"<svg height=\"300\" width=\"300\">\n";
    Turtle t;
    int n= 32;
    t.changePenState(false);
    t.rotate(45);
    t.forward(200);

    bool isPenDown = true;
    t.changePenState(isPenDown);
    for(int i=0;i<n;i++){
        t.forward(10);
        t.rotate(360.0/n);
        isPenDown=!isPenDown;
        t.changePenState(isPenDown);
    }
    cout<<"</svg>\n";
    cout<<"</body>\n</html>";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Command{
public:
    virtual void write(ostream&os)const=0;
    virtual void read(istream&is)=0;
    virtual void applyTo(Turtle&turtle)const=0;
    virtual ~Command(){}
};




class Forward : public Command{
    double distance;
public:
    Forward(double distance=0){
        this->distance=distance;
    }

    void write(ostream&os)const{
        os<<"FD"<<" "<<distance<<endl;
    }
    void read(istream&is){
        is>>distance;
    }

    void applyTo(Turtle&t)const{
        t.forward(distance);
    }
};

class Rotate : public Command{
    double angle;
public:
    Rotate(double angle=0){
        this->angle=angle;
    }
    void write(ostream&os)const{
        os<<"RL"<<" "<<angle<<endl;
    }
    void read(istream&is){
        is>>angle;
    }
    void applyTo(Turtle&t)const{
        t.rotate(angle);
    }
};


class ChangePenState: public Command{
    bool putDown;
public:
    ChangePenState(bool putDown=true){
        this->putDown=putDown;
    }
    void write(ostream&os)const{
        os<<"PD"<<" "<<putDown<<endl;
    }
    void read(istream&is){
        is>>putDown;
    }
    void applyTo(Turtle&t)const{
        t.changePenState(putDown);
    }
};

void Turtle::execute(const Command&c){
    c.applyTo(*this);
}

void demo(){
    Turtle t;
    Rotate r(45);
    t.execute(r);
    t.execute(Forward(100));

}

void drawCircle(){
    int n= 16;
    Turtle t;
    t.execute(ChangePenState(false));
    t.execute(Rotate(45));
    t.execute(Forward(100));
    t.execute(ChangePenState(true));


    for(int i=0;i<n;i++){
        Forward f(10);
        Rotate r(360.0/n);
        t.execute(f);
        t.execute(r);
    }
}

void drawHexagon(){
    int n= 6;
    Turtle t;
    t.execute(ChangePenState(false));
    t.execute(Rotate(45));
    t.execute(Forward(200));
    t.execute(ChangePenState(true));

    for(int i=0;i<n;i++){
        Forward f(50);
        Rotate r(360.0/n);
        t.execute(f);
        t.execute(r);
    }
}


void test_commands(){
    int n= 16;
    int p= 2;
//    Command*cmds[p+3*n];
    Command*cmds[50];
    cmds[0] = new Rotate(45);
    cmds[1] = new Forward(100);

    bool isPenDown = true;
    for(int i=0;i<n;i++){
        cmds[p+3*i] = new Forward(10);
        cmds[p+3*i+1] = new Rotate(360.0/n);
        isPenDown=!isPenDown;
        cmds[p+3*i+2] = new ChangePenState(isPenDown);
    }

    Turtle t;

    for(int i=0;i<sizeof(cmds)/sizeof(cmds[0]);i++){
//        t.execute(*cmds[i]);
        cmds[i]->applyTo(t);
    }

//    cout<<"---------------\n";
    ofstream of("commands.txt");
    for(int i=0;i<sizeof(cmds)/sizeof(cmds[0]);i++){
        cmds[i]->write(of);
    }


        for(int i=0;i<sizeof(cmds)/sizeof(cmds[0]);i++){
            delete cmds[i];
        }


}


Command*next(istream&is){
    if(!is)return 0;
    string s;
    is>>s;
    Command *c=0;
    if(s=="FD"){
        c=new Forward();
    }
    if(s=="RL"){
        c=new Rotate();
    }
    if(s=="PD"){
        c=new ChangePenState();
    }
    if(!c)return c;
    c->read(is);
    return c;
}

void read_execute(){
    ifstream is("commands.txt");
    vector<Command*> cmds;
    for(;;){
        Command*c = next(is);
        if(!c)break;
        cmds.push_back(c);
    }
    Turtle t;
    for(int i=0;i<cmds.size();i++){
        t.execute(*cmds[i]);
    }
    for(int i=0;i<cmds.size();i++){
        delete cmds[i];
    }
}

int main(){
////    test();
////    demo();
////    drawCircle();
////    drawHexagon();
////    test_commands();
////    read_execute();
}