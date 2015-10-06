#include<string>

#include"hamming_distance.h"
int hamming_distance(std::string seq_A, std::string seq_B)
{
	int weight=0;
	if(seq_A.length()!=seq_B.length())
		{
			return -1;
		}
		weight=0;
		for(std::string::iterator i=seq_A.begin(),j=seq_B.begin();i!=seq_A.end();i++, j++)
		if(*i!=*j)
			weight++;
		return weight;
}
