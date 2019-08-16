// Node.cpp
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
#include "Node.h" // Class definition

BOOL Free_Array(char s[], int size)
{
	int j;
	for(j=0; j < size; j++)
	{
		s[j] = '\0';
	}
	return TRUE;
}

bool Node::init()
{
	ID        = 0  ;
	loc       = 99 ;
	fi        = 0.0;    
	lamda     = 0.0; 
	h         = 0.0;
	Xp        = 0.0;
	Yp        = 0.0;
	Zp        = 0.0; 
	N         = 0.0;
	sin_fi    = 0.0; 
	cos_fi    = 0.0; 
	sin_lamda = 0.0; 
	r2p       = 0.0;   
	rp        = 0.0;     // r = sqrt(rr)
	cos_lamda = 0.0 ;
	tan_lamda = 0.0 ;

    rw= 0.0  ;		
    Zw= 0.0  ;	    
    rw1= 0.0  ;	    
    Zw1= 0.0  ;	 
    rw2= 0.0  ;	 
    Zw2= 0.0  ;	 
    rQw= 0.0  ;	 
    ZQw= 0.0  ;	 
    ZQw1= 0.0  ;
    rQ= 0.0  ;	 
    ZQ= 0.0  ;	 
    ZQ1= 0.0  ;	
     m1= 0.0  ;  
     m2= 0.0  ;  
     m3= 0.0  ;  
     m4= 0.0  ;  
     mw= 0.0  ;  
     mQ= 0.0  ;  
    taw = 0.0  ; 
	tawQ = 0.0  ;
	dr = 0.0;
	dZ = 0.0;
	ddr = 0.0 ;
	fi_w = 0.0;
	fi_err = 0.0;
	fi_err_DD = 0.0;
	hw = 0.0;
	h_err = 0.0 ;
	X_in = 0.0;         
    Y_in = 0.0;       
    Z_in = 0.0;

	h_new  = 0.0; 
	fi_new = 0.0;

	loc_W = 0.0;
	return true;
};

