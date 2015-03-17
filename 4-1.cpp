/*
 *	brief:   会场安排问题 
 *  note：   null 
 *  author:  brt
 *  date:    2014-06-5
 *  version: release
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 analysis：
     把n个活动时间看做直线上n个区间，把所有的开始时间和结束按大小排序，得到一个2n的有序数组。
     hallNum用于统计会场数，遍历数组，统计区间的最大的重叠数目。遇到开始时间，一种活动进栈
	 （相当于要安排一个会场），hallNum数加1，比较当前的会场使用数是否是最大。遇到结束，一种活动出栈
	 （相当于一个会场用完，可以作为其他活动用），hallNumber数减1，直到把所有的活动都安排好，结束遍历。
     由于我们只要得到最少的会场数，遍历数组时，遇到一个开始时间，就把当前的会场数加1，遇到对应的结束时间，
	 就把当前的会场数减1，同时记录每次循环时最大的会场数，循环结束时，最大的会场数就是我们需要的最少会场数。
	 这个算法的时间复杂度主要是由排序所影响，复杂度为O(N*logN)。
*/

class activity
{
	public :
    int time;
 	bool start; //the flag start time of activity 
 
    activity(int t, bool f):time(t),start(f){};
    bool operator < (const activity & rhs)const { //template function sort : ascending sort needed 
    	return time < rhs.time;
    }
    bool operator > (const activity & rhs)const { //template function sort : discending sort needed
    	return time > rhs.time;
    }
    bool operator == (const activity & rhs)const {
    	return time == rhs.time;
    }
};


int greedy(vector<activity> x)
{
    int max = 0,hallNum = 0,n = x.size();
    sort(x.begin(),x.end()); //sort template defaut : ascending sort 
    for(int i=0;i<n;i++)
    {
        if(x[i].start)  
            ++hallNum;
        else
            --hallNum;
        if((i == n-1 || x[i] < x[i+1]) && hallNum > max)
            max = hallNum;
    }               
    return max;     
}

int main()
{
    vector<activity> xVec;
    int n, start, finish;
    
    cout << "please input the number of activities :" << '\n' 
	     << "input the begin time and finish time in new line " << endl;
	     
    while(cin>>n,n) //recycle test, end with 0
    {
        for(int i=0;i < n; ++i)
        {
            cin >> start >> finish;
			activity temp1(start, true);
			xVec.push_back(temp1);  
			activity temp2(finish, false);
			xVec.push_back(temp2);
        }
        cout << "least sites number is : " << greedy(xVec) << endl;
        xVec.clear();
    }
    return 0;
}
