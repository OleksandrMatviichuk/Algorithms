#include<string>
#include<iostream>

using namespace std;

#include"needleman_wunsch.h"
#include"table/table.h"
int main()
{
	//memory alloc block
	Table *tab =new Table();
	Needleman_Wunsch * alg=new Needleman_Wunsch();
	//end memory depended block
//********************	input block
	string seq_a;
	string seq_b; 
	cout<<"input first sequences: ";
	cin>>seq_a;
	cout<<"input second sequences: ";
	cin>>seq_b;
	int pen =6;
	cout<<"input gap penalty: ";
	cin>>pen;
//******************* end input block

	//calculate block
	alg->set_table(tab);
	alg->set_seq_A(seq_a);
	alg->set_seq_B(seq_b);
	alg->set_penalty(pen);
	alg->calculate();
	//end calculate block


//**********************output block
	cout<<"alingment first sequences : "<<alg->get_r_seq_A()<<endl;
	cout<<"alingment second sequences: "<<alg->get_r_seq_B()<<endl;
	cout<<"alingment weight: "<<alg->get_penalty_weight()<<endl;
//**********************end output block

	delete tab;
	delete alg;
	
	return 0;
}
