/*
 *	brief:   �᳡�������� 
 *  note��   null 
 *  author:  brt
 *  date:    2014-06-5
 *  version: release
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 analysis��
     ��n���ʱ�俴��ֱ����n�����䣬�����еĿ�ʼʱ��ͽ�������С���򣬵õ�һ��2n���������顣
     hallNum����ͳ�ƻ᳡�����������飬ͳ������������ص���Ŀ��������ʼʱ�䣬һ�ֻ��ջ
	 ���൱��Ҫ����һ���᳡����hallNum����1���Ƚϵ�ǰ�Ļ᳡ʹ�����Ƿ����������������һ�ֻ��ջ
	 ���൱��һ���᳡���꣬������Ϊ������ã���hallNumber����1��ֱ�������еĻ�����źã�����������
     ��������ֻҪ�õ����ٵĻ᳡������������ʱ������һ����ʼʱ�䣬�Ͱѵ�ǰ�Ļ᳡����1��������Ӧ�Ľ���ʱ�䣬
	 �Ͱѵ�ǰ�Ļ᳡����1��ͬʱ��¼ÿ��ѭ��ʱ���Ļ᳡����ѭ������ʱ�����Ļ᳡������������Ҫ�����ٻ᳡����
	 ����㷨��ʱ�临�Ӷ���Ҫ����������Ӱ�죬���Ӷ�ΪO(N*logN)��
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
