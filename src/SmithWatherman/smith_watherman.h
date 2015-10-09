#ifndef Smith_Watherman_h
#define Smith_Watherman_h

#include<string>
using namespace std;

#include"table/table.h"

class Smith_Watherman
{
public:
	Smith_Watherman();
	~Smith_Watherman();
	void calculate();		//start calculate
	void set_seq_A(string& seq);	//set A sequence
	void set_seq_B(string& seq);	//set B sequence
	void set_penalty(int p);	//set penalty on gap
	void set_table(Table*);			
	string get_r_seq_A()const;	//return A alingment sequence
	string get_r_seq_B()const;	//return B alingment sequence
	int get_penalty_weight()const;	//return weight alingment
private:
	string seq_A;		//Input sequence A
	string seq_B;		//Input sequence B
	int **F;		//Matrix compliance
	int size_a;		//Matrix compliance size for A sequence
	int size_b;		//Matrix compliance size for B sequence
	int gap_penalty;	//Gap penalty
	string r_seq_A;		//returned alingment sequence A
	string r_seq_B;		//returned alingment sequence B
	int penalty_weight;	//weight alingment sequences A and
	Table* table;		//table length between nucleotide, not created in this class	
};
	

#endif
