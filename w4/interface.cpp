//
// Created by pszwed on 20.03.2020.
//

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class IStack{
public:
    virtual bool push(int i)=0;
    virtual int pop()=0;
    virtual bool empty()const=0;
    virtual ~IStack(){} //nie zaszkodzi
};

class IRandomAccess{
public:
    virtual int size()const=0;
    virtual int get(int i)const=0;
    virtual ~IRandomAccess(){} //nie zaszkodzi
};


class MyStack: public IStack, public IRandomAccess{
    int*tab;
    int capacity;
    int cnt;
public:
    MyStack(int _size):tab(new int[_size]),capacity(_size),cnt(0){}
    ~MyStack(){if (tab) delete []tab;}
    bool push(int i){
        if (cnt == capacity) return false;
        tab[cnt++]=i;
        return true;
    }
    int pop(){return tab[--cnt];}
    bool empty()const{return cnt==0;}
    int size()const{return cnt;}
    int get(int i)const{return tab[i];}
};


void fillStack(IStack&s){
    for(int i=0;i<10;i++)s.push(i);
}

void emptyStack(IStack&s){
    while(!s.empty())cout<<s.pop()<<" ";
}

void iterate(IRandomAccess&s){
    for(int i=0;i<s.size();i++){
        cout<<s.get(i)<<" ";
    }
}


class StackAsVector:
        public vector<int>,
        public IStack,
        public IRandomAccess{
public:
    bool push(int i){
        push_back(i);
        return true;
    }
    int pop(){
        int r = back();
        pop_back();
        return r;
    }
    bool empty()const{return vector<int>::empty();}
    int size()const{return vector<int>::size();}
    int get(int i)const{return at(i);}

};


class StackUsingVector: public IStack, public IRandomAccess{
    vector<int> tab;
public:
    bool push(int i){
        tab.push_back(i);
        return true;
    }
    int pop(){
        int r = tab.back();
        tab.pop_back();
        return r;
    }
    bool empty()const{return tab.empty();}
    int size()const{return tab.size();}
    int get(int i)const{return tab[i];}

};



int test_stack_main(){
    StackUsingVector ms;
    fillStack(ms);
    iterate(ms);
    cout<<endl;
    emptyStack(ms);
    return 0;
}

