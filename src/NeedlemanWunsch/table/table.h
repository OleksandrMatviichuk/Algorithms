#ifndef TABLE_H
#define	TABLE_H

#include<string>
using std::string;

class Table
{
public:
	Table();
	~Table();
	int get_distance(char a, char b);	//return distance between a and b
	void inp_data(int **data, int size);//temp function created for test in this level
	void inp_lett(string&);//temp function
	void open();//temp function loaded Blosssm 40 table
protected:
	string letters;		//save al chars in matrix
	int **matrix;		//matrix distances
	int size;		//size matrix

	int get_index(char a);		//return index letter in matrix distances
	int get_distance(int a, int b);		//search distance in matrix for returned letter

};

#endif
