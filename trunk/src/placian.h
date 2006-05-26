#include "../libplacian/libplacian.h"
#include <iostream>
#include <vector>
#include <string>
#include <getopt.h>
#include <sstream>
#include <fstream>

#ifndef PLACIAN_H
#define PLACIAN_H

namespace placian{

static void showhelp();
void init(int,char**);

std::vector<double> readfromstream(iprobe<double>&, model<double>&, std::istream&);
void writetostream(std::vector<double> &x, std::vector<double> &y, std::ostream &output);
void run();

extern bool gtk_gui;
extern bool keyboard;

}   //end of placian namespace

#endif //PLACIAN_H
