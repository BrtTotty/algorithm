/*
 * breif   : Fibonacci number sequence
 * author  : brt
 * version : 2014/05/18
 * note    : null
 */ 
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

template <class Type>
Type fibonacciDynamic(Type n)
{
	Type *arr = new Type[int(n)];//size in array new must have integral type
	for(int i = 0; i < n; ++i){
		if(i <= 1)
			 arr[i] = 1;
	    else{
	    	arr[i] = arr[i - 1] + arr[i - 2]; 
	    }
	}
	return arr[int(n - 1)];//size in array new must have integral type
}

template <class Type>
Type fibonacciDivision(Type n)
{
	if(n <= 2)
		 return 1;
    else
    	return fibonacciDivision(n-1)+ fibonacciDivision(n-2);
}
int main()
{
	time_t begin, end;
	double n, result;
	cout << "请输入你要求得的第几个Fibonacci数列的数(为了不要等待太久建议小于50 ：" << endl;
	cin >> n;
	begin = clock();
	result = fibonacciDynamic(n);
	end = clock();
	cout << "动归方法 Fibonacci数列的第" <<  int(n) << "个数是：" << std :: fixed << setprecision(0) << result << ", 耗时："  << end - begin << "ms" << endl;  
	
	begin = clock();
	result = fibonacciDivision(n);
	end = clock();	
	cout << "递归方法 Fibonacci数列的第" <<  int(n) << "个数是：" << std :: fixed << setprecision(0) << result << ", 耗时：" << end -begin << "ms" << endl;  
	return 0;
}
