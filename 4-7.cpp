/*
 *	brief:   多处服务最优解（多处生产最优问题） 
 *  note：   null 
 *  author:  brt
 *  date:    2014-06-12
 *  version: release
 */
 
#include<iostream>
#include <vector>
#include<algorithm> 
using namespace std;

double greedy(vector<int>x,int serverNum)
{
 	   vector<int>serveTimeSum(serverNum+1,0);
 	   vector<int>allGuessWaitSum(serverNum+1,0);
 	   int guessNum=x.size();
 	   sort(x.begin(),x.end());
 	   int i=0,j=0;
 	   while(i<guessNum){
		   	 serveTimeSum[j]+=x[i];              //serveTimeSum[num] : the sum time of all serve of window num  
		 	 allGuessWaitSum[j]+=serveTimeSum[j];//allGuestWaitSum[num] :the sum time of all waiting of window num
		 	 i++;
		 	 j++;
		 	 if(j==serverNum)j=0;
        }
		double waitSum = 0;
		for(i = 0; i < serverNum; i++) 
			  waitSum += allGuessWaitSum[i];
		waitSum /= guessNum;
		return waitSum;
}
int  main()
{
	int guessNum;
	int serverNum;
	int i, temp, average;
	vector<int>serveTimeVec;
	
	cin>>guessNum;
	cout<<"please input the num of the server:"<<endl;
	cin>>serverNum;
	cout<<"please input the need service time of each customer:"<<endl;
	
	for(i = 1; i <= guessNum; ++i){
		cout << "No."<<i<<endl;
		cin >> temp;
		serveTimeVec.push_back(temp);
	}
	
	average = greedy(serveTimeVec, serverNum);
	cout << "the least average waiting time is:" << average << endl;		
	return 0;
}

