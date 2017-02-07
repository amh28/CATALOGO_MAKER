#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "CImg.h"

using namespace std;
using namespace cimg_library;
using namespace boost::filesystem;

typedef string S;
typedef boost::filesystem::path PATH;
typedef boost::filesystem::directory_iterator DIR_ITER;
typedef stringstream SS;
typedef vector<S> VS;
typedef CImg<unsigned char> IC;
typedef CImg<float> IF;
typedef float F;
typedef int I;


#define NUM_FILS 3
#define NUM_COLS 3

#define ESP_X 40
#define ESP_Y 50

#define	BORDE_IZQ 100
#define BORDE_DER 100
#define BORDE_SUP 350
#define BORDE_INF 50

#define WIDTH 1245
#define HEIGHT 1755

void print(VS &path)
{
	for(auto i=path.begin(); i!=path.end(); i++)
		cout<<*i<<endl;
}

/*VS check_path(S dir)
{
	path p(dir);
	VS paths;
    
    DIR_ITER b(p), e;
        
    for (auto i=b; i!=e; ++i)
    {
		PATH path = i -> path();
        PATH fe = path.extension();
        S ext = fe.string();        
        if(ext==".jpg" || ext==".png")
			paths.push_back(path.string());
    }       
	return paths;
}*/


VS check_path(S dir)
{
	path p(dir);
	VS paths;
    
    DIR_ITER b(p), e;
        
    for (auto i=b; i!=e; ++i)
    {
		PATH pathh = i -> path();		//obtengo path
		//cout<<path.string()<<endl;		        
		path sp(pathh.string());
		
		if(is_directory(sp))	//verifico si es directorio
		{
			DIR_ITER sb(sp), se;				
			for(auto j=sb; j!=se; ++j)		//itero en subpath
			{
				PATH subpath = j -> path();
				PATH fe = subpath.extension();
				S ext = fe.string();        
				if(ext==".jpg" || ext==".png")
					paths.push_back(subpath.string());
			}
		}
    }       
	return paths;
}

void auto_calc_width_and_height(int & width, int &height)
{
	width = (WIDTH - (BORDE_IZQ + BORDE_DER) - NUM_COLS* (ESP_X - 1) )/NUM_COLS;
	height = (HEIGHT - (BORDE_SUP + BORDE_INF) - NUM_FILS* (ESP_Y - 1) )/NUM_FILS;
}


void create(int width, int height, VS &paths)
{
	int NUM_IMAGES = paths.size();
	int NUM_PAGS = ceil(NUM_IMAGES / (NUM_FILS*NUM_COLS*1.0));
	
	cout<<NUM_PAGS<<endl;	
	
	S head = "RESULTADOS/";
	S ext(".jpg");		
	int cont = 0;	
	
	for(int i=0;i<NUM_PAGS;i++)
	{
		IF page(WIDTH,HEIGHT,1,3,255);					//crear imagen A4
		S name_img;
		SS convert;
		convert<<i;
		name_img = convert.str();
		name_img = head + name_img + ext;
		
		int INI_X, INI_Y;
		
		
		for(int j=0;j<NUM_FILS; j++)
		{
			for(int k=0;k<NUM_COLS;k++)
			{
				if(cont==NUM_IMAGES) break;
				
				S dir=paths[cont];
				cout<<"Leyendo imagen: "<<dir<<endl;
				cont++;
				
				IF img(dir.c_str());							//leer imagen pelicula
				img.resize(width,height); 	
				//img.display();					//resize imagen pelicula
				
				INI_X = BORDE_IZQ + (k*width + k*ESP_X);					//STEP_X
				INI_Y = BORDE_SUP + (j*height + j*ESP_Y);					//STEP_Y
				
				int ini_x, ini_y;
				for(int h=0; h<img.height(); h++)
				{
					for(int w=0; w<img.width(); w++)
					{
						ini_x = w + INI_X;	
						ini_y = h + INI_Y;
						
						page(ini_x, ini_y, 0) = img(w, h, 0) ;
						page(ini_x, ini_y, 1) = img(w, h, 1) ;
						page(ini_x, ini_y, 2) = img(w, h, 2) ;
						
						/*float color[3] = {255,0,0};
						page.draw_circle(ini_x, ini_y,10,color);*/
					}
				}
				if(k==2) break;												
				
			}
		}
		
		page.save(name_img.c_str());
		page.display();
	}
}



int main(int argc, char *argv[]) {
    int width, height;
    VS subpaths;
    
    auto_calc_width_and_height(width,height);
    
    
	subpaths = check_path("IMAGENES");
    print(subpaths);
    
    create(width,height,subpaths);
    
}

