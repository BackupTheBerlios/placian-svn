#ifndef DISCRETE_BOREL_H
#define DISCRETE_BOREL_H

template<typename T,typename TMP>
T discrete_borel(T &A,T &B,TMP step)
{
    T res;
    if(A.size()!=B.size()){throw(0);/*"Incoherent sizes!"*/}
    TMP tmp=0;
    for(int i=0;i<A.size();i++)
    {
        T surf; //creating surface points
        for(int j=0;j<=i && i;j++)
            surf.push_back(A[j]*B[i-j]);	//borel goes here

        //integrating with trapezoid method
        if(surf.size()>1)
        {
        	tmp = (surf[0] + surf[i])*0.5;
        	for(int j=1;j<i;j++)tmp+=surf[j];
        }

        res.push_back(tmp*step);
        tmp=0;
    }
    return res;
}

#endif //DISCRETE_BOREL_H
