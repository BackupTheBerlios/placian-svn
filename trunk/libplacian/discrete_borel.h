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
        T surf; //surface points
        for(int j=0;j<i;j++)
            surf.push_back(A[j]*B[i-j]);

        //integrating
        for(int j=0;(j<surf.size()-1) && surf.size();j++)
	    tmp+=step*(surf[j]+surf[j+1])/2;

        res.push_back(tmp);
        tmp=0;
    }
    return res;
}

#endif //DISCRETE_BOREL_H
