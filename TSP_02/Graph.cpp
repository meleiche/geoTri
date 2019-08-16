// Graph.cpp

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

using namespace std;

Graph::Graph(void)
{
}

Graph::~Graph(void)
{
}

void Graph::init()
{
	ID              = 0;         
	start_node      = 0;         
	end_node        = 0;         
	cost_incident   = 0.0;         
	cost_outgoing   = 0.0;         
	cost_travel     = 0.0;         
	from_node       = 0;         
	to_node         = 0;         
	sort            = 0; 
	sort_in         = 0;
    sort_out        = 0;
	return;
}

//******************************************************
// Write the Graph to external file
//******************************************************
void Graph::write(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode

	fn.setf(ios::right);
	fn.width(10);	
	fn << ID  ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);	
	fn << sort_in  ;
	
	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << cost_incident ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << from_node ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << start_node ;
	
	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << end_node ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << to_node ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << cost_outgoing ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << sort_out << '\n';

	fn.close();
	return;
};

