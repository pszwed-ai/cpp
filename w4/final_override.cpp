//
// Created by pszwed on 24.03.2021.
//
#include <cmath>
#include <iostream>

#define TEST_FINAL 0
#define TEST_OVERRIDE 0

#if TEST_FINAL || TEST_OVERRIDE
class Funkcja{
public:
    virtual double evaluate(double x)const=0;
};

#endif


#if TEST_FINAL

class Sinus final:public Funkcja {
public:
    double evaluate(double x)const{
        return sin(x);
    }
};

class LepszySinus: public Sinus{
public:
    double evaluate(double x)const{
        std::cout<<"obliczam sin("<<x<<")";
        return Sinus::evaluate(x);
    }
};

#endif

#if TEST_OVERRIDE

class ArcusSinus final :public Funkcja {
public:
    virtual double evaluate(double x)const{
        if(x<-1.0 || x>1.0)return NAN;
        return acos(x);
    }
    virtual Funkcja*getInverse()const override;
};

class Sinus final:public Funkcja {
public:
    double evaluate(double x)const{
        return sin(x);
    }
    virtual Funkcja*getInverse()const override;
};

#endif