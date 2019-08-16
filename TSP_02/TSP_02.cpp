// TSP_02.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include <stdlib.h>
#include <cmath>		 
//#include <math.h>	
#include <windows.h>
#include <Commdlg.h>	 
//#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>


#include "Node.h"
#include "Node_fi.h"	
#include "height.h"	
#include "Counter.h"
#include "WGS84.h"
#include "TSP_02.h"

using namespace std;
 
#define MAX_LOADSTRING 100
 
// Global Variables:
HINSTANCE hInst;								// current instance
char szTitle[MAX_LOADSTRING];					// The title bar text
char szWindowClass[MAX_LOADSTRING];			// the main window class name

char szFileName[MAX_PATH] ="";	  // input file name
Counter Con;					  // counter to count points
Node    *Node_Array;			  // Array of Node
Node_fi *Node_Array_fi;			  // Array of Node_fi
WGS84   WGS84_Datum;				  // Datum parameters Latest 
height  height_List; 

HWND hwnd;              // owner window
HANDLE hf;              // file handle
HWND g_hMainDialog = NULL;
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//-------------------------------------------------------
// Write the input read data to external file
//-------------------------------------------------------
BOOL Write_Input_To_File()
{
	int kk, l;
	char rr[300];
	FILE *log;
	char fn[] = OUTPUT_FILE ;		
	log = fopen(fn, "w");
	kk = Con.Nodes;
	l=0;
	l = strlen(szFileName);
	sprintf_s( rr, 300,  "****************************************************************************************** \n\n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "                  TSP Program  \nVersion 7.0 \nNov 2012       \n\n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "****************************************************************************************** \n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "\n\n\n------------------------------------------------------------------------------------------ \n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "                    I N P U T      D A T A    \n\n\n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "               Name of file data is %s    \n", szFileName);
	fputs(rr, log);
	sprintf_s( rr, 300,  "------------------------------------------------------------------------------------------ \n\n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "Input Array of Nodes \n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "****************************************************************************************** \n");
	fputs(rr, log);
	fclose (log) ;	
	log = fopen(fn, "a"); // apend
	sprintf_s( rr, 300,  "****************************************************************************************** \n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "				End of  Write_Input_To_File() \n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "****************************************************************************************** \n");
	fputs(rr, log);
	fclose (log) ;
	return TRUE;
}
// ----------------------------------------------------------------------------------------------------------
// Select Data file 
// ----------------------------------------------------------------------------------------------------------
void DoFileSelect(HWND hwnd)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFileName;	
	ofn.lpstrFilter = "Data Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";	
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "txt";
	if(GetOpenFileName(&ofn))
	{
		SetDlgItemText(g_hMainDialog, IDC_TEXT, szFileName);
	}
	//MessageBox(hwnd, "Done File Select", NULL, NULL);
	return ;
}
// ----------------------------------------------------------------------------------------------------------
// Read Data file to count records ONLY
// ----------------------------------------------------------------------------------------------------------
BOOL Count_Records(Counter& Coun)
{
	FILE *inFile;
	errno_t err;
	char buff[MAX_REC_LEN];
	char yy[300];
	ofstream fn;	
	//char rr[100];
	char z[] = "z"; //separator between datasets
	int i, flag;
	i = flag = 0;	
	// --------------------------------------------------------------------
	// Open File and Count Number Of Records
	// --------------------------------------------------------------------	
	err  = fopen_s( &inFile, szFileName , "r" );
	if( err == 0 )
	{
		sprintf_s(yy,100, "The file was opened\n");
		MessageBox(hwnd, yy, "i",MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		sprintf_s(yy,100, "The file was not opened\n");
		MessageBox(hwnd, yy, "i",MB_OK | MB_ICONINFORMATION);
	}

	while(fgets(buff,sizeof(buff),inFile) != NULL)
	{			
		i++;   		
	}		
	//sprintf_s(yy,250, "i = %d   nodes = %d", i,  Coun.Nodes);
	//MessageBox(hwnd, yy, "i",MB_OK | MB_ICONINFORMATION);
	Coun.Nodes = i ; // EOF	
	fclose(inFile);
	sprintf_s(yy,250, "i = %d    nodes = %d", i,  Coun.Nodes);
	MessageBox(hwnd, yy, "i",MB_OK | MB_ICONINFORMATION);
	fn.open(OUTPUT_FILE,ios::out); // new output file
	fn.close();
	//Coun.write(OUTPUT_FILE);
	return TRUE;	
}
// ----------------------------------------------------------------------------------------------------------
//	HEader for results of XYZ to fi
// ----------------------------------------------------------------------------------------------------------
void write_Header_XYZ(char ff[20])
{
	ofstream fn;
	int i, j;
//	int h[20];													   
	i = j = 0;
	fn.open(ff,ios::app); // open file in append mode
	//fn << std::fixed << std::setprecision(10) ;
	// current date/time based on current system
   time_t now = time(0);
   	   // convert now to string form
   char* dt = ctime(&now);
	   //cout << "The local date and time is: " << dt << endl;
	   // convert now to tm struct for UTC
   tm *gmtm = gmtime(&now);
   dt = asctime(gmtm);
   //cout << "The UTC date and time is:"<< dt << endl;


	fn << "********************************************************************\n";
	fn << "              Trilateration Algorithm    \n\n\n";
	fn << " This is conversion of (X,Y,Z) to fi, lamda, h)   " << endl;
	fn << "                                                   April 2018 " << endl;
	fn << "********************************************************************\n\n";

	fn << "\n\n     Input File Name:  " <<  szFileName  <<endl << endl;
	Con.write(OUTPUT_FILE);
	fn << " GMT time of processing is :" << dt << endl ;
	fn << "********************************************************************\n\n\n";
	/*
	fn << "ID" << "," << "fi" << "," << "lamda" << "," << "h" << "," << "Xp" << "," << "Yp" << "," << "Zp" ;
	fn << ",fi1,hw,fi_err,h_err,ddr,taw" << endl;
	*/	
	fn.close();
	return;	 	
};
// ----------------------------------------------------------------------------------------------------------
//	HEader for results of (r,Z) to (fi.h)
// ----------------------------------------------------------------------------------------------------------
void write_Header_rZ(char ff[20])
{
	ofstream fn;
	int i, j;
//	int h[20];													   
	i = j = 0;
	fn.open(ff,ios::app); // open file in append mode
	//fn << std::fixed << std::setprecision(10) ;
	// current date/time based on current system
  time_t now = time(0);
   	   // convert now to string form
   char* dt = ctime(&now);
	   //cout << "The local date and time is: " << dt << endl;
	   // convert now to tm struct for UTC
//   tm *gmtm = gmtime(&now);
  // dt = asctime(gmtm);
   //cout << "The UTC date and time is:"<< dt << endl;


	fn << "********************************************************************\n";
	fn << "              Trilateration Algorithm    \n\n\n";
	fn << " This is conversion of (r,Z) to fi, h)   " << endl;
	fn << "                                                   June 2018 " << endl;
	fn << "********************************************************************\n\n";

	fn << "\n\n     Input File Name:  " <<  szFileName  <<endl << endl;
	Con.write(OUTPUT_FILE);
	fn << " GMT time of processing is :" << dt << endl ;
	fn << "********************************************************************\n\n\n";		   	
	fn.close();
	return;	 	
};
// ----------------------------------------------------------------------------------------------------------
//	HEader for results of fi  to XYZ
// ----------------------------------------------------------------------------------------------------------
void write_Header_fi(char ff[20])
{
	ofstream fn;
	int i, j;
//	int h[20];													   
	i = j = 0;

	// current date/time based on current system
  // time_t now = time(0);
   	   // convert now to string form
  // char* dt = ctime(&now);
	   //cout << "The local date and time is: " << dt << endl;
	   // convert now to tm struct for UTC
  // tm *gmtm = gmtime(&now);
  // dt = asctime(gmtm);
  
	fn.open(ff,ios::app); // open file in append mode
	//fn << std::fixed << std::setprecision(10) ;
	fn << "********************************************************************\n";
	fn << "              Trilateration Algorithm    \n\n\n";
	fn << " This is conversion of (fi, lamda, h) to (X,Y,Z) " << endl;
	fn << "                                                   April 2018 " << endl;
	fn << "********************************************************************\n\n";

	fn << "\n\n     Input File Name:  " <<  szFileName  <<endl << endl;
	Con.write(OUTPUT_FILE);
	fn << " GMT time of processing is :" <<  endl ;
	fn << "********************************************************************\n\n\n";	  	
	fn.close();
	return;
};
// ----------------------------------------------------------------------------------------------------------
//	HEader for results of data in required format
// ----------------------------------------------------------------------------------------------------------
void write_matrix(char ff[20])
{
	ofstream fn;
	int i, j;	
	i = j = 0;
	fn.open(ff,ios::app); // open file in append mode
	//fn << std::fixed << std::setprecision(10) ;

	fn << "********************************************************************\n";
	fn << "              Trilateration Algorithm    \n\n\n";
	fn << " This is Sample data file " << endl;
	fn << "                                                   April 2018 " << endl;
	fn << "********************************************************************\n\n";

	fn << "\n\n     Input File Name:  " <<  szFileName  <<endl << endl;

	fn << " Data format:  " << endl;
	fn << "ID,fi,lamda,h,Xp,Yp,Zp,fi_w,hw,fi_err,h_err,ddr_taw"  << endl << endl;

	
	fn << "********************************************************************\n\n\n";

	 for (i = 0; i<Con.Nodes ; i++)
	 {
		fn << Node_Array[i].ID <<"," << Node_Array[i].fi <<"," << Node_Array[i].lamda <<"," << Node_Array[i].h <<"," ;
		fn << Node_Array[i].Xp <<"," << Node_Array[i].Yp <<"," << Node_Array[i].Zp <<"," ;
		fn << Node_Array[i].fi_w <<"," << Node_Array[i].hw << "," ;
		fn << Node_Array[i].fi_err <<"," << Node_Array[i].h_err <<"," << Node_Array[i].ddr <<"," << Node_Array[i].taw ;
		fn << endl ;
	 }
	fn << "********************************************************************\n";
	fn << "              Trilateration Algorithm    \n\n\n";
	fn << " ddr for all fi" << endl;
	fn << "                                                 " << endl;
	fn << "********************************************************************\n\n";
	 for (i = 0; i<Con.Nodes ; i++)
	 {	   
		 //fn << "i = " << i << "j = " << j << endl ;
		  fn << Node_Array[i].ddr << "," ;
		  j++;
		  if (j == 90)
		  {
			  j=0;
			   //fn << "i = " << i << "j = " << j << endl;
			   fn << endl ;
		  }
	 }	
	fn << "********************************************************************\n";
	fn << "              Trilateration Algorithm    \n\n\n";
	fn << " fi_err for all fi" << endl;
	fn << "                                                 " << endl;
	fn << "********************************************************************\n\n";
	 for (i = 0; i<Con.Nodes ; i++)
	 {	   
		 //fn << "i = " << i << "j = " << j << endl ;
		  fn << Node_Array[i].fi_err << "," ;
		  j++;
		  if (j == 90)
		  {
			  j=0;
			   //fn << "i = " << i << "j = " << j << endl;
			   fn << endl ;
		  }
	 }
	fn << "********************************************************************\n";
	fn << "              Trilateration Algorithm    \n\n\n";
	fn << " h_err for all fi" << endl;
	fn << "                                                 " << endl;
	fn << "********************************************************************\n\n";
	 for (i = 0; i<Con.Nodes ; i++)
	 {	   
		 //fn << "i = " << i << "j = " << j << endl ;
		  fn << Node_Array[i].h_err << "," ;
		  j++;
		  if (j == 90)
		  {
			  j=0;
			   //fn << "i = " << i << "j = " << j << endl;
			   fn << endl ;
		  }
	 }	
	fn.close();
	return;
};
void write_Data(char ff[20])
{
	ofstream fn;
	int i, j;	
	i = j = 0;
	fn.open(ff,ios::app); // open file in append mode
	fn << "********************************************************************\n";
	fn << "              Trilateration Algorithm    \n\n\n";
	fn << " This is Sample data file " << endl;
	fn << "                                                   April 2018 " << endl;
	fn << "********************************************************************\n\n";

	fn << " Data format:  " << endl;
	fn << "ID,fi,lamda,h"  << endl << endl;

	
	fn << "********************************************************************\n\n\n";
		 for (i = 0; i<91 ; i++)
		 {
			 fn << i+1 <<",50," ;

		 }

}
 /*
// ---------------------------------------------------------------------
// Fill Node record #i
// ---------------------------------------------------------------------
BOOL Fill_Node(char s[], int i)
{
	int   k, j;
	char c2[20];

	 k = j = 0;

	for (k = 0; (k < MAX_REC_LEN -1) && (s[k] != '\0') ; k++)
	{
		c2[j] = s[k];
		j++;
	}
	//Node_Array[i].ID = atoi(c2);
	//Free_Array(c2, 20);

	return TRUE;
}
*/
// export data which are input to algorithm: fi,50,h 
void write_List_fi(char ff[20])
{
    ofstream fn;
	int i, j;
	i = j = 0;
	fn.open(ff,ios::app); // open file in append mode
	fn << std::fixed << std::setprecision(18) ;	
	//fn.setf(ios::right);
	for(i=0; i<91;i++)
	{
		fn << i << ",50," << height_List.h1 << endl;
		fn << i << ",50," << height_List.h2 << endl;
		fn << i << ",50," << height_List.h3 << endl;
		fn << i << ",50," << height_List.h4 << endl;
		fn << i << ",50," << height_List.h5 << endl;
		fn << i << ",50," << height_List.h6 << endl;
		fn << i << ",50," << height_List.h7 << endl;
		fn << i << ",50," << height_List.h8 << endl;
		fn << i << ",50," << height_List.h9 << endl;
		fn << i << ",50," << height_List.h10 << endl;
		fn << i << ",50," << height_List.h11 << endl;
		fn << i << ",50," << height_List.h12 << endl;
		fn << i << ",50," << height_List.h13 << endl;
		fn << i << ",50," << height_List.h14 << endl;
		fn << i << ",50," << height_List.h15 << endl;
		fn << i << ",50," << height_List.h16 << endl;
		fn << i << ",50," << height_List.h17 << endl;
		fn << i << ",50," << height_List.h18 << endl;
		fn << i << ",50," << height_List.h19 << endl;
		fn << i << ",50," << height_List.h20 << endl;
		fn << i << ",50," << height_List.h21 << endl;
		fn << i << ",50," << height_List.h22 << endl;
		fn << i << ",50," << height_List.h23 << endl;
		fn << i << ",50," << height_List.h24 << endl;
		fn << i << ",50," << height_List.h25 << endl;
		fn << i << ",50," << height_List.h26 << endl;
		fn << i << ",50," << height_List.h27 << endl;
		fn << i << ",50," << height_List.h28 << endl;
		fn << i << ",50," << height_List.h29 << endl;
		fn << i << ",50," << height_List.h30 << endl;
		fn << i << ",50," << height_List.h31 << endl;
		fn << i << ",50," << height_List.h32 << endl;
		fn << i << ",50," << height_List.h33 << endl;
		fn << i << ",50," << height_List.h34 << endl;
		fn << i << ",50," << height_List.h35 << endl;  
	}
	//fn.close();
	return;
}
// ----------------------------------------------------------------------------------------------------------
// Fill fi, lmada, h
// ----------------------------------------------------------------------------------------------------------
BOOL Fill_Input_Array_fi(int N)
{
	FILE *inFile;
	errno_t err;
	char line[MAX_REC_LEN];
	//char rr[100];
	int i, j, m, flag1, k2;
	i = j = flag1 = k2 = m = 0;
	// --------------------------------------------------------------------
	// Open  Data File
	// --------------------------------------------------------------------
	err  = fopen_s( &inFile, szFileName , "r" );
	//WGS84_Datum.write(OUTPUT_FILE);
	i = 0;
	while(fgets(line, sizeof(line) ,inFile) != NULL)
	{	  		
		if ( i  < N  )
		{
			Node_Array[i].init();
			Node_Array[i].set_ID(i);
			Node_Array[i].fill_fi(line);
					  
			//Node_Array[i].compute_cos(6378137.0,0.00669437999014132, 0.00335281066474751); // excel file - GRS80
			//Node_Array[i].write(OUTPUT_FILE);
			
			i++;
		}
		
	}	
	fclose(inFile);
	//sprintf( rr, "Read Finished \n Number of Nodes = %d" , N );
	//MessageBox(hwnd, rr, "Count" ,MB_OK | MB_ICONINFORMATION);
	return TRUE;											 
}
// ----------------------------------------------------------------------------------------------------------
// XYZ input
// ----------------------------------------------------------------------------------------------------------
BOOL Fill_Input_Array_XYZ(int N)
{
	FILE *inFile;
	errno_t err;
	char line[MAX_REC_LEN];
//	char rr[100];
	int i, j, m, flag1, k2;
	i = j = flag1 = k2 = m = 0;
	// --------------------------------------------------------------------
	// Open  Data File
	// --------------------------------------------------------------------
	err  = fopen_s( &inFile, szFileName , "r" );
	WGS84_Datum.write(OUTPUT_FILE);
	i = 0;
	while(fgets(line, sizeof(line) ,inFile) != NULL)
	{	  		
		if ( i  < N  )
		{
			Node_Array[i].init();
			Node_Array[i].set_ID(i);
			Node_Array[i].fill_XYZ(line);		   			
			//Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
			//Node_Array[i].write(OUTPUT_FILE);
			/*
			//Input fi, lamda, h
			Node_Array[i].fill_fi(line);
			Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee);
			Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
			Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		  
			//Node_Array[i].compute_cos(6378137.0,0.00669437999014132, 0.00335281066474751); // excel file - GRS80
			Node_Array[i].write(OUTPUT_FILE);
			*/
			i++;
		}
		
	}	
	fclose(inFile);
	//sprintf( rr, "Read Finished \n Number of Nodes = %d" , N );
	//MessageBox(hwnd, rr, "Count" ,MB_OK | MB_ICONINFORMATION);
	return TRUE;											 
}
// ----------------------------------------------------------------------------------------------------------
// rZ input
// ----------------------------------------------------------------------------------------------------------
BOOL Fill_Input_Array_rZ(int N)
{
	FILE *inFile;
	errno_t err;
	char line[MAX_REC_LEN];
//	char rr[100];
	int i, j, m, flag1, k2;
	i = j = flag1 = k2 = m = 0;
	// --------------------------------------------------------------------
	// Open  Data File
	// --------------------------------------------------------------------
	err  = fopen_s( &inFile, szFileName , "r" );
	WGS84_Datum.write(OUTPUT_FILE);
	i = 0;
	while(fgets(line, sizeof(line) ,inFile) != NULL)
	{	  		
		if ( i  < N  )
		{
			Node_Array[i].init();
			Node_Array[i].set_ID(i);
			Node_Array[i].fill_rZ(line);		
			i++;
		}  		
	}	
	fclose(inFile);						
	return TRUE;											 
}
// ----------------------------------------------------------------------------------------------------------
//	input XYZ list
// ----------------------------------------------------------------------------------------------------------
BOOL Fill_Input_Array_err(int N)
{
	FILE *inFile;
	errno_t err;
	char line[MAX_REC_LEN];
//	char rr[100];
	int i, j, m, flag1, k2;
	i = j = flag1 = k2 = m = 0;
	// --------------------------------------------------------------------
	// Open  Data File
	// --------------------------------------------------------------------
	err  = fopen_s( &inFile, szFileName , "r" );  	
	i = 0;
	while(fgets(line, sizeof(line) ,inFile) != NULL)
	{	  		
		if ( i  < N  )
		{
			Node_Array[i].init();
			Node_Array[i].set_ID(i);
			Node_Array[i].fill_err(line);			
			i++;
		}			
	}	
	fclose(inFile);		
	return TRUE;											 
}
// ----------------------------------------------------------------------------------------------------------
//(fi, lamda, h) to (X,Y,Z)
// ----------------------------------------------------------------------------------------------------------
void fi2XYZ()
{
	int i = 0 ;
	DoFileSelect(hwnd);	  // open input file
	Con.init();			  //
	Count_Records(Con);	  // count records and store in [Con.Nodes]
	//Con.write(OUTPUT_FILE);	// 
	write_Header_fi(OUTPUT_FILE);
	Node_Array = new Node[Con.Nodes];	// create new array of nodes with size [Con.Nodes]
	Fill_Input_Array_fi(Con.Nodes);		// fill input data inside array
	for(i=0; i<Con.Nodes; i++)
	{
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].compute_delta_r();
		Node_Array[i].write(OUTPUT_FILE);
		Node_Array[i].write_map(SOLUTION_FILE);
		Node_Array[i].write_XYZ2(XYZ_FILE);
		Node_Array[i].write_rZ(rZ_FILE);
		Node_Array[i].write_Results_err(err_FILE);
	}					   
	//MessageBox(hwnd, "Done", "Done",MB_OK | MB_ICONINFORMATION);
	//write_Matrix(SOLUTION_FILE);	
	//write_matrix(Data_FILE);
	return;
}
// ----------------------------------------------------------------------------------------------------------
//	(X,Y,Z) to (fi, lamda, h) 
// ----------------------------------------------------------------------------------------------------------
void XYZ2fi()
{
	int i = 0 ;
	int test = 0 ;
	DoFileSelect(hwnd);	
	Con.init();
	Count_Records(Con);
	Con.write(OUTPUT_FILE);
	write_Header_XYZ(OUTPUT_FILE);
	Node_Array = new Node[Con.Nodes];	
	Fill_Input_Array_XYZ(Con.Nodes);
	for(i=0; i<Con.Nodes; i++)
	{
		Node_Array[i].XYZ2fi_S(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].write_XYZ(OUTPUT_FILE);
		Node_Array[i].fill_fi_1();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].Compute_dXYZ();
		Node_Array[i].write(OUTPUT_FILE);
		//Number of iteration (test)
		//test = 20 ;
		test = 2;
		while (test != 0)
		{
			Node_Array[i].fill_fi_2();
			Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
			Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
			Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
			Node_Array[i].Compute_dXYZ();
			Node_Array[i].write(OUTPUT_FILE);
			test--;
		}
		Node_Array[i].write_map(SOLUTION_FILE);
		/*
		Node_Array[i].fill_fi_2();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].write(OUTPUT_FILE);
		Node_Array[i].fill_fi_2();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].write(OUTPUT_FILE);
		Node_Array[i].fill_fi_2();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].write(OUTPUT_FILE);
		Node_Array[i].fill_fi_2();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].write(OUTPUT_FILE);
		Node_Array[i].fill_fi_2();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].write(OUTPUT_FILE);
		*/
	}

	//MessageBox(hwnd, "Done", "Done",MB_OK | MB_ICONINFORMATION);
	//write_Matrix(SOLUTION_FILE);
	//write_matrix(Data_FILE);
	return;
}
// ----------------------------------------------------------------------------------------------------------
//	(r,Z) to (fi, h) 
// ----------------------------------------------------------------------------------------------------------
void rZ2fi()
{
	int i = 0 ;
	int test = 0 ;
	DoFileSelect(hwnd);	
	Con.init();
	Count_Records(Con);
	Con.write(OUTPUT_FILE);
	write_Header_rZ(OUTPUT_FILE);
	Node_Array = new Node[Con.Nodes];	
	Fill_Input_Array_rZ(Con.Nodes);
	for(i=0; i<Con.Nodes; i++)
	{
		Node_Array[i].rZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].write_XYZ(OUTPUT_FILE);
		/*
		Node_Array[i].fill_fi_1();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].Compute_dXYZ();
		Node_Array[i].write(OUTPUT_FILE);
		//Number of iteration (test)
		test = 20 ;
		test = 2;
		while (test != 0)
		{
			Node_Array[i].fill_fi_2();
			Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
			Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
			Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
			Node_Array[i].Compute_dXYZ();
			Node_Array[i].write(OUTPUT_FILE);
			test--;
		}
		*/
		Node_Array[i].write_map(SOLUTION_FILE);
		/*
		Node_Array[i].fill_fi_2();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].write(OUTPUT_FILE);
		Node_Array[i].fill_fi_2();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].write(OUTPUT_FILE);
		Node_Array[i].fill_fi_2();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].write(OUTPUT_FILE);
		Node_Array[i].fill_fi_2();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].write(OUTPUT_FILE);
		Node_Array[i].fill_fi_2();
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].Exact_Q(WGS84_Datum.a,  WGS84_Datum.b);
		Node_Array[i].write(OUTPUT_FILE);
		*/
	}	 
	return;
}
void err_sum()
{
	int i = 0 ;
	DoFileSelect(hwnd);	
	Con.init();
	Count_Records(Con);
	Con.write(OUTPUT_FILE);
	//write_Header_XYZ(OUTPUT_FILE);
	Node_Array = new Node[Con.Nodes];	
	Fill_Input_Array_err(Con.Nodes);
	for(i=0; i<Con.Nodes; i++)
	{
		Node_Array[i].write_err(OUTPUT_FILE);
	}		 	
	return;
}


