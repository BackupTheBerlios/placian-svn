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


template<typename T>
model<T>::model(std::vector<T> N,std::vector<T> D,T k_):fraction<T>(N,D),k(k_)
{
    for(int i=0;i<D.size();i++)
        if(fraction<T>::m[i])
        {
            s.push_back(-D[i]);
            mm.push_back(fraction<T>::m[i]);
        }

    B = fraction<T>::A;
    for(int i=0;i<B.size();i++)
        for(int k=0;k<B[i].size();k++)
            B[i][k]/=T(fraction<T>::factor(mm[i]-k-1));
}

template<typename T>
T model<T>::operator()(T t)
{
    T val = 0;
    for(int i=0;i<B.size();i++)
        for(int k=0;k<B[i].size();k++)
            val+=B[i][k]*pow(t,mm[i]-k-1)*exp(s[i]*t);
    return val*k;
}

#endif //MODEL_H
