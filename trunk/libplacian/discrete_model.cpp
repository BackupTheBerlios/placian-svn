#include "discrete_model.h"

template<typename T>
discrete_model<T>::discrete_model(model<T> g,T period_,int size_):period(period_),size(size_)
{
    for(int i=0;i<size;i++)push_back(g(period*T(i)));   //reverse order to boost reading values and eliminate index substraction
}
