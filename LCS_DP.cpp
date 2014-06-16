#include<iostream>
#define LEN_ARR_A  20
#define LEN_ARR_B  12
using namespace std;

/*
 *  brief     : calculate longest common substring of two string and 
 *              mark  path of getting the longest common substring  
 *	parameter : lenComStr : length of common substring
 *              solutionPath : mark of path of solution
 *
 *  note£º      dunamic programming :caculate longest common substring between X(n)
 *              and Y(m-1),likey to caculate longest common substring between X(n) 
 *              and Y(m-1) or between X(n-1) and Y(m). X(0) and Y(0) are not referenced!
 *
 *
 *	return :    null
 */
template<class Type>
void LCSLength(size_t lenStrA, size_t lenStrB, Type *strA, Type *strB, size_t ** lenComStr, size_t ** solutionPath)
{
	for(size_t i = 0; i < lenStrA; ++i)
		lenComStr[i][0] = 0;
	for(size_t i = 0; i < lenStrB; ++i)
		lenComStr[0][i] = 0;
	for(size_t i = 1; i < lenStrA; ++i)
		for(size_t j = 1; j < lenStrB; ++j){
			if(strA[i] == strB[j]){
				lenComStr[i][j] = lenComStr[i -1][j - 1] + 1; 
				//global solution depends on local solution
				solutionPath[i][j] = 1;               
				//mark  path of getting the longest common substring 
			}
			else if(lenComStr[i - 1][j] >= lenComStr[i][j - 1]){
				lenComStr[i][j] = lenComStr[i - 1][j];  
				//global solution depends on local solution
				solutionPath[i][j] = 2;
			}else{
				lenComStr[i][j] = lenComStr[i][j - 1];  
				//global solution depends on local solution
				solutionPath[i][j] = 3;
			}
		}
}
/*
 *  brief     : output longest common substring of two string  
 *              
 *	parameter : i is beginning index of char array
 *              j is end index of char array
 *              solutionPath : mark of path of solution
 *
 *  note£º      value of solutionPath[i][j] has 3 states  
 *
 *	return :    null
 */
 template<class Type>
void LCS(size_t i, size_t j, Type * strA, size_t ** solutionPath)
{
	if(i == -1 || j == -1)	return;
	if(solutionPath[i][j] == 1){
		LCS(i - 1, j - 1, strA, solutionPath); 
		cout << strA[i];
	}else if(solutionPath[i][j] == 2)
			LCS(i - 1, j, strA, solutionPath);
	else{
			LCS(i, j - 1, strA, solutionPath);
	}
}

int main()
{
	char strA[LEN_ARR_A] = { '0','b', 'c', 'e', 'f', 's', 'j', 'f', 'u', 'i', 'j', 'k', 'y', 'h', 'n', 't', 'r', 'd', 'e', 'm'};
	char strB[LEN_ARR_B] = { '0', 'e', 'j', 'u', 'k', 'y', 'n', 'r', 'd', 'e', 'f', 's'};

	size_t ** lenComStr = new size_t*[LEN_ARR_A];
	size_t ** solutionPath = new size_t*[LEN_ARR_A];
	for(size_t i = 0; i < LEN_ARR_A; ++i)	{
		lenComStr[i] = new size_t[LEN_ARR_B];
		solutionPath[i] = new size_t[LEN_ARR_B];
	}
	LCSLength(LEN_ARR_A, LEN_ARR_B, strA, strB, lenComStr, solutionPath);
	LCS(LEN_ARR_A - 1, LEN_ARR_B - 1, strA, solutionPath);
	return 0;
}





