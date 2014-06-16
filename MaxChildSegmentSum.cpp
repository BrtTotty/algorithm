#include<iostream>

using namespace std; 

/*
 *  brief : caculate  max sum of continuous child segment of array
 *
 *  parameter :  len is length of array;
 *               arr is array of needed calculation 				
 *                
 *  return :     max sum value of continuous child segment of array
 *
 *	date :       2014/04/09
 *
 */
template<class Type> 
Type maxContinuousChildSegSum(const size_t &len, Type * arr, int &begin, int& end)
{
	
	Type preSegSum = 0;
	Type max = 0;
	for(size_t i = 0; i < len; ++i){
		if(preSegSum > 0){          //note : ditinguish between greater than 0 and greater equal than 0    
			preSegSum += arr[i];    //need previuos child segment sum to get MAX
		}
		else{
			begin = i;    
			preSegSum = arr[i];     //ignoring previuos child segment sum to get MAX
		}
		if(preSegSum > max){        //note : ditinguish between greater than 0 and greater equal than 0    
			max = preSegSum;        //replace max with preChildSegmentSum 
			end = i;
		}
	}
	return max;
} 

int main()
{
	int num, begin, end;
	cout << "���������ֶεĸ�����" << endl;
	cin >> num;
	int *digits = new int[num]; 
	cout << "����������֣� " << endl; 
	for(int i = 0; i < num; ++i){
		cin >> digits[i];
	} 
	cout << "���������Ӷκ� : " << maxContinuousChildSegSum(num, digits, begin, end) <<  endl;
	cout << "���±� " << begin << " �� " << end << endl; 
	return 0;
}
