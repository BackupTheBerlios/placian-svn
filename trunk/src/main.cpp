#include "placian.h"

int main(int argc,char **argv)
{
    try{
        placian::init(argc,argv);
    }catch(...){};

    try{
        placian::run();
    }catch(...){};
}
