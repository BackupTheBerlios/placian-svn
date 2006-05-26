#include "placian.h"

int main(int argc,char **argv)
{
    try{
        placian::init(argc,argv);
    }catch(...){};
    
    try{
        placian::run();
    }catch(...){};
    
    if(placian::gtk_gui)
	std::cout<<"Widac chcesz gui ale nie mozesz"<<std::endl;
}
