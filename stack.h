#ifndef STACK_H
#define STACK_H
#include <sstream>
#include "list.h"
using namespace std;
template <class T>
class Stack{
private:
    List <T> data;
public:

    T get(){
        return data.get(0);
    }
    void pop(){
        if (data.getSize()==0)
            return;
        data.remove(0);
    }
    void push(T val){
        data.add_first(val);
    }
    int Size(){
            return data.getSize();
    }
    bool empty(){
        return data.getSize()==0;
    }

};
#endif
