#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#define _USE_MATH_DEFINES // for C++  
#include <cmath>  	
#include "TSP_02.h"
using namespace std;
#include "Node_fi.h"


Node_fi::Node_fi(void)
{	  	
	ID        = 0  ;  	
	fi        = 0.0;    
	lamda     = 0.0; 
	h         = 0.0;
	Xp        = 0.0;
	Yp        = 0.0;
	Zp        = 0.0; 

	err_0_fi   = 0.0;
	err_0_h    = 0.0;
	err_0_X    = 0.0;
	err_0_Y    = 0.0;
	err_0_Z    = 0.0;
	
	err_1_fi   = 0.0;
	err_1_h    = 0.0;
	err_1_X    = 0.0;
	err_1_Y    = 0.0;
	err_1_Z    = 0.0;
	
	err_2_fi   = 0.0;
	err_2_h    = 0.0;
	err_2_X    = 0.0;
	err_2_Y    = 0.0;
	err_2_Z    = 0.0;
}


Node_fi::~Node_fi(void)
{
}

void Node_fi::write_err_0(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
	fn << ID <<"," << err_0_fi  <<"," << 	err_0_h   <<"," << 	err_0_X   <<"," << 	err_0_Y  <<"," << 	err_0_Z  ;	  	
	fn << endl	;
	fn.close();
	return;
}
void Node_fi::write_err_1(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
	fn << ID <<"," << err_1_fi  <<"," << 	err_1_h   <<"," << 	err_1_X   <<"," << 	err_1_Y  <<"," << 	err_1_Z  ;	  	
	fn << endl	;
	fn.close();
	return;
}
void Node_fi::write_err_2(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
	fn << ID <<"," << err_2_fi  <<"," << 	err_2_h   <<"," << 	err_2_X   <<"," << 	err_2_Y  <<"," << 	err_2_Z  ;	  	
	fn << endl	;
	fn.close();
	return;
}