void Node::write(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
	//setprecision(8)	;

	fn.setf(ios::right);
	
	//fn.width(10);	
	fn << "ID = " << ID   << endl;
	fn << "fi = " << fi << "   lamda = " << lamda << "    h = " << h << endl;
	fn << "Xp = " << Xp << "      Yp = " << Yp    << "   Zp = " << Zp << endl << endl;

	fn << "X_in = " << X_in << "      Y_in = " << Y_in    << "   Z_in = " << Z_in << endl << endl;

	fn << "fi_err = " << fi_err << "fi_err_DD = " << fi_err_DD << "   h_err = " << h_err <<endl;

	fn << "rp = "   << rp   << "    N = " <<  N  << "    h = " << h   << " hw = " << hw <<endl; 	
	fn << "m1 = "   << m1   << "  rw1 = " << rw1 << "  Zw1 = " << Zw1 << endl;
	fn << "m2 = "   << m2   << "  rw2 = " << rw2 << "  Zw2 = " << Zw2 << endl;
	fn << "mw = "   << mw   << "   rw = " << rw  << "   Zw = " << Zw  << endl;
	fn << "rQw = "  << rQw  << "  ZQw = " << ZQw << " ZQw1 = " << ZQw1 << endl; 	
	fn << "mQ = "   << mQ   << "  rQ  = " << rQ  << "  ZQ  = " << ZQ << " ZQ1 = " << ZQ1 << endl;
	fn << "taw = "  << taw  << "   dr = " << dr  << "   dZ = " << dZ << " ddr = " << ddr << endl;
	fn << "fi_w = " << fi_w <<  "  loc= " << loc <<  "  check_ellipse = " << check_ellipse << endl;

	
	// << " dZ =   "<< dZ << " ddr =   "<< ddr << endl;
	
	fn << ID << "," << fi << "," << lamda << "," << h << "," << Xp << "," << Yp << "," << Zp ;
	fn << "," << fi_w << "," << hw << "," << fi_err << "," << h_err << "," << ddr << "," << taw << endl ;

	fn << "dXX = " << dXX << "       dYY = " << dYY << "   dZZ = " << dZZ <<endl;


	fn << endl << endl << endl	;
	fn.close();
	return;
};
void Node::write_err(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
		//setprecision(8)	;

	fn.setf(ios::right);   	
	
	fn <<  Xp << " + " << Yp << " - " << Zp << " = " << fi <<endl;	 	
	
	fn.close();
	return;
};
void Node::write_XYZ(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
	//setprecision(8)	;
	 	fn.setf(ios::right);
	
	fn << "*********    XYZ to fi, lamda, h  *********  " << endl << endl ;
	fn << ID << "," << fi << "," << lamda << "," << h << "," << Xp << "," << Yp << "," << Zp ;
	fn << "," << fi_w << "," << hw << "," << fi_err << "," << h_err << "," << ddr << "," << taw ;
	fn << endl	;
					    
	fn << "ID = " << ID << endl;
	fn << "fi = " << fi << " lamda = " << lamda << "  h = " << h << endl;
	fn << "Xp = " << Xp << "    Yp = " << Yp    << " Zp = " << Zp << endl << endl;
	fn << "X_in = " << X_in << "      Y_in = " << Y_in    << "   Z_in = " << Z_in << endl << endl;
	fn << "fi_err = " << fi_err << "  fi_err_DD = " << fi_err_DD <<"   h_err = " << h_err <<endl;
	fn << " loc = " << loc << "  check_ellipse = " << check_ellipse <<endl ;
	fn << "rp   = "	<< rp   << "     N   = " << N   << "  h   = " << h    << endl;   	
	fn << "m1   = " << m1   << "     rw1 = " << rw1 << "  Zw1 = " << Zw1  << endl;
	fn << "m2   = " << m2   << "     rw2 = " << rw2 << "  Zw2 = " << Zw2  << endl;
	fn << "mw   = " << mw   << "     rw  = " << rw  << "  Zw  = " << Zw   << endl;
	fn << "rQw  = " << rQw  << "    ZQw  = " << ZQw << " ZQw1 = " << ZQw1 << endl;		
	fn << "mQ   = " << mQ   << "     rQ  = " << rQ  << "   ZQ = " << ZQ   << " ZQ1 = " <<  ZQ1 << endl;
	fn << "taw  = " << taw  << "      dr = " << dr  << "   dZ = " << dZ   << " ddr = " << ddr  << endl;
	fn << "fi_w = " << fi_w << "  fi_err = " << fi_err << endl;
	fn << "fi_w = " << fi_w << "   lamda = " << lamda 	<< " hw = " << hw << endl;
	fn << endl	<< endl;
	fn.close();
	return;
};
 void Node::write_map(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
	
	fn << ID <<"," << fi <<"," << lamda <<"," << h <<"," ;
	fn << Xp <<"," << Yp <<"," << Zp <<"," << rp <<",";
	fn << fi_w <<"," << hw << "," ;
	fn << fi_err <<"," << fi_err_DD <<","<< h_err <<"," << ddr <<"," << taw << ",";
	fn << rQ <<"," << ZQ << "," << rQw << "," << ZQw << "," << dr << ","<< dZ << ",";
	fn << fi_new <<"," << h_new;
	fn << endl	;
	fn.close();
	return;
};
 void Node::write_XYZ2(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
		
	fn << Xp <<"," << Yp <<"," << Zp ;
	fn << endl	;
	fn.close();
	return;
};
 void Node::write_rZ(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
	
	fn << rp <<"," << Zp ;	  	
	fn << endl	;
	fn.close();
	return;
}
 void Node::write_loc(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
	
	fn << ID <<"," << check_ellipse <<"," << loc_W ;	  	
	fn << endl	;
	fn.close();
	return;
};
 void Node::write_Results_err(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;
	
	fn << fi_err <<"," << h_err <<"," << delta_r;	  	
	fn << endl	;
	fn.close();
	return;
}
void Node::fill_fi(char s[])
{
   int  Field, k, flag, j;
	char c1[] = "," ;
	char c2[40];

	Field = flag = j = 0;
	Free_Array(c2, 40);
	
	for (k = 0; (k < 200) && (s[k] != '\0') ; k++)
	{
		if (s[k] == c1[0])
				flag = 1;

		if (flag == 0) // Fill c2
		{
			c2[j] = s[k];
			j++;
		}

		if (flag == 1) // "," catched
		{
			switch(Field)
			{
				case 0:
					//fi = atof(c2);
					fi = stold(c2);
				break;

				case 1:
					//lamda = atof(c2);
					lamda = stold(c2);
				break;
			}		
			Free_Array(c2, 40);
			flag = 0;
			j = 0;
			Field++;
		}
	}
	
	//h = atof(c2);
	h = stold(c2);
	return ;

		/*
	int   k, j;
	char c2[20];

	k = j = 0;	

	for (k = 0; (k < 200) && (s[k] != '\0') ; k++)
	{
		c2[j] = s[k];
		j++;
	}
	fi = atoi(c2);
	return ; */
}
void Node::fill_XYZ(char s[])
{
   int  Field, k, flag, j;
	char c1[] = "," ;
	char c2[40];

	Field = flag = j = 0;
	Free_Array(c2, 40);
	
	for (k = 0; (k < 200) && (s[k] != '\0') ; k++)
	{
		if (s[k] == c1[0])
				flag = 1;

		if (flag == 0) // Fill c2
		{
			c2[j] = s[k];
			j++;
		}

		if (flag == 1) // "," catched
		{
			switch(Field)
			{
				case 0:
					//Xp = atof(c2);
					Xp = stold(c2);
				break;

				case 1:
					//Yp = atof(c2);
					Yp = stold(c2);
				break;
			}		
			Free_Array(c2, 40);
			flag = 0;
			j = 0;
			Field++;
		}
	}
	
	//Zp = atof(c2);
	Zp = stold(c2);
	fill_in_XYZ();
	return ;
}
void Node::fill_rZ(char s[])
{
   int  k, flag, j;
	char c1[] = "," ;
	char c2[40];

	flag = j = k = 0;
	Free_Array(c2, 40);
	
	for (k = 0; (k < 200) && (s[k] != '\0') ; k++)
	{
		if (s[k] == c1[0])
				flag = 1;

		if (flag == 0) // Fill c2
		{
			c2[j] = s[k];
			j++;
		}

		if (flag == 1) // "," catched
		{
			rp = stold(c2);
			r2p = rp*rp ;
			Free_Array(c2, 40);
			flag = 0;
			j = 0;
		}				
	}	
	Zp = stold(c2);	  	
	return ;
}
void Node::fill_fi_1()
{
	fi = fi_w ;
	fi_new = 0.0;
	fi_new = fi_w;
	h = hw ;
	h_new = 0.0;
	h_new = hw;
	return;
}
void Node::fill_fi_2()
{
	fi = fi_new - fi_err_DD ;
	h  =  h_new - h_err     ;
	return;
}
void Node::fill_in_XYZ()
{
	X_in = Xp;
	Y_in = Yp;
	Z_in = Zp;
	return;
}
//****************************************************************************************************
//Fill sum error in same line
// format of data line is fi, err,0.0
//****************************************************************************************************
void Node::fill_err(char s[])
{
   int  Field, k, flag, j;
	char c1[] = "," ;
	char c2[40];

	Field = flag = j = 0;
	Free_Array(c2, 40);
	
	for (k = 0; (k < 200) && (s[k] != '\0') ; k++)
	{
		if (s[k] == c1[0])
				flag = 1;

		if (flag == 0) // Fill c2
		{
			c2[j] = s[k];
			j++;
		}

		if (flag == 1) // "," catched
		{
			switch(Field)
			{
				case 0:
					//Xp = atof(c2);
					Xp = stold(c2);
				break;

				case 1:
					//Yp = atof(c2);
					Yp = stold(c2);
				break;
			}		
			Free_Array(c2, 40);
			flag = 0;
			j = 0;
			Field++;
		}
	}
	
	//Zp = atof(c2);
	Zp = stold(c2);
	fi = (Xp + Yp - Zp) ;
	return ;
}
//****************************************************************************************************
// Given fi, h ==>> compute sin, cos, r, Z from fi, h	(No XY)
//****************************************************************************************************
bool Node::fi2rZ(long double a, long double f, long double ee)
{
	std::setprecision(18) ;
	long double k  = 0.0;
	long double kk = 0.0;
	//long double kkk = 0.0;
	kk          = (long double) (1-1/f)*(1-1/f)  ;

	sin_fi      =  (long double) sin((long double) (fi/180.0)*PI)   ;
	cos_fi      =  (long double) cos((long double) (fi/180.0)*PI)   ;
	sin_lamda   =  (long double) sin((long double) (lamda/180.0)*PI);
	cos_lamda   =  (long double) cos((long double) (lamda/180.0)*PI);
	tan_lamda   =  (long double) tan((long double) (lamda/180.0)*PI);
	
	k           = (long double) sqrt(1 - (ee*sin_fi*sin_fi));
	N           = (long double) a/k   ;
	rp          =  (N*cos_fi) + (cos_fi*h); //*cos_fi   ;
	r2p         = rp * rp ;
	
	Xp          = (long double) rp*cos_lamda   ;
	Yp          = (long double) rp*sin_lamda   ;
	//Yp          = (long double) Xp * tan_lamda   ;	// use this equation to get exact tan(lamda)
	Zp          = (long double) ((kk*N)+h)*sin_fi        ;
	//compute_rp();		
	return true;
};
//****************************************************************************************************
// Given fi,lamda, h ==>> compute sin, cos from fi, lamda, h
//****************************************************************************************************
bool Node::fi2XYZ(long double a, long double f, long double ee)
{
	std::setprecision(18);
	compute_sin_fi()     ;
	compute_cos_fi()     ;
	compute_sin_lamda()  ;
	compute_cos_lamda()  ;
	compute_tan_lamda()  ; 
	compute_N(a, f, ee)  ;
	compute_rp_fi()      ;
	compute_r2p()        ;
	compute_Xp()         ;
	compute_Yp()         ;
	compute_Zp(f)	     ;
	/*				    
	long double k  = 0.0;
	long double kk = 0.0;
	//long double kkk = 0.0;
	kk          = (long double) (1-1/f)*(1-1/f)  ;

	sin_fi      =  (long double) sin((long double) (fi/180.0)*PI)   ;
	cos_fi      =  (long double) cos((long double) (fi/180.0)*PI)   ;
	sin_lamda   =  (long double) sin((long double) (lamda/180.0)*PI);
	cos_lamda   =  (long double) cos((long double) (lamda/180.0)*PI);
	tan_lamda   =  (long double) tan((long double) (lamda/180.0)*PI);
	
	k           = (long double) sqrt(1 - (ee*sin_fi*sin_fi));
	N           = (long double) a/k   ;
	//kkk         =  (N*cos_fi) + (cos_fi*h); //*cos_fi   ;
	rp          =  (N*cos_fi) + (cos_fi*h); //*cos_fi   ;
	r2p = rp * rp ;
	
	//Xp          = (long double) kkk*cos_lamda   ;
	//Yp          = (long double) kkk*sin_lamda   ;
	Xp          = (long double) rp*cos_lamda      ;
	Yp          = (long double) rp*sin_lamda      ;
	Zp          = (long double) ((kk*N)+h)*sin_fi ;
	//compute_rp();
	*/
	return true;
};
//****************************************************************************************************
// used after fi2XYZ - rp is computed exactly
//****************************************************************************************************
bool Node::XYZ2fi(long double a, long double b, long double ep)
{		  	
	compute_loc(a,b);
	compute_m1(ep)  ;
	compute_rw1(a,b,ep) ;
	compute_Zw1(ep) ;
	
	compute_m2(ep)  ;
	compute_rw2(a,b,ep) ;
	compute_Zw2(ep) ;
	
	compute_m3(ep)   ;
	compute_m4(ep)   ;
	compute_rw(ep)   ;
	compute_Zw(ep)   ;
	compute_loc_W(a,b);
	compute_mw()     ;
	compute_rQw(a,b) ;
	compute_ZQw()    ;
	compute_ZQw1(a,b);
	compute_taw()    ;
	compute_hw()     ;
	compute_fi_w()   ;
	/*
	double k  = 0.0;
	double kk = 0.0;
	double kkk = 0.0;
	double k1  = 0.0;
	double k2  = 0.0;
	// m1
	m1=Zp/(rp - ep) ;  	
	k = (b*b*sqrt(1 + m1*m1))/a ;
	kk = (m1*m1 +  (b*b/(a*a)) ) ;
	if (m1>=0)
	{	 
		rw1 = (ep*m1*m1 + k)/kk	  ;
	}
	if (m1<0)
	{	 
		rw1 = (ep*m1*m1 - k)/kk	  ;
	}
	Zw1 =  m1*(rw1 - ep) ;

	// m2
	k = kk = 0.0 ;
	m2=Zp/(rp + ep) ;  	
	k = (b*b*sqrt(1 + m2*m2))/a ;
	kk = (m2*m2 +  (b*b/(a*a)) ) ;
	if (m2>=0)
	{	 
		rw2 = (-1*ep*m2*m2 + k)/kk	  ;
	}
	if (m2<0)
	{	 
		rw2 = (-1*ep*m2*m2 - k)/kk	  ;
	}
	Zw2 =  m2*(rw2 + ep) ;

	// m3
	m3 = Zw2/(rw2 - ep) ;
	// m4
	m4 = Zw1/(rw1 + ep) ;

	rw = ep * (m3 + m4)/(m3 - m4)   ;
	Zw =  m4*(rw + ep) ;
	mw = (Zp-Zw)/(rp-rw)    ;

	k = kk = kkk = 0.0 ; 	
	k = (a*a*mw*mw) + (b*b)  ;
	kk =  (rp*mw - Zp)*(rp*mw - Zp)	 ;
	kkk =  (b/a)*(sqrt(k - kk) ) ;

	k1 = ( mw*mw*rp - mw*Zp ) ; // (-b)
	k2 = (mw*mw +  (b*b/(a*a)) ) ;	// denomitor

	if (mw>=0)
	{	 
		rQw = (k1 + kkk)/k2	  ;
	}
	if (mw<0)
	{	 
		rQw = (k1 - kkk)/k2	  ;  
	}

	ZQw =  Zp + mw*(rQw - rp) ;
	ZQw1 = -1*(b*b* rQw)/(a*a* ZQw) ;
	taw =  ZQw1*mw ;
	compute_hw();
	compute_fi_w();
	*/
	return true;
};
//****************************************************************************************************
// Given (X,Y,Z) compute (fi_w,hw)
//****************************************************************************************************
bool Node::XYZ2fi_S(long double a, long double b, long double ep)
{
	compute_rp()    ;
	compute_lamda() ;
	compute_loc(a,b);
	compute_m1(ep)  ;
	compute_rw1(a,b,ep) ;
	compute_Zw1(ep) ;
	
	compute_m2(ep)  ;
	compute_rw2(a,b,ep) ;
	compute_Zw2(ep) ;
	
	compute_m3(ep)   ;
	compute_m4(ep)   ;
	compute_rw(ep)   ;
	compute_Zw(ep)   ;
	compute_loc_W(a,b);
	compute_mw()     ;
	compute_rQw(a,b) ;
	compute_ZQw()    ;
	compute_ZQw1(a,b);
	compute_taw()    ;
	compute_hw()     ;
	compute_fi_w()   ;
	/*
	double k  = 0.0;
	double kk = 0.0;
	double kkk = 0.0;
	double k1  = 0.0;
	double k2  = 0.0;
	compute_rp();
	compute_lamda();
	compute_loc(a,b);
	// m1
	m1=Zp/(rp - ep) ;  	
	k = (b*b*sqrt(1 + m1*m1))/a ;
	kk = (m1*m1 +  (b*b/(a*a)) ) ;
	if (m1>=0)
	{	 
		rw1 = (ep*m1*m1 + k)/kk	  ;
	}
	if (m1<0)
	{	 
		rw1 = (ep*m1*m1 - k)/kk	  ;
	}
	Zw1 =  m1*(rw1 - ep) ;

	// m2
	k = kk = 0.0 ;
	m2=Zp/(rp + ep) ;  	
	k = (b*b*sqrt(1 + m2*m2))/a ;
	kk = (m2*m2 +  (b*b/(a*a)) ) ;
	if (m2>=0)
	{	 
		rw2 = (-1*ep*m2*m2 + k)/kk	  ;
	}
	if (m2<0)
	{	 
		rw2 = (-1*ep*m2*m2 - k)/kk	  ;
	}
	Zw2 =  m2*(rw2 + ep) ;

	// m3
	m3 = Zw2/(rw2 - ep) ;
	// m4
	m4 = Zw1/(rw1 + ep) ;

	rw = ep * (m3 + m4)/(m3 - m4)   ;
	Zw =  m4*(rw + ep) ;
	mw = (Zp-Zw)/(rp-rw)    ;

	k = kk = kkk = 0.0 ; 	
	k = (a*a*mw*mw) + (b*b)  ;
	kk =  (rp*mw - Zp)*(rp*mw - Zp)	 ;
	kkk =  (b/a)*(sqrt(k - kk) ) ;

	k1 = ( mw*mw*rp - mw*Zp ) ; // (-b)
	k2 = (mw*mw +  (b*b/(a*a)) ) ;	// denomitor

	if (mw>=0)
	{	 
		rQw = (k1 + kkk)/k2	  ;
	}
	if (mw<0)
	{	 
		rQw = (k1 - kkk)/k2	  ;  
	}

	ZQw =  Zp + mw*(rQw - rp) ;
	ZQw1 = -1*(b*b* rQw)/(a*a* ZQw) ;
	taw =  ZQw1*mw ;
	compute_hw();
	compute_fi_w();
	*/
	return true;
};
//****************************************************************************************************
// Given (X,Y,Z) compute (fi_w,hw)
//****************************************************************************************************
bool Node::rZ2fi(long double a, long double b, long double ep)
{			
	compute_loc(a,b);
	compute_m1(ep)  ;
	compute_rw1(a,b,ep) ;
	compute_Zw1(ep) ;
	
	compute_m2(ep)  ;
	compute_rw2(a,b,ep) ;
	compute_Zw2(ep) ;
	
	compute_m3(ep)   ;
	compute_m4(ep)   ;
	compute_rw(ep)   ;
	compute_Zw(ep)   ;
	compute_loc_W(a,b);
	compute_mw()     ;
	compute_rQw(a,b) ;
	compute_ZQw()    ;
	compute_ZQw1(a,b);		
	compute_hw()     ;
	compute_fi_w()   ;	
	compute_taw()    ;
	//compute_fi_err()  ;			
	//compute_h_err()   ;
	return true;
};
//****************************************************************************************************
// Compute exact value of point Q (rQ, ZQ) from (fi, lamda, h)
//****************************************************************************************************
bool Node::Exact_Q(long double a, long double b)
{
	long double t  = 0.0;
	long double tt = 0.0;
	long double k  = 0.0;
	long double kk = 0.0;
	long double kkk = 0.0;
	long double k1  = 0.0;
	long double k2  = 0.0;
	
	t   = (long double) tan(fi*PI/180)       ;	  // tan fi
	tt  = (long double) t*t                  ;	  // tan fi * tan fi

	k2  = (long double) (tt +  (b*b/(a*a)) ) ;	// dominator
	k1  = (long double)( tt*rp - t*Zp )      ; // (-b)
	 		
	k   = (long double) (a*a*tt) + (b*b)     ;
	kk  = (long double) (rp*t - Zp)*(rp*t - Zp)	 ;
	kkk = (long double) (b/a)*(sqrt(k - kk) ) ;
	 
	if (t>=0)
	{	 
		rQ = (long double) (k1 + kkk)/k2	  ;
	}
	if (t<0)
	{	 
		rQ = (long double) (k1 - kkk)/k2	  ;  
	}

	ZQ =  (long double) (Zp + t*(rQ - rp) );
	ZQ1 = -1*(b*b* rQ)/(a*a* ZQ) ;
	dr = rQ-rQw ;
	dZ = ZQ-ZQw	 ;
	Compute_mQ() ;
	Compute_ddr();
	//compute_fi_w();
	compute_fi_err();
	//compute_hw();
	compute_h_err();
	//tawQ =  ZQ1*mQ ;
	return true;
};
//****************************************************************************************************

