#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <vector>
#include "poly.h"



template<typename T>
class fraction{
protected:
    std::vector<T> N;	//numerator
    std::vector<T> D;	//denumerator
    std::vector< std::vector<T> > A;    //coefficients
    std::vector<int> m;  //degree of pole
public:
    fraction(std::vector<T>,std::vector<T>);

    int factor(int);

    friend std::ostream& operator<<(std::ostream& s, fraction<T> x)
    {
        s<<"Coeffs: ";
        if(x.A.size())
            for(int i=0;i<x.A.size();i++)
                for(int k=0;k<x.A[i].size() && x.m[i];k++)
                    s<<"A_"<<i<<","<<k<<"="<<x.A[i][k]<<" ";

        return s;
    }

};




#endif
