#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
#include "smith_watherman.h"

Smith_Watherman::Smith_Watherman():F(NULL),
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

Smith_Watherman::~Smith_Watherman()
{
	if(F!=NULL)
	{
		for(int i=0;i<size_a;i++)
			delete [] F[i];
		delete [] F;
	}
}

void Smith_Watherman::set_seq_A(string& seq)
{
	seq_A=seq;
}

void Smith_Watherman::set_seq_B(string& seq)
{
	seq_B=seq;
}

void Smith_Watherman::set_penalty(int pen)
{
	gap_penalty=pen;
}
void Smith_Watherman::set_table(Table *tab)
{
	table=tab;
}

string Smith_Watherman::get_r_seq_A()const
{
	return r_seq_A;
}

string Smith_Watherman::get_r_seq_B()const
{
	return r_seq_B;
}
int Smith_Watherman::get_penalty_weight()const
{
    return penalty_weight;
}

void Smith_Watherman::calculate()
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
    F=new int*[size_a];
    for(int i=0;i<size_a;i++)
        F[i]=new int[size_b];
//******algorithm realizations
    //matrix calculate
    for(int i=0;i<size_a;i++)
        F[i][0]=0;
    for(int i=0;i<size_b;i++)
        F[0][i]=0;
    int max_elem_value=0;
    int x_max_elem_value=0;
    int y_max_elem_value=0;
    for(int i=1;i<size_a;i++)
        for(int j=1;j<size_b;j++)
        {
            int match=F[i-1][j-1]+table->get_distance(seq_A[i-1],seq_B[j-1]);
            int del=F[i-1][j]-gap_penalty;
            int incert=F[i][j-1]-gap_penalty;
            F[i][j]=max(max(match,del),max(incert,0));
            if(F[i][j]>=max_elem_value)
            {
                max_elem_value=F[i][j];
                x_max_elem_value=i;
                y_max_elem_value=j;
            }
        }

    //end matrix calculate
    r_seq_A="";
    r_seq_B="";
    penalty_weight=0;
    int i=x_max_elem_value;
    int j=y_max_elem_value;
    while(F[i][j]!=0)
    {
        int score=F[i][j];
        int score_diag=F[i-1][j-1];
        int score_up=F[i][j-1];
        int score_left=F[i-1][j];
        if(score==score_diag+table->get_distance(seq_A[i-1],seq_B[j-1]))
        {
            r_seq_A=seq_A[i-1]+r_seq_A;
            r_seq_B=seq_B[j-1]+r_seq_B;
            penalty_weight=penalty_weight+table->get_distance(seq_A[i-1],seq_B[j-1]);
            i--;
            j--;
        } else if(score==score_left-gap_penalty)
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

    //build alingment
    //end build alingment
//******end algorithm realizations


}