void Node::set_ID(int i)
{
	ID = i+1;
	return;
};
void Node::Compute_mQ()
{
	mQ = (Zp -ZQ)/(rp - rQ) ;
	return;

}
void Node::Compute_ddr()
{
	ddr = (Zp)*( (1/mw) - (1/mQ)  ) ;
	return;

}
void Node::compute_fi_w()
{
	double k = 0.0 ;
	k = atan(mw) ;
	fi_w = k * 180 / PI ;
    return ;
}
void Node::compute_fi_err()
{		
	fi_err_DD = (fi_w - fi)      ;
	fi_err    = (fi_w - fi)*3600 ;
    return ;
}
void Node::compute_hw()
{
	double rr = 0.0 ;
	double zz = 0.0 ;
	rr =  rp - rQw;
	zz =  Zp - ZQw;
	hw = loc * sqrt((rr*rr) + (zz*zz)) ; 
	// check if P inside ellipse, then hw is negative
	return;
}
void Node::compute_h_err()
{
	h_err  = hw - h;
	return ;
}
void Node::compute_rp()
{
	rp = 0.0;
	r2p = 0.0;
	r2p 	    = (long double) (Xp*Xp + Yp*Yp )   ;
	rp          = (long double) sqrt(r2p)        ;
	return;
}
void Node::compute_lamda()
{
	long  double k = 0.0 ;
	k = (long double) atan(Yp/Xp) ;
	lamda = (long double) k * 180 / PI ;
    return ;
}
void Node::Compute_dXYZ()
{
   dXX = X_in - Xp;
   dYY = Y_in - Yp;
   dZZ = Z_in - Zp;
   return;
}	  
void Node::compute_loc(long double a, long double b)
{
	check_ellipse = 0.0;
	loc = 0;
	check_ellipse = (  r2p/(a*a)  )	+  ( (Zp*Zp)/(b*b)  )   	  ;

	if (check_ellipse == 1.000)    // on ellipse
	{
		loc = 0;
		return;
	}
	if (check_ellipse > 1.000) 	  // outside ellipse
	{
		loc = 1;
		return;
	}
	if (check_ellipse < 1.000) 		// inside ellipse
	{
		loc = -1;
		return;
	} 	
}
void Node::compute_loc_W(long double a, long double b)
{
	loc_W = 0.0;
	loc_W = (  (rw*rw)/(a*a)  )	+  ( (Zw*Zw)/(b*b)  )   	  ;	
		return; 	
}
void Node::compute_m1(long double ep)
{
	m1=Zp/(rp - ep) ;
	return;
}
void Node::compute_rw1(long double a, long double b, long double ep)
{
	double k  = 0.0;
	double kk = 0.0;
	k = (b*b*sqrt(1 + m1*m1))/a ;
	kk = (m1*m1 +  (b*b/(a*a)) ) ;
	if (m1>=0)
	{	 
		rw1 = (ep*m1*m1 + k)/kk	  ;
	}
	if (m1<0)
	{	 
		rw1 = (ep*m1*m1 - k)/kk	  ;
	}
	return;
}
void Node::compute_Zw1(long double ep)
{
	Zw1 =  m1*(rw1 - ep) ;
	return;
}

