#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <vector>


template<typename T>
class polynomian{
    std::vector<T> coeffs;
public:
    //constructors
    polynomian(){};
    polynomian(const std::vector<T>&);        //initalizing with zeros
    polynomian(const polynomian<T>&x):coeffs(x.coeffs){}   //coping constructor
    //semi-constructor
    void set_coeffs(const std::vector<T>&);        //coping coeffs

    //methods
    polynomian<T> operator-(polynomian<T>);
    polynomian<T> operator*(polynomian<T>);
    polynomian<T> derive();

    //horner scheme
    T operator()(T);

    friend std::ostream& operator<<(std::ostream& s, polynomian<T> x)
    {
        if(x.coeffs.size())for(int i=x.coeffs.size()-1;i>=0;i--)s<<x.coeffs[i]<<"s^"<<i<<" ";
        return s;
    }

};


template<typename T>
polynomian<T>::polynomian(const std::vector<T>& zeros)
{
    if(zeros.size())
    {
        coeffs.resize(2);
        coeffs[0]=zeros[0];
        coeffs[1]=1;
        for(int i=1;i<zeros.size();i++)
        {
            std::vector<T> tmp(coeffs);
            tmp.resize(coeffs.size()+1);
            for(int j=0;j<coeffs.size();j++)tmp[j]*=zeros[i];
            for(int j=0;j<coeffs.size();j++)tmp[j+1]+=coeffs[j];
            coeffs=tmp;
        }
    }
};

template<typename T>
polynomian<T> polynomian<T>::operator-(polynomian<T> x)
{
    std::vector<T> tmp(coeffs.size(),T(0));
    if(x.coeffs.size()>coeffs.size())tmp.resize(x.coeffs.size(),T(0));
    for(int i=0;i<coeffs.size();i++)tmp[i]=coeffs[i];
    for(int i=0;i<x.coeffs.size();i++)tmp[i]-=x.coeffs[i];
    polynomian<T> g;
    g.coeffs=tmp;
    return g;
}

template<typename T>
void polynomian<T>::set_coeffs(const std::vector<T>& x)
{
    coeffs = x;
}

template<typename T>
polynomian<T> polynomian<T>::operator*(polynomian<T> x)
{
    std::vector<T> tmp(coeffs.size()+x.coeffs.size()-1,T(0));

    for(int i=0;i<coeffs.size();i++)
        for(int j=0;j<x.coeffs.size();j++)
            tmp[i+j]+=coeffs[i]*x.coeffs[j];

    polynomian<T> g;
    g.coeffs=tmp;
    return g;
}

template<typename T>
polynomian<T> polynomian<T>::derive()
{
    polynomian<T> tmp(*this);
    for(int i=1;i<tmp.coeffs.size();i++)tmp.coeffs[i-1]=tmp.coeffs[i]*i;
    if(coeffs.size()>1)tmp.coeffs.pop_back();
    else tmp.coeffs[0] = 0;                     //patch
    return tmp;
}

template<typename T>
T polynomian<T>::operator()(T x)
{
    T y = coeffs[coeffs.size()-1];
    for(int i=coeffs.size()-2;i>=0;y=y*x+coeffs[i--]);
    return y;
}

#endif //POLY_H
