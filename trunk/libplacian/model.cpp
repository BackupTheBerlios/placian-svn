#include "model.h"

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
