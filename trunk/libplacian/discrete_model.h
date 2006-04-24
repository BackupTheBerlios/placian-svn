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

#endif