// ----------------------------------------------------------------------------------------------------------
// Validate Algorithm
// input fi, lamda, h)
//(fi, lamda, h) to (X,Y,Z) 
//(X,Y,Z) to (fi, lamda, h)
//(fi_w, lamda, hw) to (X0,Y0,Z0) 
//(fi1, lamda, h1) to (X1,Y1,Z1) 
//(fi2, lamda, h2) to (X2,Y2,Z2) 
// ----------------------------------------------------------------------------------------------------------
void Validate_XYZ2fi()
{
	int i = 0;
	long double fi_w     = 0.0;
	long double lamda    = 0.0;
	long double h_w      = 0.0;
	long double fi_err0  = 0.0;
	long double fi_err1  = 0.0;
	long double  h_err0  = 0.0;
	long double  h_err1  = 0.0;

	//fi2XYZ();
	DoFileSelect(hwnd);	  // open input file
	Con.init();			  //
	Count_Records(Con);	  // count records and store in [Con.Nodes]
	//Con.write(OUTPUT_FILE);	// 
	//write_Header_fi(OUTPUT_FILE);
	Node_Array    = new Node[Con.Nodes];	// create new array of nodes with size [Con.Nodes]
	Node_Array_fi = new Node_fi[Con.Nodes];	// create new array of nodes with size [Con.Nodes]
	Fill_Input_Array_fi(Con.Nodes);		// fill input data inside array

	for(i=0; i<Con.Nodes; i++)
	{
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		// Store original data inside: 	Node_Array_fi[i]
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 	 
		Node_Array_fi[i].ID    =  Node_Array[i].ID;
		Node_Array_fi[i].fi    =  Node_Array[i].fi;
		Node_Array_fi[i].lamda =  Node_Array[i].lamda;
		Node_Array_fi[i].h     =  Node_Array[i].h;

		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation	for (Xp,Yp, Zp)  

		Node_Array_fi[i].Xp    =  Node_Array[i].Xp;
		Node_Array_fi[i].Yp    =  Node_Array[i].Yp;
		Node_Array_fi[i].Zp    =  Node_Array[i].Zp;
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		// Start of validation - From 	(Xp,Yp, Zp)
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		
		//Input (Xp,Yp,Zp) to get fi(fi_w, lamda, h_w)
		Node_Array[i].init();
		Node_Array[i].ID   =   Node_Array_fi[i].ID ;
		Node_Array[i].Xp   =   Node_Array_fi[i].Xp ;
		Node_Array[i].Yp   =   Node_Array_fi[i].Yp ;
		Node_Array[i].Zp   =   Node_Array_fi[i].Zp ;

		Node_Array[i].XYZ2fi_S(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].write_loc(loc_File);
		fi_w    = 0.0;
		lamda   = 0.0;
		h_w     = 0.0;
		fi_w    =  Node_Array[i].fi_w ;
		lamda   =  Node_Array[i].lamda ;
		h_w     =  Node_Array[i].hw ;
		
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		// First Point P0 (fi_w, lamda, hw) to (X,Y,Z)
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		Node_Array[i].init();
		Node_Array[i].ID    =  	Node_Array_fi[i].ID;
		Node_Array[i].fi    =  	fi_w  ;
		Node_Array[i].lamda =  	lamda ;
		Node_Array[i].h     =   h_w   ;
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation	get(X0, Y0, Z0)
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].compute_h_err();
		Node_Array[i].compute_fi_err() ;
		
		fi_err0 = 0.0; 
		h_err0  = 0.0; 
		fi_err0 =  Node_Array[i].fi_err_DD ;
		h_err0  =  Node_Array[i].h_err ;

		Node_Array_fi[i].err_0_fi = Node_Array[i].fi - Node_Array_fi[i].fi	 ; 
		Node_Array_fi[i].err_0_h  = Node_Array[i].h  - Node_Array_fi[i].h	 ; 
		Node_Array_fi[i].err_0_X  = Node_Array[i].Xp - Node_Array_fi[i].Xp	 ; 
		Node_Array_fi[i].err_0_Y  = Node_Array[i].Yp - Node_Array_fi[i].Yp	 ; 
		Node_Array_fi[i].err_0_Z  = Node_Array[i].Zp - Node_Array_fi[i].Zp	 ; 
		Node_Array_fi[i].write_err_0(ERR_0_File) ;
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		// Second Point P1 (fi_w+err0, lamda, hw-err0) to (X,Y,Z)
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		Node_Array[i].init();
		Node_Array[i].ID    =  	Node_Array_fi[i].ID;
		Node_Array[i].fi    =  	fi_w - fi_err0 ;
		Node_Array[i].lamda =  	lamda ;
		Node_Array[i].h     =   h_w - h_err0 ;	  		
				
		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation	get(X1, Y1, Z1)
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);
		Node_Array[i].compute_h_err();
		Node_Array[i].compute_fi_err() ;

		fi_err1 = 0.0; 
		h_err1  = 0.0; 
		fi_err1 =  Node_Array[i].fi_err_DD ;
		h_err1  =  Node_Array[i].h_err ;

		Node_Array_fi[i].err_1_fi = Node_Array[i].fi - Node_Array_fi[i].fi	 ; 
		Node_Array_fi[i].err_1_h  = Node_Array[i].h  - Node_Array_fi[i].h	 ; 
		Node_Array_fi[i].err_1_X  = Node_Array[i].Xp - Node_Array_fi[i].Xp	 ; 
		Node_Array_fi[i].err_1_Y  = Node_Array[i].Yp - Node_Array_fi[i].Yp	 ; 
		Node_Array_fi[i].err_1_Z  = Node_Array[i].Zp - Node_Array_fi[i].Zp	 ; 
		Node_Array_fi[i].write_err_1(ERR_1_File) ;
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		// Third Point P2 (fi_w+err1, lamda, hw-err1) to (X,Y,Z)
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 		  
		Node_Array[i].init();
		Node_Array[i].ID    = Node_Array_fi[i].ID   	 ; 
		Node_Array[i].fi    =  	fi_w - fi_err1 ;
		Node_Array[i].lamda =  	lamda ;
		Node_Array[i].h     =   h_w - h_err1 ;

		Node_Array[i].fi2XYZ(WGS84_Datum.a,  WGS84_Datum.f, WGS84_Datum.ee); // geodesy computation	get(X2, Y2, Z2)
		Node_Array[i].XYZ2fi(WGS84_Datum.a,  WGS84_Datum.b, WGS84_Datum.epson);

		Node_Array_fi[i].err_2_fi = Node_Array[i].fi - Node_Array_fi[i].fi	 ; 
		Node_Array_fi[i].err_2_h  = Node_Array[i].h  - Node_Array_fi[i].h	 ; 
		Node_Array_fi[i].err_2_X  = Node_Array[i].Xp - Node_Array_fi[i].Xp	 ; 
		Node_Array_fi[i].err_2_Y  = Node_Array[i].Yp - Node_Array_fi[i].Yp	 ; 
		Node_Array_fi[i].err_2_Z  = Node_Array[i].Zp - Node_Array_fi[i].Zp	 ; 
		Node_Array_fi[i].write_err_2(ERR_2_File) ;
	}
	return;
}
	  

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	 	// TODO: Place code here.

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TSP_02, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TSP_02));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}  
	return (int) msg.wParam;
}		
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TSP_02));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TSP_02);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_File_fi:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			fi2XYZ();			
			break;
		case IDM_File_XYZ:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			XYZ2fi();			
			break;
		case IDM_File_rZ:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			rZ2fi();			
			break;
		case IDM_Validate:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			Validate_XYZ2fi();			
			break;
		case IDM_File_err:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			err_sum();			
			break;
		case IDM_File_List:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			 write_List_fi(List_FILE);			
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		{
			
			return (INT_PTR)TRUE;
		}

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
