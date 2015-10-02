#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
#include "needleman_wunsch.h"

Needleman_Wunsch::Needleman_Wunsch():F(NULL),
				     size_a(0),
				     size_b(0),
				     gap_penalty(6),
				     penalty_weight(0),
				     table(NULL)
{
	seq_A="";
	seq_B="";
	r_seq_A="";
	r_seq_B="";
}

Needleman_Wunsch::~Needleman_Wunsch()
{
	if(F!=NULL)
	{
		for(int i=0;i<size_a;i++)
			delete [] F[i];
		delete [] F;
	}
}

void Needleman_Wunsch::set_seq_A(string& seq)
{
	seq_A=seq;
}

void Needleman_Wunsch::set_seq_B(string& seq)
{
	seq_B=seq;
}

void Needleman_Wunsch::set_penalty(int pen)
{
	gap_penalty=pen;
}
void Needleman_Wunsch::set_table(Table *tab)
{
	table=tab;
}

string Needleman_Wunsch::get_r_seq_A()const
{
	return r_seq_A;
}

string Needleman_Wunsch::get_r_seq_B()const
{
	return r_seq_B;
}
int Needleman_Wunsch::get_penalty_weight()const
{
	return penalty_weight;
}

void Needleman_Wunsch::calculate()
{
	//clean old memory
	if(F!=NULL)
	{
		for(int i=0;i<size_a;i++)
			delete [] F[i];
		delete [] F;
	}
	//save currend size depend memory
	size_a=seq_A.length()+1;
	size_b=seq_B.length()+1;
	cout<<"size a "<<size_a<<endl;
	cout<<"size b "<<size_b<<endl;
	F=new int*[size_a];
	for(int i=0;i<size_a;i++)
		F[i]=new int[size_b];
//******algorithm realizations
	//matrix calculate
	for(int i=0;i<size_a;i++)
		F[i][0]=i*gap_penalty*(-1);
	for(int i=0;i<size_b;i++)
		F[0][i]=i*gap_penalty*(-1);
	for(int i=1;i<size_a;i++)
		for(int j=1;j<size_b;j++)
		{
			int match=F[i-1][j-1]+table->get_distance(seq_A[i-1],seq_B[j-1]);
			int del=F[i-1][j]-gap_penalty;
			int incert=F[i][j-1]-gap_penalty;
			F[i][j]=max(max(match,del),incert);
		}
	for(int i=0;i<size_a;i++)
	{
		for(int j=0;j<size_b;j++)
			cout<<F[i][j]<<"   ";
		cout<<endl;
	}
	//end matrix calculate
	r_seq_A="";
	r_seq_B="";
	penalty_weight=0;
	int i=size_a-1;
	int j=size_b-1;	
	//build alingment
	while(i>0 && j>0)
	{
		int score=F[i][j];
		int score_diag=F[i-1][j-1];
		int score_up=F[i][j-1];
		int score_left=F[i-1][j];
		if(score==(score_diag+table->get_distance(seq_A[i-1],seq_B[j-1])))
		{
			r_seq_A=seq_A[i-1]+r_seq_A;
			r_seq_B=seq_B[j-1]+r_seq_B;	
			penalty_weight=penalty_weight+table->get_distance(seq_A[i-1],seq_B[j-1]);
			i--;
			j--;
		} else if(score==(score_left-gap_penalty))
		{
			r_seq_A+=seq_A[i-1];
			r_seq_B+='-';
			penalty_weight=penalty_weight+gap_penalty;
			i--;
		}else
		{
			r_seq_A='-'+r_seq_A;
			r_seq_B=seq_B[j-1]+r_seq_B;
			penalty_weight=penalty_weight+gap_penalty;
			j--;
		}
	}
	while(i>0)
	{
		r_seq_A=seq_A[i-1]+r_seq_A;
		r_seq_B='-'+r_seq_B;
		i--;
	}
	while(j>0)
	{
		r_seq_A='-'+r_seq_A;
		r_seq_B=seq_B[j-1]+r_seq_B;
		j--;	
	}
	

	//end build alingment
//******end algorithm realizations

}

