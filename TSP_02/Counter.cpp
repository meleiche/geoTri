// Counter.cpp
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#include "Counter.h"

Counter::Counter(void)
{
}

Counter::~Counter(void)
{
}

void Counter::init()
{
	Nodes     = 0;
	}

void Counter::write(char ff[20])
{
	ofstream fn;	
	fn.open(ff,ios::app); // open file in append mode
	//fn << "Writing Counter to a file:\n";
	fn << "Number of input points = "        << Nodes           << '\n';
	fn.close(); 
};


void Counter::node_header(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << "***********************************************************\n";
	fn << "              N O D E    A R R A Y     \n";
	fn << "***********************************************************\n";
	fn <<  "       ID " << "      fi (lat)" << "    lamda (long) " << "       h " ;
	fn << "          Xp " << "        Yp" << "    Zp" << "       Graph"  <<'\n';
	fn << "    ========== " << " ========== " <<  " ========== " << "    ========== ";	
	fn << "    ========== " << " ========== " <<  " ========== " << '\n';	
	fn.close();
	return;
}

