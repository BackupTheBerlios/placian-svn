#include "placian.h"

int main(int argc,char **argv)
{
    try{
    	gtk_init (&argc, &argv);
        placian::init(argc,argv);
    }catch(...){};
    
    try{
        placian::run();
    }catch(...){};   
}
