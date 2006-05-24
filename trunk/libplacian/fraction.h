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


template<typename T>
fraction<T>::fraction(std::vector<T> numerator,std::vector<T> denumerator):N(numerator),D(denumerator),m(D.size(),int(1))
{
    //check for the repeating poles
    for(int i=0;i<D.size();i++)
        for(int j=i+1;j<D.size();j++)
            if(D[i]==D[j] && m[i])
            {
                m[i]++;
                m[j]=0;    //erase
            }

    //calculate coeffs
    for(int i=0;i<D.size();i++)
    {
        A.push_back(std::vector<T>());
        //preparing numerator
        polynomian<T> num(N);

        //preparing denumerator
        std::vector<T> D_temp;
        for(int j=0;j<D.size();j++)
            if(i!=j)for(int jj=0;jj<m[j];jj++)D_temp.push_back(D[j]);
	    polynomian<T> denum(D_temp);
	    if(!D_temp.size())
	    {
	        D_temp = std::vector<T>(1,T(1));
	        denum.set_coeffs(D_temp);     //patch
	    }

        //evaluating coeffs
        for(int k=1;k<=m[i];k++)
        {
            T val=1/T(factor(k-1));

            //std::cout<<-D[i]<<" --> "<<num<<" : "<<denum<<std::endl;

            val = val*num(-D[i])/denum(-D[i]);
            A[i].push_back(val);

            num=num.derive()*denum-num*denum.derive();
            denum=denum*denum;
        }
    }
}

template<typename T>
int fraction<T>::factor (int num)
{
    if(!num)return 1;
    int result=1;
    for (int i=1; i<=num; i++)result*=i;
    return result;
}

#endif //FRACTION_H
