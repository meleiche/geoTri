// Node.h
#pragma once
#ifndef _NODE_
#define _NODE_

class Node
{
public:
    int ID   ;
	int flag ; // flag = 1 for fi2XYZ,, flag = 0 for XYZ2fi
	int loc  ; // loc = 0 for point on ellipse,  loc = 1 for point outside ellipse, loc = -1 for point inside ellipse
	
	long double check_ellipse;	 // >1 out ellipse, = 1 on ellipse, <1 inside ellipse
	long double loc_W;	 // 

	long double fi   ;  // input	 latitude (decimal degree)
    long double lamda;  // input	 longitude (decimal degree)
    long double h    ;  // input   h (ellipsoidal height m)
    long double Xp   ;  // computed from (fi, lamda, h)
    long double Yp   ;  // computed from (fi, lamda, h)
    long double Zp   ;  // computed from (fi, lamda, h)
	long double r2p  ;  // rr = 	Xp*Xp + Yp*Yp
	long double rp   ;  // r = sqrt(rr)
	
	long double sin_fi ;
	long double cos_fi ;
	long double sin_lamda ;
	long double cos_lamda ;
	long double tan_lamda ;

	long double N ;	    // radius of curvature

	long double X_in;   // input from file
    long double Y_in;   // input from file
    long double Z_in;   // input from file
	
	long double dXX ;   // dXX = X_in  - Xp
	long double dYY ;   // dYY = ZY_in - Yp
	long double dZZ ;   // dZZ = ZZ_in - Zp
	
	
	long double rw   ;	// point W
	long double Zw   ;	// point W
	long double rw1  ;	// point W1
	long double Zw1  ;	// point W1
	long double rw2  ;	// point W2
	long double Zw2  ;	// point W2
	long double rQw  ;	// point Qw
	long double ZQw  ;	// point Qw
	long double ZQw1 ;	// point Z'Qw
	long double rQ   ;	// point Q
	long double ZQ   ;	// point Q
	long double ZQ1  ;	// point Z'Q
	long double  m1  ;  // slope of line (F1-P)
	long double  m2  ;  // slope of line (F2-P)
	long double  m3  ;  // slope of line (F1-W2)
	long double  m4  ;  // slope of line (F2-W1)
	long double  mw  ;  // slope of line (P-Qw - W)
	long double  mQ  ;  // slope of line (P-Q)
	long double taw  ;  // taw = Zqw1*mw,,, taw != -1 
	long double tawQ ;  // taw = ZQ1*mQ,,, taw == -1 
	long double dr   ;  // dr = rQ-rQw
	long double dZ   ;  // dZ = ZQ-ZQw
	long double ddr  ;  // ddr = Zp/(1/mw-1/mQ))
	long double fi_w ;  // tan fi1 = mw
	long double hw   ; 	// distance from (Qw to P)

	long double fi_err    ; // fi_err = (fi - fi1)*3600 (seconds)
	long double fi_err_DD ; // fi_err_DD = (fi - fi1)(degree)	  
	long double h_err     ;	// h_err = h-hw
	
	long double h_new;
	long double fi_new;
	long double delta_r; //  delta_r = rXY - rp
	
            

public:
	bool init()                ;
	void fill_fi(char s[])     ;
	void fill_XYZ(char s[])    ;
	void fill_rZ(char s[])     ;
	void fill_err(char s[])	   ;
	void fill_fi_1()           ;
	void fill_fi_2()           ;
	void fill_in_XYZ()         ;

	//void write_Header(char ff[20]) ;
	void write(char ff[20])    ;
	void write_XYZ(char ff[20]);
	void write_map(char ff[20]);
	void write_err(char ff[20]);
	void write_XYZ2(char ff[20]);
	void write_rZ(char ff[20]) ;
	void write_loc(char ff[20]);
	
	bool fi2XYZ(long double a, long double ee, long double f)   ;
	bool XYZ2fi(long double a, long double b, long double ep)   ;
	bool XYZ2fi_S(long double a, long double b, long double ep) ;
	bool Exact_Q(long double a, long double b)                  ;
	bool fi2rZ(long double a, long double f, long double ee)    ;
	bool rZ2fi(long double a, long double b, long double ep)    ;

	
	void set_ID(int i)     ;
	void Compute_mQ()      ;
	void Compute_ddr()     ;
	void compute_fi_w()    ;
	void compute_fi_err()  ;
	void compute_hw()      ;
	void compute_h_err()   ;	 	
	void compute_rp()      ;
	void compute_lamda()   ;
	void Compute_dXYZ()    ;

	void Node::compute_m1(long double ep)  ;
	void Node::compute_rw1(long double a, long double b, long double ep) ;
	void Node::compute_Zw1(long double ep) ;

	void Node::compute_m2(long double ep)  ;
	void Node::compute_rw2(long double a, long double b, long double ep) ;
	void Node::compute_Zw2(long double ep) ;

	void Node::compute_m3(long double ep)  ;
	void Node::compute_m4(long double ep)  ;
	void Node::compute_rw(long double ep)  ;
	void Node::compute_Zw(long double ep)  ;
	void Node::compute_mw()                ;
	void Node::compute_rQw(long double a, long double b) ;
	void Node::compute_ZQw() ;
	void Node::compute_ZQw1(long double a, long double b) ;
	void Node::compute_taw() ;

	void Node::compute_sin_fi()   	 ;
    void Node::compute_cos_fi()    	 ;
    void Node::compute_sin_lamda() 	 ;
    void Node::compute_cos_lamda() 	 ;
    void Node::compute_tan_lamda()   ; 
    void Node::compute_N(long double a, long double f, long double ee)         	 ;
    void Node::compute_rp_fi()       ;
    void Node::compute_r2p()     	 ;
    void Node::compute_Xp()        	 ;
    void Node::compute_Yp()        	 ;
    void Node::compute_Zp(long double f) ;

	
	void compute_loc(long double a, long double b);
	void compute_loc_W(long double a, long double b);
	void compute_delta_r();
	void write_Results_err(char ff[20]);

	//BOOL Free_Array(char s[], int size);

}; 

#endif