void Node::compute_m2(long double ep)
{
	m2=Zp/(rp + ep) ;
	return;
}
void Node::compute_rw2(long double a, long double b, long double ep)
{
	double k  = 0.0;
	double kk = 0.0;
	k = (b*b*sqrt(1 + m2*m2))/a ;
	kk = (m2*m2 +  (b*b/(a*a)) ) ;
	if (m2>=0)
	{	 
		rw2 = (-1*ep*m2*m2 + k)/kk	  ;
	}
	if (m2<0)
	{	 
		rw2 = (-1*ep*m2*m2 - k)/kk	  ;
	}
	return;
}
void Node::compute_Zw2(long double ep)
{
	Zw2 =  m2*(rw2 + ep) ;
	return;
}

void Node::compute_m3(long double ep)
{
	m3 = Zw2/(rw2 - ep) ;
	return;
}
void Node::compute_m4(long double ep)
{
	m4 = Zw1/(rw1 + ep) ;
	return;
}
void Node::compute_rw(long double ep)
{
	rw = ep * (m3 + m4)/(m3 - m4)   ;
	return;
}
void Node::compute_Zw(long double ep)
{
	Zw =  m4*(rw + ep) ;
	return;
}

void Node::compute_mw()
{
	mw = (Zp-Zw)/(rp-rw)    ;
	return;
}	 
void Node::compute_rQw(long double a, long double b)
{
	double k   = 0.0;
	double kk  = 0.0;
	double kkk = 0.0;
	double k1  = 0.0;
	double k2  = 0.0;  
		
	k   = (a*a*mw*mw) + (b*b)        ;
	kk  =  (rp*mw - Zp)*(rp*mw - Zp) ;
	kkk =  (b/a)*(sqrt(k - kk) )     ;

	k1  = ( mw*mw*rp - mw*Zp )       ; // (-b)
	k2  = (mw*mw +  (b*b/(a*a)) )    ;	// denomitor

	if (mw>=0)
	{	 
		rQw = (k1 + kkk)/k2	  ;
	}
	if (mw<0)
	{	 
		rQw = (k1 - kkk)/k2	  ;  
	}	  
	return;
}
void Node::compute_ZQw()
{
	ZQw =  Zp + mw*(rQw - rp) ;
	return;
}
void Node::compute_ZQw1(long double a, long double b)
{
	ZQw1 = -1*(b*b* rQw)/(a*a* ZQw) ;
	return;
}

