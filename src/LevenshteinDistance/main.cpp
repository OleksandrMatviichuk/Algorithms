#include<iostream>
#include<string>
using namespace std;


#include"levenshtein_distance.h"

int main()
{
	cout<<"first sequences : ";
	string seq_A;
	cin>>seq_A;
	cout<<"second sequences: ";
	string seq_B;
	cin>>seq_B;
	int len=levenshtein_distance(seq_A, seq_B);
	cout<<"Levenshtein distance between sequences A and B : "<<len<<endl;
	return 0;
}
