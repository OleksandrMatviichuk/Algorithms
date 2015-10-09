#include<string>
#include<algorithm>
using namespace std;

#include"levenshtein_distance.h"

int levenshtein_distance(std::string seq_A, std::string seq_B)
{
	int weight=0;
	//create depend memory
	int size_a=seq_A.length()+1;
	int size_b=seq_B.length()+1;
	int **matrix=new int*[size_a];
	for(int i=0;i<size_a;i++)
		matrix[i]=new int[size_b];
	//end depend memory block	
//*******************algorithm
	for(int i=0;i<size_a;i++)
		matrix[i][0]=i;
	for(int j=0;j<size_b;j++)
		matrix[0][j]=j;
	int cost=2;
	for(int i=1;i<size_a;i++)
		for(int j=1;j<size_b;j++)
		{
			if(seq_A[i-1]==seq_B[j-1])
				cost=0;
			else 
				cost=1;
			matrix[i][j]=min(matrix[i-1][j]+1,min(matrix[i][j-1]+1,matrix[i-1][j-1]+cost));
		}

	weight=matrix[size_a-1][size_b-1];
//******************end algorithm
	//free memory block
	for(int i=0;i<size_a;i++)
		delete [] matrix[i];
	delete [] matrix;
	//end free memory block
	return weight;
}
