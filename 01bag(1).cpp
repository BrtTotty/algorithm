#include <iostream>
#include <algorithm>
#define NUM 10
#define CAPACITY 20

using namespace std;

template <class Type>
void package01(Type (&val)[NUM+1], Type (&weight)[NUM+1], Type capacity,Type num, Type (&maxVal)[NUM+1][CAPACITY+1])
{
	int currentMax = min(weight[num] - 1, capacity);
	
	//if current capacity of bag lower than min, initial the value as 0
	for(size_t i = 0; i <= currentMax; ++i)	
		maxVal[num][i] = 0; 
	
	//if current capacity of bag lower than capacity of bag and higher than current weight of object, initialize the value as the value of current object      
	for(size_t i = weight[num]; i <= capacity; ++i)	
		maxVal[num][i] = val[i]; 
	
	for(int i = num - 1; i > 1; --i){
		currentMax = min(weight[i] - 1, capacity);
		for(int curCap = 0; curCap < currentMax; ++curCap)
			maxVal[i][curCap] = maxVal[i + 1][curCap];
		for(int curCap = weight[i]; curCap < capacity; ++curCap)
			maxVal[i][curCap] = max(maxVal[i + 1][curCap], maxVal[i + 1][curCap - weight[i]] + val[i]); 
	}	
	maxVal[1][capacity] = maxVal[2][capacity];
	
	if(capacity >= weight[1])
		maxVal[1][capacity] = max(maxVal[1][capacity], maxVal[2][capacity - weight[1]] + val[1]);
}

template <class Type>
void traceBack(Type (&maxVal)[NUM+1][CAPACITY+1], Type (& weight)[NUM+1], Type capacity, Type num, Type (& x)[NUM+1])
{	
	for(size_t i = 1; i < num; ++i){
		if(maxVal[i][capacity] == maxVal[i + 1][capacity])
			x[i] = 0;
		else
			x[i] = 1;
			capacity -= weight[i]; 
	} 
	x[num] = (maxVal[num][capacity]) ? 1 : 0;
}

int main()
{
	int num =NUM;
	int capacity = CAPACITY; 
	int weight[NUM+1] = {0,3,4,9,8,7,3,4,1,3,8};
	int values[NUM+1] = {0,90,30,40,70,80,90,20,30,80,90};
	int path[NUM+1]   = {0,0,0,0,0,0,0,0,0,0,0}; 
	int maxVal[NUM+1][CAPACITY+1];
	
	for(size_t i = 0; i <= NUM; ++i)
		for(size_t j = 0; j <= NUM; ++j)
			maxVal[i][j] = 0;
	package01(values, weight, capacity, num, maxVal);
	traceBack(maxVal, weight, capacity, num, path);
	cout << "follow goods will be select: " << endl;
	for(size_t i = 0; i <= NUM; ++i){
		if(path[i] != 0)
			cout << i << " "; 
	}
	cout << endl;
	return 0;
}	 
