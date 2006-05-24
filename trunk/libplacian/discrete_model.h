#include "model.h"
#include <vector>

#ifndef DISCRETE_MODEL_H
#define DISCRETE_MODEL_H

template<typename T>
class discrete_model : public std::vector<T>
{
    T period;
    int size;
public:
    discrete_model(model<T>,T,int);
};

template<typename T>
discrete_model<T>::discrete_model(model<T> g,T period_,int size_):period(period_),size(size_)
{
    for(int i=0;i<size;i++)push_back(g(period*T(i)));   //reverse order to boost reading values and eliminate index substraction
}

#endif //DISCRETE_MODEL_H
