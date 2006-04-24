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

#endif
