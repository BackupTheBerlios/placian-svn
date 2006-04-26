#ifndef IPROBE_H
#define IPROBE_H
#include <vector>
#include <string>
#include <sstream>

template<typename T>
class iprobe : public std::vector<T>{
public:
    iprobe():std::vector<T>(0){}

    friend std::istream& operator>>(std::istream& s, iprobe<T>& x)
    {
        //cleaning from wastes
        std::string tmp;
        s>>tmp;
        for(int i=0;i<tmp.size();i++)
            if(((tmp[i]>='0' && tmp[i]<='9') || tmp[i]=='-') || tmp[i]=='.' || tmp[i]==',')
            {
                if(tmp[i]==',')tmp[i]='.';
            }
            else tmp[i]=' ';

        //converting string to typename T values
        std::istringstream ins;      // Declare an input string stream.
        ins.str(tmp);           // Specify string to read.

        T val;
        while(ins>>val)x.push_back(val);

        return s;
    }
};

#endif
