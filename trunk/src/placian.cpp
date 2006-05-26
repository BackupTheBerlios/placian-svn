#include "placian.h"

namespace placian{

//HOWTO
static void showhelp() {
	std::cout<<"Usage: placian [PARAMETRS] [OPTIONS] [filename(s)...]\n\
\n\
HELP:\n\
  -h, --help             	show this help message\n\
\n\
PARAMETRS:\n\
  --numerator <...>		numerator parametrs (short -n)\n\
  --denumerator	<...>           denumerator parametrs (short -d)\n\
  --amplification <k>		amplification rate (short -a | optional)\n\
  --freq <Hz>			sample rate (short -f | optional)\n\
  --delay <s>			delay time (short -D | optional)\n\
\n\
OPTIONS:\n\
  --gtk-plot			draws gtk-plot\n\
  --dir				target directory for output"<<std::endl;
}

//PARAMS
int option_index = 0;
static option long_options[] = {
    {"numerator", 1, 0, 'n'},
    {"denumerator", 1, 0, 'd'},
    {"amplification", 1, 0, 'a'},
    {"freq", 1, 0, 'f'},
    {"delay", 1, 0, 'D'},
    {"gtk-plot", 0, 0, 300},
    //{"step", 0, 0, 101},
    //{"equations", 0, 0, 102},
    //{"no-key", 0, 0, 103},
    //{"dir", 1, 0, 104},
    {"help", 0, 0, 'h'},
    {0, 0, 0, 0}
};

//MODEL SETTINGS
std::vector<double> N,D;
double k=1,freq=10,delay=0;

std::string num,denum,amp,fr,de;
std::vector<std::string> infile;

bool gtk_gui = 0;
//bool step  = 0;
//bool equations = 0;
bool keyboard = 1;


//INITALIZING SEQUENCE
void init(int argc,char **argv)
{
    int c;
    while ( (c = getopt_long (argc, argv, "n:d:ha:f:D:",long_options, &option_index)) != -1)
    {
        switch(c)
        {
        case 0:
            std::cout<<"Option"<<long_options[option_index].name<<std::endl;
            break;
        case 'h':
            showhelp();
            exit(0);
            break;
        case 'n':
            num = optarg;
            break;
        case 'd':
            denum = optarg;
            break;
        case 'a':
            amp = optarg;
            break;
        case 'f':
            fr = optarg;
            break;
        case 'D':
            de = optarg;
            break;
	case 300:
	    gtk_gui = true;
	    break;
        case '?':
            showhelp();
            exit(0);
            break;
        default:
            ;
        }
    }

    if (optind < argc)
    {
        while (optind < argc)infile.push_back(argv[optind++]);
        keyboard = 0;
    }

    //converting string to double
    std::istringstream str;
    double tmp;
    if(num.size() && denum.size())
    {
        //numerator variables
        str.str(num);
        while(str>>tmp)N.push_back(tmp);
        str.clear();

        //denum....
        str.str(denum);
        while(str>>tmp)D.push_back(tmp);
        str.clear();
    }

    if(N.size()>=D.size())
    {
        std::cerr<<"Polynomial division not yet supported"<<std::endl;
        abort();
    }

    if(amp.size())
    {
        str.str(amp);
        while(str>>k);
        str.clear();
    }

    if(fr.size())
    {
        str.str(fr);
        while(str>>freq);
    }

    if(de.size())
    {
        str.str(de);
        while(str>>freq);
        str.clear();
    }
}

std::vector<double> readfromstream(iprobe<double> &x, model<double> &g,std::istream &input)
{
    std::vector<double> y;      //output
    do{input>>x;}while(input);
    input.clear();
    discrete_model<double> g_dsk(g,1/freq,x.size());  //discrete model
    y = discrete_borel< std::vector<double>,double>(x,g_dsk,1/freq);
    return y;
}

void writetostream(std::vector<double> &x, std::vector<double> &y, std::ostream &output)
{
    if(x.size()!=y.size())abort();
    for(int i=0;i<x.size();i++)
        output<<x[i]<<"\t"<<y[i]<<std::endl;
}


void run()
{
    iprobe<double> x;           //input
    model<double> g(N,D,k);     //continuous model
    std::vector<double> y;      //output

    if(keyboard)
    {
        y = readfromstream(x,g,std::cin);
        writetostream(x,y,std::cout);
    }
    else
    {
        for(int i=0;i<infile.size();i++)
        {
            y.clear();
            //READ
            std::ifstream fin;
            fin.open(infile[i].c_str(), std::ifstream::in);
            y = readfromstream(x,g,fin);
            fin.close();
            //WRITE
            std::string path = "out-"+infile[i];
            std::ofstream fout;
            fout.open(path.c_str());
            writetostream(x,y,fout);
            fout.close();
        }
    }
}

}   //end of placian namespace
