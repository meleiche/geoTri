#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "TSP_02.h"
using namespace std	;
#include "WGS84.h"


WGS84::WGS84(void)
{
	init();
}


WGS84::~WGS84(void)
{
}

bool WGS84::init()
{
	a = 6378137.0 ;	//meters
	//a = 6378137000.0 ;	 //millimeters
	f = 298.257223563;	  
	b = a*(1 - 1/f);	  
	aa = a*a;	  
	bb = b*b;		
	epson2 = aa - bb;
	epson = sqrt (epson2) ;
	ee = epson2/aa;   
	return true;
};

bool WGS84::write(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(10) ;
		//setprecision(8)	;

	fn.setf(ios::right);
	//fn.width(10);	
	fn << "a = " << a << endl  ;
	fn << "b = " << b << endl  ;
	fn << "f = " << f << endl  ;
	fn << "ee = " << ee << endl  ;
	fn << "epson = " << epson << endl  ;

	fn << endl	;
	fn.close();
	return true;
};