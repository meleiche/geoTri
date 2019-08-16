// Counter.h
#pragma once
class Counter
{
public:
	int Nodes;	 	

public:
	Counter(void);
	~Counter(void);
	void init();
	void write(char ff[20]);
	void node_header(char ff[20]);	  	
};

