#include <stdio.h>
#include <iostream>
#include "CImg.h"
#include <math.h>
#include <chrono>

using namespace std;
using namespace cimg_library;


typedef CImg<unsigned char> IC;
typedef CImg<float> IF;
typedef float F;
typedef int I;


void create()
{
	IF img(1245,1755,1,3,0);
	IF tmp("hobbit.jpg");
	tmp.resize(415, 585);
	//tmp.display();
	int ini_x=200;
	int ini_y=100;
	
	for(int i=0; i<tmp.height(); i++)
		for(int j=0; j<tmp.width(); j++)
		{
			img(j+ini_y,i+ini_x,0) = tmp(j,i,0) ;
			img(j+ini_y,i+ini_x,1) = tmp(j,i,1) ;
			img(j+ini_y,i+ini_x,2) = tmp(j,i,2) ;
		}
	
	img.save("result.jpg");
	img.display();
	
	
}



int main()
{
	create();
	return 0;
}
