#include <vector>

#ifndef GPLACIAN_H
#define GPLACIAN_H

#ifndef BORDER
#define BORDER 40
#endif

namespace gplacian{

template<typename T>
class gCairoPlot{
    struct axis{
    T min,max;
    };

    //auxiliary functions
    axis minmax(const std::vector<T> &z)
    {
        axis tmp;
        if(z.size())
        {
            tmp.min=tmp.max=z[0];
            for(int i=1;i<z.size();i++)
                if(z[i]<tmp.max)tmp.max = z[i];
                else if(z[i]>tmp.min)tmp.min = z[i];
        }
        return tmp;
    }

    //plot data
    std::vector<T> *x,*y;       //original
    std::vector<T> x_px,y_px;   //converted to pixels
    axis OX,OY;

    int width,height;   //plot resolution
    cairo_t *cr;        //handle to plot

public:
    //constructor
    gCairoPlot(cairo_t *cr_,int width_=800, int height_=600,std::vector<T> *x_=0,std::vector<T> *y_=0):cr(cr_),width(width_),height(height_),x(x_),y(y_)
    {
        sync();
    }

    //this cas be called pseudo-constructor or reconstructor
    void update(std::vector<T> *x_,std::vector<T> *y_);

    //drawing
    void draw()
    {
        draw_scene();
        draw_points();
    }
    void draw(int width_,int height_);

    //drawing sub-routines
    void draw_scene();
    void draw_points();

    //this function synchronizes plot data with plot layout
    void sync();

};

template<typename T>
void gCairoPlot<T>::sync()
{
    int rwidth = width - 2*BORDER;
    int rheight = height - 2*BORDER;

    if(x && y) //then find axis min and max
    {
        OX = minmax(*x);
        OY = minmax(*y);
    }

    //prepare points for plot matrix

    T x_interval = OX.max - OX.min;
    T y_interval = OY.max - OY.min;

    T x_scale = (rwidth)/x_interval;
    T y_scale = (rheight)/y_interval;

    //erasing pixel matrix
    x_px.clear();
    y_px.clear();

    //reverting y axis and transforming with vector u = [border,border]
    for(int i=0;i<rwidth;i++)
    {
        x_px.push_back( x_scale*((*x)[i*(x->size())/rwidth]-OX.min) );
        x_px[i] += BORDER;
        y_px.push_back( y_scale*((*y)[i*(y->size())/rwidth]-OY.min) );
        y_px[i] = height - BORDER - y_px[i];
    }

}

template<typename T>
void gCairoPlot<T>::draw_scene()
{
    //setting background
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    //drawing main frame
    cairo_rectangle (cr, BORDER, BORDER, width-BORDER*2, height-BORDER*2);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_fill_preserve (cr);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);

    //drawing additional lines

    cairo_set_line_width(cr,0.5);

    for(int yy=BORDER;yy<height-BORDER;yy+=20)
    {
        cairo_move_to(cr,BORDER,yy);
        cairo_line_to(cr,width-BORDER,yy);
    }

    for(int xx=BORDER;xx<width-BORDER;xx+=20)
    {
        cairo_move_to(cr,xx,BORDER);
        cairo_line_to(cr,xx,height-BORDER);
    }

    cairo_set_source_rgb (cr, 0.3, 0.3, 0.3);
    //double dashes[] = {20,20};
    //cairo_set_dash(cr, dashes,0,1);

    cairo_stroke (cr);
    
    
    if(x && y) //then draw axis min and max
    {
	cairo_scale (cr, 1, 1);
	cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (cr, 12);
		   
	cairo_move_to (cr, BORDER  ,BORDER/2);
	cairo_show_text (cr, "gPlacian Plot");
	
	cairo_move_to (cr, width-BORDER-10, height-BORDER/2);
	cairo_show_text (cr, "t");
				   
	cairo_move_to (cr, BORDER*1/4, BORDER*3/2);
	cairo_show_text (cr, "y(t)");

	cairo_set_source_rgb (cr, 0.5, 0.5, 1);
	cairo_fill_preserve (cr);
	cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);
	cairo_set_line_width (cr, 3);
	cairo_stroke (cr);
	
	//cairo_move_to (cr, 100, 100);
	//cairo_show_text (cr, "gPlacian Plot");
    }

}

template<typename T>
void gCairoPlot<T>::draw_points()
{

    if(x_px.size() && y_px.size())
    {
        //drawing curve
        cairo_set_line_width(cr,2);

        cairo_move_to (cr, x_px[0], y_px[0]);

        for(int i=0;i<width-2*BORDER;i++)cairo_line_to(cr,x_px[i],y_px[i]);

        cairo_set_source_rgb (cr, 0.3, 0.6, 0.3);
        cairo_stroke (cr);
    }

}

//----------------------------------

static void
draw (cairo_t *cr, int width, int height, std::vector<double> x, std::vector<double> y)
{
    //generating cube function in order to test plot class
    //std::vector<double> x,y;
    //for(double i=-5;i<=5;i+=0.1)
    //{
    //   x.push_back(i);
    //    y.push_back((i+2)*(i-3)*(i-4));
    //}

    gCairoPlot<double>(cr,width,height,&x,&y).draw();


}

} //end of gplacian namespace

#endif //GPLACIAN_H
