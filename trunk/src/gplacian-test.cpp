/*
This is gplacian-test
*/

#include "gplacian.h"
#include <math.h>

int
main (int argc, char **argv)
{
    gtk_init (&argc, &argv);
    
    std::vector<double> x,y;
    for(double i=-5;i<=5;i+=0.1)
    {
        x.push_back(i);
        y.push_back((i+2)*(i-3)*(i-4));
    }

    gplacian::run(x,y);
    
    x.clear();
    y.clear();
    
    for(double i=0;i<=6.28;i+=0.1)
    {
        x.push_back(i);
        y.push_back(1-exp(-i));
    }
    
    gplacian::run(x,y);
    
    x.clear();
    y.clear();
    
    for(double i=0;i<=6.28;i+=0.1)
    {
        x.push_back(i);
        y.push_back(sin(i));
    }
    
    gplacian::run(x,y);

}
