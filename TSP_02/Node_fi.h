#pragma once
class Node_fi
{
public:
    int ID   ;	  
	long double fi   ;  // input	 latitude (decimal degree)
    long double lamda;  // input	 longitude (decimal degree)
    long double h    ;  // input   h (ellipsoidal height m)
    long double Xp   ;  // computed from (fi, lamda, h)
    long double Yp   ;  // computed from (fi, lamda, h)
    long double Zp   ;  // computed from (fi, lamda, h)

	long double err_0_fi   ; // fi_w - fi
	long double err_0_h    ; // hw - h
	long double err_0_X    ; // X0 - Xp
	long double err_0_Y    ; // Y0 - Yp
	long double err_0_Z    ; // Z0 - Zp

	long double err_1_fi   ;  // fi_w1 - fi
	long double err_1_h    ;  // hw - h
	long double err_1_X    ;  // X1 - Xp
	long double err_1_Y    ;  // Y1 - Yp
	long double err_1_Z    ;  // Z1 - Zp

	long double err_2_fi   ; // fi_w2 - fi
	long double err_2_h    ; // hw - h
	long double err_2_X    ; // X2 - Xp
	long double err_2_Y    ; // Y2 - Yp
	long double err_2_Z    ; // Z2 - Zp
   	
public:
	Node_fi(void);
	~Node_fi(void);
	void write_err_0(char ff[20]);
	void write_err_1(char ff[20]);
	void write_err_2(char ff[20]);
};

