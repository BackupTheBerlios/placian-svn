#include <iostream>
#include <vector>
#include <math.h>

#ifndef MODEL_H
#define MODEL_H

#include "fraction.h"

template<typename T>
class model : public fraction<T>{
T k;                    //amplify
std::vector< std::vector<T> > B;  //A recalulated
std::vector<T> s;
std::vector<int> mm;
public:
    model(std::vector<T>,std::vector<T>,T);

    T operator()(T);

    friend std::ostream& operator<<(std::ostream& s, model<T> x)
    {
        s<<"Equation in time domain: ";
        for(int i=0;i<x.B.size();i++)
            for(int k=0;k<x.B[i].size();k++)
                s<<x.B[i][k]<<"*t^"<<(x.mm[i]-1-k)<<"*exp("<<x.s[i]<<"*t) ";

        return s;
    }
};

#endif