void Node::compute_taw()
{
	taw =  ZQw1*mw ;
	return;
}


void Node::compute_sin_fi()   
{
	sin_fi      =  (long double) sin((long double) (fi/180.0)*PI)   ;		
	return;
}
void Node::compute_cos_fi()
{
	cos_fi      =  (long double) cos((long double) (fi/180.0)*PI)   ;	
	return;
}
void Node::compute_sin_lamda()
{
	sin_lamda   =  (long double) sin((long double) (lamda/180.0)*PI);	 	
	return;
} 
void Node::compute_cos_lamda()
{
	cos_lamda   =  (long double) cos((long double) (lamda/180.0)*PI); 	
	return;
} 
void Node::compute_tan_lamda()
{
	tan_lamda   =  (long double) tan((long double) (lamda/180.0)*PI);
	return;
}      
void Node::compute_N(long double a, long double f, long double ee)
{
	long double k  = 0.0;
	long double kk = 0.0;
	kk          = (long double) (1-1/f)*(1-1/f)  ;
	k           = (long double) sqrt(1 - (ee*sin_fi*sin_fi));
	N           = (long double) a/k   ;
	return;
}         
void Node::compute_rp_fi()
{
	rp          =  (N*cos_fi) + (cos_fi*h);
	return;
}
void Node::compute_r2p()  	
{
	r2p = rp * rp ;
	return;
}
void Node::compute_Xp()
{
	Xp          = (long double) rp*cos_lamda      ;	   	
	return;
}        
void Node::compute_Yp()	  
{   Yp          = (long double) rp*sin_lamda      ;	 	
	return;
}
 void Node::compute_Zp(long double f)
{
	long double kk = 0.0;	
	kk          = (long double) (1-1/f)*(1-1/f)  ;
	Zp          = (long double) ((kk*N)+h)*sin_fi ;
	return;
}

 void Node::compute_delta_r()	  
{   
	long double kk = sqrt((Xp*Xp) + (Yp*Yp));
		delta_r    = (long double) (rp - kk)     ;	 	
	return;
}